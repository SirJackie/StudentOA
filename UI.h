#ifndef __UI_H__
#define __UI_H__

#define PI 3.1415926f
#define WIN_WIDTH 80
#define WIN_HEIGHT 25
#define TOTAL_COMPLETENESS 100.0f

/**
 * @brief: Make sure min <= value < max. (including left but not including right)
 * @param minVal: Minimum value for clampping.
 * @param value: The value to clamp.
 * @param maxVal: Maximum value for clampping.
 * @return _T: The result of clampped value.
 */

#define clamp(minVal, value, maxVal) (((value) < (minVal))? (minVal) : (((value) > (maxVal-1))? (maxVal-1) : (value)))

/**
 * @brief: Make sure min <= value <= max. (including left AND right)
 * @param minVal: Minimum value for clampping.
 * @param value: The value to clamp.
 * @param maxVal: Maximum value for clampping.
 * @return _T: The result of clampped value.
 */

#define clampF(minVal, value, maxVal) (((value) < (minVal))? (minVal) : (((value) > (maxVal))? (maxVal) : (value)))

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
	bool text_centered;
};

void UI_Init();
void UI_GotoXY(int x, int y);
void UI_DrawRect(
	int x0, int y0, int width, int height, bool drawX, bool drawY
);
void UI_DrawRect_Animated(
	int x0, int y0, int width, int height, bool drawX, bool drawY, float completeness
);
void UI_PrintfWordWrap(
	int x, int y, int maxWidth, int maxHeight, const char* str, bool centered
);
void UI_PrintfWordWrap_Animated(
	int x, int y, int maxWidth, int maxHeight, const char* str_raw, bool centered,
	float completeness
);
void UI_DrawDiv(Div& div);
void UI_DrawDiv_Animated(Div& div, float completeness);
void UI_DrawDivList(Div* divList, int length);
void UI_DrawDivList_Animated(Div* divList, int length, float completeness);
void UI_Render(Div* divList, int length);

#endif
