#include "Globals.h" 

void main() {
	while (true) {
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