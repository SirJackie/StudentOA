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

bool isArbitaryStrEqual(char* str1, char* str2, int length) {
	for (int i = 0; i < length; i++) {
		if (str1[i] != str2[i]) {
			return false;
		}
	}
	return true;
}

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
