#include "Globals.h"

void main() {
	while (true) {
		getCurrentDate();
		getCurrentSchoolYear();
		loginSystem();
		if (currentUser->isStaff) {
			staffMenu();
		}
		else {
			studentMenu();
		}
		system("cls");
	}

}