#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Student.h"

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
		{1001, "Jackie", "dmbasfk", 2005},
		{1002, "Sarah", "lululemon", 2006},
		{1003, "Paul", "rockstarOG", 2005},
		{1004, "Vangel", "immaGreek", 1979},
		{1005, "Carl", "losantoYeah", 1985}
	};

	int length = 5;

	Save(students, length);
}
#endif

#ifdef MODE_MAIN_OA
int main() {
	printf("---------- Student OA ----------\n");
	printf("Enter Your Option, d for Display, s for Search, a for Append, r for Reset, x for Exit.\n");
	length = Load(students);

	char option;
	bool wannaExit = false;

	while (true) {
		printf("Option: ");
		option = getchar();

		switch (option) {
		case 'd':
			Display();
			break;
		case 's':
			Search();
			break;
		case 'a':
			Append();
			break;
		case 'r':
			Reset();
			break;
		case 'x':
			printf("Exiting...\n");
			wannaExit = true;
			break;
		default:
			printf("Option NOT FOUND!\n");
			printf("--------------------------------\n");
			getchar();  // Flush Stdin
		}

		if (wannaExit) {
			break;
		}
	}

	return 0;
}
#endif
