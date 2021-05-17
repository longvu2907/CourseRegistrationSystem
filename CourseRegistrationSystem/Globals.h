#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <conio.h>
#include <windows.h>

#include "AcademicStaff.h"
#include "Student.h"

using namespace std;

struct User {
	string id;
	string password;
	string fullName;
	string className;
	string gender;
	bool isAdmin;
	User* prev;
	User* next;
};
struct List {
	User* pHead;
	User* pTail;
	int size;


};

void gotoXY(int x, int y);
void hideCursor(bool);
void drawTable(int width, int height, int left, int top);

extern User* currentUser;