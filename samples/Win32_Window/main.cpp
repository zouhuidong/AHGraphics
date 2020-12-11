#include "AHGraphics.h"

// 保存窗口句柄
HWND wnd;

// 绘图
void Draw()
{
	cleardevice();

	line(0, 0, GetWindowSize(wnd).x, GetWindowSize(wnd).y);

	POINT point = GetMousePoint();
	WCHAR str_point[20] = { 0 };
	wsprintf(str_point, L"%d, %d", point.x, point.y);
	outtextxy(0, 0, str_point);

	circle(getwidth() / 2, getheight() / 2, 10);

	FlushDrawingToWnd();
}

LRESULT __stdcall WindowProcedure(HWND window, unsigned int msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_SIZE:

		// 调整IMAGE对象大小以适应窗口大小
		MainImageFitWindow();

	case WM_PAINT:

		// 重绘
		Draw();

	default:
		return DefWindowProc(window, msg, wp, lp);
	}
}

// 创建win32窗口
HWND CreatWnd(LPCTSTR strTitle = _T("title"), LPCTSTR strClass = _T("WndClass"))
{
	// 窗口类
	WNDCLASSEX wc;

	wc.cbSize = sizeof(WNDCLASSEX);
	/* Win 3.x */
	wc.style = CS_DBLCLKS;
	wc.lpfnWndProc = WindowProcedure;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = GetModuleHandle(0);
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = 0;
	wc.lpszClassName = strClass;
	/* Win 4.0 */
	wc.hIconSm = LoadIcon(0, IDI_APPLICATION);

	if (RegisterClassEx(&wc))
	{
		RECT rect;
		rect.left = 300;
		rect.top = 300;
		rect.right = 640;
		rect.bottom = 480;

		HWND window = CreateWindowEx(0, strClass, strTitle,
			WS_OVERLAPPEDWINDOW, rect.left, rect.top,
			rect.right, rect.bottom, 0, 0, GetModuleHandle(0), 0);

		if (window)
		{
			ShowWindow(window, SW_SHOWDEFAULT);
			return window;
		}
		else
		{
			return NULL;
		}
	}
	else
	{
		return NULL;
	}
}

// 派发消息
void OnMsg()
{
	MSG msg;
	GetMessage(&msg, 0, 0, 0);
	DispatchMessage(&msg);
}

int main()
{
	wnd = CreatWnd(L"My Wnd");

	InitDrawing(wnd);

	setbkcolor(WHITE);
	setlinecolor(BLACK);
	settextcolor(BLACK);

	while (true)
	{
		Draw();
		OnMsg();
	}

	return 0;
}