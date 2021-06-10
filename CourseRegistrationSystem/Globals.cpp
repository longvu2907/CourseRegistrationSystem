#include "Globals.h"

const string userDataPath = "Data/Accounts/users.csv";
Date currentDate;
string currentSchoolYear;

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
void gotoXY(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
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

void notifyBox(string msg) {
	hideCursor(true);
	system("cls");
	int width = 45;
	int height = 6;
	int left = 40;
	int top = 9;

	drawBox(width, height, left, top);
	gotoXY(57, 8); cout << "NOTIFICATION";
	gotoXY(45, 11); cout << msg;
	gotoXY(45, 13); cout << "Press any key to continue...";
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