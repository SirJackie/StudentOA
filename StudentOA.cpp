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

	UI_Init();

	Div divList[] = {
		{   // Window Border
			0, 0, WIN_WIDTH, WIN_HEIGHT,
			true, true, 0, 0, 0, 0,
			"", false
		},
		{
			1, 2, 78, 3,
			false, true, 3, 0, 0, 0,
			"Student OA", true
		},
		{
			1, 6, 78, 1,
			false, false, 0, 0, 0, 0,
			"Input Your Option, e.g. 'd', Then Press Enter.", true
		},
		{
			1, 8, 38, 3,
			true, true, 3, 0, 0, 0,
			"d. Display", false
		},
		{
			1, 12, 38, 3,
			true, true, 3, 0, 0, 0,
			"s. Search", false
		},
		{
			1, 16, 38, 3,
			true, true, 3, 0, 0, 0,
			"a. Append", false
		},
		{
			40, 8, 38, 3,
			true, true, 3, 0, 0, 0,
			"r. Reset Password", false
		},
		{
			40, 12, 38, 3,
			true, true, 3, 0, 0, 0,
			"f. Reset Database", false
		},
		{
			40, 16, 38, 3,
			true, true, 3, 0, 0, 0,
			"x. Exit", false
		}
	};

	float completeness = 0.0f;
	float speed = 1.0f;
	while (true) {
		UI_DrawDivList_Animated(divList, sizeof(divList) / sizeof(Div), completeness);
		//Sleep(5);
		speed = 0.25f + fabs(3.5f * sin((completeness / TOTAL_COMPLETENESS) * PI));
		completeness += speed;

		if (completeness >= 102.0f) {
			break;
		}
	}
}

#ifdef MODE_MAIN_OA
int main() {
	G_length = Load(G_students);

	char option;
	bool wannaExit = false;

	while (true) {
		system("cls");
		UI_DrawStarterPage();

		UI_GotoXY(3, 21);
		printf("Please Enter Your Option: ");
		option = getchar();
		system("cls");

		switch (option) {
		case 'd':
			Display();
			getchar();
			break;
		case 's':
			Search();
			getchar();
			break;
		case 'a':
			Append();
			getchar();
			break;
		case 'r':
			Reset();
			getchar();
			break;
		case 'x':
			printf("Exiting...\n");
			wannaExit = true;
			break;
		default:
			printf("Option NOT FOUND!\n");
			printf("--------------------------------\n");
			getchar();  // Flush Stdin
			getchar();
		}

		if (wannaExit) {
			break;
		}
	}

	return 0;
}

#endif
