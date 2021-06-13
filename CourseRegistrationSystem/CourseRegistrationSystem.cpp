#include "Globals.h" 

void main() {
	while (true) {
		getCurrentDate();
		getCurrentSchoolYear();
		getCurrentSemester();
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