#ifndef __STUDENT_H__
#define __STUDENT_H__

/**
 * @section
 * Struct Definitions
 */

struct Student {
	int id;
	char name[16];
	char pwd[32];
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
extern Student G_students[];
extern int G_length;

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

bool isArbitaryStrEqual(const char* str1, const char* str2, int length);
bool vagueFind(const char* str, const char* subStr);

/**
 * @section
 * Business Logics
 */

void Display();
void Search();
void Append();
void Reset();
void ResetDatabase();

#endif
