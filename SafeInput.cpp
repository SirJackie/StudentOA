#define _CRT_SECURE_NO_WARNINGS
#include "SafeInput.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @section
 * Compatibility Considering getch()
 */

#ifndef _WIN32
int getch(void) {
	struct termios oldt, newt;
	int ch;
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	ch = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	return ch;
}
#endif

/**
 * @section
 * The Safe Input Function
 */

/**
 * @brief: Input a string to a buffer, with safe boundary checking.
 * @param buffer: The buffer where input data will be stored.
 * @param maxLength: The Maximum Length of the buffer given above.
 * @return void
 */

void SafeInput(char* buffer, int maxLength) {
	int length = 0;

	while (true) {
		char ch = getch();

		if (ch == '\n' || ch == '\r') {
			// Enter Pressed, Exiting.
			putchar('\n');
			break;
		}

		if (ch == 127 || ch == '\b') {
			// Backspace Pressed, Delete 1 Char.
			if (length > 0) {
				// Delete Char in Buffer
				length--;
				buffer[length] = '\0';
				// Delete Char on Screen
				printf("\b \b");  // Move Left, Output Space, Move Left
			}
			continue;
		}

		if (length < maxLength) {
			// If Buffer is NOT Fulled Yet.
			buffer[length++] = ch;
			buffer[length] = '\0';
			putchar(ch);
		}
	}
}
