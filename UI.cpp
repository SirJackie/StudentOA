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
    // ��Windowsƽ̨�£�ʹ��Windows API����COORD��SetConsoleCursorPosition
    HANDLE hConsoleOutput;
    COORD dwCursorPosition;
    dwCursorPosition.X = x;
    dwCursorPosition.Y = y;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
#elif defined(__linux__)
    // ��Linuxƽ̨�£�ʹ��ANSIת������
    printf("\033[%d;%dH", y, x);
    fflush(stdout);
#endif
}

void UI_DrawRect(int x0, int y0, int width, int height) {

    int x1 = x0 + width - 1;
    int y1 = y0 + height - 1;

    // �����ϱ�
    for (int i = x0 + 1; i <= x1 - 1; i++) {
        UI_GotoXY(i, y0);
        printf("%c", 205); // 205��ˮƽ�����ַ���ASCII��
    }
    // �����±�
    for (int i = x0 + 1; i <= x1 - 1; i++) {
        UI_GotoXY(i, y1);
        printf("%c", 205);
    }
    // �������
    for (int i = y0 + 1; i <= y1 - 1; i++) {
        UI_GotoXY(x0, i);
        printf("%c", 186); // 186�Ǵ�ֱ�����ַ���ASCII��
    }
    // �����ұ�
    for (int i = y0 + 1; i <= y1 - 1; i++) {
        UI_GotoXY(x1, i);
        printf("%c", 186);
    }

    // �������Ͻ�
    UI_GotoXY(x0, y0);
    printf("%c", 201); // 201�����Ͻǹս��ַ���ASCII��
    // �������Ͻ�
    UI_GotoXY(x1, y0);
    printf("%c", 187); // 187�����Ͻǹս��ַ���ASCII��
    // �������½�
    UI_GotoXY(x0, y1);
    printf("%c", 200); // 200�����½ǹս��ַ���ASCII��
    // �������½�
    UI_GotoXY(x1, y1);
    printf("%c", 188); // 188�����½ǹս��ַ���ASCII��
}

void UI_DrawDiv(Div& div) {
    UI_DrawRect(div.x, div.y, div.width, div.height);
}
