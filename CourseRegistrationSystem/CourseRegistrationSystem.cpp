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
	/*gotoXY(5, 0); cout << "Creating A";
	loading(5, 1);
	clearLine(1);
	gotoXY(5,1); cout << "Done";
	gotoXY(5, 2); cout << "Creating B";
	loading(5, 3);
	clearLine(3);
	gotoXY(5, 3); cout << "Done";
	gotoXY(5, 4); cout << "Creating C";
	loading(5,5);
	clearLine(5);
	gotoXY(5, 5); cout << "Done";*/
}