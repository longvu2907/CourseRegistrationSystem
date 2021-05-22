#include "Globals.h"

void main() {
	while (true) {
		getCurrentDate();
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