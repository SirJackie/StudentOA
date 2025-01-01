#include "UI.h"
#include <math.h>
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

void UI_DrawRect(
    int x0, int y0, int width, int height, bool drawX, bool drawY
) {

    int x1 = x0 + width - 1;
    int y1 = y0 + height - 1;

    if (drawX) {
        // Left
        for (int i = y0; i <= y1; i++) {
            UI_GotoXY(x0, i);
            printf("%c", 186);
        }
        // Right
        for (int i = y0; i <= y1; i++) {
            UI_GotoXY(x1, i);
            printf("%c", 186);
        }
    }

    if (drawY) {
        // Up
        for (int i = x0; i <= x1; i++) {
            UI_GotoXY(i, y0);
            printf("%c", 205);
        }
        // Down
        for (int i = x0; i <= x1; i++) {
            UI_GotoXY(i, y1);
            printf("%c", 205);
        }
    }

    if (drawX && drawY) {
        // Top-Left Corner
        UI_GotoXY(x0, y0);
        printf("%c", 201);
        // Top-Right Corner
        UI_GotoXY(x1, y0);
        printf("%c", 187);
        // Bottom-Left Corner
        UI_GotoXY(x0, y1);
        printf("%c", 200);
        // Bottom-Right Corner
        UI_GotoXY(x1, y1);
        printf("%c", 188);
    }
}

void UI_DrawRect_Animated(
    int x0, int y0, int width, int height, bool drawX, bool drawY, float completeness
) {

    int x1 = x0 + width - 1;
    int y1 = y0 + height - 1;

    bool isOdd;
    int C;
    completeness = clampF(0.0f, completeness, 100.0f);
    float ratio = completeness / TOTAL_COMPLETENESS;

    if (drawX) {
        isOdd = height % 2 == 1;
        C = isOdd ? 1 : 0;
        int centerY = (y0 + y1) / 2;
        int frameCountY = ratio * (y1 - (centerY + 1));
        // Left
        if (isOdd) {
            UI_GotoXY(x0, centerY);
            printf("%c", 186);
        }
        for (int i = centerY - C; i >= centerY - C - frameCountY; i--) {
            UI_GotoXY(x0, i);
            printf("%c", 186);
        }
        for (int i = centerY + 1; i <= centerY + 1 + frameCountY; i++) {
            UI_GotoXY(x0, i);
            printf("%c", 186);
        }
        // Right
        if (isOdd) {
            UI_GotoXY(x1, centerY);
            printf("%c", 186);
        }
        for (int i = centerY - C; i >= centerY - C - frameCountY; i--) {
            UI_GotoXY(x1, i);
            printf("%c", 186);
        }
        for (int i = centerY + 1; i <= centerY + 1 + frameCountY; i++) {
            UI_GotoXY(x1, i);
            printf("%c", 186);
        }
    }

    if (drawY) {
        isOdd = width % 2 == 1;
        C = isOdd ? 1 : 0;
        int centerX = (x0 + x1) / 2;
        int frameCountX = ratio * (x1 - (centerX + 1));
        // Up
        if (isOdd) {
            UI_GotoXY(centerX, y0);
            printf("%c", 205);
        }
        for (int i = centerX - C; i >= centerX - C - frameCountX; i--) {
            UI_GotoXY(i, y0);
            printf("%c", 205);
        }
        for (int i = centerX + 1; i <= centerX + 1 + frameCountX; i++) {
            UI_GotoXY(i, y0);
            printf("%c", 205);
        }
        // Down
        if (isOdd) {
            UI_GotoXY(centerX, y1);
            printf("%c", 205);
        }
        for (int i = centerX - C; i >= centerX - C - frameCountX; i--) {
            UI_GotoXY(i, y1);
            printf("%c", 205);
        }
        for (int i = centerX + 1; i <= centerX + 1 + frameCountX; i++) {
            UI_GotoXY(i, y1);
            printf("%c", 205);
        }
    }

    if (completeness > 99.5f) {
        if (drawX && drawY) {
            // Top-Left Corner
            UI_GotoXY(x0, y0);
            printf("%c", 201);
            // Top-Right Corner
            UI_GotoXY(x1, y0);
            printf("%c", 187);
            // Bottom-Left Corner
            UI_GotoXY(x0, y1);
            printf("%c", 200);
            // Bottom-Right Corner
            UI_GotoXY(x1, y1);
            printf("%c", 188);
        }
    }
}

void UI_PrintfWordWrap(
    int x, int y, int maxWidth, int maxHeight, const char* str, bool centered
) {
    int len = strlen(str);
    int lineCount = 0;

    for (int i = 0; i < len; i += maxWidth) {
        UI_GotoXY(x, y + lineCount);
        if (i + maxWidth < len) {
            printf("%.*s", maxWidth, str + i);
            lineCount += 1;
        }
        else {
            if (centered) {
                int this_len = strlen(str + i);
                int padding = (maxWidth - this_len) / 2;
                for (int j = 0; j < padding; j++) {
                    printf(" ");
                }
            }
            printf("%s\n", str + i);
            lineCount += 1;
        }

        if (lineCount >= maxHeight) {
            break;
        }
    }
}

void UI_PrintfWordWrap_Animated(
    int x, int y, int maxWidth, int maxHeight, const char* str_raw, bool centered,
    float completeness
) {
    int len_raw = strlen(str_raw);
    char* str = new char[len_raw + (long long)1];
    strcpy_s(str, len_raw + (long long)1, str_raw);

    completeness = clampF(0.0f, completeness, 100.0f);
    int frameCount = (float)len_raw / TOTAL_COMPLETENESS * completeness;

    if (frameCount < len_raw) {
        str[frameCount] = '\0';  // Truncation in Advance.
    }

    int len = strlen(str);
    int lineCount = 0;

    for (int i = 0; i < len; i += maxWidth) {
        UI_GotoXY(x, y + lineCount);
        if (i + maxWidth < len) {
            printf("%.*s", maxWidth, str + i);
            lineCount += 1;
        }
        else {
            if (centered) {
                int this_len = strlen(str + i);
                int padding = (maxWidth - this_len) / 2;
                for (int j = 0; j < padding; j++) {
                    printf(" ");
                }
            }
            printf("%s\n", str + i);
            lineCount += 1;
        }

        if (lineCount >= maxHeight) {
            break;
        }
    }

    delete[] str;
}

void UI_DrawDiv(Div& div) {
    int borderX = div.x + div.marginX;
    int borderY = div.y + div.marginY;
    int borderWidth = div.width - 2 * div.marginX;
    int borderHeight = div.height - 2 * div.marginY;

    if (div.borderX || div.borderY) {
        UI_DrawRect(
            borderX, borderY, borderWidth, borderHeight, div.borderX, div.borderY
        );
    }
    
    int textX = borderX + 1 + div.paddingX;
    int textY = borderY + 1 + div.paddingY;
    int textWidth = borderWidth - 2 * (1 + div.paddingX);    // 1 for BorderWidth
    int textHeight = borderHeight - 2 * (1 + div.paddingY);  // 1 for BorderHeight

    if (div.width == 1) {
        textX = borderX;
    }

    if (div.height == 1) {
        textY = borderY;
    }

    UI_PrintfWordWrap(
        textX, textY, textWidth, textHeight, div.text, div.text_centered
    );
}

void UI_DrawDiv_Animated(Div& div, float completeness) {
    int borderX = div.x + div.marginX;
    int borderY = div.y + div.marginY;
    int borderWidth = div.width - 2 * div.marginX;
    int borderHeight = div.height - 2 * div.marginY;

    if (div.borderX || div.borderY) {
        UI_DrawRect_Animated(
            borderX, borderY, borderWidth, borderHeight, div.borderX, div.borderY,
            completeness
        );
    }

    int textX = borderX + 1 + div.paddingX;
    int textY = borderY + 1 + div.paddingY;
    int textWidth = borderWidth - 2 * (1 + div.paddingX);    // 1 for BorderWidth
    int textHeight = borderHeight - 2 * (1 + div.paddingY);  // 1 for BorderHeight

    if (div.width == 1) {
        textX = borderX;
    }

    if (div.height == 1) {
        textY = borderY;
    }

    UI_PrintfWordWrap_Animated(
        textX, textY, textWidth, textHeight, div.text, div.text_centered,
        completeness
    );
}

void UI_DrawDivList(Div* divList, int length) {
    for (int i = 0; i < length; i++) {
        UI_DrawDiv(divList[i]);
    }
}

void UI_DrawDivList_Animated(Div* divList, int length, float completeness) {
    for (int i = 0; i < length; i++) {
        UI_DrawDiv_Animated(divList[i], completeness);
    }
}

void UI_Render(Div* divList, int length) {

    UI_Init();

    float completeness = 0.0f;
    float speed = 1.0f;
    while (true) {
        UI_DrawDivList_Animated(divList, length, completeness);
        Sleep(3);
        speed = 0.25f + fabs(3.5f * sin((completeness / TOTAL_COMPLETENESS) * PI));
        completeness += speed;

        if (completeness >= 102.0f) {
            break;
        }
    }
}
