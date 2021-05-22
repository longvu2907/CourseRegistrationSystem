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
		drawTable(width, height, left, top);
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
int command(int& curPos, int minPos, int maxPos, function<int(int)> option) {
	int key = _getch();
	switch (key) {
	case 13:
		return option(curPos);
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

void Profile() {
	const int width = 40;
	const int height = 7;
	const int left = 40;
	const int top = 8;
	int curPos = 0;
	do {
		system("cls");
		drawTable(width, height, left, top);
		gotoXY(48, 9); cout << "Name: " << currentUser->fullName;
		gotoXY(48, 10); cout << "Gender: " << currentUser->gender;
		if (!currentUser->isAdmin) {
			gotoXY(48, 11); cout << "Class: " << currentUser->className;
		}
		else {
			gotoXY(48, 11); cout << "Academic staff member";
		}
		gotoXY(48, 13); cout << "Change password";
		gotoXY(48, 14); cout << "Back";
		gotoXY(70, curPos + 13); cout << cursor;
	} while (command(curPos, 0, 1, subOption1));
	
}
void changePassword() {
	const int width = 40;
	const int height = 7;
	const int left = 40;
	const int top = 8;
	int curPos = 0;
	string oldPassword;

	hideCursor(false);
	do {
		system("cls");
		drawTable(width, height, left, top);
		gotoXY(48, 9); cout << "Your old password: ";
		getline(cin, oldPassword);
		if (oldPassword == currentUser->password) {
			gotoXY(48, 10); cout << "Enter new password: ";
			getline(cin, currentUser->password);
			gotoXY(48, 12); cout << "Successful";
			gotoXY(48, 13); cout << "Enter to continue...";
			_getch();
			hideCursor(true);
			saveListUser();
			return;
		}
		else {
			gotoXY(48, 11); cout << "Wrong!!";
			gotoXY(48, 12); cout << "Enter to try again...";
			gotoXY(48, 13); cout << "Esc to return...";
			int key = _getch();
			if (key == 27) {
				hideCursor(true);
				return;
			}
		}
	} while (true);
}

void logout() {
	
	currentUser = NULL;
}