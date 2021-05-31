#include "Globals.h"

const string userDataPath = "Data/Accounts/users.csv";
Date currentDate;
string currentSchoolYear;

Date strToDate(string str) {
	Date date;
	date.day = stoi(str.substr(0, str.find('/')));
	str.erase(0, str.find('/') + 1);
	date.month = stoi(str.substr(0, str.find('/')));
	str.erase(0, str.find('/') + 1);
	date.year = stoi(str.substr(0, str.find('/')));
	str.erase(0, str.find('/') + 1);
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
int removeDir(string dirPath)
{
	struct _finddata_t fb;   //find the storage structure of the same properties file.
	string path;
	long    handle;
	int  resultone;
	int   noFile;            // the tag for the system's hidden files

	noFile = 0;
	handle = 0;

	path = dirPath + "/*";

	handle = _findfirst(path.c_str(), &fb);

	//find the first matching file
	if (handle != -1)
	{
		//find next matching file
		while (0 == _findnext(handle, &fb))
		{
			// "." and ".." are not processed
			noFile = strcmp(fb.name, "..");

			if (0 != noFile)
			{
				path.clear();
				path = dirPath + "/" + fb.name;

				//fb.attrib == 48 means folder
				if (fb.attrib == 48)
				{
					removeDir(path);
				}
				else
				{
					//not folder, delete it. if empty folder, using _rmdir istead.
					remove(path.c_str());
				}
			}
		}
		// close the folder and delete it only if it is closed. For standard c, using closedir instead(findclose -> closedir).
		// when Handle is created, it should be closed at last.  
		_findclose(handle);
	}
	_rmdir(dirPath.c_str());
	return 0;
}
string* ls(string folder)
{
	string* names = new string[15];
	string s = folder + "/*.*";
	wstring search_path = wstring(s.begin(), s.end());
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
	int i = 0;
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			// read all (real) files in current folder
			// , delete '!' read other 2 default folder . and ..
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				wstring ws(fd.cFileName);
				string str(ws.begin(), ws.end());
				names[i] = str;
				i++;
			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
	return names;
}
void clearLine(int y) {
	gotoXY(0, y);
	printf("%c[2K", 27);
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
void loading(int x, int y) {
	for (int i = 0; i < 20; i++) {
		gotoXY(i + x, y); cout << char(219);
		Sleep(100);
	}
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