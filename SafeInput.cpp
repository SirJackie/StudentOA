#define _CRT_SECURE_NO_WARNINGS
#include "SafeInput.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @section
 * Compatibility Considering getch()
 */

#ifdef _WIN32
#define getch() _getch()
#else
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
 * Compatibility Considering getch_nonblocking()
 */

#ifdef _WIN32
char getch_nonblocking() {
	if (_kbhit()) {
		return _getch();
	}
	return -1;
}
#else
// 保存原始终端设置
struct termios original_termios;
bool isInNonBlockingState = false;

// 恢复原始终端设置
void restore_terminal() {
	tcsetattr(STDIN_FILENO, TCSANOW, &original_termios);
}

// 设置终端为非阻塞模式
void set_nonblocking() {
	struct termios new_termios;
	tcgetattr(STDIN_FILENO, &original_termios);
	new_termios = original_termios;
	new_termios.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
	int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
}

// 非阻塞读取字符
int getch_nonblocking() {

	if (isInNonBlockingState == false) {
		set_nonblocking();
		atexit(restore_terminal);
		isInNonBlockingState = true;
	}

	struct timeval tv;
	fd_set fds;
	tv.tv_sec = 0;
	tv.tv_usec = 0;
	FD_ZERO(&fds);
	FD_SET(STDIN_FILENO, &fds);
	if (select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv) == -1) {
		perror("select error");
		return -1;
	}
	else if (FD_ISSET(STDIN_FILENO, &fds)) {
		return getchar();
	}
	return -1;
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
