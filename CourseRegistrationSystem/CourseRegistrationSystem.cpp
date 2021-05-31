#include "Globals.h" 

void inputInfo() {
	int no = 1;
	int yPos = 2;
	int xPos = 17;
	int width = 100;
	int height = 3;
	int left = xPos - 5;
	int top = yPos + 1;
	ListStudent listStudent;
	initList(listStudent);
	
	gotoXY(55, yPos); cout << "CLASS 20CTT3";
	yPos += 2;
	gotoXY(xPos, yPos); cout << "No |";
	gotoXY(xPos + 5, yPos); cout << "Student ID   |";
	gotoXY(xPos + 20, yPos); cout << "Last Name         |";
	gotoXY(xPos + 40, yPos); cout << "First Name   |";
	gotoXY(xPos + 55, yPos); cout << "Gender  |";
	gotoXY(xPos + 65, yPos); cout << "Date of Birth |";
	gotoXY(xPos + 81, yPos); cout << "Social ID";
	yPos++;
	while (no!=4) {
		Student* student = new Student;
		drawBox(width, height, left, top);
		string dateOfBirth;
		gotoXY(xPos, yPos); cout << no;
		gotoXY(xPos + 3, yPos); cout << "| "; getline(cin, student->studentID);
		gotoXY(xPos + 18, yPos); cout << "| "; getline(cin, student->lastName);
		gotoXY(xPos + 38, yPos); cout << "| "; getline(cin, student->firstName);
		gotoXY(xPos + 53, yPos); cout << "| "; getline(cin, student->gender);
		gotoXY(xPos + 63, yPos); cout << "| "; getline(cin, dateOfBirth);
		student->dateOfBirth = strToDate(dateOfBirth);
		gotoXY(xPos + 79, yPos); cout << "| "; getline(cin, student->socialID);
		student->prev = NULL;
		student->next = NULL;
		no++;
		yPos++;
		height++;
		clearLine(yPos);
		addStudent(listStudent, student);
		drawBox(width, height, left, top);
	}
}

void main() {
	//while (true) {
	//	getCurrentDate();
	//	getCurrentSchoolYear();
	//	loginSystem();
	//	if (currentUser->isStaff) {
	//		staffMenu();
	//	}
	//	else {
	//		studentMenu();
	//	}
	//	system("cls");
	//}
	inputInfo();
	_getch();
}