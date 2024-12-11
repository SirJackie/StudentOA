#include "Student.h"

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <process.h>

/**
 * @section
 * Global Variables
 */

Student students[STUDENT_MAX_LEN];
int length = 0;

/**
 * @section
 * Save & Load Functions
 */

/**
 * @brief: Save students data into a file.
 * @param students: Pointer to an array of student structs to be saved.
 * @param length: How many student structs you want to save.
 * @return: void
 */

void Save(Student* students, int length) {
	// Initialize
	FILE* fp = fopen("database.bin", "wb");
	if (fp == NULL) {
		perror("Error Opening File");
		system("pause");
	}

	// Save to File
	fwrite(students, sizeof(Student), length, fp);

	// Finalize
	fclose(fp);
}

/**
 * @brief: Load students data from a file.
 * @param buffer: Pointer to an buffer where loaded contents will be stored here.
 * @return int: How many student structures are loaded from the file.
 */

int Load(Student* buffer) {
	// Initialize
	FILE* fp = fopen("database.bin", "rb");
	if (fp == NULL) {
		perror("Error Opening File");
		system("pause");
	}

	// Pointer Operations
	int currLength = 0;
	Student* ptr = buffer;

	// Read from File
	while (true) {
		fread(ptr, sizeof(Student), 1, fp);
		if (feof(fp)) {
			break;
		}
		currLength++;
		ptr++;
	}

	// Finalize
	fclose(fp);

	return currLength;
}

/**
 * @section
 * Search Algorithm
 */

/**
 * @brief: Compare if the first nth chars in two strings are equal or not.
 * @param str1: first string being compared.
 * @param str2: second string being compared.
 * @param length: How many chars do you wanna compare? (first nth)
 * @return bool: If they are equal, true or false.
 */

bool isArbitaryStrEqual(char* str1, char* str2, int length) {
	for (int i = 0; i < length; i++) {
		if (str1[i] != str2[i]) {
			return false;
		}
	}
	return true;
}

/**
 * @brief: Determine if a string includes a sub-string or not.
 * @param str: the parent string.
 * @param subStr: the child sub-string.
 * @return bool: If the parent string includes the child sub-string.
 */

bool vagueFind(char* str, char* subStr) {
	int sLen = strlen(str);      // For instance 5
	int ssLen = strlen(subStr);  // For instance 3

	for (int starter = 0; starter < sLen - ssLen + 1; starter++) {  // 0 1 2
		char* ptrStarter = str + starter;
		if (isArbitaryStrEqual(ptrStarter, subStr, ssLen) == true) {
			return true;
		}
	}

	return false;
}

/**
 * @section
 * Business Logics
 */

/**
 * @brief: Display all the student information.
 * @return void
 */

void Display() {
	for (int i = 0; i < length; i++) {
		printf(
			"%d\t%s\t%s\t%d\n",
			students[i].id,
			students[i].name,
			students[i].pwd,
			students[i].year
		);
	}
	getchar();  // Flush Stdin
	printf("--------------------------------\n");
}

/**
 * @brief: Search if a given name is inside the Student Structure Array.
 * @return void
 */

void Search() {
	printf("Please Enter Student's Name, Vague Find Supported: ");
	char buffer[1000];
	scanf("%s", buffer);
	getchar();  // Flush Stdin

	for (int i = 0; i < length; i++) {
		if (vagueFind(students[i].name, buffer)) {
			printf(
				"%d\t%s\t%s\t%d\n",
				students[i].id,
				students[i].name,
				students[i].pwd,
				students[i].year
			);
		}
	}

	printf("--------------------------------\n");
}

/**
 * @brief: Append a student into the Student Structure Array.
 * @return void
 */

void Append() {
	printf("Please Enter the Student's Information that You Wanna Append.\n");
	printf("Format: name password year\n");
	scanf(
		"%s %s %d",
		students[length].name,
		students[length].pwd,
		&students[length].year
	);

	// ID Self Increment
	students[length].id = students[length - 1].id + 1;

	printf(
		"New Student Appended:\n%d\t%s\t%s\t%d\n",
		students[length].id,
		students[length].name,
		students[length].pwd,
		students[length].year
	);
	length++;   // Step in

	Save(students, length);
	printf("Data Saved to the Database.\n");

	getchar();  // Flush Stdin
	printf("--------------------------------\n");
}

/**
 * @brief: Reset a student's password.
 * @return void
 */

void Reset() {
	printf("Please Enter the Reset Information.\n");
	printf("Format: id old_password new_password\n");

	int id;
	char oldPwd[1000];
	char newPwd[1000];

	scanf(
		"%d %s %s",
		&id,
		oldPwd,
		newPwd
	);

	bool successFlag = false;

	for (int i = 0; i < length; i++) {
		if (students[i].id == id && STR_EQUAL(students[i].pwd, oldPwd)) {
			strcpy(students[i].pwd, newPwd);
			successFlag = true;
		}
	}

	if (successFlag == true) {
		printf("Reset Operation Succeed.\n");
		Save(students, length);
		printf("Data Saved to the Database.\n");
	}
	else {
		printf("Reset Operation Failed.\n");
	}

	getchar();  // Flush Stdin
	printf("--------------------------------\n");
}
