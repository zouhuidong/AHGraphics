#include "AHGraphics.h"
#include <conio.h>

int main()
{
	InitDrawing(GetConsoleWindow()/* �õ�cmd��� */);

	setlinestyle(PS_SOLID, 5);

	setlinecolor(BLUE);
	line(0, 0, 200, 200);

	setlinecolor(RED);
	line(30, 30, 200, 30);

	// ��ͼ��Ҫ����ͼ������� 
	FlushDrawingToWnd();

	_getch();

	EndDrawing();

	return 0;
}


