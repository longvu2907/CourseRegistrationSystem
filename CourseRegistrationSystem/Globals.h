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
#include<io.h>

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
struct List {
	User* pHead;
	User* pTail;
	int size;
};

Date strToDate(string);
void gotoXY(int x, int y);
void clearLine(int y);
void hideCursor(bool);
bool dirExists(const std::string& dirName_in);
string* ls(string folder);
int removeDir(string dirPath);

void drawTable(int width, int height, int left, int top);
void loading(int x, int y);

void addUser(List& list, User* user);
void saveListUser();
void getCurrentDate();
void getCurrentSchoolYear();

extern User* currentUser;
extern List listUser;
extern Date currentDate;
extern string currentSchoolYear;