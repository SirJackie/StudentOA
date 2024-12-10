#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <process.h>

struct Student{
	int id;
	char name[10];
	char pwd[100];
	int year;
};

#define STUDENT_MAX_LEN 1000
Student students[STUDENT_MAX_LEN];
int length = 0;

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

int Load(Student* buffer){
	// Initialize
	FILE* fp = fopen("database.bin", "rb");
	if (fp == NULL){
		perror("Error Opening File");
		system("pause");
	}
	
	// Pointer Operations
	int currLength = 0;
	Student* ptr = buffer;
	
	// Read from File
	while (true){
		fread(ptr, sizeof(Student), 1, fp);
		if (feof(fp)){
			break;
		}
		currLength++;
		ptr++;
	}
	
	// Finalize
	fclose(fp);
	
	return currLength;
}

int main(){
	length = Load(students);
	
	int x = 0;
}

