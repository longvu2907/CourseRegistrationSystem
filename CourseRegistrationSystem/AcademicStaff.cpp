#include "AcademicStaff.h"

const char cursor = char(174);
const int timeBeginSchoolYear = 9;

int command(int&, int, int, function<int(int)>);
int staffOption(int);
int userAccountOption(int);
int subOption1(int);
int subOption2(int);

void userAccount();
void changePassword();
void logout();
void Profile();

void staffMenu() {
	const int width = 40;
	const int height = 10;
	const int left = 40;
	const int top = 8;

	int curPos = 0;
	int yPos = 9;
	do {
		hideCursor(true);
		system("cls");
		drawTable(width, height, left, top);
		gotoXY(55, 6); cout << "HCMUS Portal";
		gotoXY(45, 7); cout << "Welcome " << currentUser->fullName;
		gotoXY(48, yPos); cout << "User account" ;
		yPos++;
		gotoXY(48, yPos); cout << "Profile";
		yPos++;
		yPos = 9;
		gotoXY(70, curPos + yPos); cout << cursor;
	} while (command(curPos, 0, 2, staffOption));
}

void userAccount() {
	const int width = 40;
	const int height = 10;
	const int left = 40;
	const int top = 8;

	int curPos = 0;
	int yPos = 9;
	do {
		system("cls");
		drawTable(width, height, left, top);
		gotoXY(55, 6); cout << "User Account";
		gotoXY(48, yPos); cout << "Change Password";
		yPos++;
		gotoXY(48, yPos); cout << "Logout";
		yPos++;
		gotoXY(48, yPos); cout << "Back";
		yPos++;
		yPos = 9;
		gotoXY(70, curPos + yPos); cout << cursor;
	} while (command(curPos, 0, 2, userAccountOption));
}

int staffOption(int curPos) {
	switch (curPos) {
	case 0:
		userAccount();
		break;
	case 1:
		Profile();
		break;
	}
	return 1;
}
int userAccountOption(int curPos) {
	switch (curPos) {
	case 0:
		changePassword();
		break;
	case 1:
		logout();
		loginSystem();
		return 0;
		break;
	case 2:
		return 0;
		break;
	}
	return 1;
}