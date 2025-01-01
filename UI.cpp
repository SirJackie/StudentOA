#include "UI.h"
#include <stdio.h>
#include <conio.h>
#include <Windows.h>

void UI_Init() {
#ifdef _WIN32
    SetConsoleOutputCP(437);
#elif defined(__linux__)
    ;
#endif
}

void UI_GotoXY(int x, int y) {
#ifdef _WIN32
    // 在Windows平台下，使用Windows API函数COORD和SetConsoleCursorPosition
    HANDLE hConsoleOutput;
    COORD dwCursorPosition;
    dwCursorPosition.X = x;
    dwCursorPosition.Y = y;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
#elif defined(__linux__)
    // 在Linux平台下，使用ANSI转义序列
    printf("\033[%d;%dH", y, x);
    fflush(stdout);
#endif
}

void UI_DrawRect(int x0, int y0, int width, int height) {

    int x1 = x0 + width - 1;
    int y1 = y0 + height - 1;

    // 绘制上边
    for (int i = x0 + 1; i <= x1 - 1; i++) {
        UI_GotoXY(i, y0);
        printf("%c", 205); // 205是水平横线字符的ASCII码
    }
    // 绘制下边
    for (int i = x0 + 1; i <= x1 - 1; i++) {
        UI_GotoXY(i, y1);
        printf("%c", 205);
    }
    // 绘制左边
    for (int i = y0 + 1; i <= y1 - 1; i++) {
        UI_GotoXY(x0, i);
        printf("%c", 186); // 186是垂直竖线字符的ASCII码
    }
    // 绘制右边
    for (int i = y0 + 1; i <= y1 - 1; i++) {
        UI_GotoXY(x1, i);
        printf("%c", 186);
    }

    // 绘制左上角
    UI_GotoXY(x0, y0);
    printf("%c", 201); // 201是左上角拐角字符的ASCII码
    // 绘制右上角
    UI_GotoXY(x1, y0);
    printf("%c", 187); // 187是右上角拐角字符的ASCII码
    // 绘制左下角
    UI_GotoXY(x0, y1);
    printf("%c", 200); // 200是左下角拐角字符的ASCII码
    // 绘制右下角
    UI_GotoXY(x1, y1);
    printf("%c", 188); // 188是右下角拐角字符的ASCII码
}

void UI_DrawDiv(Div& div) {
    UI_DrawRect(div.x, div.y, div.width, div.height);
}
