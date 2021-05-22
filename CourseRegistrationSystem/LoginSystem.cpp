#include "LoginSystem.h"

using namespace std;

const string userDataPath = "data/users.csv";
string id, password;
User* currentUser = NULL;
List listUser;

User* createUser(string data) {
	User* usersData = new User;
	usersData->id = data.substr(0, data.find(','));
	data.erase(0, data.find(',') + 1);
	usersData->password = data.substr(0, data.find(','));
	data.erase(0, data.find(',') + 1);
	usersData->fullName = data.substr(0, data.find(','));
	data.erase(0, data.find(',') + 1);
	usersData->className = data.substr(0, data.find(','));
	data.erase(0, data.find(',') + 1);
	usersData->gender = data.substr(0, data.find(','));
	data.erase(0, data.find(',') + 1);
	if (data.substr(0, data.find('\n')) == "TRUE") usersData->isAdmin = true;
	else usersData->isAdmin = false;
	usersData->next = NULL;
	usersData->prev = NULL;
	return usersData;
}
void addUser(List& list, User* user) {
	if (list.pHead == NULL) {
		list.pHead = list.pTail = user;
	}
	else {
		list.pTail->next = user;
		user->prev = list.pTail;
		list.pTail = user;
	}
}
void initList(List& list) {
	list.pHead = NULL;
	list.pTail = NULL;
	list.size = 0;
}
void readUsersData(List& listUsers) {
	ifstream fin(userDataPath);
	string  data = "";
	getline(fin, data);
	initList(listUsers);
	while (!fin.eof()) {
		getline(fin, data);
		if (data != "") {
			addUser(listUsers, createUser(data));
			listUsers.size++;
		}
	}
}

User* login(string id, string password, List list) {
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
		gotoXY(70, 13);
		if (isHidden) cout << char(254);
		else cout << " ";
		gotoXY(58 + passwrd.length(), 13);
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

void viewProfile(User* currUser) {
	cout << "Student ID: " << currUser->id << endl;
	cout << "Password: " << currUser->password << endl;
	cout << "Full name: " << currUser->fullName<< endl;
	cout << "Class: " << currUser->className << endl;
	cout << "Gender: " << currUser->gender << endl;
	if (currUser->isAdmin) cout << "Academic staff member" << endl;
	else cout << "Student" << endl;
}

void loginUI(List listUser) {
	const int width = 40;
	const int height = 10;
	const int left = 40;
	const int top = 8;
	drawTable(width, height, left, top);

	gotoXY(58, 6);
	cout << "LOGIN";
	gotoXY(48, 11);
	cout << "ID:";
	gotoXY(48, 13);
	cout << "PASSWORD:";
	gotoXY(70, 13);
	cout << char(254);
	cout << " Hidden";
	gotoXY(55, 11);
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
			gotoXY(55, 15);
			cout << "Wrong !!!!!";
			gotoXY(50, 16);
			cout << "Enter to try again...";
			_getch();
			system("cls");
		}
		else {
			gotoXY(55, 15);
			cout << "Successful";
			gotoXY(50, 16);
			cout << "Enter to continue...";
			_getch();
			system("cls");
			break;
		}
	}
}