#include <stdio.h>
#include <process.h>

struct Student{
	int id;
	char name[10];
	char pwd[100];
	int year;
};

void Save(Student* students, int length){
	// Initialize
	FILE* fp = fopen("database.bin", "wb");
	if (fp == NULL){
		perror("Error Opening File");
		system("pause");
	}

	// Save to File
	fwrite(students, sizeof(Student), length, fp);

	// Finalize
	fclose(fp);
}

int main(){
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

