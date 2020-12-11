///////////////////////////////////////////////////////
//
//	AHGraphics.cpp (All HWnd Graphics with EasyX)
//	by huidong <mailkey@yeah.net>
//
//	�������԰����㽫EasyX�Ļ�ͼ���ݸ��Ƶ��κδ�����
//
//	����ʱ�䣺2020.7.8
//	����޸ģ�2020.12.11
//
//

#include "AHGraphics.h"

//////////////////// ȫ�ֱ��� ////////////////////

// �ڲ�����
// ��ǰ��ͼ����HWND
HWND m_wnd = NULL;

// �ڲ�����
// ��ǰ��ͼHDC
HDC m_hdc = NULL;

// �ڲ�����
// ��ǰ��ͼ��IMAGE����
IMAGE m_img;

// �ڲ�����
// �Զ������ͼ���ݵ��̵߳ľ��
HANDLE m_hThAutoFlush = NULL;

// �ڲ�����
// ���Զ������ͼ���ݵ��̵߳�ͨѶ��־
// ָ���Ƿ��Զ���ͼ
bool m_isAutoFlush = false;


//////////////////// �������� ////////////////////

//////////////////// ��������

// �õ��������ڴ��ڵ�λ��
POINT GetMousePoint()
{
	POINT point;    // �������λ��
	GetCursorPos(&point);            // ��ȡ���ָ��λ�ã���Ļ���꣩
	ScreenToClient(GetWorkingHWnd(), &point);    // �����ָ��λ��ת��Ϊ��������
	return point;
}

// �õ�����λ�á�����
RECT GetWindowRect(HWND wnd)
{
	RECT rcClient;
	GetClientRect(wnd, &rcClient);
	return rcClient;
}

// �õ����ڴ�С
POINT GetWindowSize(HWND wnd)
{
	POINT size;
	RECT rct;

	rct = GetWindowRect(wnd);
	size = { rct.right - rct.left,rct.bottom - rct.top };

	return size;
}

//////////////////// ���ò����ຯ��

// ���õ�ǰ��ͼĿ�괰��
// ����ֱ�ӵ��ô˺�������ʹ��InitDrawing
void SetWorkingHWnd(HWND wnd)
{
	m_wnd = wnd;
	m_hdc = GetDC(m_wnd);
}

// �õ���ǰ��ͼĿ�괰��
HWND GetWorkingHWnd()
{
	return m_wnd;
}

// ���õ�ǰ��ͼĿ��HDC
// ����ֱ�ӵ��ô˺�������ʹ��InitDrawing
void SetWorkingHDC(HDC hdc)
{
	m_hdc = hdc;
	SetWorkingHWnd(WindowFromDC(hdc));
}

// �õ���ǰ��ͼĿ��HDC
HDC GetWorkingHDC()
{
	return m_hdc;
}

// �õ�������
IMAGE* GetMainImage()
{
	return &m_img;
}


//////////////////// ��ͼ����

// ��������easyx�е�������ʾ��Ŀ�괰����
// img Ҫ��ʾ�Ļ�ͼ����Ĭ��Ϊ������
// wnd Ŀ���ͼ���ڣ�Ĭ��Ϊ������
void FlushDrawingToWnd(IMAGE* img, HWND* wnd)
{
	HDC me_hdc;
	HDC img_hdc;

	if (img == NULL)
	{
		img_hdc = GetImageHDC(GetMainImage());
	}
	else
	{
		img_hdc = GetImageHDC(img);
	}

	if (wnd == NULL)
	{
		me_hdc = GetWorkingHDC();
	}
	else
	{
		me_hdc = GetDC(*wnd);
	}

	POINT wnd_size = GetWindowSize(GetWorkingHWnd());

	BitBlt(
		me_hdc,			// Ŀ���ͼ�豸 
		0,				// Ŀ���������Ͻ�x���� 
		0,				// Ŀ���������Ͻ�y���� 
		wnd_size.x,		// Ŀ�������� 
		wnd_size.y,		// Ŀ������߶� 
		img_hdc,		// Դ��ͼ�豸 
		0,				// Դ�������Ͻ�x���� 
		0,				// Դ�������Ͻ�y���� 
		SRCCOPY			// �����롣����SRCCOPY�����ƣ�
	);
}


// һֱ���»�ͼ���ݣ������Եģ�
//
// delay ÿ�θ��µ���ʱ��ms��
// flag ���������ı�־��Ϊfalseʱֹͣ
void KeepFlushDrawing(int delay = 60, bool* flag = &m_isAutoFlush)
{
	while (true)
	{
		if (*flag == false)
		{
			return;
		}

		FlushDrawingToWnd();
		Sleep(delay);
	}
}



//////////////////// ��ͼ������ʼ���ຯ��


// ʹ��IMAGE������С��ӦĿ���ͼ���ڴ�С
void MainImageFitWindow()
{
	POINT wnd_size = GetWindowSize(GetWorkingHWnd());
	GetMainImage()->Resize(wnd_size.x, wnd_size.y);
}


// ��ĳһ���ڻ�ͼǰ�ĳ�ʼ��
// wnd ���ھ��
void InitDrawing(HWND wnd)
{
	SetWorkingHWnd(wnd);
	SetWorkingImage(GetMainImage());

	MainImageFitWindow();
}

// ��ĳһHDC��ͼǰ�ĳ�ʼ��
// hdc DC���
void InitDrawing(HDC hdc)
{
	SetWorkingHDC(hdc);
	SetWorkingImage(GetMainImage());

	MainImageFitWindow();
}

// ���� / �ر� �Զ������ͼ���ݣ������ڻ�ͼ���ֶ�FlushDrawingToWnd��
// ע�⣺���Ǳ�Ҫ������Ҫ�����Զ������ͼ����
//
// isAuto �رջ��ǿ����Զ������Ĭ��Ϊtrue
void AutoFlushDrawing(bool isAuto)
{
	if (isAuto)
	{
		m_isAutoFlush = true;
		m_hThAutoFlush = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)KeepFlushDrawing/* ������ */, 0, 0, NULL);
	}
	else
	{
		m_isAutoFlush = false;

		// �ر��Զ������ͼ���ݵ��߳�
		if (m_hThAutoFlush != NULL)
		{
			CloseHandle(m_hThAutoFlush);
		}
	}

}

// ������ͼ
// ����һЩ������ͼ�ĺ�������
void EndDrawing()
{
	// �ر��Զ������ͼ����
	AutoFlushDrawing(false);

	// ��������HWNDΪNULL,��Ϊ����HDC��ֱ�ӽ�HWND���
	SetWorkingHDC(NULL);
}
