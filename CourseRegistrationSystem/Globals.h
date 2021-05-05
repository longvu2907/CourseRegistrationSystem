#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <conio.h>
#include <windows.h>

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
void getConsoleSize();
void hideCursor();

extern User* currentUser;
extern RECT* consoleRect;