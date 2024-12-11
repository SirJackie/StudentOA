#ifndef __SAFE_INPUT_H__
#define __SAFE_INPUT_H__

/**
 * @section
 * Compatibility Considering getch()
 */

#ifdef _WIN32
// getch() in conio.h (Win32 Platform)
#include <conio.h>
#define getch(x) _getch(x)  // getch() is redefined as _getch() in MSVC
#else
// getch() implemented by ourselves (POSIX-Like Platform)
#include <termios.h>
#include <unistd.h>
int getch(void);
#endif

/**
 * @section
 * The Safe Input Function
 */

void SafeInput(char* buffer, int maxLength);

#endif