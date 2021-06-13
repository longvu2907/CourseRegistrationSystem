#include "Student.h"


const char cursor = char(174);

int command(int&, int, int, function<int (int)>);
int studentOption(int);
int subOption1(int);
int subOption2(int);
void Profile();
void changePassword();
void logout();

void studentMenu() {
	const int width = 40;
	const int height = 4;
	const int left = 40;
	const int top = 8;
	
	int curPos = 0;

	hideCursor(true);
	do {
		system("cls");
		drawBox(width, height, left, top);
		gotoXY(58, 6); cout << "STUDENT";
		gotoXY(48, 9); cout << "View profile";
		gotoXY(48, 10); cout << "Log out";
		gotoXY(70, curPos + 9); cout << cursor;
	} while (command(curPos, 0, 1, studentOption));
}

int studentOption(int curPos) {
	switch (curPos) {
	case 0:
		Profile();
		break;
	case 1:
		logout();
		return 0;
		break;
	case 2:
		break;
	case 3:
		break;
	}
	return 1;
}
int subOption1(int curPos) {
	switch (curPos) {
	case 0:
		changePassword();
		break;
	case 1:
		return 0;
		break;
	case 2:
		break;
	case 3:
		break;
	}
	return 1;
}
int subOption2(int curPos) {
	switch (curPos) {
	case 0:
		Profile();
		break;
	case 1:
		logout();
		return 0;
		break;
	case 2:
		break;
	case 3:
		break;
	}
	return 1;
}

