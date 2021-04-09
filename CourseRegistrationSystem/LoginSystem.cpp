#include "LoginSystem.h"
#include <string>
#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

struct User {
	int id;
	string password;
	bool isAdmin;
	int size;
	User* next;
};

const string userData = "data/users.csv";

void readUsersData(User*& usersData, int& numbers) {
	ifstream fin(userData);
	string s, data = "";
	//Allocate for usersData
	getline(fin, s);
	int count = 0;
	while (!fin.eof()) {
		getline(fin, s);
		if (s != "") {
			data += s + '\n';
			count++;
		}
	}
	usersData = new User[count];
	cout << data;
	//Read data from csv file
	for (int i = 0; i < count; i++) {
		usersData[i].id = stoi(data.substr(0, data.find(',')));
		data.erase(0, data.find(',') + 1);
		usersData[i].password = data.substr(0, data.find(','));
		data.erase(0, data.find(',') + 1);
		if (data.substr(0, data.find('\n')) == "TRUE") usersData[i].isAdmin = true;
		else usersData[i].isAdmin = false;
		data.erase(0, data.find('\n') + 1);
		cout << usersData[i].id << endl;
		cout << usersData[i].password << endl;
		cout << usersData[i].isAdmin << endl;
	}

}

void loginScreen() {
	User* usersData;
	int quantity;
	readUsersData();

}