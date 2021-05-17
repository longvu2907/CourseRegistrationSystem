#include "AcademicStaff.h"


int command(int&, int, int);
void viewProfile();
void logout();

void staffMenu() {
	const int width = 40;
	const int height = 4;
	const int left = 40;
	const int top = 8;
	const char cursor = char(174);
	int curPos = 0;

	hideCursor(true);
	do {
		system("cls");
		drawTable(width, height, left, top);
		gotoXY(48, 9); cout << "View profile";
		gotoXY(48, 10); cout << "Log out";
		gotoXY(70, curPos + 9); cout << cursor;
	} while (command(curPos, 0, 2));
}

int command(int& curPos, int minPos, int maxPos) {
	int key = _getch();
	switch (key) {
	case 13:
		switch (curPos) {
		case 0:
			viewProfile();
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
		break;
	case 224:
		key = _getch();
		switch (key) {
		case 72:
			if (curPos > minPos) curPos--;
			break;
		case 80:
			if (curPos < maxPos) curPos++;
			break;
		}
	}
	return 1;
}

void viewProfile() {
	const int width = 40;
	const int height = 4;
	const int left = 40;
	const int top = 8;
	const char cursor = char(174);
	int curPos = 0;

	do {
		system("cls");
		drawTable(width, height, left, top);
		gotoXY(48, 9); cout << "View profile";
		gotoXY(48, 10); cout << "Log out";
		gotoXY(70, curPos + 9); cout << cursor;
	} while (command(curPos,0,0));
}

void logout() {
	currentUser = NULL;
}