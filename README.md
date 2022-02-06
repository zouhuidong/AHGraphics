# AHGraphics

A tool in order to let EasyX lib drawing on all of windows. 用于让 EasyX lib 在所有窗口上绘图的库

---

使用 AHGraphics ，首先include它，然后调用InitDrawing来设置目标绘图HWND或者HDC：

```
#include "AHGraphics.h"
#include <conio.h>
 
int main()
{
    InitDrawing(GetConsoleWindow()/* 得到cmd句柄 */);
     
    _getch();
 
    EndDrawing();
 
    return 0;
}
```

以上的代码设置了绘图目标窗口为cmd。


设置了目标绘图窗口，就可以直接使用easyx函数绘图了，例子：

```
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
```

效果图片请看samples中各个例子的screenshot文件


## 注意事项

*设置了绘图目标窗口后，*

*不要使用MouseHit和GetMouseMsg等函数，因为什么也得不到，请使用GetMousePoint来得到鼠标位置。*

*不要直接SetWorkingImage(NULL)，因为设置了目标绘图窗口后，主画布(IMAGE对象)就不再是NULL可以表示的了，请将其改成：*
`SetWorkingImage(GetMainImage()/* 得到主画布的地址 */);`


## 更新日志

**Ver2.0**

修复了 `FlushDrawingToWnd` 函数的 Bug。


