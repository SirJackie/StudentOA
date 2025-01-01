#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <process.h>
#include <Windows.h>

#include "UI.h"
#include "Student.h"

/**
 * @section
 * Main Entry
 */

int main() {
	G_length = Load(G_students);

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

	char option;
	bool wannaExit = false;

	while (true) {
		system("cls");
		UI_Render(divList, sizeof(divList) / sizeof(Div));

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
		case 'f':
			ResetDatabase();
			UI_MessageBox("Successfully reset the Database.");
			getchar();  // Flush Stdin
			break;
		case 'x':
			wannaExit = true;
			UI_MessageBox("The Program will be Exited Right Now.");
			getchar();  // Flush Stdin
			break;
		default:
			UI_MessageBox("Option NOT FOUND!");
			if (option != '\n') getchar();  // Flush Stdin if Needed.
			break;
		}

		if (wannaExit) {
			break;
		}
	}

	return 0;
}
