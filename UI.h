#ifndef __UI_H__
#define __UI_H__

#define WIN_WIDTH 80
#define WIN_HEIGHT 25

struct Div {
	int x;
	int y;
	int width;
	int height;

	bool borderX;
	bool borderY;

	int marginX;
	int marginY;

	int paddingX;
	int paddingY;

	char text[1000] = { 0 };
};

void UI_Init();
void UI_GotoXY(int x, int y);
void UI_DrawRect(int x0, int y0, int width, int height, bool drawX, bool drawY);
void UI_DrawWindow();
void UI_DrawDiv(Div& div);

#endif
