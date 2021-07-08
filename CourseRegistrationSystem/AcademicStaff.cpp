#include "AcademicStaff.h"

const char cursor = char(174);

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
		hideCursor(true);
		schoolYearPath = "./data/" + currentSchoolYear;
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
		gotoXY(70, curPos + yPos); cout << cursor;
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
		gotoXY(45, yPos); cout << "Your old password: ";
		yPos++;
		yPos++;
		getline(cin, currentPassword);
		if (currentPassword == currentUser->password) {
			gotoXY(45, yPos); cout << "Enter new password: ";
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
	const int width = 30;
	const int height = 7;
	const int left = 44;
	const int top = 8;

	int curPos = 0;
	int yPos = 10;
	do {
		system("cls");
		drawBox(width, height, left, top);
		gotoXY(55, 5); cout << "HCMUS Portal";
		gotoXY(55, 7); cout << "User Account";
		gotoXY(53, yPos); cout << "Change Password";
		yPos++;
		gotoXY(53, yPos); cout << "Logout";
		yPos++;
		yPos++;
		gotoXY(53, yPos); cout << "Back";
		yPos = 10;
		if (curPos == 2) yPos++;
		gotoXY(70, curPos + yPos); cout << cursor;
		yPos = 10;
	} while (command(curPos, 0, 2, userAccountOption));
}

//Profile
void Profile() {
	const int width = 34;
	const int height = 10;
	const int left = 43;
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
		gotoXY(58, yPos); cout << "Back";
		gotoXY(70, curPos + yPos); cout << cursor;
		yPos = 10;
	} while (command(curPos, 0, 0, generalOption));

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
	gotoXY(48, 13); cout << "Year(1/2/3/4): "; cin >> year;
	cin.ignore();
	gotoXY(48, 14); cout << "Class: "; getline(cin, listStudent.className);
	gotoXY(48, 15); cout << "Number of students: "; cin >> quantity;
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
	int width = 40;
	int height = 8;
	int left = 40;
	int top = 9;
	string dir = "./data/files imported/";

	string temp;
	gotoXY(55, 5); cout << "HCMUS Portal";
	gotoXY(53, 7); cout << "Import Class Data";
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
	dir += temp;
	ifstream fin(dir);
	if (!fin) {
		notifyBox("FILE NOT EXISTS");
		return;
	}
	string s = "";
	getline(fin, s);
	while (!fin.eof()) {
		addStudent(listStudent, convertStudentData(fin));
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
		gotoXY(48, yPos); cout << "Input Class Data";
		yPos++;
		gotoXY(48, yPos); cout << "Import Class Data";
		yPos++;
		gotoXY(48, yPos); cout << "Back";
		yPos++;
		yPos = 10;
		gotoXY(70, curPos + yPos); cout << cursor;
		
	} while (command(curPos, 0, 2, createClassOption));
}
void newSchoolYear() {
	int lastYear = stoi(currentSchoolYear.substr(0, 4));
	string prevSchoolYearPath = "./data/" + to_string(lastYear - 1) + "-" + to_string(lastYear);
	string classesPath = schoolYearPath + "/classes";
	if (dirExists(prevSchoolYearPath)) {
		fs::create_directories(classesPath);
		ofstream(schoolYearPath + "/semester.txt");
		prevSchoolYearPath += "/classes";
		copyFolder(prevSchoolYearPath, classesPath);
		fs::remove_all(classesPath + "/final-year student");
		fs::rename(classesPath + "/third-year student", classesPath + "/final-year student");
		fs::rename(classesPath + "/second-year student", classesPath + "/third-year student");
		fs::rename(classesPath + "/first-year student", classesPath + "/second-year student");
		fs::create_directories(classesPath + "/first-year student/APCS");
		fs::create_directories(classesPath + "/first-year student/CTT");
		fs::create_directories(classesPath + "/first-year student/CLC");
		fs::create_directories(classesPath + "/first-year student/VP");
	}
	else {
		ofstream(schoolYearPath + "/semester.txt");
		fs::create_directories(classesPath + "/first-year student/APCS");
		fs::create_directories(classesPath + "/first-year student/CTT");
		fs::create_directories(classesPath + "/first-year student/CLC");
		fs::create_directories(classesPath + "/first-year student/VP");
		fs::create_directories(classesPath + "/second-year student/APCS");
		fs::create_directories(classesPath + "/second-year student/CTT");
		fs::create_directories(classesPath + "/second-year student/CLC");
		fs::create_directories(classesPath + "/second-year student/VP");
		fs::create_directories(classesPath + "/third-year student/APCS");
		fs::create_directories(classesPath + "/third-year student/CTT");
		fs::create_directories(classesPath + "/third-year student/CLC");
		fs::create_directories(classesPath + "/third-year student/VP");
		fs::create_directories(classesPath + "/final-year student/APCS");
		fs::create_directories(classesPath + "/final-year student/CTT");
		fs::create_directories(classesPath + "/final-year student/CLC");
		fs::create_directories(classesPath + "/final-year student/VP");
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
void manageStudent() {
	const int width = 30;
	const int height = 10;
	const int left = 45;
	const int top = 8;
	int curPos = 0;
	int yPos = 10;

	do {
		system("cls");
		drawBox(width, height, left, top);
		gotoXY(55, 5); cout << "HCMUS Portal";
		gotoXY(55, 7); cout << "Manage Student";
		gotoXY(52, yPos); cout << "Create school year";
		yPos++;
		gotoXY(52, yPos); cout << "Create classes";
		yPos++;
		yPos++;
		gotoXY(52, yPos); cout << "Back";
		yPos = 10;
		if (curPos == 2) yPos++;
		gotoXY(73, curPos + yPos); cout << cursor;
		yPos = 10;
	} while (command(curPos, 0, 2, manageStudentOption));
}

//Manage Courses
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
void viewCourse(Course* course) {
	const int width = 40;
	const int height = 12;
	const int left = 40;
	const int top = 8;
	int curPos = 0;

	do {
		system("cls");
		gotoXY(55, 5); cout << "HCMUS Portal";
		gotoXY(55, 7); cout << "View Course";
		drawBox(width, height, left, top);
		gotoXY(45, 10); cout << "Course ID: " << course->id;
		gotoXY(45, 11); cout << "Course name: " << course->courseName;
		gotoXY(45, 12); cout << "Teacher name: " << course->teacherName;
		gotoXY(45, 13); cout << "Number of credits: " << course->credits;
		gotoXY(45, 14); cout << "Maximum nums of student: " << course->maxStudents;
		gotoXY(45, 15); cout << "Weekday: " << course->wDay;
		gotoXY(45, 16); cout << "Session: " << course->session[0] << "-" << course->session[1];
		gotoXY(45, 18); cout << "Back";
		gotoXY(75, 18 + curPos); cout << cursor;
	} while (command(curPos, 0, 0, generalOption));

}
void modifyCourse(Course* course) {
	const int width = 40;
	const int height = 10;
	const int left = 40;
	const int top = 8;

	system("cls");
	string session;
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
	gotoXY(62, 15); getline(cin, course->wDay);
	toUpper(course->wDay);
	gotoXY(68, 16); getline(cin, session);
	toUpper(session);
	course->session[0] = session.substr(session.find('S'), 2);
	session.erase(session.find('S'), 2);
	course->session[1] = session.substr(session.find('S'), 2);
	hideCursor(true);
	saveCourses();
}
void deleteCourse(Course* course) {
	if (course == listCourses.head && course == listCourses.tail) {
		listCourses.head = listCourses.tail = NULL;
		delete course;
	}
	else if (course == listCourses.head) {
		listCourses.head = listCourses.head->next;
		listCourses.head->prev = NULL;
		delete course;
	}
	else if (course == listCourses.tail) {
		listCourses.tail = listCourses.tail->prev;
		listCourses.tail->next = NULL;
		delete course;
	}
	else {
		course->prev->next = course->next;
		delete course;
	}
	listCourses.size--;
}
int updateCourseOption(int curPos, Course* course) {
	switch (curPos)
	{
	case 0:
		viewCourse(course);
		break;
	case 1:
		modifyCourse(course);
		break;
	case 2:
		deleteCourse(course);
		break;
	case 3:
		break;
	}
	return 0;
}
void updateCourse(Course* course) {
	const int width = 30;
	const int height = 8;
	const int left = 45;
	const int top = 8;
	int curPos = 0;
	int yPos = 10;

	do {
		system("cls");
		gotoXY(55, 5); cout << "HCMUS Portal";
		gotoXY(55, 7); cout << "Update Course";
		drawBox(width, height, left, top);
		gotoXY(55, yPos); cout << "View";
		yPos++;
		gotoXY(55, yPos); cout << "Modify";
		yPos++;
		gotoXY(55, yPos); cout << "Delete";
		yPos++;
		yPos++;
		gotoXY(55, yPos); cout << "Back";
		yPos = 10;
		if (curPos == 3) yPos++;
		gotoXY(70, curPos + yPos); cout << cursor;
		yPos = 10;
	} while (updateCourseCommand(curPos, 0, 3, course, updateCourseOption));

	saveCourses();
}
int viewCourseOption(int curPos) {
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
		updateCourse(courseChoosed);
	}
	return 1;
}
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
void createSemester(){
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
		gotoXY(48, yPos); cout << "Back";
		gotoXY(70, curPos + yPos); cout << cursor;
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
	height = 3;
	left = xPos - 5;
	top = yPos + 1;
	gotoXY(50, yPos); cout << "ADD COURSES";
	yPos += 2;
	gotoXY(xPos, yPos); cout << "No |";
	gotoXY(xPos + 5, yPos); cout << "Course ID |";
	gotoXY(xPos + 17, yPos); cout << "    Course name      |";
	gotoXY(xPos + 40, yPos); cout << "     Teacher name      |";
	gotoXY(xPos + 65, yPos); cout << "Credits |";
	gotoXY(xPos + 75, yPos); cout << "Max students |";
	gotoXY(xPos + 90, yPos); cout << "Weekday  |";
	gotoXY(xPos + 101, yPos); cout << "Session";
	yPos++;
	while (no <= num) {
		Course* newCourse = new Course;
		drawBox(width, height, left, top);
		string session;
		gotoXY(xPos, yPos); cout << no;

		gotoXY(xPos + 3, yPos); cout << "| "; getline(cin, newCourse->id);
		gotoXY(xPos + 15, yPos); cout << "| "; getline(cin, newCourse->courseName);
		gotoXY(xPos + 38, yPos); cout << "| "; getline(cin, newCourse->teacherName);
		gotoXY(xPos + 63, yPos); cout << "| "; cin >> newCourse->credits;
		gotoXY(xPos + 73, yPos); cout << "| "; cin >> newCourse->maxStudents;
		cin.ignore();
		gotoXY(xPos + 88, yPos); cout << "| "; getline(cin, newCourse->wDay);
		toUpper(newCourse->wDay);
		gotoXY(xPos + 99, yPos); cout << "| "; getline(cin, session);
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
	int width = 40;
	int height = 8;
	int left = 40;
	int top = 9;
	string dir = "./data/files imported/";

	string temp;
	drawBox(width, height, left, top);
	gotoXY(48, 15); cout << "Dir: Files Imported/"; getline(cin, temp);

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
		addCourse(listCourses, convertCourseData(fin));
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
		gotoXY(48, yPos); cout << "Import Courses Data";
		yPos++;
		gotoXY(48, yPos); cout << "Back";
		yPos++;
		yPos = 10;
		gotoXY(70, curPos + yPos); cout << cursor;

	} while (command(curPos, 0, 2, addCoursesOption));
}
void viewCourses() {
	const int width = 40;
	int height = 5;
	const int left = 40;
	const int top = 8;
	int curPos = 0;
	int yPos = 10;

	do {
		system("cls");
		height = 5;
		height += listCourses.size;
		gotoXY(55, 5); cout << "HCMUS Portal";
		gotoXY(55, 7); cout << "List Course";
		drawBox(width, height, left, top);
		if (listCourses.head != NULL) {
			Course* temp = listCourses.head;
			while (temp != NULL) {
				gotoXY(43, yPos); cout << temp->id << "  " << temp->courseName;
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
	} while (command(curPos, 0, listCourses.size, viewCourseOption));
}
void manageCourses() {
	const int width = 40;
	const int height = 10;
	const int left = 40;
	const int top = 8;
	int curPos = 0;
	int yPos = 10;
	getListCourses();
	do {
		system("cls");
		drawBox(width, height, left, top);
		gotoXY(55, 5); cout << "HCMUS Portal";
		gotoXY(55, 7); cout << "Manage Courses";
		if (isExpired(currentDate, currentSemester.endDate)) {
			gotoXY(48, yPos); cout << "Create semester";
			yPos++;
		}
		else {
			gotoXY(48, yPos); cout << "Semester Infomation";
			yPos++;
		}
		if (isOnRegSession()) {
			gotoXY(48, yPos); cout << "Modify Registration Session";
			yPos++;
		}
		else {
			gotoXY(48, yPos); cout << "Create Registration Session";
			yPos++;
		}
		gotoXY(48, yPos); cout << "Add Courses";
		yPos++;
		gotoXY(48, yPos); cout << "View List Courses";
		yPos++;
		yPos++;
		gotoXY(48, yPos); cout << "Back";
		yPos = 10;
		if (curPos == 4) yPos++;
		gotoXY(76, curPos + yPos); cout << cursor;
		yPos = 10;
	} while (command(curPos, 0, 4, manageCoursesOption));
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
	cout << currentDate.day << '/' << currentDate.month << '/' << currentDate.year;
	gotoXY(48, 12); cout << "(dd/mm/YYYY)";
	gotoXY(48, 11); cout << "Change Date: "; getline(cin, date);
	currentDate = strToDate(date);
	hideCursor(true);
	getCurrentSchoolYear();
	getCurrentSemester();
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
		return 0;
		break;
	}
	return 1;
}