#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <process.h>
#include "Student.h"
#include "SafeInput.h"

/**
 * @section
 * Global Variables
 */

Student G_students[STUDENT_MAX_LEN];
int G_length = 0;

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
	FILE* fp = fopen("database.txt", "w");
	if (fp == NULL) {
		perror("Error Opening File");
		system("pause");
	}

	// Save to File
	for (int i = 0; i < length; i++) {
		fprintf(
			fp, "%d %s %s %d\n",
			students[i].id,
			students[i].name,
			students[i].pwd,
			students[i].year
		);
	}

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
	FILE* fp = fopen("database.txt", "r");
	if (fp == NULL) {
		perror("Error Opening File");
		system("pause");
	}

	// Pointer Operations
	int currLength = 0;
	Student* ptr = buffer;

	// Read from File
	while (true) {
		fscanf(
			fp, "%d %s %s %d",
			&ptr->id,
			ptr->name,
			ptr->pwd,
			&ptr->year
		);

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

bool isArbitaryStrEqual(const char* str1, const char* str2, int length) {
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

bool vagueFind(const char* str, const char* subStr) {
	int sLen = strlen(str);      // For instance 5
	int ssLen = strlen(subStr);  // For instance 3

	for (int starter = 0; starter < sLen - ssLen + 1; starter++) {  // 0 1 2
		const char* ptrStarter = str + starter;
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
	for (int i = 0; i < G_length; i++) {
		printf(
			"%d\t%s\t%s\t%d\n",
			G_students[i].id,
			G_students[i].name,
			G_students[i].pwd,
			G_students[i].year
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
	printf("Please Enter Student's Name, Vague Find Supported (<= 15 Chars): ");
	char buffer[16] = { 0 };
	SafeInput(buffer, 15);
	getchar();  // Flush Stdin

	for (int i = 0; i < G_length; i++) {
		if (vagueFind(G_students[i].name, buffer)) {
			printf(
				"%d\t%s\t%s\t%d\n",
				G_students[i].id,
				G_students[i].name,
				G_students[i].pwd,
				G_students[i].year
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

	printf("Name (<= 15 Chars): ");
	SafeInput(G_students[G_length].name, 15);

	printf("Password (<= 31 Chars): ");
	SafeInput(G_students[G_length].pwd, 31);

	printf("Year: ");
	scanf("%d", &G_students[G_length].year);

	// ID Self Increment
	G_students[G_length].id = G_students[G_length - 1].id + 1;

	printf(
		"New Student Appended:\n%d\t%s\t%s\t%d\n",
		G_students[G_length].id,
		G_students[G_length].name,
		G_students[G_length].pwd,
		G_students[G_length].year
	);
	G_length++;   // Step in

	Save(G_students, G_length);
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

	int id;
	char oldPwd[32] = { 0 };
	char newPwd[32] = { 0 };

	printf("ID: ");
	scanf("%d", &id);

	printf("Old Password (<= 31 Chars): ");
	SafeInput(oldPwd, 31);

	printf("New Password (<= 31 Chars): ");
	SafeInput(newPwd, 31);

	bool successFlag = false;

	for (int i = 0; i < G_length; i++) {
		if (G_students[i].id == id && STR_EQUAL(G_students[i].pwd, oldPwd)) {
			strcpy(G_students[i].pwd, newPwd);
			successFlag = true;
		}
	}

	if (successFlag == true) {
		printf("Reset Operation Succeed.\n");
		Save(G_students, G_length);
		printf("Data Saved to the Database.\n");
	}
	else {
		printf("Reset Operation Failed.\n");
	}

	getchar();  // Flush Stdin
	printf("--------------------------------\n");
}
