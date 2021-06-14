#include "LoginSystem.h"

using namespace std;

const string userDataPath = "data/accounts/users.csv";
string id, password;
User* currentUser = NULL;
ListUser listUser;
int yPos = 13;

User* convertData(ifstream& data) {
	User* usersData = new User;
	Date dateOfBirth;
	string temp;
	getline(data,usersData->id,',');
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
void readUsersData(ListUser& listUsers) {
	ifstream fin(userDataPath);
	string  data = "";
	getline(fin, data);
	initList(listUsers);
	while (!fin.eof()) {
		addUser(listUsers, convertData(fin));
		listUsers.size++;
	}
}

User* login(string id, string password, ListUser list) {
	User* data = list.pHead;
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
		gotoXY(70, yPos + 2);
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
		else if (passwrd.length() == 10) {

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

void loginUI(ListUser listUser) {
	const int width = 40;
	const int height = 10;
	const int left = 40;
	const int top = 10;

	drawBox(width, height, left, top);
	gotoXY(52, 6);
	cout << "HCMUS PORTAL - LOGIN";
	gotoXY(40, 8); cout << currentDate.wDay;
	gotoXY(40, 9); cout << dateToStr(currentDate);
	gotoXY(48, yPos);
	cout << "ID:";
	gotoXY(48, yPos + 2);
	cout << "PASSWORD:";
	gotoXY(70, yPos + 2);
	cout << char(254);
	cout << " Hidden";
	gotoXY(48, yPos + 3);
	cout << "(press F1 to show password)";
	gotoXY(55, yPos);
	getline(cin, id);
	password = getPassword(true);
	currentUser = login(id, password, listUser);
	
}

void loginSystem() {
	system("cls");
	readUsersData(listUser);
	while (true) {
		hideCursor(false);
		loginUI(listUser);
		if (currentUser == NULL) {
			notifyBox("LOGIN FAIL!");
		}
		else {
			notifyBox("LOGIN SUCCEEDED");
			break;
		}
	}
}