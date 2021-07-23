#include "LoginSystem.h"

using namespace std;

const string userDataPath = "data/accounts/users.csv";
string id, password;
User* currentUser = NULL;
ListUser listUser;
int yPos = 13;


void getListUsers() {
	ifstream fin(userDataPath);
	string  data = "";
	getline(fin, data);
	initList(listUser);
	while (!fin.eof()) {
		addUser(listUser, convertUserData(fin));
	}
}

User* login(string id, string password) {
	User* data = listUser.head;
	while (data != NULL) {
		if (id == data->id) {
			if (password == data->password) return data;
			else return NULL;
		}
		data = data->next;
	}
	return NULL;
}
string getPassword(bool isHidden) {
	string passwrd = "";
	while (true) {
		gotoXY(79, yPos + 2);
		if (isHidden) cout << char(254);
		else cout << " ";
		gotoXY(58 + passwrd.length(), yPos + 2);
		char ch;
		ch = _getch();
		if (ch == 13) {
			cout << endl;
			return passwrd;
		}
		else if (ch == 0) {
			ch = _getch();
			if (ch == 59) {
				if (isHidden) {
					string temp = passwrd;
					while (temp.length() > 0) {
						cout << "\b \b";
						temp.pop_back();
					}
					cout << passwrd;
				}
				else {
					string temp = passwrd;
					while (temp.length() > 0) {
						cout << "\b \b";
						temp.pop_back();
					}
					for (int i = 0; i < passwrd.length(); i++) {
						cout << '*';
					}
				}
				isHidden = !isHidden;
			}
		}
		else if (ch == 8) {
			if (passwrd.length() > 0) {
				cout << "\b \b";
				passwrd.pop_back();
			}
		}
		else if (passwrd.length() == 13) {

		}
		else {
			passwrd += ch;
			if (isHidden) {
				cout << "*";
			}
			else cout << ch;
		}	
	}
}

void loginUI() {
	const int width = 40;
	const int height = 10;
	const int left = 40;
	const int top = 10;

	drawBox(width, height, left, top);
	textAlignCenter("HCMUS PORTAL", left, width, 6);
	textAlignCenter("LOGIN", left, width, 7);
	gotoXY(40, 8); cout << currentDate.wDay;
	gotoXY(40, 9); cout << dateToStr(currentDate);
	gotoXY(48, yPos);
	cout << "ID:";
	gotoXY(48, yPos + 2);
	cout << "PASSWORD:";
	gotoXY(72, yPos + 2);
	cout << " Hidden";
	cout << char(254);
	gotoXY(48, yPos + 3);
	cout << "(press F1 to show password)";
	gotoXY(55, yPos);
	getline(cin, id);
	password = getPassword(true);
	currentUser = login(id, password);
}

void loginSystem() {
	system("cls");
	getListUsers();
	getCurrentSchoolYear();
	getCurrentSemester();
	getListCourses();
	schoolYearPath = "./data/" + currentSchoolYear;

	while (true) {
		hideCursor(false);
		loginUI();
		if (currentUser == NULL) {
			notifyBox("Login Fail");
		}
		else {
			notifyBox("Login Succesful");
			break;
		}
	}
	if (currentUser->isStaff) {
		staffMenu();
	}
	else {
		studentMenu();
	}
	system("cls");
}