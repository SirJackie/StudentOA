#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#include <math.h>
#include <process.h>
#include <Windows.h>

#include "UI.h"
#include "Student.h"

#define PI 3.1415926f

/**
 * @section
 * Mode Selection
 */

//#define MODE_CREATOR
#define MODE_MAIN_OA

/**
 * @section
 * Main Entry
 */

#ifdef MODE_CREATOR
int main() {
	Student students[5] = {
		{1001, "Jackie", "dumbasfuk", 2005},
		{1002, "Sarah", "lululemon", 2006},
		{1003, "Paul", "rockstarOG", 2005},
		{1004, "Vangel", "immaGreek", 1979},
		{1005, "Carl", "losantoYeah", 1985}
	};

	int length = 5;

	Save(students, length);
}
#endif

#define CONSOLE_WIDTH  80
#define CONSOLE_HEIGHT 25
#define X_AXIS_PADDING 12
#define Y_BUTTON_HEIGHT 3

void UI_DrawStarterPage() {

	/*UI_DrawWindow();
	int yNow = 1;
	UI_DrawButton(yNow, "---------- Student OA ----------", false, true);
	yNow += Y_BUTTON_HEIGHT;
	UI_DrawButton(yNow, "Enter Your Option, e.g. 'd', Then Press Enter.", false, true);
	yNow += Y_BUTTON_HEIGHT;
	UI_DrawButton(yNow, "d. Display", true, false);
	yNow += Y_BUTTON_HEIGHT;
	UI_DrawButton(yNow, "s. Search", true, false);
	yNow += Y_BUTTON_HEIGHT;
	UI_DrawButton(yNow, "a. Append", true, false);
	yNow += Y_BUTTON_HEIGHT;
	UI_DrawButton(yNow, "r. Reset", true, false);
	yNow += Y_BUTTON_HEIGHT;
	UI_DrawButton(yNow, "x. Exit", true, false);
	yNow += Y_BUTTON_HEIGHT;

	UI_GotoXY(0, 25);
	printf("Please Enter Your Option: ");*/
}

#ifdef MODE_MAIN_OA
//int main() {
//	
//	G_length = Load(G_students);
//	UI_Init();
//
//	char option;
//	bool wannaExit = false;
//
//	while (true) {
//		system("cls");
//		UI_DrawStarterPage();
//		option = getchar();
//		system("cls");
//
//		switch (option) {
//		case 'd':
//			Display();
//			getchar();
//			break;
//		case 's':
//			Search();
//			getchar();
//			break;
//		case 'a':
//			Append();
//			getchar();
//			break;
//		case 'r':
//			Reset();
//			getchar();
//			break;
//		case 'x':
//			printf("Exiting...\n");
//			wannaExit = true;
//			break;
//		default:
//			printf("Option NOT FOUND!\n");
//			printf("--------------------------------\n");
//			getchar();  // Flush Stdin
//			getchar();
//		}
//
//		if (wannaExit) {
//			break;
//		}
//	}
//
//	return 0;
//}

int main() {
	UI_Init();
	UI_DrawRect(0, 0, WIN_WIDTH, WIN_HEIGHT, true, true);

	Div div = {
		1, 1, 78, 23,
		true, true, 5, 5, 3, 3,
		"A quick brown fox jumps over the lazy dog.", true
	};
	//UI_DrawDiv(div);

	float completeness = 0.0f;
	float speed = 1.0f;
	while (true) {
		UI_DrawDiv_Animated(div, completeness);
		Sleep(5);
		speed = 0.25f + 3.5f * sin((completeness / TOTAL_COMPLETENESS) * PI);
		completeness += speed;
	}

	getchar();
	return 0;
}
#endif
