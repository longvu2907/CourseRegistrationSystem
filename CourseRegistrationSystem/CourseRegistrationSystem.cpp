#include <iostream>
#include <fstream>
#include <string>

#include "Globals.h"
#include "LoginSystem.h"

using namespace std;

void main() {
	while (true) {
		loginSystem();
		if (currentUser->isAdmin) {
			staffMenu();
		}
		else {
			studentMenu();
		}
		system("cls");
	}
}