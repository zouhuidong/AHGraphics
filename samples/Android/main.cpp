#include "AHGraphics.h"
#include <conio.h>

int main()
{
	system("mode con cols=100 lines=40");

	InitDrawing(GetConsoleWindow());

	// Android 小人绘制代码摘自 https://codebus.cn/yangw/a/android-robot?tdsourcetag=s_pctim_aiomsg

	double PI = 3.1415926;

	// 设置原点 (0, 0) 为屏幕中央（Y轴默认向下为正）
	setorigin(400, 300);

	// 使用藏青色填充背景
	setbkcolor(0x7c5731);
	cleardevice();

	// 设置绘图样式
	setlinecolor(WHITE);                            // 设置线条颜色为白色
	setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 10);    // 设置线条样式为宽度 10 的实线，端点是平的
	setfillcolor(0x24c097);                            // 设置填充颜色为绿色

	// 画身体
	fillroundrect(-75, -111, 75, 39, 36, 36);

	// 画头
	fillpie(-75, -166, 75, -30, 0, PI);                // 脸
	circle(-31, -131, 3);                            // 右眼
	circle(31, -131, 3);                            // 左眼

	// 画天线
	fillellipse(-52, -181, -38, -167);                // 右天线
	line(-50, -169, -41, -156);
	line(-38, -177, -28, -162);
	fillellipse(52, -181, 38, -167);                // 左天线
	line(50, -169, 41, -156);
	line(38, -177, 28, -162);
	// 用绿色擦掉天线部分多余的线
	setlinecolor(0x24c097);                            // 设置线条颜色为绿色
	setlinestyle(PS_SOLID | PS_ENDCAP_ROUND, 5);    // 设置线条样式为宽度 5 的实线，端点为圆形
	line(-44, -174, -23, -142);                        // 画右天线内部的绿线
	line(44, -174, 23, -142);                        // 画左天线内部的绿线
	setlinecolor(WHITE);                            // 恢复线条颜色为白色
	setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 10);    // 恢复线条样式为宽度 10 的实线，端点是平的

	// 画胳膊
	fillroundrect(-117, -99, -75, 7, 42, 42);        // 右胳膊
	fillroundrect(117, -99, 75, 7, 42, 42);        // 左胳膊

	// 画腿
	fillpie(-50, 49, -8, 91, PI, PI * 2);            // 右腿
	line(-50, 40, -50, 70);
	line(-8, 40, -8, 70);
	solidroundrect(-45, 0, -13, 86, 32, 32);
	fillpie(50, 49, 8, 91, PI, PI * 2);            // 左腿
	line(50, 40, 50, 70);
	line(8, 40, 8, 70);
	solidroundrect(45, 0, 13, 86, 32, 32);

	// 画字母 A
	arc(-185, 132, -144, 173, PI / 2, PI * 3 / 2);
	line(-165, 132, -135, 132);
	line(-165, 173, -154, 173);
	line(-140, 127, -140, 178);

	// 画字母 N
	arc(-118, 131, -78, 171, 0, PI);
	line(-118, 151, -118, 178);
	line(-78, 151, -78, 178);

	// 画字母 D
	arc(-57, 132, -16, 173, PI * 3 / 2, PI / 2);
	line(-60, 132, -37, 132);
	line(-60, 173, -37, 173);

	// 画字母 R
	arc(14, 132, 40, 158, PI * 3 / 2, PI / 2);
	arc(-2, 158, 38, 198, 0, PI / 2);
	line(1, 132, 27, 132);
	line(1, 158, 27, 158);

	// 画字母 O
	circle(81, 152, 21);

	// 画字母 I
	line(124, 127, 124, 178);

	// 画字母 D
	arc(144, 132, 185, 173, PI * 3 / 2, PI / 2);
	line(141, 132, 164, 132);
	line(141, 173, 164, 173);

	setorigin(0, 0);

	FlushDrawingToWnd();

	_getch();

	EndDrawing();

	return 0;
}