#include "AHGraphics.h"
#include <conio.h>

int main()
{
	InitDrawing(GetConsoleWindow()/* 得到cmd句柄 */);

	setlinestyle(PS_SOLID, 5);

	setlinecolor(BLUE);
	line(0, 0, 200, 200);

	setlinecolor(RED);
	line(30, 30, 200, 30);

	// 绘图后要将绘图内容输出 
	FlushDrawingToWnd();

	_getch();

	EndDrawing();

	return 0;
}


