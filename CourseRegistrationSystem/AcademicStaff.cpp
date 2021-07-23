#include "AcademicStaff.h"

const char cursorLeft = char(175);
const char cursorRight = char(174);

void userAccount();
void Profile();
void manageStudent();
void manageCourses();
void setting();

int command(int&, int, int, function<int(int)>);
int staffOption(int);
int userAccountOption(int);
int generalOption(int);
int manageStudentOption(int);
int manageCoursesOption(int);

void staffMenu() {
	const int width = 40;
	const int height = 10;
	const int left = 40;
	const int top = 8;

	int curPos = 0;
	int yPos = 10;
	do {
		schoolYearPath = "./data/" + currentSchoolYear;
		hideCursor(true);
		system("cls");
		drawBox(width, height, left, top);
		gotoXY(55, 5); cout << "HCMUS Portal";
		gotoXY(40, 6); cout << currentDate.wDay;
		gotoXY(40, 7); cout << dateToStr(currentDate);
		gotoXY(75, 6); cout << "Welcome ";
		gotoXY(75, 7); cout << currentUser->lastName << " " << currentUser->firstName;
		gotoXY(52, yPos); cout << "User account" ;
		yPos++;
		gotoXY(52, yPos); cout << "Profile";
		yPos++;
		gotoXY(52, yPos); cout << "Manage student";
		yPos++;
		gotoXY(52, yPos); cout << "Manage courses";
		yPos++;
		gotoXY(52, yPos); cout << "Setting";
		yPos++;
		yPos++;
		gotoXY(52, yPos); cout << "Exit";
		yPos = 10;
		if (curPos == 5) yPos++;
		gotoXY(50, curPos + yPos); cout << cursorLeft;
		gotoXY(75, curPos + yPos); cout << cursorRight;
		yPos = 10;
	} while (command(curPos, 0, 5, staffOption));
}

//User Account
void changePassword() {
	const int width = 40;
	const int height = 7;
	const int left = 40;
	const int top = 8;
	int curPos = 0;
	int yPos = 10;
	string currentPassword;

	hideCursor(false);
	do {
		system("cls");
		gotoXY(55, 5); cout << "HCMUS Portal";
		gotoXY(53, 7); cout << "Change Password";
		drawBox(width, height, left, top);
		gotoXY(45, yPos); cout << "Current password: ";
		yPos++;
		yPos++;
		getline(cin, currentPassword);
		if (currentPassword == currentUser->password) {
			gotoXY(45, yPos); cout << "New password: ";
			yPos++;
			getline(cin, currentUser->password);
			notifyBox("Successful");
			hideCursor(true);
			saveListUser();
			return;
		}
		else {
			gotoXY(45, 11); cout << "Wrong password";
			gotoXY(45, 12); cout << "Enter to try again...";
			gotoXY(45, 13); cout << "Esc to back...";
			int key = _getch();
			if (key == 27) {
				hideCursor(true);
				return;
			}
		}
		yPos = 10;
	} while (true);
}
void logout() {
	currentUser = NULL;
}
void userAccount() {
	const int width = 40;
	const int height = 7;
	const int left = 40;
	const int top = 8;

	int curPos = 0;
	int yPos = 10;
	do {
		system("cls");
		drawBox(width, height, left, top);
		gotoXY(55, 5); cout << "HCMUS Portal";
		gotoXY(55, 7); cout << "User Account";
		gotoXY(52, yPos); cout << "Change Password";
		yPos++;
		gotoXY(52, yPos); cout << "Logout";
		yPos++;
		yPos++;
		gotoXY(52, yPos); cout << "Back";
		yPos = 10;
		if (curPos == 2) yPos++;
		gotoXY(50, curPos + yPos); cout << cursorLeft;
		gotoXY(70, curPos + yPos); cout << cursorRight;
		yPos = 10;
	} while (command(curPos, 0, 2, userAccountOption));
}

//Profile
void Profile() {
	const int width = 40;
	const int height = 10;
	const int left = 40;
	const int top = 8;

	int curPos = 0;
	int yPos = 10;
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
		gotoXY(60, yPos); cout << "Back";
		gotoXY(58, curPos + yPos); cout << cursorLeft;
		gotoXY(65, curPos + yPos); cout << cursorRight;
		yPos = 10;
	} while (command(curPos, 0, 0, generalOption));

}

//Manage Student
string studentYear(int year) {
	string s;
	switch (year) {
	case 1:
		s = "first-year classes";
		break;
	case 2:
		s = "second-year classes";
		break;
	case 3:
		s = "third-year classes";
		break;
	default:
		s = "final-year classes";
		break;
	}
	return s;
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
	user->academicYear = student->academicYear;
	user->isStaff = false;
	user->prev = NULL;
	user->next = NULL;
	return user;
}
void addStudentAccount(ListStudent listStudent) {
	Student* temp = listStudent.head;
	while (temp != NULL) {
		addUser(listUser, toUser(temp, listStudent.className));
		temp = temp->next;
	}
	saveListUser();
}
void saveListStudent(ListStudent listStudent) {
	string path = "./data/" + currentSchoolYear + "/classes/" + listStudent.year
		+ "/" + listStudent.program + "/" + listStudent.className + ".csv";
	saveClass(path, listStudent);
}
void inputClassData() {
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

	gotoXY(55, 5); cout << "HCMUS Portal";
	gotoXY(53, 7); cout << "Input Class Data";
	drawBox(width, height, left, top);
	gotoXY(48, 12); cout << "(APCS/CLC/CTT/VP)";
	gotoXY(48, 11); cout << "Curriculum program: "; getline(cin, listStudent.program);
	toUpper(listStudent.program);
	gotoXY(48, 13); cout << "Academic Year: "; cin >> listStudent.academicYear;
	cin.ignore();
	gotoXY(48, 14); cout << "Class: "; getline(cin, listStudent.className);
	gotoXY(48, 15); cout << "Number of students: "; cin >> quantity;
	cin.ignore();
	year = stoi(currentSchoolYear.substr(0, 4)) - listStudent.academicYear + 1;
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
		Student* newStudent = new Student;
		drawBox(width, height, left, top);
		string dateOfBirth;
		gotoXY(xPos, yPos); cout << no;
		gotoXY(xPos + 3, yPos); cout << "|                ";
		gotoXY(xPos + 5, yPos); getline(cin, newStudent->studentID);
		gotoXY(xPos + 18, yPos); cout << "|                "; 
		gotoXY(xPos + 20, yPos); getline(cin, newStudent->lastName);
		gotoXY(xPos + 38, yPos); cout << "|                ";
		gotoXY(xPos + 40, yPos); getline(cin, newStudent->firstName);
		gotoXY(xPos + 53, yPos); cout << "|                "; 
		gotoXY(xPos + 55, yPos); getline(cin, newStudent->gender);
		toupper(newStudent->gender[0]);
		gotoXY(xPos + 63, yPos); cout << "|                "; 
		gotoXY(xPos + 65, yPos); getline(cin, dateOfBirth);
		newStudent->dateOfBirth = strToDate(dateOfBirth);
		gotoXY(xPos + 79, yPos); cout << "|      "; 
		gotoXY(xPos + 81, yPos); getline(cin, newStudent->socialID);
		newStudent->academicYear = listStudent.academicYear;
		newStudent->prev = NULL;
		newStudent->next = NULL;
		no++;
		yPos++;
		height++;
		clearLine(yPos);
		addStudent(listStudent, newStudent);
		ofstream fout("./data/student/" + newStudent->studentID + "-overallGPA.dat");
		fout << -1;
		fout.close();
		drawBox(width, height, left, top);
	}
	hideCursor(true);
	saveListStudent(listStudent);
	addStudentAccount(listStudent);
	loading("Creating...");
	notifyBox("Created new class");
}
void importClassData() {
	ListStudent listStudent;
	initList(listStudent);
	system("cls");
	hideCursor(false);
	int year;
	int no = 1;
	int yPos = 2;
	int xPos = 17;
	int width = 50;
	int height = 8;
	int left = 35;
	int top = 9;
	string dir = "./data/importFiles/classes/";

	string temp;
	gotoXY(55, 5); cout << "HCMUS Portal";
	gotoXY(52, 7); cout << "Import Class Data";
	drawBox(width, height, left, top);
	gotoXY(38, 12); cout << "(APCS/CLC/CTT/VP)";
	gotoXY(38, 11); cout << "Curriculum program: "; getline(cin, listStudent.program);
	gotoXY(38, 13); cout << "Academic Year: "; cin >> listStudent.academicYear;
	cin.ignore();
	gotoXY(38, 14); cout << "Class: "; getline(cin, listStudent.className);
	gotoXY(38, 15); cout << "Dir: " + dir; getline(cin, temp);

	year = stoi(currentSchoolYear.substr(0, 4)) - listStudent.academicYear + 1;
	listStudent.year = studentYear(year);
	if (temp.find(".csv") == string::npos) {
		temp += ".csv";
	}
	dir += temp;
	ifstream fin(dir);
	if (!fin) {
		notifyBox("FILE NOT EXISTS");
		return;
	}
	string s = "";
	getline(fin, s);
	while (!fin.eof()) {
		Student* newStudent = convertStudentData(fin);
		if (newStudent != NULL) {
			newStudent->academicYear = listStudent.academicYear;
			addStudent(listStudent, newStudent);
			ofstream fout("./data/student/" + newStudent->studentID + "-overallGPA.dat");
			fout << -1;
			fout.close();
		}
	}
	hideCursor(true);
	saveListStudent(listStudent);
	addStudentAccount(listStudent);
	loading("Importing...");
	notifyBox("Created new class");
}
int createClassOption(int curPos) {
	switch (curPos) {
	case 0:
		inputClassData();
		break;
	case 1:
		importClassData();
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
	int yPos = 10;
	do {
		system("cls");
		drawBox(width, height, left, top);
		gotoXY(55, 5); cout << "HCMUS Portal";
		gotoXY(55, 7); cout << "Create Classes";
		gotoXY(52, yPos); cout << "Input Class Data";
		yPos++;
		gotoXY(52, yPos); cout << "Import Class Data File";
		yPos++;
		gotoXY(52, yPos); cout << "Back";
		yPos++;
		yPos = 10;
		gotoXY(50, curPos + yPos); cout << cursorLeft;
		gotoXY(76, curPos + yPos); cout << cursorRight;

	} while (command(curPos, 0, 2, createClassOption));
}
void newSchoolYear() {
	int lastYear = stoi(currentSchoolYear.substr(0, 4));
	string prevSchoolYearPath = "./data/" + to_string(lastYear - 1) + "-" + to_string(lastYear);
	string classesPath = schoolYearPath + "/classes";
	ofstream fout("./data/schoolyear.dat");
	fout << currentSchoolYear << endl;
	fout << dateToStr(currentDate) << endl;
	fout << "9/" + to_string(lastYear + 1);
	fout.close();
	if (dirExists(prevSchoolYearPath)) {
		fs::create_directories(classesPath);
		ofstream(schoolYearPath + "/semester.dat");
		prevSchoolYearPath += "/classes";
		copyFolder(prevSchoolYearPath, classesPath);
		fs::remove_all(classesPath + "/final-year classes");
		fs::rename(classesPath + "/third-year classes", classesPath + "/final-year classes");
		fs::rename(classesPath + "/second-year classes", classesPath + "/third-year classes");
		fs::rename(classesPath + "/first-year classes", classesPath + "/second-year classes");
		fs::create_directories(classesPath + "/first-year classes/APCS");
		fs::create_directories(classesPath + "/first-year classes/CTT");
		fs::create_directories(classesPath + "/first-year classes/CLC");
		fs::create_directories(classesPath + "/first-year classes/VP");
	}
	else {
		ofstream(schoolYearPath + "/semester.dat");
		fs::create_directories(classesPath + "/first-year classes/APCS");
		fs::create_directories(classesPath + "/first-year classes/CTT");
		fs::create_directories(classesPath + "/first-year classes/CLC");
		fs::create_directories(classesPath + "/first-year classes/VP");
		fs::create_directories(classesPath + "/second-year classes/APCS");
		fs::create_directories(classesPath + "/second-year classes/CTT");
		fs::create_directories(classesPath + "/second-year classes/CLC");
		fs::create_directories(classesPath + "/second-year classes/VP");
		fs::create_directories(classesPath + "/third-year classes/APCS");
		fs::create_directories(classesPath + "/third-year classes/CTT");
		fs::create_directories(classesPath + "/third-year classes/CLC");
		fs::create_directories(classesPath + "/third-year classes/VP");
		fs::create_directories(classesPath + "/final-year classes/APCS");
		fs::create_directories(classesPath + "/final-year classes/CTT");
		fs::create_directories(classesPath + "/final-year classes/CLC");
		fs::create_directories(classesPath + "/final-year classes/VP");
	}
}
void createSchoolYear() {
	if (dirExists(schoolYearPath)) {
		notifyBox("Can not create new school year this time.");
	}
	else {
		newSchoolYear();
		loading("Creating...");
		notifyBox("New school year has been created");
	}
}
void schoolYearInfo() {
	int width = 40;
	int height = 8;
	int left = 40;
	int top = 8;
	int curPos = 0;
	int yPos = 10;

	do {
		system("cls");
		drawBox(width, height, left, top);
		gotoXY(55, 5); cout << "HCMUS Portal";
		textAlignCenter("School Year Infomation", left, width, 7);
		ifstream fin("./data/schoolyear.dat");
		string s;
		getline(fin, s);
		gotoXY(48, yPos); cout << "School Year " << s;
		yPos++;
		getline(fin, s);
		gotoXY(48, yPos); cout << "Start date: " << s;
		yPos++;
		getline(fin, s);
		gotoXY(48, yPos); cout << "End date: " << s;
		yPos += 2;
		gotoXY(59, yPos); cout << "Back";
		gotoXY(57, curPos + yPos); cout << cursorLeft;
		gotoXY(64, curPos + yPos); cout << cursorRight;
		yPos = 10;
	} while (command(curPos, 0, 0, generalOption));

}
void manageStudent() {
	const int width = 40;
	const int height = 11;
	const int left = 40;
	const int top = 8;
	int curPos = 0;
	int yPos = 10;

	do {
		system("cls");
		drawBox(width, height, left, top);
		gotoXY(55, 5); cout << "HCMUS Portal";
		gotoXY(55, 7); cout << "Manage Student";
		if (dirExists(schoolYearPath)) {
			gotoXY(52, yPos); cout << "School Year Infomation";
			yPos++;
		}
		else {
			gotoXY(52, yPos); cout << "Create School Year";
			yPos++;
		}
		gotoXY(52, yPos); cout << "Create Classes";
		yPos++;
		gotoXY(52, yPos); cout << "List Of Classes";
		yPos++;
		yPos++;
		gotoXY(52, yPos); cout << "Back";
		yPos = 10;
		if (curPos == 3) yPos++;
		gotoXY(50, curPos + yPos); cout << cursorLeft;
		gotoXY(75, curPos + yPos); cout << cursorRight;
		yPos = 10;
	} while (command(curPos, 0, 3, manageStudentOption));
}
//Scoreboard In Class
ListStudent getListOfStudentScoreboard(Course* course);
ListStudent getListOfStudentInClass(Class* c);
void viewEnrolledCourseScore(Student* s) {
	const int width = 50;
	int height = 10;
	const int left = 35;
	const int top = 8;
	int curPos = 0;
	int yPos = 13;
	int no = 0;
	
	getEnrolledCourses(s);
	ListStudent list;
	do {
		system("cls");
		gotoXY(55, 5); cout << "HCMUS Portal";
		gotoXY(56, 7); cout << "Scoreboard";
		textAlignCenter(s->lastName + " " + s->firstName , left, width, 9);
		gotoXY(38, 11); cout << "No";
		gotoXY(42, 11); cout << "ID";
		gotoXY(52, 11); cout << "Course name";
		gotoXY(75, 11); cout << "Final Mark";
		if (s->enrolledCourses.head != NULL) {
			Course* course = s->enrolledCourses.head;
			while (course != NULL) {
				list = getListOfStudentScoreboard(course);
				Student* temp = list.head;
				while (temp != NULL) {
					if (temp->studentID == s->studentID) break;
					temp = temp->next;
				}
				no++;
				gotoXY(38, yPos); cout << no;
				gotoXY(42, yPos); cout << course->id;
				string courseName;
				if (course->courseName.length() > 23) courseName = course->courseName.substr(0, 23);
				else courseName = course->courseName;
				gotoXY(52, yPos); cout << courseName;
				float totalMark;
				if (temp == NULL) totalMark = 0;
				else totalMark = temp->courseMark.totalMark;
				gotoXY(75, yPos); cout << totalMark;
				yPos++;
				course = course->next;
			}
			drawBox(width, height, left, top);
			yPos++;
			gotoXY(59, yPos); cout << "Back";
			gotoXY(57, yPos); cout << cursorLeft;
			gotoXY(64, yPos); cout << cursorRight;
			yPos = 13;
		}
		else {
			notifyBox("Empty List...");
			return;
		}
	} while (command(curPos, 0, 0, generalOption));
}
int viewStudentScoreboardCommand(int& curPos, int minPos, int maxPos, ListStudent list,
	int& page, int numberPages, function<int(int, int, ListStudent)> option) {
	int key = _getch();
	switch (key) {
	case 13:
		return option(curPos, page, list);
	case 224:
		key = _getch();
		switch (key) {
		case 72://up key
			if (curPos > minPos) curPos--;
			else {
				curPos = maxPos;
			}
			break;
		case 80://down key
			if (curPos < maxPos) curPos++;
			else {
				curPos = minPos;
			}
			break;
		case 75://left key
			if (page > 1) {
				page--;
				curPos = 0;
			}
			break;
		case 77://right key
			if (page < numberPages) {
				page++;
				curPos = 0;
			}
			break;
		}
	}
	return 1;
}
int viewStudentScoreboardOption(int curPos, int page, ListStudent list) {
	int count = 0;

	Student* temp = list.head;
	for (int i = 0; i < (page - 1) * 10; i++) {
		temp = temp->next;
	}
	Student* studentSelected = NULL;
	while (count < 10 && temp != NULL) {
		if (count == curPos) {
			studentSelected = temp;
			break;
		}
		count++;
		temp = temp->next;
	}
	if (studentSelected == NULL) {
		return 0;
	}
	else {
		viewEnrolledCourseScore(studentSelected);
	}
	return 1;
}
void viewScoreboard(Class* c) {
	const int width = 60;
	int height = 10;
	const int left = 30;
	const int top = 8;
	int curPos = 0;
	int yPos = 14;
	int numberPages;
	int page = 1;
	int i = 0;
	int no;
	ListStudent list = getListOfStudentInClass(c);
	do {
		numberPages = (list.size / 10) + 1;
		i = 0;
		height = 10;
		system("cls");
		gotoXY(55, 5); cout << "HCMUS Portal";
		gotoXY(56, 7); cout << "Scoreboard";
		textAlignCenter(c->className, left, width, 9);
		gotoXY(33, 11); cout << "No";
		gotoXY(37, 11); cout << "ID";
		gotoXY(47, 11); cout << "Full name";
		gotoXY(77, 11); cout << "GPA";
		gotoXY(82, 11); cout << "Overall";
		gotoXY(82, 12); cout << "GPA";
		if (list.head != NULL) {
			Student* temp = list.head;
			for (int i = 0; i < (page - 1) * 10; i++) {
				temp = temp->next;
			}
			while (i < 10 && temp != NULL) {
				getEnrolledCourses(temp);
				calcGPA(temp);
				no = (page - 1) * 10 + i + 1;
				gotoXY(33, yPos); cout << no;
				gotoXY(37, yPos); cout << temp->studentID;
				string fullName = temp->lastName + " " + temp->firstName;
				if (fullName.length() > 30) fullName = fullName.substr(0, 30);
				gotoXY(47, yPos); cout << fullName;
				gotoXY(77, yPos); cout << temp->semesterMark.GPA;
				gotoXY(82, yPos); cout << temp->semesterMark.overallGPA;
				yPos++;
				i++;
				temp = temp->next;
			}
			height += i;
			drawBox(width, height, left, top);
			yPos++;
			gotoXY(58, yPos);
			if (page > 1) cout << char(174);
			cout << char(174) << "  " << page << "  " << char(175);
			if (page < numberPages) cout << char(175);
			yPos++;
			gotoXY(59, yPos); cout << "Back";
			yPos = 14;
			if (curPos == i) {
				yPos += 2;
				gotoXY(57, curPos + yPos); cout << cursorLeft;
				gotoXY(64, curPos + yPos); cout << cursorRight;
			}
			else {
				gotoXY(31, curPos + yPos); cout << cursorLeft;
				gotoXY(90, curPos + yPos); cout << cursorRight;
			}
			yPos = 14;
		}
		else {
			notifyBox("Empty List...");
			return;
		}
	} while (viewStudentScoreboardCommand(curPos, 0, i, list, page, numberPages, viewStudentScoreboardOption));
}

//Manage Courses
//Create new semester, Courses registration session
void newSemester(string semesterFolder, int semester, string startDate, string endDate) {

	if (dirExists(schoolYearPath + "/" + semesterFolder)) {
		notifyBox(semesterFolder + " is exists!");
	}
	else if (!isExpired(currentDate, currentSemester.endDate)) {
		notifyBox(semesterFolder + " has not finished yet!");
	}
	else {
		ofstream fout(schoolYearPath + "/semester.dat");
		loading("Creating...");
		fs::create_directories(schoolYearPath + "/" + semesterFolder + "/student");
		fs::create_directories(schoolYearPath + "/" + semesterFolder + "/courses");
		fout << semester << '\n' << startDate << '\n' << endDate;
		notifyBox("Created new semester.");
	}
}
void createSemester() {
	int width = 40;
	int height = 8;
	int left = 40;
	int top = 8;

	system("cls");
	int semester;
	string startDate, endDate;
	hideCursor(false);
	gotoXY(55, 5); cout << "HCMUS Portal";
	gotoXY(55, 7); cout << "Create Semester";
	drawBox(width, height, left, top);
	gotoXY(48, 11); cout << "Semester(1/2/3): "; cin >> semester;
	gotoXY(48, 12); cout << "Start date: "; cin >> startDate;
	gotoXY(48, 13); cout << "End date: "; cin >> endDate;
	string semesterFolder = "semester " + to_string(semester);
	newSemester(semesterFolder, semester, startDate, endDate);
	getCurrentSemester();
	hideCursor(true);
}
int semesterInfoOption(int curPos) {
	switch (curPos) {
	case 0:
		return 0;
		break;
	}
	return 1;
}
void semesterInfo() {
	int width = 40;
	int height = 8;
	int left = 40;
	int top = 8;
	int curPos = 0;
	int yPos = 10;

	do {
		system("cls");
		drawBox(width, height, left, top);
		gotoXY(55, 5); cout << "HCMUS Portal";
		gotoXY(52, 7); cout << "Semester Infomation";
		gotoXY(48, yPos); cout << "Semester " << currentSemester.semester;
		yPos++;
		gotoXY(48, yPos); cout << "Start date: " << dateToStr(currentSemester.startDate);
		yPos++;
		gotoXY(48, yPos); cout << "End date: " << dateToStr(currentSemester.endDate);
		yPos += 2;
		gotoXY(59, yPos); cout << "Back";
		gotoXY(57, curPos + yPos); cout << cursorLeft;
		gotoXY(64, curPos + yPos); cout << cursorRight;
		yPos = 10;
	} while (command(curPos, 0, 0, semesterInfoOption));

}
void modifyCourseReg() {
	const int width = 40;
	const int height = 7;
	const int left = 40;
	const int top = 8;

	system("cls");

	string startDate, endDate;
	hideCursor(false);
	gotoXY(55, 5); cout << "HCMUS Portal";
	gotoXY(50, 7); cout << "Modify Course Registraion";
	drawBox(width, height, left, top);
	gotoXY(48, 10); cout << "Current registration session: ";
	gotoXY(48, 11); cout << dateToStr(listCourses.startDate) << " - " << dateToStr(listCourses.endDate);
	gotoXY(48, 12); cout << "Start date: ";
	gotoXY(48, 13); cout << "End date: ";
	gotoXY(60, 12); cin >> startDate;
	gotoXY(58, 13); cin >> endDate;
	listCourses.startDate = strToDate(startDate);
	listCourses.endDate = strToDate(endDate);
	saveCourses();
	hideCursor(true);
}
void createCourseReg() {
	const int width = 40;
	const int height = 6;
	const int left = 40;
	const int top = 8;

	system("cls");

	string startDate, endDate;
	hideCursor(false);
	gotoXY(55, 5); cout << "HCMUS Portal";
	gotoXY(50, 7); cout << "Create Course Registraion";
	drawBox(width, height, left, top);
	gotoXY(48, 10); cout << "Start date: ";
	gotoXY(48, 12); cout << "End date: ";
	gotoXY(60, 10); cin >> startDate;
	gotoXY(58, 12); cin >> endDate;
	listCourses.startDate = strToDate(startDate);
	listCourses.endDate = strToDate(endDate);
	saveCourses();
	hideCursor(true);
}
//Scoreboard In Course
ListStudent getListOfStudentInCourse(Course* c);
void exportListStudentInCourse(Course* course) {
	ListStudent list = getListOfStudentInCourse(course);
	if (list.head == NULL) {
		notifyBox("Empty List...");
		return;
	}
	ofstream fout("./data/exportFiles/scoreboard/" + course->id + "-scoreboard.csv");
	fout << "No,Student Id,Full name,Other mark,Midterm mark,Final mark,Total mark" << endl;
	int no = 1;
	Student* temp = list.head;
	while (temp != NULL) {
		fout << no << "," << temp->studentID << "," << temp->lastName << " " << temp->firstName
			<< "," << "," << "," << "," << endl;
		temp = temp->next;
		no++;
	}
	fout.close();
}
void importScoreboard(Course* course) {
	string src = "./data/importFiles/scoreboard/" + course->id + "-scoreboard.csv";
	ifstream fin(src);
	if (fin.fail()) notifyBox("The scoreboard of course does not exist");
	else {
		string dest = "./data/" + currentSchoolYear + "/semester " +
			to_string(currentSemester.semester) + "/courses/" + course->id + "-scoreboard.dat";
		fs::copy(src, dest);
	}
	fin.close();
}
Student* getScoreboard(ifstream& data) {
	string s;
	Student* newStudent = new Student;
	getline(data, s, ',');
	if (s == "") return NULL;
	getline(data, newStudent->studentID, ',');
	string fullName;
	getline(data, fullName, ',');
	newStudent->lastName = fullName.substr(0, fullName.find_last_of(' '));
	newStudent->firstName = fullName.substr(fullName.find_last_of(' ') + 1);
	CourseMark courseMark;
	string mark;
	getline(data, mark, ',');
	if (mark == "") {
		getline(data, mark, '\n');
	}
	else {
		courseMark.otherMark = stof(mark);
		getline(data, mark, ',');
		courseMark.midtermMark = stof(mark);
		getline(data, mark, ',');
		courseMark.finalMark = stof(mark);
		getline(data, mark, '\n');
		courseMark.totalMark = stof(mark);
	}
	newStudent->courseMark = courseMark;
	newStudent->prev = NULL;
	newStudent->next = NULL;
	return newStudent;
}
ListStudent getListOfStudentScoreboard(Course* course) {
	ListStudent list;
	initList(list);
	ifstream fin("./data/" + currentSchoolYear + "/semester " +
		to_string(currentSemester.semester) + "/courses/" + course->id + "-scoreboard.dat");
	if (fin.fail()) {
		return list;
	}
	string s;
	getline(fin, s);
	while (!fin.eof()) {
		addStudent(list, getScoreboard(fin));
	}
	fin.close();
	return list;
}
void saveScoreboard(ListStudent list, Course course) {
	ofstream fout("./data/" + currentSchoolYear + "/semester " 
		+ to_string(currentSemester.semester) + "/courses/" + course.id + "-scoreboard.dat");
	fout << "No,Student Id,Full name,Other mark,Midterm mark,Final mark,Total mark" << endl;
	int no = 1;
	Student* temp = list.head;
	while (temp != NULL) {
		fout << no << "," << temp->studentID << "," << temp->lastName << " " << temp->firstName
			<< "," << temp->courseMark.otherMark << "," << temp->courseMark.midtermMark << "," 
			<< temp->courseMark.finalMark << ","  << temp->courseMark.totalMark << endl;
		temp = temp->next;
		no++;
	}
	fout.close();
}
void updateStudentResult(Student* student) {
	const int width = 30;
	int height = 8;
	const int left = 45;
	const int top = 8;
	int curPos = 0;

	hideCursor(false);
	system("cls");
	textAlignCenter("HCMUS Portal", left, width, 5);
	textAlignCenter("Update Student Result", left, width, 7);
	drawBox(width, height, left, top);
	textAlignCenter(student->lastName + " " + student->firstName, left, width, 9);
	gotoXY(50, 11); cout << "Other Mark: "; cin >> student->courseMark.otherMark;
	gotoXY(50, 12); cout << "Midterm Mark: "; cin >> student->courseMark.midtermMark;
	gotoXY(50, 13); cout << "Final Mark: "; cin >> student->courseMark.finalMark;
	gotoXY(50, 14); cout << "Total Mark: "; cin >> student->courseMark.totalMark;
	hideCursor(true);
}
int viewScoreboardCommand(int& curPos, int minPos, int maxPos, ListStudent list, Course course,
	int& page, int numberPages, function<int(int, int, ListStudent, Course)> option) {
	int key = _getch();
	switch (key) {
	case 13:
		return option(curPos, page, list, course);
	case 224:
		key = _getch();
		switch (key) {
		case 72://up key
			if (curPos > minPos) curPos--;
			else {
				curPos = maxPos;
			}
			break;
		case 80://down key
			if (curPos < maxPos) curPos++;
			else {
				curPos = minPos;
			}
			break;
		case 75://left key
			if (page > 1) {
				page--;
				curPos = 0;
			}
			break;
		case 77://right key
			if (page < numberPages) {
				page++;
				curPos = 0;
			}
			break;
		}
	}
	return 1;
}
int viewScoreboardOption(int curPos, int page, ListStudent list, Course course) {
	int count = 0;

	Student* temp = list.head;
	for (int i = 0; i < (page - 1) * 10; i++) {
		temp = temp->next;
	}
	Student* studentSelected = NULL;
	while (count < 10 && temp != NULL) {
		if (count == curPos) {
			studentSelected = temp;
			break;
		}
		count++;
		temp = temp->next;
	}
	if (studentSelected == NULL) {
		int n = count - curPos;
		switch (n) {
		case 0:
			loading("Saving...");
			saveScoreboard(list, course);
			return 0;
		}
		return 0;
	}
	else {
		updateStudentResult(studentSelected);
	}
	return 1;
}
void viewScoreboard(Course* course) {
	const int width = 64;
	int height = 10;
	const int left = 28;
	const int top = 8;
	int curPos = 0;
	int yPos = 13;
	int numberPages;
	int page = 1;
	int i = 0;
	int no;
	ListStudent list = getListOfStudentScoreboard(course);
	do {
		numberPages = (list.size / 10) + 1;
		i = 0;
		height = 10;
		system("cls");
		gotoXY(55, 5); cout << "HCMUS Portal";
		gotoXY(56, 7); cout << "Scoreboard";
		textAlignCenter(course->courseName, left, width, 9);
		gotoXY(31, 11); cout << "No";
		gotoXY(36, 11); cout << "ID";
		gotoXY(45, 11); cout << "Full name";
		gotoXY(63, 11); cout << "Other";
		gotoXY(70, 11); cout << "Midterm";
		gotoXY(79, 11); cout << "Final";
		gotoXY(86, 11); cout << "Total";
		if (list.head != NULL) {
			Student* temp = list.head;
			for (int i = 0; i < (page - 1) * 10; i++) {
				temp = temp->next;
			}
			while (i < 10 && temp != NULL) {
				no = (page - 1) * 10 + i + 1;
				gotoXY(31, yPos); cout << no;
				gotoXY(36, yPos); cout << temp->studentID;
				string fullName = temp->lastName + " " + temp->firstName;
				if (fullName.length() > 27) fullName = fullName.substr(0, 27);
				gotoXY(45, yPos); cout << fullName;
				gotoXY(63, yPos); cout << temp->courseMark.otherMark;
				gotoXY(70, yPos); cout << temp->courseMark.midtermMark;
				gotoXY(79, yPos); cout << temp->courseMark.finalMark;
				gotoXY(86, yPos); cout << temp->courseMark.totalMark;
				yPos++;
				i++;
				temp = temp->next;
			}
			height += i;
			drawBox(width, height, left, top);
			yPos++;
			gotoXY(58, yPos);
			if (page > 1) cout << char(174);
			cout << char(174) << "  " << page << "  " << char(175);
			if (page < numberPages) cout << char(175);
			yPos++; 
			gotoXY(59, yPos); cout << "Save";
			yPos++;
			gotoXY(59, yPos); cout << "Back";
			yPos = 13;
			if (curPos == i || curPos == i + 1) {
				yPos += 2;
				gotoXY(57, curPos + yPos); cout << cursorLeft;
				gotoXY(64, curPos + yPos); cout << cursorRight;
			}
			else {
				gotoXY(29, curPos + yPos); cout << cursorLeft;
				gotoXY(92, curPos + yPos); cout << cursorRight;
			}
			yPos = 13;
		}
		else {
			notifyBox("Empty List...");
			return;
		}
	} while (viewScoreboardCommand(curPos, 0, i + 1, list, *course, page, numberPages, viewScoreboardOption));
}

//Update list of courses
void viewListOfStudent(Course* c);
int updateCourseCommand(int& curPos, int minPos, int maxPos, Course* course, function<int(int, Course*)> option) {
	int key = _getch();
	switch (key) {
	case 13:
		return option(curPos, course);
	case 224:
		key = _getch();
		switch (key) {
		case 72:
			if (curPos > minPos) curPos--;
			else {
				curPos = maxPos;
			}
			break;
		case 80:
			if (curPos < maxPos) curPos++;
			else {
				curPos = minPos;
			}
			break;
		}
	}
	return 1;
}
void courseDetail(Course* course) {
	const int width = 40;
	const int height = 14;
	const int left = 40;
	const int top = 8;
	int curPos = 0;
	int yPos = 10;

	do {
		system("cls");
		gotoXY(55, 5); cout << "HCMUS Portal";
		gotoXY(55, 7); cout << "View Course";
		drawBox(width, height, left, top);
		alignRow(45, yPos, "Course ID: " + course->id, 32);
		alignRow(45, yPos, "Course name: " + course->courseName, 32);
		alignRow(45, yPos, "Teacher name: " + course->teacherName, 32);
		alignRow(45, yPos, "Academic year: " + to_string(course->academicYear), 32);
		alignRow(45, yPos, "Credits: " + to_string(course->credits), 32);
		alignRow(45, yPos, "Number of student: " + to_string(course->maxStudents), 32);
		alignRow(45, yPos, "Weekday: " + course->wDay, 32);
		alignRow(45, yPos, "Session: " + course->session[0] + "-" + course->session[1], 32);
		yPos++;
		gotoXY(60, yPos); cout << "Back";
		gotoXY(58, yPos + curPos); cout << cursorLeft;
		gotoXY(65, curPos + yPos); cout << cursorRight;
		yPos = 10;
	} while (command(curPos, 0, 0, generalOption));

}
void modifyCourse(Course* course) {
	const int width = 40;
	const int height = 10;
	const int left = 40;
	const int top = 8;

	system("cls");
	string session;
	string id = course->id;
	gotoXY(55, 5); cout << "HCMUS Portal";
	gotoXY(55, 7); cout << "Modify Course";
	drawBox(width, height, left, top);
	hideCursor(false);
	gotoXY(45, 10); cout << "Course ID: ";
	gotoXY(45, 11); cout << "Course name:";
	gotoXY(45, 12); cout << "Teacher name: ";
	gotoXY(45, 13); cout << "Number of credits: ";
	gotoXY(45, 14); cout << "Maximum nums of student: ";
	gotoXY(45, 15); cout << "Weekday: ";
	gotoXY(45, 16); cout << "Session (S1,S2,S3,S4): ";

	gotoXY(56, 10); getline(cin, course->id);
	gotoXY(58, 11); getline(cin, course->courseName);
	gotoXY(59, 12); getline(cin, course->teacherName);
	gotoXY(64, 13); cin >> course->credits;
	gotoXY(70, 14); cin >> course->maxStudents;
	cin.ignore();
	gotoXY(54, 15); getline(cin, course->wDay);
	toUpper(course->wDay);
	gotoXY(68, 16); getline(cin, session);
	toUpper(session);
	course->session[0] = session.substr(session.find('S'), 2);
	session.erase(session.find('S'), 2);
	course->session[1] = session.substr(session.find('S'), 2);
	hideCursor(true);
	fs::rename(schoolYearPath + "/semester " + to_string(currentSemester.semester)
		+ "/courses/" + id + ".dat",
		schoolYearPath + "/semester " + to_string(currentSemester.semester)
		+ "/courses/" + course->id + ".dat");
	saveCourses();
}
void removeCourse(Course* course) {
	fs::remove("./data/" + currentSchoolYear + "/semester " +
		to_string(currentSemester.semester) + "/courses/" + course->id + ".dat");
	removeCourse(listCourses, course);
}
int updateCourseOption(int curPos, Course* course) {
	switch (curPos)
	{
	case 0:
		courseDetail(course);
		return 1;
		break;
	case 1:
		modifyCourse(course);
		if (!confirmBox()) return 1;
		break;
	case 2:
		if (confirmBox()) removeCourse(course);
		else return 1;
		break;
	case 3:
		viewListOfStudent(course);
		return 1;
		break;
	case 4:
		loading("Exporting...");
		exportListStudentInCourse(course);
		return 1;
		break;
	case 5:
		loading("Importing...");
		importScoreboard(course);
		return 1;
		break;
	case 6:
		viewScoreboard(course);
		return 1;
		break;
	case 7:
		break;
	}
	saveCourses();
	return 0;
}
void updateCourse(Course* course) {
	const int width = 30;
	const int height = 12;
	const int left = 45;
	const int top = 8;
	int curPos = 0;
	int yPos = 10;

	do {
		system("cls");
		gotoXY(55, 5); cout << "HCMUS Portal";
		gotoXY(55, 7); cout << "Update Course";
		drawBox(width, height, left, top);
		gotoXY(58, yPos); cout << "Detail";
		yPos++;
		gotoXY(58, yPos); cout << "Modify";
		yPos++;
		gotoXY(58, yPos); cout << "Delete";
		yPos++;
		textAlignCenter("List Of Student", 45, 30, yPos);
		yPos++;
		textAlignCenter("Export List Of Student", 45, 30, yPos);
		yPos++;
		textAlignCenter("Import Scoreboard", 45, 30, yPos);
		yPos++;
		textAlignCenter("View Scoreboard", 45, 30, yPos);
		yPos++;
		yPos++;
		gotoXY(58, yPos); cout << "Back";
		yPos = 10;
		if (curPos == 7) yPos++;
		if (curPos < 3 || curPos == 7) {
			gotoXY(56, curPos + yPos); cout << cursorLeft;
			gotoXY(65, curPos + yPos); cout << cursorRight;
		}
		else {
			gotoXY(48, curPos + yPos); cout << cursorLeft;
			gotoXY(73, curPos + yPos); cout << cursorRight;
		}
		yPos = 10;
	} while (updateCourseCommand(curPos, 0, 7, course, updateCourseOption));

	saveCourses();
}
//Input Courses
void inputCoursesData() {
	int width = 40;
	int height = 8;
	int left = 40;
	int top = 8;
	int no = 1;
	int yPos = 2;
	int xPos = 7;

	system("cls");
	gotoXY(55, 5); cout << "HCMUS Portal";
	gotoXY(52, 7); cout << "Input Courses Data";
	drawBox(width, height, left, top);
	int num;
	hideCursor(false);
	gotoXY(48, 11); cout << "Number of courses: "; cin >> num;
	cin.ignore();

	system("cls");
	width = 115;
	height = 4;
	left = xPos - 5;
	top = yPos + 1;
	gotoXY(53, yPos); cout << "ADD COURSES";
	yPos += 2;
	gotoXY(xPos, yPos); cout << "No |";
	gotoXY(xPos, yPos + 1); cout << "   |";
	gotoXY(xPos + 5, yPos); cout << "Course   |";
	gotoXY(xPos + 5, yPos + 1); cout << "ID       |";
	gotoXY(xPos + 16, yPos); cout << "Course name        |";
	gotoXY(xPos + 16, yPos + 1); cout << "                   |";
	gotoXY(xPos + 37, yPos); cout << "Teacher name        |";
	gotoXY(xPos + 37, yPos + 1); cout << "                    |";
	gotoXY(xPos + 59, yPos); cout << "Academic |";
	gotoXY(xPos + 59, yPos + 1); cout << "Year     | ";
	gotoXY(xPos + 70, yPos); cout << "Credits |";
	gotoXY(xPos + 70, yPos + 1); cout << "        |";
	gotoXY(xPos + 80, yPos); cout << "Number of |";
	gotoXY(xPos + 80, yPos + 1); cout << "students  |";
	gotoXY(xPos + 92, yPos); cout << "Weekday |";
	gotoXY(xPos + 92, yPos + 1); cout << "        |";
	gotoXY(xPos + 102, yPos); cout << "Session";
	yPos += 2;
	while (no <= num) {
		Course* newCourse = new Course;
		drawBox(width, height, left, top);
		string session;
		gotoXY(xPos, yPos); cout << no;

		gotoXY(xPos + 3, yPos); cout << "|              ";
		gotoXY(xPos + 5, yPos); getline(cin, newCourse->id);
		gotoXY(xPos + 14, yPos); cout << "|              ";
		gotoXY(xPos + 16, yPos); getline(cin, newCourse->courseName);
		gotoXY(xPos + 35, yPos); cout << "|              ";
		gotoXY(xPos + 37, yPos); getline(cin, newCourse->teacherName);
		gotoXY(xPos + 57, yPos); cout << "|              ";
		gotoXY(xPos + 59, yPos); cin >> newCourse->academicYear;
		gotoXY(xPos + 68, yPos); cout << "|              ";
		gotoXY(xPos + 70, yPos); cin >> newCourse->credits;
		gotoXY(xPos + 78, yPos); cout << "|              ";
		gotoXY(xPos + 80, yPos); cin >> newCourse->maxStudents;
		cin.ignore();
		gotoXY(xPos + 90, yPos); cout << "|        ";
		gotoXY(xPos + 92, yPos); getline(cin, newCourse->wDay);
		toUpper(newCourse->wDay);
		gotoXY(xPos + 100, yPos); cout << "|        ";
		gotoXY(xPos + 102, yPos); getline(cin, session);
		toUpper(session);
		newCourse->session[0] = session.substr(session.find('S'), 2);
		session.erase(session.find('S'), 2);
		newCourse->session[1] = session.substr(session.find('S'), 2);
		newCourse->prev = NULL;
		newCourse->next = NULL;
		no++;
		yPos++;
		height++;
		clearLine(yPos);
		addCourse(listCourses, newCourse);
		ofstream("./data/" + currentSchoolYear + "/semester " +
			to_string(currentSemester.semester) + "/courses/" + newCourse->id + ".dat");
		drawBox(width, height, left, top);
	}
	hideCursor(true);
	saveCourses();
	loading("Creating...");
	notifyBox("Added New Courses");
}
void importCoursesData() {
	ListCourses coursesImported;
	initList(coursesImported);
	system("cls");
	hideCursor(false);
	int year;
	int no = 1;
	int yPos = 2;
	int xPos = 17;
	int width = 50;
	int height = 4;
	int left = 35;
	int top = 8;
	string dir = "./data/importFiles/courses/";

	string temp;
	gotoXY(55, 5); cout << "HCMUS Portal";
	gotoXY(51, 7); cout << "Import Courses Data";
	drawBox(width, height, left, top);
	gotoXY(38, 10); cout << "Dir: " + dir; getline(cin, temp);

	if (temp.find(".csv") == string::npos) {
		temp += ".csv";
	}
	dir += temp;
	ifstream fin(dir);
	if (!fin) {
		notifyBox("FILE NOT EXISTS");
		return;
	}
	string s = "";
	getline(fin, s);
	while (!fin.eof()) {
		Course* newCourse = convertCourseData(fin);
		addCourse(listCourses, newCourse);
		if (newCourse != NULL) ofstream("./data/" + currentSchoolYear + "/semester " +
			to_string(currentSemester.semester) + "/courses/" + newCourse->id + ".dat");
	}
	hideCursor(true);
	saveCourses();
	loading("Importing...");
	notifyBox("Added New Courses");
}
int addCoursesOption(int curPos) {
	switch (curPos) {
	case 0:
		inputCoursesData();
		break;
	case 1:
		importCoursesData();
		break;
	case 2:
		return 0;
		break;
	}
	return 1;
}
void addCourses() {
	const int width = 40;
	const int height = 8;
	const int left = 40;
	const int top = 8;

	int curPos = 0;
	int yPos = 10;
	do {
		system("cls");
		drawBox(width, height, left, top);
		gotoXY(55, 5); cout << "HCMUS Portal";
		gotoXY(55, 7); cout << "Add Courses";
		gotoXY(48, yPos); cout << "Input Courses Data";
		yPos++;
		gotoXY(48, yPos); cout << "Import Courses Data File";
		yPos++;
		gotoXY(48, yPos); cout << "Back";
		yPos++;
		yPos = 10;
		gotoXY(46, curPos + yPos); cout << cursorLeft;
		gotoXY(74, curPos + yPos); cout << cursorRight;

	} while (command(curPos, 0, 2, addCoursesOption));
}
//Calculate overall GPA
void calcOverallGPA() {
	ListStudent list;
	initList(list);
	string path = semesterPath + "/student/";
	string ext(".dat");
	for (auto& p : fs::recursive_directory_iterator(path))
	{
		if (p.path().extension() == ext) {
			Student* s = new Student;
			s->studentID = p.path().stem().string();
			getEnrolledCourses(s);
			s->next = NULL;
			s->prev = NULL;
			addStudent(list, s);
		}
	}
	Student* temp = list.head;
	while (temp != NULL) {
		saveOverallGPA(temp);
		temp = temp->next;
	}
}
//View courses
int viewCourseOption(int curPos, int page) {
	int count = 0;
	
	Course* temp = listCourses.head;
	for (int i = 0; i < (page - 1) * 10; i++) {
		temp = temp->next;
	}
	Course* courseSelected = NULL;
	while (count < 10 && temp != NULL) {
		if (count == curPos ) {
			courseSelected = temp;
			break;
		}
		count++;
		temp = temp->next;
	}
	if (courseSelected == NULL) {
		return 0;
	}
	else {
		updateCourse(courseSelected);
	}
	return 1;
}
int viewCoursesCommand(int& curPos, int minPos, int maxPos, int& page, int numberPages, function<int(int, int)> option) {
	int key = _getch();
	switch (key) {
	case 13:
		return option(curPos, page);
	case 224:
		key = _getch();
		switch (key) {
		case 72://up key
			if (curPos > minPos) curPos--;
			else {
				curPos = maxPos;
			}
			break;
		case 80://down key
			if (curPos < maxPos) curPos++;
			else {
				curPos = minPos;
			}
			break;
		case 75://left key
			if (page > 1) {
				page--;
				curPos = 0;
			}
			break;
		case 77://right key
			if (page < numberPages) {
				page++;
				curPos = 0;
			}
			break;
		}
	}
	return 1;
}
void viewCourses() {
	const int width = 50;
	int height = 9;
	const int left = 35;
	const int top = 8;
	int curPos = 0;
	int yPos = 13;
	int numberPages;
	int page = 1;
	int i = 0;

	do {
		i = 0;
		numberPages = ((listCourses.size - 1) / 10) + 1;
		height = 9;
		system("cls");
		gotoXY(55, 5); cout << "HCMUS Portal";
		gotoXY(55, 7); cout << "List Course";
		gotoXY(38, 10); cout << "ID";
		gotoXY(48, 10); cout << "Course name";
		gotoXY(73, 10); cout << "Academic";
		gotoXY(75, 11); cout << "year";
		if (listCourses.head != NULL) {
			Course* temp = listCourses.head;
			for (int i = 0; i < (page - 1) * 10; i++) {
				temp = temp->next;
			}
			while (i < 10 && temp != NULL) {
				gotoXY(38, yPos); cout << temp->id;
				string courseName = temp->courseName;
				if (courseName.length() > 24) courseName = courseName.substr(0, 24);
				gotoXY(48, yPos); cout << courseName;
				gotoXY(75, yPos); cout << temp->academicYear;
				yPos++;
				i++;
				temp = temp->next;
			}
			height += i;
			drawBox(width, height, left, top);
			yPos++;
			gotoXY(58, yPos);
			if (page > 1) cout << char(174);
			cout << char(174) << "  " << page << "  " << char(175);
			if (page < numberPages) cout << char(175);
			yPos++;
			gotoXY(59, yPos); cout << "Back";
			yPos = 13;
			if (curPos == i) {
				yPos += 2;
				gotoXY(57, curPos + yPos); cout << cursorLeft;
				gotoXY(64, curPos + yPos); cout << cursorRight;
			}
			else {
				gotoXY(36, curPos + yPos); cout << cursorLeft;
				gotoXY(82, curPos + yPos); cout << cursorRight;
			}
			yPos = 13;
		}
		else {
			notifyBox("Empty List...");
			return;
		}
	} while (viewCoursesCommand(curPos, 0, i, page, numberPages, viewCourseOption));
}
void manageCourses() {
	if (!dirExists(schoolYearPath)) {
		notifyBox("Please create school year !");
		return;
	}
	const int width = 40;
	const int height = 11;
	const int left = 40;
	const int top = 8;
	int curPos = 0;
	int yPos = 10;
	do {
		getListCourses();
		system("cls");
		drawBox(width, height, left, top);
		gotoXY(55, 5); cout << "HCMUS Portal";
		gotoXY(55, 7); cout << "Manage Courses";
		if (isExpired(currentDate, currentSemester.endDate)) {
			gotoXY(50, yPos); cout << "Create semester";
			yPos++;
		}
		else {
			gotoXY(50, yPos); cout << "Semester Infomation";
			yPos++;
		}
		if (isOnRegSession()) {
			gotoXY(50, yPos); cout << "Modify Registration Session";
			yPos++;
		}
		else {
			gotoXY(50, yPos); cout << "Create Registration Session";
			yPos++;
		}
		gotoXY(50, yPos); cout << "Add Courses";
		yPos++;
		gotoXY(50, yPos); cout << "List Of Courses";
		yPos++;
		gotoXY(50, yPos); cout << "Semester Summary";
		yPos++;
		yPos++;
		gotoXY(50, yPos); cout << "Back";
		yPos = 10;
		if (curPos == 5) yPos++;
		gotoXY(48, curPos + yPos); cout << cursorLeft;
		gotoXY(78, curPos + yPos); cout << cursorRight;
		yPos = 10;
	} while (command(curPos, 0, 5, manageCoursesOption));
}

//Setting
void setting() {
	system("cls");
	int width = 40;
	int height = 6;
	int left = 40;
	int top = 8;

	string date;
	hideCursor(false);
	gotoXY(55, 5); cout << "HCMUS Portal";
	gotoXY(57, 7); cout << "Setting";
	drawBox(width, height, left, top);
	gotoXY(48, 10); cout << "Current Date: "; 
	cout << dateToStr(currentDate);
	gotoXY(48, 12); cout << "(dd/mm/YYYY)";
	gotoXY(48, 11); cout << "Change Date: "; getline(cin, date);
	if (date == "") return;
	currentDate = strToDate(date);
	hideCursor(true);
	getCurrentSchoolYear();
	getCurrentSemester();
	schoolYearPath = "./data/" + currentSchoolYear;
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
			else {
				curPos = maxPos;
			}
			break;
		case 80:
			if (curPos < maxPos) curPos++;
			else {
				curPos = minPos;
			}
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
		manageCourses();
		break;
	case 4:
		setting();
		break;
	case 5:
		exit(0);
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
int generalOption(int curPos) {
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
		if (dirExists(schoolYearPath)) schoolYearInfo();
		else createSchoolYear();
		break;
	case 1:
		createClasses();
		break;
	case 2:
		viewListOfClasses();
		break;
	case 3:
		return 0;
		break;
	}
	return 1;
}
int manageCoursesOption(int curPos) {
	switch (curPos) {
	case 0:
		if (isExpired(currentDate, currentSemester.endDate)) createSemester();
		else semesterInfo();
		break;
	case 1:
		if (isOnRegSession()) modifyCourseReg();
		else createCourseReg();
		break;
	case 2:
		addCourses();
		break;
	case 3:
		viewCourses();
		break;
	case 4:
		calcOverallGPA();
		loading("Calculating...");
		break;
	case 5:
		return 0;
		break;
	}
	return 1;
}