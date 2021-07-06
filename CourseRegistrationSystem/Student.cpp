#include "Student.h"


const char cursor = char(174);

void userAccount();
void Profile();
void coursesReg();
void setting();

int command(int&, int, int, function<int(int)>);
int studentOption(int);
int coursesRegOption(int);
void registerCourses();

void studentMenu() {
	const int width = 40;
	const int height = 10;
	const int left = 40;
	const int top = 8;

	int curPos = 0;
	int yPos = 9;
	do {
		hideCursor(true);
		schoolYearPath = "./data/" + currentSchoolYear;
		system("cls");
		drawBox(width, height, left, top);
		gotoXY(55, yPos - 4); cout << "HCMUS Portal";
		gotoXY(40, yPos - 3); cout << currentDate.wDay;
		gotoXY(40, yPos - 2); cout << dateToStr(currentDate);
		gotoXY(75, yPos - 3); cout << "Welcome ";
		gotoXY(75, yPos - 2); cout << currentUser->lastName << " " << currentUser->firstName;
		gotoXY(48, yPos); cout << "User account";
		yPos++;
		gotoXY(48, yPos); cout << "Profile";
		yPos++;
		gotoXY(48, yPos); cout << "Courses registration";
		yPos++;
		gotoXY(48, yPos); cout << "Setting";
		yPos++;
		yPos = 9;
		gotoXY(70, curPos + yPos); cout << cursor;
	} while (command(curPos, 0, 4, studentOption));
}
void registerCourses() {
	const int width = 40;
	const int height = 10;
	const int left = 40;
	const int top = 8;

	int curPos = 0;
	int yPos = 9;
	do {

	} while (true);
}
void coursesReg() {
	const int width = 40;
	const int height = 10;
	const int left = 40;
	const int top = 8;

	int curPos = 0;
	int yPos = 9;
	do {
		hideCursor(true);
		schoolYearPath = "./data/" + currentSchoolYear;
		system("cls");
		drawBox(width, height, left, top);
		gotoXY(55, yPos - 4); cout << "HCMUS Portal";
		gotoXY(50, yPos - 2); cout << "Courses Registration";
		gotoXY(48, yPos); cout << "Register Courses";
		yPos++;
		gotoXY(48, yPos); cout << "Enrolled Courses";
		yPos++;
		yPos = 9;
		gotoXY(70, curPos + yPos); cout << cursor;
	} while (command(curPos, 0, 4, studentOption));
}


int studentOption(int curPos) {
	switch (curPos) {
	case 0:
		userAccount();
		break;
	case 1:
		Profile();
		break;
	case 2:
		coursesReg();
		break;
	case 3:
		setting();
		break;
	}
	return 1;
}
