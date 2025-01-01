#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Student.h"
#include "UI.h"
#include <string.h>
#include <process.h>

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
	UI_DrawWindow();

	Div div = {
		1, 1, 78, 23,
		false, true, 5, 5, 3, 3,
		"A quick brown fox jumps over the lazy dog. A quick brown fox jumps over the lazy dog. A quick brown fox jumps over the lazy dog. A quick brown fox jumps over the lazy dog. A quick brown fox jumps over the lazy dog. A quick brown fox jumps over the lazy dog. A quick brown fox jumps over the lazy dog. A quick brown fox jumps over the lazy dog. A quick brown fox jumps over the lazy dog. A quick brown fox jumps over the lazy dog. A quick brown fox jumps over the lazy dog. A quick brown fox jumps over the lazy dog. A quick brown fox jumps over the lazy dog. A quick brown fox jumps over the lazy dog. A quick brown fox jumps over the lazy dog. A quick brown fox jumps over the lazy dog. A quick brown fox jumps over the lazy dog. A quick brown fox jumps over the lazy dog. A quick brown fox jumps over the lazy dog. A quick brown fox jumps over the lazy dog. "
	};
	UI_DrawDiv(div);

	getchar();
	return 0;
}
#endif
