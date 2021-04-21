#include "LoginSystem.h"
#include <string>
#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

const string userData = "data/users.csv";

struct User {
	int id;
	string password;
	bool isAdmin;
	User* prev;
	User* next;
};
struct List {
	User* pHead;
	User* pTail;
	int size;


};

User* createUser(string data) {
	User* usersData = new User;
	usersData->id = stoi(data.substr(0, data.find(',')));
	data.erase(0, data.find(',') + 1);
	usersData->password = data.substr(0, data.find(','));
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
void printUsersData(List listUsers) {
	User* temp = listUsers.pHead;
	while (temp != NULL) {
		cout << "Username: " << temp->id << endl;
		cout << "Password: " << temp->password << endl;
		cout << "Is admin: " << temp->isAdmin << endl;
		temp = temp->next;
	}
}

void loginScreen() {
	int quantity;
	List listUsers;
	readUsersData(listUsers);
	printUsersData(listUsers);

}