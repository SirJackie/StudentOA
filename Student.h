#ifndef __STUDENT_H__
#define __STUDENT_H__

/**
 * @section
 * Struct Definitions
 */

struct Student {
	int id;
	char name[10];
	char pwd[100];
	int year;
};

/**
 * @section
 * Macro Functions
 */

#define STR_EQUAL(a, b) (!strcmp(a, b))

/**
 * @section
 * Global Variables
 */

#define STUDENT_MAX_LEN 1000
extern Student students[];
extern int length;

/**
 * @section
 * Save & Load Functions
 */

void Save(Student* students, int length);
int  Load(Student* buffer);

/**
 * @section
 * Search Algorithm
 */

bool isArbitaryStrEqual(char* str1, char* str2, int length);
bool vagueFind(char* str, char* subStr);

/**
 * @section
 * Business Logics
 */

void Display();
void Search();
void Append();
void Reset();

#endif
