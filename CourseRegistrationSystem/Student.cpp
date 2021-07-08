#include "Student.h"

ListCourses enrolledCourses;
const char cursor = char(174);

void userAccount();
void Profile();
void coursesReg();
void setting();

void saveEnrolledCourses();
void getEnrolledCourses();
int command(int&, int, int, function<int(int)>);
int studentOption(int);
int coursesRegOption(int);


void studentMenu() {
	const int width = 40;
	const int height = 10;
	const int left = 40;
	const int top = 8;

	int curPos = 0;
	int yPos = 10;
	do {
		hideCursor(true);
		schoolYearPath = "./data/" + currentSchoolYear;
		system("cls");
		drawBox(width, height, left, top);
		gotoXY(55, 5); cout << "HCMUS Portal";
		gotoXY(40, 6); cout << currentDate.wDay;
		gotoXY(40, 7); cout << dateToStr(currentDate);
		gotoXY(75, 6); cout << "Welcome ";
		gotoXY(75, 7); cout << currentUser->lastName << " " << currentUser->firstName;
		gotoXY(48, yPos); cout << "User account";
		yPos++;
		gotoXY(48, yPos); cout << "Profile";
		yPos++;
		gotoXY(48, yPos); cout << "Courses registration";
		yPos++;
		gotoXY(48, yPos); cout << "Setting";
		yPos++;
		yPos++;
		gotoXY(48, yPos); cout << "Exit";
		yPos = 10;
		if (curPos == 4) yPos++;
		gotoXY(70, curPos + yPos); cout << cursor;
		yPos = 10;
	} while (command(curPos, 0, 4, studentOption));
}

//Courses Registration
int registerCoursesOption(int curPos) {
	int count = 0;

	Course* temp = listCourses.head;
	Course* courseChoosed = NULL;
	while (temp != NULL) {
		if (count == curPos) {
			courseChoosed = temp;
			break;
		}
		count++;
		temp = temp->next;
	}
	if (courseChoosed == NULL) {
		return 0;
	}
	else {
		return 0;
	}
	return 1;
}
void registerCourses() {
	const int width = 40;
	int height = 5;
	const int left = 40;
	const int top = 8;
	int curPos = 0;
	int yPos = 10;

	do {
		if (isOnRegSession()) {
			system("cls");
			height = 5;
			height += listCourses.size;
			gotoXY(55, 5); cout << "HCMUS Portal";
			gotoXY(53, 7); cout << "Register Courses";
			drawBox(width, height, left, top);
			if (listCourses.head != NULL) {
				Course* temp = listCourses.head;
				while (temp != NULL) {
					gotoXY(43, yPos); cout << temp->id << "   " << temp->courseName;
					yPos++;
					temp = temp->next;
				}
				yPos++;
				gotoXY(58, yPos); cout << "Back";
				yPos = 10;
				if (curPos == listCourses.size) yPos++;
				gotoXY(78, curPos + yPos); cout << cursor;
				yPos = 10;
			}
			else {
				notifyBox("Empty List...");
				return;
			}
		}
		else {
			notifyBox("Courses registration session has expired from " + dateToStr(listCourses.endDate));
			return;
		}
	} while (command(curPos, 0, listCourses.size, registerCoursesOption));
}
void viewEnrolledCourses() {
	const int width = 40;
	int height = 5;
	const int left = 40;
	const int top = 8;
	int curPos = 0;
	int yPos = 10;
	
	getEnrolledCourses();
	do {
		system("cls");
		height = 5;
		height += enrolledCourses.size;
		gotoXY(55, 5); cout << "HCMUS Portal";
		gotoXY(53, 7); cout << "Register Courses";
		drawBox(width, height, left, top);
		if (enrolledCourses.head != NULL) {
			Course* temp = enrolledCourses.head;
			while (temp != NULL) {
				gotoXY(43, yPos); cout << temp->id << "   " << temp->courseName;
				yPos++;
				temp = temp->next;
			}
			yPos++;
			gotoXY(58, yPos); cout << "Back";
			yPos = 10;
			if (curPos == enrolledCourses.size) yPos++;
			gotoXY(78, curPos + yPos); cout << cursor;
			yPos = 10;
		}
		else {
			notifyBox("Empty List...");
			return;
		}
	} while (command(curPos, 0, enrolledCourses.size, registerCoursesOption));
}
void coursesReg() {
	const int width = 40;
	const int height = 10;
	const int left = 40;
	const int top = 8;

	int curPos = 0;
	int yPos = 10;
	getListCourses();
	do {
		hideCursor(true);
		schoolYearPath = "./data/" + currentSchoolYear;
		system("cls");
		drawBox(width, height, left, top);
		gotoXY(55, 5); cout << "HCMUS Portal";
		gotoXY(50, 7); cout << "Courses Registration";
		gotoXY(48, yPos); cout << "Register Courses";
		yPos++;
		gotoXY(48, yPos); cout << "View Enrolled Courses";
		yPos++;
		yPos++;
		gotoXY(48, yPos); cout << "Back";
		yPos = 10;
		if (curPos == 2) yPos++;
		gotoXY(73, curPos + yPos); cout << cursor;
		yPos = 10;
	} while (command(curPos, 0, 2, coursesRegOption));
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
	case 4:
		exit(0);
		break;
	}
	return 1;
}
int coursesRegOption(int curPos) {
	switch (curPos) {
	case 0:
		registerCourses();
		break;
	case 1:
		viewEnrolledCourses();
		break;
	case 2:
		return 0;
		break;
	case 3:
		setting();
		break;
	}
	return 1;
}

void saveEnrolledCourses() {
	ofstream fout(semesterPath + "/student/" + currentUser->id + ".dat", ios::binary);
	Course* temp = enrolledCourses.head;
	while (temp != NULL) {
		Course data = *temp;
		fout.write((char*)&data, sizeof(Course));
	}
	fout.close();
}
void getEnrolledCourses() {
	initList(enrolledCourses);
	saveEnrolledCourses();
}