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

void UI_PrintfWordWrap(int x, int y, const char* str, int maxLen) {
    int len = strlen(str);
    int lineCount = 0;

    for (int i = 0; i < len; i += maxLen) {
        UI_GotoXY(x, y + lineCount);
        if (i + maxLen < len) {
            printf("%.*s", maxLen, str + i);
            lineCount += 1;
        }
        else {
            printf("%s\n", str + i);
            lineCount += 1;
        }
    }
}

void UI_DrawDiv(Div& div) {
    int borderX = div.x + div.marginX;
    int borderY = div.y + div.marginY;
    int borderWidth = div.width - 2 * div.marginX;
    int borderHeight = div.height - 2 * div.marginY;
    if (div.border) UI_DrawRect(borderX, borderY, borderWidth, borderHeight);
    
    int textX = borderX + 1;
    int textY = borderY + 1;
    int textWidth = borderWidth - 2 * 1;    // 1 for BorderWidth
    int textHeight = borderHeight - 2 * 1;  // 1 for BorderHeight
    UI_PrintfWordWrap(textX, textY, div.text, 20);
}
