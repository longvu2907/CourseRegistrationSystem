#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <conio.h>
#include <windows.h>
#include <functional>
#include <time.h>
#include <direct.h>
#include <io.h>
#include <filesystem>

#include "AcademicStaff.h"
#include "Student.h"
#include "LoginSystem.h"

using namespace std;

struct Date {
	int year;
	int month;
	int day;
	string wDay;
};
struct User {
	string id;
	string password;
	string lastName;
	string firstName;
	string className;
	string gender;
	bool isStaff;
	Date dateOfBirth;
	User* prev;
	User* next;
};
struct Student {
	string studentID;
	string lastName;
	string firstName;
	string gender;
	string socialID;
	Date dateOfBirth;
	Student* prev;
	Student* next;
};
struct ListUser {
	User* pHead;
	User* pTail;
	int size;
};
struct ListStudent {
	Student* pHead;
	Student* pTail;
	int size;
	string program;
	string className;
	string year;
};

Date strToDate(string);
void gotoXY(int x, int y);
void clearLine(int y);
void hideCursor(bool);
bool dirExists(const std::string& dirName_in);
void copyFolder(string from, string to);

void drawBox(int width, int height, int left, int top);
void loading(string text);
void notifyBox(string msg);

void addUser(ListUser& list, User* user);
void addStudent(ListStudent& list, Student* student);
void saveListUser();
void saveClass(string path, ListStudent listStudent);
void initList(ListUser& list);
void initList(ListStudent& list);
void getCurrentDate();
void getCurrentSchoolYear();

extern User* currentUser;
extern ListUser listUser;
extern Date currentDate;
extern string currentSchoolYear;