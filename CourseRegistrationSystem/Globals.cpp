#include "Globals.h"

const string userDataPath = "data/users.csv";
Date currentDate;

void gotoXY(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void hideCursor(bool isHiden) {
	CONSOLE_CURSOR_INFO cursor;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
	cursor.bVisible = !isHiden;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}

void drawTable(int width, int height, int left, int top) {
	gotoXY(left, top);
	cout << char(201);
	for (int i = 0; i < width; i++) {
		cout << char(205);
	}
	cout << char(187);
	for (int i = top + 1; i < height + top; i++) {
		gotoXY(left, i);
		cout << char(186);
	}
	gotoXY(left, height + top);
	cout << char(200);
	for (int i = 0; i < width; i++) {
		cout << char(205);
	}
	cout << char(188);
	for (int i = height + top - 1; i > top; i--) {
		gotoXY(left + width + 1, i);
		cout << char(186);
	}
}

void saveListUser() {
	ofstream fout(userDataPath);
	fout << "id,password,fullName,class,gender,isAdmin" << endl;
	User* curr = listUser.pHead;
	while (curr != NULL) {
		fout << curr->id << "," << curr->password << "," << curr->fullName << ","
			<< curr->className << "," << curr->gender << ",";
		if (curr->isAdmin) fout << "TRUE" << endl;
		else fout << "FALSE" << endl;
		curr = curr->next;
	}
}

const string currentDateTime() {
	time_t now = time(0);
	tm ltm;
	localtime_s(&ltm,&now);
	cout << "Year: " << 1900 + ltm.tm_year << endl;
	cout << "Month: " << 1 + ltm.tm_mon << endl;
	cout << "Day: " << ltm.tm_mday << endl;
	cout << "Time: " << 1 + ltm.tm_hour << ":";
	cout << 1 + ltm.tm_min << ":";
	cout << 1 + ltm.tm_sec << endl;

	return "";
}
void getCurrentDate() {
	time_t now = time(0);
	tm ltm;
	localtime_s(&ltm, &now);
	string wDay;
	switch (ltm.tm_wday) {
	case 0:
		wDay = "Sun";
		break;
	case 1:
		wDay = "Mon";
		break;
	case 2:
		wDay = "Tue";
		break;
	case 3:
		wDay = "Wed";
		break;
	case 4:
		wDay = "Thu";
		break;
	case 5:
		wDay = "Fri";
		break;
	case 6:
		wDay = "Sat";
		break;
	}
	currentDate.year = 1900 + ltm.tm_year;
	currentDate.month = 1 + ltm.tm_mon;
	currentDate.day = ltm.tm_mday;
	currentDate.wDay = wDay;
}