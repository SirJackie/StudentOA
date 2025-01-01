#ifndef __UI_H__
#define __UI_H__

struct Div {
	int x;
	int y;
	int width;
	int height;

	bool border;
	int paddingX;
	int paddingY;
	int marginX;
	int marginY;

	char text[1000] = { 0 };
};

void UI_Init();
void UI_GotoXY(int x, int y);
void UI_DrawRect(int x0, int y0, int x1, int y1);
void UI_DrawDiv(Div& div);

#endif
