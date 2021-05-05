#include "LoginSystem.h"

using namespace std;

const string userData = "data/users.csv";
string id, password;
User* currentUser = NULL;


void drawTable() {
	
	gotoXY(0, consoleRect->right);
	for (int i = consoleRect->left; i < consoleRect->right; i++) {
		cout << char(205);
	}
}
void loginUI() {
	getConsoleSize();
	drawTable();
}

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
	ifstream fin(userData);
	string  data = "";
	//Allocate for usersData
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

void checkUser(string id, string password, List list, User* &currUser) {
	User* data = list.pHead;
	while (data != NULL) {
		if (id == data->id) {
			if (password == data->password) currUser = data;
			else break;
		}
		data = data->next;
	}
}
void getPassword(bool isHidden) {
	password = "";
	while (true) {
		char ch;
		ch = _getch();
		if (ch == 13) {
			cout << endl;
			return;
		}
		else if (ch == 0) {
			ch = _getch();
			if (ch == 59) {
				if (isHidden) {
					string temp = password;
					while (temp.length() > 0) {
						cout << "\b \b";
						temp.pop_back();
					}
					cout << password;
				}
				else {
					string temp = password;
					while (temp.length() > 0) {
						cout << "\b \b";
						temp.pop_back();
					}
					for (int i = 0; i < password.length(); i++) {
						cout << '*';
					}
				}
				isHidden = !isHidden;
			}
		}
		else if (ch == 8) {
			if (password.length() > 0) {
				cout << "\b \b";
				password.pop_back();
			}
		}
		else if (password.length() == 10) {

		}
		else {
			password += ch;
			if (isHidden) {
				cout << "*";
			}
			else cout << ch;
		}
		
	}
}
void loginScreen(List list, User* &currUser) {
	cout << "Id: ";
	cin >> id;
	cout << "Password: ";
	cin.ignore();
	getPassword(true);
	cout << password;
	checkUser(id, password, list, currUser);
	if (currUser == NULL) cout << "Try again" << endl;
	else cout << "Successful" << endl;
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



void login() {
	/*string s;
	List listUsers;
	hideCursor();
	readUsersData(listUsers);
	hideCursor();
	loginScreen(listUsers, currentUser);
	viewProfile(currentUser);*/
	hideCursor();
	while (true) {
		loginUI();
	}
}