#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <process.h>

#include "UI.h"
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

	int indexOffset = 10;
	int divLength = indexOffset + G_length * 4;
	Div* divList = new Div[divLength];

	// Window Border
	divList[0] = {
		0, 0, WIN_WIDTH, WIN_HEIGHT,
		true, true, 0, 0, 0, 0,
		"", false
	};

	// Window Title
	divList[1] = {
		1, 2, 78, 3,
		false, true, 3, 0, 0, 0,
		"Display", true
	};

	// Horizontal Splitter
	divList[2] = {
		4, 7, 72, 1,
		false, true, 0, 0, 0, 0,
		"", false
	};

	// Sheet Title 1
	divList[3] = {
		3, 6, 8, 1,
		false, false, 0, 0, 0, 0,
		"ID", false
	};

	// Vertical Splitter
	divList[4] = {
		12, 6, 1, G_length + 2,
		true, false, 0, 0, 0, 0,
		"", false
	};

	// Sheet Title 2
	divList[5] = {
		13, 6, 16, 1,
		false, false, 0, 0, 0, 0,
		"Name", false
	};

	// Vertical Splitter
	divList[6] = {
		30, 6, 1, G_length + 2,
		true, false, 0, 0, 0, 0,
		"", false
	};

	// Sheet Title 3
	divList[7] = {
		31, 6, 32, 1,
		false, false, 0, 0, 0, 0,
		"Password", false
	};

	// Vertical Splitter
	divList[8] = {
		64, 6, 1, G_length + 2,
		true, false, 0, 0, 0, 0,
		"", false
	};

	// Sheet Title 4
	divList[9] = {
		65, 6, 8, 1,
		false, false, 0, 0, 0, 0,
		"Year", false
	};

	// Convert Student Infos Into Divs
	char* ptr = nullptr;
	for (int i = 0; i < G_length; i++) {

		// Sheet Title 1
		divList[indexOffset + 4 * i + 0] = {
			3, 8 + i, 8, 1,
			false, false, 0, 0, 0, 0,
			"", false
		};
		ptr = divList[indexOffset + 4 * i + 0].text;
		sprintf(ptr, "%d", G_students[i].id);

		// Sheet Title 2
		divList[indexOffset + 4 * i + 1] = {
			13, 8 + i, 16, 1,
			false, false, 0, 0, 0, 0,
			"", false
		};
		ptr = divList[indexOffset + 4 * i + 1].text;
		sprintf(ptr, "%s", G_students[i].name);

		// Sheet Title 3
		divList[indexOffset + 4 * i + 2] = {
			31, 8 + i, 32, 1,
			false, false, 0, 0, 0, 0,
			"", false
		};
		ptr = divList[indexOffset + 4 * i + 2].text;
		sprintf(ptr, "%s", G_students[i].pwd);

		// Sheet Title 4
		divList[indexOffset + 4 * i + 3] = {
			65, 8 + i, 8, 1,
			false, false, 0, 0, 0, 0,
			"", false
		};
		ptr = divList[indexOffset + 4 * i + 3].text;
		sprintf(ptr, "%d", G_students[i].year);
	}

	UI_Render(divList, divLength);
	getchar();  // Wait For Exit

	delete[] divList;
	divList = nullptr;
}

/**
 * @brief: Search if a given name is inside the Student Structure Array.
 * @return void
 */

void Search() {

	Div divList[] = {
		{   // Window Border
			0, 0, WIN_WIDTH, WIN_HEIGHT,
			true, true, 0, 0, 0, 0,
			"", false
		},
		{
			1, 2, 78, 3,
			false, true, 3, 0, 0, 0,
			"Search", true
		},
		{
			1, 6, 78, 5,
			true, true, 3, 0, 1, 1,
			"Student's Name: ", false
		}
	};

	// Draw Search UI
	UI_Render(divList, sizeof(divList) / sizeof(Div));

	// Response to User Input
	int length = 16;
	char buffer[16] = { 0 };
	UI_InputAnimation(divList[2], buffer, length);

	// Vague Find
	int* foundList = new int[G_length];
	int foundListLen = 0;
	for (int i = 0; i < G_length; i++) {
		if (vagueFind(G_students[i].name, buffer)) {
			foundList[foundListLen] = i;
			foundListLen += 1;
		}
	}

	//
	// Display Search Result
	//

	system("cls");

	int indexOffset = 10;
	int divLength2 = indexOffset + foundListLen * 4;
	Div* divList2 = new Div[divLength2];

	// Window Border
	divList2[0] = {
		0, 0, WIN_WIDTH, WIN_HEIGHT,
		true, true, 0, 0, 0, 0,
		"", false
	};

	// Window Title
	divList2[1] = {
		1, 2, 78, 3,
		false, true, 3, 0, 0, 0,
		"Search Result", true
	};

	// Horizontal Splitter
	divList2[2] = {
		4, 7, 72, 1,
		false, true, 0, 0, 0, 0,
		"", false
	};

	// Sheet Title 1
	divList2[3] = {
		3, 6, 8, 1,
		false, false, 0, 0, 0, 0,
		"ID", false
	};

	// Vertical Splitter
	divList2[4] = {
		12, 6, 1, foundListLen + 2,
		true, false, 0, 0, 0, 0,
		"", false
	};

	// Sheet Title 2
	divList2[5] = {
		13, 6, 16, 1,
		false, false, 0, 0, 0, 0,
		"Name", false
	};

	// Vertical Splitter
	divList2[6] = {
		30, 6, 1, foundListLen + 2,
		true, false, 0, 0, 0, 0,
		"", false
	};

	// Sheet Title 3
	divList2[7] = {
		31, 6, 32, 1,
		false, false, 0, 0, 0, 0,
		"Password", false
	};

	// Vertical Splitter
	divList2[8] = {
		64, 6, 1, foundListLen + 2,
		true, false, 0, 0, 0, 0,
		"", false
	};

	// Sheet Title 4
	divList2[9] = {
		65, 6, 8, 1,
		false, false, 0, 0, 0, 0,
		"Year", false
	};

	// Convert Student Infos Into Divs
	char* ptr = nullptr;
	for (int i = 0; i < foundListLen; i++) {

		// Sheet Title 1
		divList2[indexOffset + 4 * i + 0] = {
			3, 8 + i, 8, 1,
			false, false, 0, 0, 0, 0,
			"", false
		};
		ptr = divList2[indexOffset + 4 * i + 0].text;
		sprintf(ptr, "%d", G_students[foundList[i]].id);

		// Sheet Title 2
		divList2[indexOffset + 4 * i + 1] = {
			13, 8 + i, 16, 1,
			false, false, 0, 0, 0, 0,
			"", false
		};
		ptr = divList2[indexOffset + 4 * i + 1].text;
		sprintf(ptr, "%s", G_students[foundList[i]].name);

		// Sheet Title 3
		divList2[indexOffset + 4 * i + 2] = {
			31, 8 + i, 32, 1,
			false, false, 0, 0, 0, 0,
			"", false
		};
		ptr = divList2[indexOffset + 4 * i + 2].text;
		sprintf(ptr, "%s", G_students[foundList[i]].pwd);

		// Sheet Title 4
		divList2[indexOffset + 4 * i + 3] = {
			65, 8 + i, 8, 1,
			false, false, 0, 0, 0, 0,
			"", false
		};
		ptr = divList2[indexOffset + 4 * i + 3].text;
		sprintf(ptr, "%d", G_students[foundList[i]].year);
	}

	UI_Render(divList2, divLength2);
	getchar();  // Wait For Exit

	delete[] divList2;
	divList2 = nullptr;

	delete[] foundList;
	foundList = nullptr;
}

/**
 * @brief: Append a student into the Student Structure Array.
 * @return void
 */

void Append() {
	Div divList[] = {
		{   // Window Border
			0, 0, WIN_WIDTH, WIN_HEIGHT,
			true, true, 0, 0, 0, 0,
			"", false
		},
		{
			1, 2, 78, 3,
			false, true, 3, 0, 0, 0,
			"Append", true
		},
		{
			1, 6, 78, 5,
			true, true, 3, 0, 1, 1,
			"Name: ", false
		},
		{
			1, 11, 78, 5,
			true, true, 3, 0, 1, 1,
			"Password: ", false
		},
		{
			1, 16, 78, 5,
			true, true, 3, 0, 1, 1,
			"Year: ", false
		}
	};

	// Draw Append UI
	UI_Render(divList, sizeof(divList) / sizeof(Div));

	// Response to User Input (Input: Name)
	UI_InputAnimation(divList[2], G_students[G_length].name, 16);

	// Response to User Input (Input: Password)
	UI_InputAnimation(divList[3], G_students[G_length].pwd, 32);

	// Response to User Input (Input: Year)
	char buffer[16] = { 0 };
	UI_InputAnimation(divList[4], buffer, 16);
	sscanf(buffer, "%d", &G_students[G_length].year);

	// ID Self Increment
	G_students[G_length].id = G_students[G_length - 1].id + 1;

	// Step in
	G_length++;

	// Update Database
	Save(G_students, G_length);

	// Successful Message
	UI_MessageBox("New Student Appended Successfully! Data Saved to the Database.");
}

/**
 * @brief: Reset a student's password.
 * @return void
 */

void Reset() {

	Div divList[] = {
		{   // Window Border
			0, 0, WIN_WIDTH, WIN_HEIGHT,
			true, true, 0, 0, 0, 0,
			"", false
		},
		{
			1, 2, 78, 3,
			false, true, 3, 0, 0, 0,
			"Reset", true
		},
		{
			1, 6, 78, 5,
			true, true, 3, 0, 1, 1,
			"ID: ", false
		},
		{
			1, 11, 78, 5,
			true, true, 3, 0, 1, 1,
			"Old Password: ", false
		},
		{
			1, 16, 78, 5,
			true, true, 3, 0, 1, 1,
			"New Password: ", false
		}
	};

	int id;
	char idBuff[16] = { 0 };
	char oldPwd[32] = { 0 };
	char newPwd[32] = { 0 };

	// Draw Reset UI
	UI_Render(divList, sizeof(divList) / sizeof(Div));

	// Response to User Input (Input: ID)
	UI_InputAnimation(divList[2], idBuff, 16);
	sscanf(idBuff, "%d", &id);

	// Response to User Input (Input: Old Password)
	UI_InputAnimation(divList[3], oldPwd, 32);

	// Response to User Input (Input: New Password)
	UI_InputAnimation(divList[4], newPwd, 32);

	// Reset User's Password
	bool successFlag = false;
	for (int i = 0; i < G_length; i++) {
		if (G_students[i].id == id && STR_EQUAL(G_students[i].pwd, oldPwd)) {
			strcpy(G_students[i].pwd, newPwd);
			successFlag = true;
		}
	}

	// Result Feedback
	if (successFlag == true) {
		// Update Database
		Save(G_students, G_length);

		// Successful Message
		UI_MessageBox("Reset Operation Succeeded! Data Saved to the Database.");
	}
	else {
		// Failed Message
		UI_MessageBox("Reset Operation Failed! Wrong Old Password.");
	}
}

void ResetDatabase() {
	Student students[5] = {
		{1001, "Jackie", "dumbasfuk", 2005},
		{1002, "Sarah", "lululemon", 2006},
		{1003, "Paul", "rockstarOG", 2005},
		{1004, "Vangel", "immaGreek", 1979},
		{1005, "Carl", "losantoYeah", 1985}
	};

	// Save the Initial Database
	int length = 5;
	Save(students, length);

	// Remember to Reload Database
	G_length = Load(G_students);
}
