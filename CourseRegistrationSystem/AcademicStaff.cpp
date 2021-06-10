#include "AcademicStaff.h"

const char cursor = char(174);
string schoolYearPath;

int command(int&, int, int, function<int(int)>);
int staffOption(int);
int userAccountOption(int);
int profileOption(int);
int manageStudentOption(int);

void userAccount();
void Profile();
void manageStudent();
void setting();

void staffMenu() {
	const int width = 40;
	const int height = 10;
	const int left = 40;
	const int top = 8;

	int curPos = 0;
	int yPos = 9;
	do {
		hideCursor(true);
		getCurrentSchoolYear();
		schoolYearPath = "./Data/" + currentSchoolYear;
		system("cls");
		drawBox(width, height, left, top);
		gotoXY(55, yPos - 4); cout << "HCMUS Portal";
		gotoXY(40, yPos - 3); cout << currentDate.wDay;
		gotoXY(40, yPos - 2); cout << currentDate.day << '/' << currentDate.month << '/' << currentDate.year;
		gotoXY(75, yPos - 3); cout << "Welcome ";
		gotoXY(75, yPos - 2); cout << currentUser->lastName << " " << currentUser->firstName;
		gotoXY(48, yPos); cout << "User account" ;
		yPos++;
		gotoXY(48, yPos); cout << "Profile";
		yPos++;
		gotoXY(48, yPos); cout << "Manage student";
		yPos++;
		gotoXY(48, yPos); cout << "Setting";
		yPos++;
		yPos = 9;
		gotoXY(70, curPos + yPos); cout << cursor;
	} while (command(curPos, 0, 3, staffOption));
}

//User Account
void changePassword() {
	const int width = 40;
	const int height = 7;
	const int left = 40;
	const int top = 8;
	int curPos = 0;
	string currentPassword;

	hideCursor(false);
	do {
		system("cls");
		drawBox(width, height, left, top);
		gotoXY(48, 9); cout << "Your old password: ";
		getline(cin, currentPassword);
		if (currentPassword == currentUser->password) {
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
void userAccount() {
	const int width = 40;
	const int height = 10;
	const int left = 40;
	const int top = 8;

	int curPos = 0;
	int yPos = 9;
	do {
		system("cls");
		drawBox(width, height, left, top);
		gotoXY(55, yPos - 4); cout << "HCMUS Portal";
		gotoXY(55, yPos - 2); cout << "User Account";
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

//Profile
void Profile() {
	const int width = 40;
	const int height = 8;
	const int left = 40;
	const int top = 8;

	int curPos = 0;
	int yPos = 9;
	Date dateOfBirth = currentUser->dateOfBirth;
	do {
		system("cls");
		gotoXY(55, yPos - 4); cout << "HCMUS Portal";
		gotoXY(57, yPos - 2); cout << "Profile";
		drawBox(width, height, left, top);
		gotoXY(48, yPos); cout << "Last name: " << currentUser->lastName;
		yPos++;
		gotoXY(48, yPos); cout << "First name: " << currentUser->firstName;
		yPos++;
		gotoXY(48, yPos); cout << "Gender: " << currentUser->gender;
		yPos++;
		if (!currentUser->isStaff) {
			gotoXY(48, yPos); cout << "Class: " << currentUser->className;
			yPos++;
			gotoXY(48, yPos); cout << "Student ID: " << currentUser->id;
			yPos++;
		}
		else {
			gotoXY(48, yPos); cout << "Staff ID: " << currentUser->id;
			yPos++;
		}
		gotoXY(48, yPos); cout << "Date of Birth: " << dateOfBirth.day<<'/'<<dateOfBirth.month<<'/'<<dateOfBirth.year;
		yPos += 2;
		gotoXY(48, yPos); cout << "Back";
		gotoXY(70, curPos + yPos); cout << cursor;
		yPos = 9;
	} while (command(curPos, 0, 0, profileOption));

}

//Manage Student
string studentYear(int year) {
	string s;
	switch (year) {
	case 1:
		s = "first-year student";
		break;
	case 2:
		s = "second-year student";
		break;
	case 3:
		s = "third-year student";
		break;
	case 4:
		s = "final-year student";
		break;
	}
	return s;
}
Student* convertData(ifstream& data) {
	Student* newStudent = new Student;
	string s, dateOfBirth;
	getline(data, s, ',');
	if (s == "") return NULL;
	getline(data, newStudent->studentID, ',');
	getline(data, newStudent->lastName, ',');
	getline(data, newStudent->firstName, ',');
	getline(data, newStudent->gender, ',');
	getline(data, dateOfBirth, ',');
	newStudent->dateOfBirth = strToDate(dateOfBirth);
	getline(data, newStudent->socialID, '\n');
	newStudent->next = NULL;
	newStudent->prev = NULL;
	return newStudent;
}
User* toUser(Student* student, string className) {
	User* user = new User;
	user->id = student->studentID;
	user->password = student->socialID;
	user->lastName = student->lastName;
	user->firstName = student->firstName;
	user->className = className;
	user->gender = student->gender;
	user->dateOfBirth = student->dateOfBirth;
	user->isStaff = false;
	user->prev = NULL;
	user->next = NULL;
	return user;
}
void addStudentAccount(ListStudent listStudent) {
	Student* temp = listStudent.pHead;
	while (temp != NULL) {
		addUser(listUser, toUser(temp, listStudent.className));
		temp = temp->next;
	}
	saveListUser();
}
void writeToFile(ListStudent listStudent) {
	string path = "./Data/" + currentSchoolYear + "/Classes/" + 
		listStudent.program + "/"+ listStudent.year + "/" + listStudent.className + ".csv";
	saveClass(path, listStudent);
}
void inputData() {
	ListStudent listStudent;
	initList(listStudent);
	int year;
	int quantity;
	system("cls");
	hideCursor(false);
	int no = 1;
	int yPos = 2;
	int xPos = 17;
	int width = 40;
	int height = 8;
	int left = 40;
	int top = 9;

	drawBox(width, height, left, top);
	gotoXY(48, 12); cout << "(APCS/CLC/CTT/VP)";
	gotoXY(48, 11); cout << "Curriculum program: "; getline(cin, listStudent.program);
	gotoXY(48, 13); cout << "Year(1/2/3/4): "; cin >> year;
	cin.ignore();
	gotoXY(48, 14); cout << "Class: "; getline(cin, listStudent.className);
	gotoXY(48, 15); cout << "Quantity: "; cin >> quantity;
	cin.ignore();

	listStudent.year = studentYear(year);
	system("cls");
	width = 100;
	height = 3;
	left = xPos - 5;
	top = yPos + 1;
	gotoXY(55, yPos); cout << "CLASS " << listStudent.className;
	yPos += 2;
	gotoXY(xPos, yPos); cout << "No |";
	gotoXY(xPos + 5, yPos); cout << "Student ID   |";
	gotoXY(xPos + 20, yPos); cout << "Last Name         |";
	gotoXY(xPos + 40, yPos); cout << "First Name   |";
	gotoXY(xPos + 55, yPos); cout << "Gender  |";
	gotoXY(xPos + 65, yPos); cout << "Date of Birth |";
	gotoXY(xPos + 81, yPos); cout << "Social ID";
	yPos++;
	while (no <= quantity) {
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
	hideCursor(true);
	writeToFile(listStudent);
	addStudentAccount(listStudent);
}
void importData() {
	ListStudent listStudent;
	initList(listStudent);
	system("cls");
	hideCursor(false);
	int year;
	int no = 1;
	int yPos = 2;
	int xPos = 17;
	int width = 40;
	int height = 8;
	int left = 40;
	int top = 9;
	string dir = "./Data/Files Imported/";

	string temp;
	drawBox(width, height, left, top);
	gotoXY(48, 12); cout << "(APCS/CLC/CTT/VP)";
	gotoXY(48, 11); cout << "Curriculum program: "; getline(cin, listStudent.program);
	gotoXY(48, 13); cout << "Year(1/2/3/4): "; cin >> year;
	cin.ignore();
	gotoXY(48, 14); cout << "Class: "; getline(cin, listStudent.className);
	gotoXY(48, 15); cout << "Dir: Files Imported/"; getline(cin, temp);

	listStudent.year = studentYear(year);
	if (temp.find(".csv") == string::npos) {
		temp += ".csv";
	}
	loading("Importing...");
	dir += temp;
	ifstream fin(dir);
	if (!fin) {
		notifyBox("FILE NOT EXISTS");
		return;
	}
	string s = "";
	getline(fin, s);
	while (!fin.eof()) {
		addStudent(listStudent, convertData(fin));
	}
	hideCursor(true);
	writeToFile(listStudent);
	addStudentAccount(listStudent);
}
int createClassOption(int curPos) {
	switch (curPos) {
	case 0:
		inputData();
		break;
	case 1:
		importData();
		break;
	case 2:
		return 0;
		break;
	}
	return 1;
}
void createClasses() {
	if (!dirExists(schoolYearPath)) {
		notifyBox("Please create school year !");
		return;
	}
	const int width = 40;
	const int height = 8;
	const int left = 40;
	const int top = 8;

	int curPos = 0;
	int yPos = 9;
	do {
		system("cls");
		drawBox(width, height, left, top);
		gotoXY(55, yPos - 2); cout << "Create Classes";
		gotoXY(48, yPos); cout << "Input Class Data";
		yPos++;
		gotoXY(48, yPos); cout << "Import Class Data";
		yPos++;
		gotoXY(48, yPos); cout << "Back";
		yPos++;
		yPos = 9;
		gotoXY(70, curPos + yPos); cout << cursor;
		
	} while (command(curPos, 0, 2, createClassOption));
}
void createSchoolYear() {
	if (dirExists(schoolYearPath)) {
		notifyBox("Can not create new school year this time.");
	}
	else {
		loading("Creating...");
		notifyBox("New school year has been created");
	}
}
void manageStudent() {
	const int width = 40;
	const int height = 10;
	const int left = 40;
	const int top = 8;
	int curPos = 0;
	int yPos = 9;

	do {
		system("cls");
		drawBox(width, height, left, top);
		gotoXY(55, yPos - 4); cout << "HCMUS Portal";
		gotoXY(55, yPos - 2); cout << "Manage Student";
		gotoXY(48, yPos); cout << "Create school year";
		yPos++;
		gotoXY(48, yPos); cout << "Create classes";
		yPos++;
		gotoXY(48, yPos); cout << "Back";
		yPos++;
		yPos = 9;
		gotoXY(70, curPos + yPos); cout << cursor;
	} while (command(curPos, 0, 2, manageStudentOption));
}

//Setting
void setting() {
	system("cls");
	int width = 40;
	int height = 6;
	int left = 40;
	int top = 9;

	string date;
	hideCursor(false);
	drawBox(width, height, left, top);
	gotoXY(45, 11); cout << "Current Date: "; 
	cout << currentDate.day << '/' << currentDate.month << '/' << currentDate.year;
	gotoXY(45, 13); cout << "(dd/mm/YYYY)";
	gotoXY(45, 12); cout << "Change Date: "; getline(cin, date);
	currentDate = strToDate(date);
	hideCursor(true);
	system("cls");
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
int staffOption(int curPos) {
	switch (curPos) {
	case 0:
		userAccount();
		break;
	case 1:
		Profile();
		break;
	case 2:
		manageStudent();
		break;
	case 3:
		setting();
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
int profileOption(int curPos) {
	switch (curPos) {
	case 0:
		return 0;
		break;
	}
	return 1;
}
int manageStudentOption(int curPos) {
	switch (curPos) {
	case 0:
		createSchoolYear();
		break;
	case 1:
		createClasses();
		break;
	case 2:
		return 0;
		break;
	}
	return 1;
}