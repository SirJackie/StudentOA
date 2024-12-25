#include "UI.h"
#include <stdio.h>
#include <conio.h>
#include <Windows.h>

void MakeSureOEMCharset() {
#ifdef _WIN32
    SetConsoleOutputCP(437);
#endif
}

// �Զ���gotoxy���������ݲ�ͬƽ̨
void GotoXY(int x, int y) {
    // ��Windowsƽ̨�£�ʹ��Windows API����COORD��SetConsoleCursorPosition
#ifdef _WIN32
    HANDLE hConsoleOutput;
    COORD dwCursorPosition;
    dwCursorPosition.X = x;
    dwCursorPosition.Y = y;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
    // ��Linuxƽ̨�£�ʹ��ANSIת������
#elif defined(__linux__)
    printf("\033[%d;%dH", y, x);
    fflush(stdout);
#endif
}

// ���ƾ��α߿�ĺ���
void DrawRect(int x0, int y0, int x1, int y1) {
    // �����޸����л���OEM�ַ���
    MakeSureOEMCharset();

    // Oversize Fix
    x1 -= 1;
    y1 -= 1;

    // �����ϱ�
    for (int i = x0; i <= x1; i++) {
        GotoXY(i, y0);
        printf("%c", 205); // 205��ˮƽ�����ַ���ASCII��
    }
    // �����±�
    for (int i = x0; i <= x1; i++) {
        GotoXY(i, y1);
        printf("%c", 205);
    }
    // �������
    for (int i = y0; i <= y1; i++) {
        GotoXY(x0, i);
        printf("%c", 186); // 186�Ǵ�ֱ�����ַ���ASCII��
    }
    // �����ұ�
    for (int i = y0; i <= y1; i++) {
        GotoXY(x1, i);
        printf("%c", 186);
    }
    // �������Ͻ�
    GotoXY(x0, y0);
    printf("%c", 201); // 201�����Ͻǹս��ַ���ASCII��
    // �������Ͻ�
    GotoXY(x1, y0);
    printf("%c", 187); // 187�����Ͻǹս��ַ���ASCII��
    // �������½�
    GotoXY(x0, y1);
    printf("%c", 200); // 200�����½ǹս��ַ���ASCII��
    // �������½�
    GotoXY(x1, y1);
    printf("%c", 188); // 188�����½ǹս��ַ���ASCII��
}
