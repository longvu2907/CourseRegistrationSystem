#include "AcademicStaff.h"

const char cursor = char(174);
string schoolYearPath;

int command(int&, int, int, function<int(int)>);
int staffOption(int);
int userAccountOption(int);
int profileOption(int);
int manageStudentOption(int);

void userAccount();
void changePassword();
void logout();
void Profile();
void manageStudent();
void createSchoolYear();
void createClasses();

void staffMenu() {
	const int width = 40;
	const int height = 10;
	const int left = 40;
	const int top = 8;

	int curPos = 0;
	int yPos = 9;
	schoolYearPath = "./Data/" + currentSchoolYear;
	do {
		hideCursor(true);
		system("cls");
		drawTable(width, height, left, top);
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
		yPos = 9;
		gotoXY(70, curPos + yPos); cout << cursor;
	} while (command(curPos, 0, 2, staffOption));
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
		drawTable(width, height, left, top);
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
		drawTable(width, height, left, top);
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
		drawTable(width, height, left, top);
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

User* convertData(ifstream& data, string className) {
	User* newUser = new User;
	string s, dateOfBirth;
	getline(data, s, ',');
	if (s == "") return NULL;
	getline(data, newUser->id, ',');
	getline(data, newUser->lastName, ',');
	getline(data, newUser->firstName, ',');
	getline(data, newUser->gender, ',');
	getline(data, dateOfBirth, ',');
	newUser->dateOfBirth = strToDate(dateOfBirth);
	getline(data, newUser->password, '\n');
	newUser->isStaff = false;
	newUser->className = className;
	newUser->next = NULL;
	newUser->prev = NULL;
	return newUser;
}
void addStudentAccount(string program) {
	string dataPath = "./Data/Students/1st-year/" + program;
	string* classes = ls(dataPath);
	int i = 0;
	while (classes[i] != "") {
		string className = classes[i].substr(0, classes[i].find('.'));
		string path = dataPath + "/" + classes[i];
		ifstream fin(path);
		string s = "";
		getline(fin, s);
		while (!fin.eof()) {
			addUser(listUser, convertData(fin,className));
			listUser.size++;
		}
		i++;
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
		drawTable(width, height, left, top);
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
void createClasses() {
	char importedFiles[] = "./Data/Files Imported";
	char firstYear[] = "./Data/Students/1st-year";
	char secondYear[] = "./Data/Students/2nd-year";
	char thirdYear[] = "./Data/Students/3rd-year";
	char fourthYear[] = "./Data/Students/4th-year";
	removeDir(fourthYear); //Remove students graduated
	rename(thirdYear, fourthYear);//third-year Student up to fourth-year
	rename(secondYear, thirdYear);//second-year Student up to third-year
	rename(firstYear, secondYear);//first-year Student up to second-year
	_mkdir(firstYear);//Create first-year Students folder
	
}
void createSchoolYear() {
	if (dirExists(schoolYearPath)) {
		cout << "Can not create new school year this time.";
	}
	else {
		cout << "New school year has been created";
		createClasses();
		/*_mkdir(schoolYearPath.c_str());
		addStudentAccount("VP");
		saveListUser();*/
	}
	_getch();
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
		return 0;
		break;
	case 2:
		return 0;
		break;
	}
	return 1;
}