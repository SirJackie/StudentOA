#include "UI.h"
#include <stdio.h>
#include <conio.h>
#include <Windows.h>

void MakeSureOEMCharset() {
#ifdef _WIN32
    SetConsoleOutputCP(437);
#endif
}

// 自定义gotoxy函数，兼容不同平台
void GotoXY(int x, int y) {
    // 在Windows平台下，使用Windows API函数COORD和SetConsoleCursorPosition
#ifdef _WIN32
    HANDLE hConsoleOutput;
    COORD dwCursorPosition;
    dwCursorPosition.X = x;
    dwCursorPosition.Y = y;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
    // 在Linux平台下，使用ANSI转义序列
#elif defined(__linux__)
    printf("\033[%d;%dH", y, x);
    fflush(stdout);
#endif
}

// 绘制矩形边框的函数
void DrawRect(int x0, int y0, int x1, int y1) {
    // 乱码修复，切换到OEM字符集
    MakeSureOEMCharset();

    // Oversize Fix
    x1 -= 1;
    y1 -= 1;

    // 绘制上边
    for (int i = x0; i <= x1; i++) {
        GotoXY(i, y0);
        printf("%c", 205); // 205是水平横线字符的ASCII码
    }
    // 绘制下边
    for (int i = x0; i <= x1; i++) {
        GotoXY(i, y1);
        printf("%c", 205);
    }
    // 绘制左边
    for (int i = y0; i <= y1; i++) {
        GotoXY(x0, i);
        printf("%c", 186); // 186是垂直竖线字符的ASCII码
    }
    // 绘制右边
    for (int i = y0; i <= y1; i++) {
        GotoXY(x1, i);
        printf("%c", 186);
    }
    // 绘制左上角
    GotoXY(x0, y0);
    printf("%c", 201); // 201是左上角拐角字符的ASCII码
    // 绘制右上角
    GotoXY(x1, y0);
    printf("%c", 187); // 187是右上角拐角字符的ASCII码
    // 绘制左下角
    GotoXY(x0, y1);
    printf("%c", 200); // 200是左下角拐角字符的ASCII码
    // 绘制右下角
    GotoXY(x1, y1);
    printf("%c", 188); // 188是右下角拐角字符的ASCII码
}
