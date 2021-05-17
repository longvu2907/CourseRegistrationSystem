#include "Student.h"

int command(int &cur);
void viewProfile();
void logout();

void studentMenu() {
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
	} while (command(curPos));
}

int command(int &curPos) {
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
			if (curPos > 0) curPos--;
			break;
		case 80:
			if (curPos < 2) curPos++;
			break;
		}
	}
	return 1;
}

void viewProfile() {

}

void logout() {
	currentUser = NULL;
}