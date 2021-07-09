#include "Globals.h"

const string userDataPath = "Data/Accounts/users.csv";
Date currentDate;
string currentSchoolYear;
Semester currentSemester;
string semesterPath;
ListCourses listCourses;
string schoolYearPath;

int dayofweek(int d, int m, int y)
{
	static int t[] = { 0, 3, 2, 5, 0, 3,
					   5, 1, 4, 6, 2, 4 };
	y -= m < 3;
	return (y + y / 4 - y / 100 +
		y / 400 + t[m - 1] + d) % 7;
}
Date strToDate(string str) {
	Date date;
	date.day = stoi(str.substr(0, str.find('/')));
	str.erase(0, str.find('/') + 1);
	date.month = stoi(str.substr(0, str.find('/')));
	str.erase(0, str.find('/') + 1);
	date.year = stoi(str.substr(0, str.find('/')));
	str.erase(0, str.find('/') + 1);
	string wDay;
	switch (dayofweek(date.day, date.month, date.year)) {
	case 0:
		wDay = "Sun";
		break;
	case 1:
		wDay = "Mon";
		break;
	case 2:
		wDay = "Tue";
		break;
	case 3:
		wDay = "Wed";
		break;
	case 4:
		wDay = "Thu";
		break;
	case 5:
		wDay = "Fri";
		break;
	case 6:
		wDay = "Sat";
		break;
	}
	date.wDay = wDay;
	return date;
}
string dateToStr(Date date) {
	string str = "";
	if (date.day < 10) str += "0";
	str += to_string(date.day) + "/";
	if (date.month < 10) str += "0";
	str += to_string(date.month) + "/";
	str += to_string(date.year);
	return str;
}
void gotoXY(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void toUpper(string& s) {
	transform(s.begin(), s.end(), s.begin(), ::toupper);
}
void hideCursor(bool isHiden) {
	CONSOLE_CURSOR_INFO cursor;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
	cursor.bVisible = !isHiden;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}
bool dirExists(const std::string& dirName_in)
{
	DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
	if (ftyp == INVALID_FILE_ATTRIBUTES)
		return false;  //something is wrong with your path!

	if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
		return true;   // this is a directory!

	return false;    // this is not a directory!
}
void copyFolder(string from, string to) {
	const auto copyOptions = filesystem::copy_options::update_existing
		| filesystem::copy_options::recursive
		;
	filesystem::copy(from, to, copyOptions);
}
void clearLine(int y) {
	gotoXY(0, y);
	printf("%c[2K", 27);
}

void alignRow(int x, int& y, string text, int rowLength) {
	int n = count(text.begin(), text.end(), ' ') + 1;
	string* strArr = new string[n];
	int i = 0;
	stringstream ssin(text);
	while (ssin.good() && i < n) {
		ssin >> strArr[i];
		i++;
	}
	i = 0;
	int s = rowLength;
	while (i < n) {		
		gotoXY(x, y);
		rowLength = s;
		while (rowLength > 0 || i < n) {
			cout << strArr[i] << " ";
			rowLength -= (strArr[i].length() + 1);
			i++;
			if (rowLength < (strArr[i].length() + 1)) break;
		}
		y++;
	}
}
void notifyBox(string msg) {
	hideCursor(true);
	system("cls");
	int width = 45;
	int height = 5;
	int left = 40;
	int top = 9;
	int yPos = 11;
	gotoXY(57, 8); cout << "NOTIFICATION";
	alignRow(45, yPos, msg, 37);
	height += (yPos - 11);
	drawBox(width, height, left, top);
	yPos++;
	gotoXY(45, yPos); cout << "Press any key to continue...";
	_getch();
	system("cls");
}
void drawBox(int width, int height, int left, int top) {
	gotoXY(left, top);
	cout << char(201);
	for (int i = 0; i < width; i++) {
		cout << char(205);
	}
	cout << char(187);
	for (int i = top + 1; i < height + top; i++) {
		gotoXY(left, i);
		cout << char(186);
	}
	gotoXY(left, height + top);
	cout << char(200);
	for (int i = 0; i < width; i++) {
		cout << char(205);
	}
	cout << char(188);
	for (int i = height + top - 1; i > top; i--) {
		gotoXY(left + width + 1, i);
		cout << char(186);
	}
}
void loading(string text) {
	system("cls");
	int width = 40;
	int height = 2;
	int left = 40;
	int top = 9;
	gotoXY(55, 8); cout << text;
	drawBox(width, height, left, top);
	for (int i = 0; i < 40; i++) {
		gotoXY(i + 41, 10); cout << char(219);
		Sleep(10);
	}
	system("cls");
}

void addUser(ListUser& list, User* user) {
	if (user == NULL) return;
	if (list.pHead == NULL) {
		list.pHead = list.pTail = user;
	}
	else {
		list.pTail->next = user;
		user->prev = list.pTail;
		list.pTail = user;
	}
	list.size++;
}
void addStudent(ListStudent& list, Student* student) {
	if (student == NULL) return;
	if (list.pHead == NULL) {
		list.pHead = list.pTail = student;
	}
	else {
		list.pTail->next = student;
		student->prev = list.pTail;
		list.pTail = student;
	}
	list.size++;
}
void addCourse(ListCourses& list, Course* course) {
	if (course == NULL) return;
	if (list.head == NULL) {
		list.head = list.tail = course;
		course->prev = NULL;
	}
	else {
		list.tail->next = course;
		course->prev = list.tail;
		list.tail = course;
	}
	list.size++;
}
void deleteCourse(ListCourses& list, Course* course) {
	if (course == list.head && course == list.tail) {
		list.head = list.tail = NULL;
		delete course;
	}
	else if (course == list.head) {
		list.head = list.head->next;
		list.head->prev = NULL;
		delete course;
	}
	else if (course == list.tail) {
		list.tail = list.tail->prev;
		list.tail->next = NULL;
		delete course;
	}
	else {
		course->prev->next = course->next;
		course->next->prev = course->prev;
		delete course;
	}
	list.size--;
}
void initList(ListUser& list) {
	list.pHead = NULL;
	list.pTail = NULL;
	list.size = 0;
}
void initList(ListStudent& list) {
	list.pHead = NULL;
	list.pTail = NULL;
	list.size = 0;
}
void initList(ListCourses& list) {
	list.head = NULL;
	list.tail = NULL;
	list.startDate = list.endDate = strToDate("0/0/0");
	list.size = 0;
}
void saveListUser() {
	ofstream fout(userDataPath);
	fout << "ID,Password,Last name,First name,Class,Gender,Date of Birth,Staff" << endl;
	User* curr = listUser.pHead;
	while (curr != NULL) {
		string dateOfBirth = to_string(curr->dateOfBirth.day) + "/" + to_string(curr->dateOfBirth.month) + "/" + to_string(curr->dateOfBirth.year);
		fout << curr->id << "," << curr->password << "," << curr->lastName << "," << curr->firstName
			<< "," << curr->className << "," << curr->gender << "," << dateOfBirth << ",";
		if (curr->isStaff) fout << "TRUE" << endl;
		else fout << "FALSE" << endl;
		curr = curr->next;
	}
	fout.close();
}
void saveClass(string path, ListStudent listStudent) {
	ofstream fout(path);
	fout << "No,Student ID,Last name,First name,Gender,Date of Birth,Social ID" << endl;
	Student* curr = listStudent.pHead;
	int no = 1;
	while (curr != NULL) {
		string dateOfBirth = to_string(curr->dateOfBirth.day) + "/" + to_string(curr->dateOfBirth.month) + "/" + to_string(curr->dateOfBirth.year);
		fout << no << "," << curr->studentID << "," << curr->lastName << "," << curr->firstName << "," << curr->gender
			<< "," << dateOfBirth << "," << curr->socialID;
		fout << endl;
		no++;
		curr = curr->next;
	}
	fout.close();
}
void saveCourses() {
	ofstream fout(semesterPath + "/courses.csv");
	fout << "Courses registration session:," << dateToStr(listCourses.startDate) << "-"
		<< dateToStr(listCourses.endDate) << endl;
	fout << "ID,Course name,Teacher name,Credits,Academic year,Number of students,Day of the week,Session" << endl;
	Course* temp = listCourses.head;
	while (temp != NULL) {
		toUpper(temp->wDay);
		string session = temp->session[0] + "-" + temp->session[1];
		fout << temp->id << "," << temp->courseName << "," << temp->teacherName << ","
			<< temp->credits << "," << temp->academicYear << "," << temp->maxStudents << "," << temp->wDay << "," << session << endl;
		temp = temp->next;
	}
	fout.close();
}

User* convertUserData(ifstream& data) {
	User* usersData = new User;
	Date dateOfBirth;
	string temp;
	getline(data, usersData->id, ',');
	if (usersData->id == "") return NULL;
	getline(data, usersData->password, ',');
	getline(data, usersData->lastName, ',');
	getline(data, usersData->firstName, ',');
	getline(data, usersData->className, ',');
	getline(data, usersData->gender, ',');
	getline(data, temp, ',');
	usersData->dateOfBirth = strToDate(temp);
	getline(data, temp, '\n');
	if (temp == "TRUE") usersData->isStaff = true;
	else usersData->isStaff = false;
	usersData->next = NULL;
	usersData->prev = NULL;
	return usersData;
}
Student* convertStudentData(ifstream& data) {
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
Course* convertCourseData(ifstream& data) {
	Course* course = new Course;
	string credits, maxStudents, session, academicYear;
	getline(data, course->id, ',');
	if (course->id == "") return NULL;
	getline(data, course->courseName, ',');
	getline(data, course->teacherName, ',');
	getline(data, credits, ',');
	course->credits = stoi(credits);
	getline(data, academicYear, ',');
	course->academicYear = stoi(academicYear);
	getline(data, maxStudents, ',');
	course->maxStudents = stoi(maxStudents);
	getline(data, course->wDay, ',');
	getline(data, session, '\n');
	course->session[0] = session.substr(session.find('S'), 2);
	session.erase(session.find('S'), 2);
	course->session[1] = session.substr(session.find('S'), 2);
	course->next = NULL;
	return course;
}
const string currentDateTime() {
	time_t now = time(0);
	tm ltm;
	localtime_s(&ltm,&now);
	cout << "Year: " << 1900 + ltm.tm_year << endl;
	cout << "Month: " << 1 + ltm.tm_mon << endl;
	cout << "Day: " << ltm.tm_mday << endl;
	cout << "Time: " << 1 + ltm.tm_hour << ":";
	cout << 1 + ltm.tm_min << ":";
	cout << 1 + ltm.tm_sec << endl;

	return "";
}
bool isExpired(Date now, Date endDate) {
	if (endDate.wDay == "") return true;
	if (now.year > endDate.year) return true;
	else if (now.year < endDate.year) return false;
	else {
		if (now.month > endDate.month) return true;
		else if (now.month < endDate.month) return false;
		else {
			if (now.day >= endDate.day) return true;
			else return false;
		}
	}
}
bool isOnRegSession() {
	return isExpired(currentDate, listCourses.startDate) && !isExpired(currentDate, listCourses.endDate);
}
void getListCourses() {
	ifstream fin(semesterPath + "/courses.csv");
	initList(listCourses);
	if (!fin) return;
	string s;
	string start, end;
	getline(fin, s);
	start = s.substr(s.find(',') + 1, 10);
	end = s.substr(s.find('-') + 1, 10);
	listCourses.startDate = strToDate(start);
	listCourses.endDate = strToDate(end);
	getline(fin, s);
	while (true) {
		if (fin.eof()) break;
		addCourse(listCourses, convertCourseData(fin));
	}
}
void getCurrentDate() {
	time_t now = time(0);
	tm ltm;
	localtime_s(&ltm, &now);
	string wDay;
	switch (ltm.tm_wday) {
	case 0:
		wDay = "Sun";
		break;
	case 1:
		wDay = "Mon";
		break;
	case 2:
		wDay = "Tue";
		break;
	case 3:
		wDay = "Wed";
		break;
	case 4:
		wDay = "Thu";
		break;
	case 5:
		wDay = "Fri";
		break;
	case 6:
		wDay = "Sat";
		break;
	}
	currentDate.year = 1900 + ltm.tm_year;
	currentDate.month = 1 + ltm.tm_mon;
	currentDate.day = ltm.tm_mday;
	currentDate.wDay = wDay;
}
void getCurrentSchoolYear() {
	const int beginSchoolYearMonth = 9;
	if (currentDate.month < beginSchoolYearMonth) {
		currentSchoolYear = to_string(currentDate.year - 1) + "-" + to_string(currentDate.year);
	}
	else {
		currentSchoolYear = to_string(currentDate.year) + "-" + to_string(currentDate.year + 1);
	}
}
void getCurrentSemester() {
	ifstream fin("data/" + currentSchoolYear + "/semester.dat");
	if (!fin) return;
	fin >> currentSemester.semester;
	string startDate, endDate, s;
	getline(fin, s);
	getline(fin, startDate);
	getline(fin, endDate);
	if (startDate == "" || endDate == "") {
		currentSemester.semester = 0;
		currentSemester.startDate = strToDate("0/0/0");
		currentSemester.endDate = strToDate("0/0/0");
	}
	else {
		currentSemester.startDate = strToDate(startDate);
		currentSemester.endDate = strToDate(endDate);
		semesterPath = "data/" + currentSchoolYear + "/semester " + to_string(currentSemester.semester);
	}
}
