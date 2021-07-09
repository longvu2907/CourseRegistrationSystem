#include "Student.h"

ListCourses enrolledCourses;
ListCourses registedCourses;
ListCourses posibleCourses;
const char cursor = char(175);

void userAccount();
void Profile();
void coursesReg();
void setting();

Course* copyCourseData(Course* src);
void saveRegistedCourses();
void getEnrolledCourses();
int command(int&, int, int, function<int(int)>);
int studentOption(int);
int coursesRegOption(int);

void getPosibleCourses() {
	initList(posibleCourses);
	Course* temp = listCourses.head;
	while (temp != NULL) {
		if (currentUser->academicYear <= temp->academicYear)
			addCourse(posibleCourses, copyCourseData(temp));
		temp = temp->next;
	}
}
void studentMenu() {
	const int width = 40;
	const int height = 10;
	const int left = 40;
	const int top = 8;

	int curPos = 0;
	int yPos = 10;

	do {
		hideCursor(true);
		schoolYearPath = "./data/" + currentSchoolYear;
		system("cls");
		drawBox(width, height, left, top);
		gotoXY(55, 5); cout << "HCMUS Portal";
		gotoXY(40, 6); cout << currentDate.wDay;
		gotoXY(40, 7); cout << dateToStr(currentDate);
		gotoXY(75, 6); cout << "Welcome ";
		gotoXY(75, 7); cout << currentUser->lastName << " " << currentUser->firstName;
		gotoXY(52, yPos); cout << "User account";
		yPos++;
		gotoXY(52, yPos); cout << "Profile";
		yPos++;
		gotoXY(52, yPos); cout << "Courses registration";
		yPos++;
		gotoXY(52, yPos); cout << "Setting";
		yPos++;
		yPos++;
		gotoXY(52, yPos); cout << "Exit";
		yPos = 10;
		if (curPos == 4) yPos++;
		gotoXY(50, curPos + yPos); cout << cursor;
		yPos = 10;
	} while (command(curPos, 0, 4, studentOption));
}

//Courses Registration
Course* copyCourseData(Course* src) {
	Course* newCourse = new Course;
	newCourse->id = src->id;
	newCourse->courseName = src->courseName;
	newCourse->teacherName = src->teacherName;
	newCourse->credits = src->credits;
	newCourse->maxStudents = src->maxStudents;
	newCourse->wDay = src->wDay;
	newCourse->session[0] = src->session[0];
	newCourse->session[1] = src->session[1];
	newCourse->academicYear = src->academicYear;
	newCourse->next = NULL;
	return newCourse;
}
bool isConflicted(Course* course) {
	Course* temp = registedCourses.head;
	while (temp != NULL) {
		if ((temp->session[0] == course->session[0] || temp->session[1] == course->session[1]
			|| temp->session[1] == course->session[0] || temp->session[0] == course->session[1])
			&& temp->wDay == course->wDay)
			return true;
		temp = temp->next;
	}
	return false;
}
Course* isRegistered(Course* course) {
	Course* temp = registedCourses.head;
	while (temp != NULL) {
		if (temp->id == course->id) return temp;
		temp = temp->next;
	}
	return NULL;
}
int registerCoursesOption(int curPos, int page) {
	int count = 0;
	
	Course* temp = posibleCourses.head;
	for (int i = 0; i < (page - 1) * 10; i++) {
		temp = temp->next;
	}
	Course* courseSelected = NULL;
	while (count < 10 && temp != NULL) {
		if (count == curPos) {
			courseSelected = temp;
			break;
		}
		count++;
		temp = temp->next;
	}
	if (courseSelected == NULL) {
		switch (curPos) {
		case 10:
			loading("Saving...");
			saveRegistedCourses();
			return 0;
		case 11:
			return 0;
		}
	}
	else {
		if (isRegistered(courseSelected) != NULL) deleteCourse(registedCourses, isRegistered(courseSelected));
		else if (registedCourses.size >= 5) notifyBox("You can enroll in at most 5 courses in a semester.");
		else if (isConflicted(courseSelected)) notifyBox("This course is conflicted with another course in your list of courses registed.");
		else {
			addCourse(registedCourses, copyCourseData(courseSelected));
		}
		return 1;
	}
}
int registerCoursesCommand(int& curPos, int minPos, int maxPos, int& page, int numberPages, function<int(int, int)> option) {
	int key = _getch();
	switch (key) {
	case 13:
		return option(curPos, page);
	case 224:
		key = _getch();
		switch (key) {
		case 72://up key
			if (curPos > minPos) curPos--;
			else {
				curPos = maxPos;
			}
			break;
		case 80://down key
			if (curPos < maxPos) curPos++;
			else {
				curPos = minPos;
			}
			break;
		case 75://left key
			if (page > 1) {
				page--;
				curPos = 0;
			}
			break;
		case 77://right key
			if (page < numberPages) {
				page++;
				curPos = 0;
			}
			break;
		}
	}
	return 1;
}
void registerCourses() {
	const int width = 85;
	int height = 7;
	const int left = 17;
	const int top = 8;
	int curPos = 0;
	int yPos = 13;
	int numberPages = (posibleCourses.size / 10) + 1;
	int page = 1;
	int i = 0;
	registedCourses = enrolledCourses;

	do {
		i = 0;
		if (isOnRegSession()) {
			system("cls");
			height = 7;
			height += posibleCourses.size;
			gotoXY(55, 5); cout << "HCMUS Portal";
			gotoXY(53, 7); cout << "Register Courses";
			gotoXY(20, 10); cout << "ID";
			gotoXY(30, 10); cout << "Course name";
			gotoXY(55, 10); cout << "Number of";
			gotoXY(55, 11); cout << "students";
			gotoXY(66, 10); cout << "Number of";
			gotoXY(66, 11); cout << "enroller";
			gotoXY(77, 10); cout << "Academic";
			gotoXY(79, 11); cout << "year";
			gotoXY(87, 10); cout << "Schedule";
			drawBox(width, height, left, top);
			if (posibleCourses.head != NULL) {
				Course* temp = posibleCourses.head;
				for (int i = 0; i < (page - 1) * 10; i++) {
					temp = temp->next;
				}
				while (i < 10 && temp != NULL) {
					gotoXY(20, yPos); cout << temp->id;
					string courseName = temp->courseName;
					if (courseName.length() > 24) courseName = courseName.substr(0, 24);
					gotoXY(30, yPos); cout << courseName;
					gotoXY(57, yPos); cout << temp->maxStudents;
					gotoXY(68, yPos); cout << temp->numberRegistered;
					gotoXY(79, yPos); cout << temp->academicYear;
					string schedule = temp->wDay + "(" + temp->session[0] + "-" + temp->session[1] + ")";
					gotoXY(87, yPos); cout << schedule;
					gotoXY(100, yPos);
					if (isRegistered(temp)) cout << char(254);
					else cout << " ";
					yPos++;
					i++;
					temp = temp->next;
				}
				yPos++;
				gotoXY(60, yPos);
				if (page > 1) cout << char(174);
				cout << char(174) << "  " << page << "  " << char(175);
				if (page < numberPages) cout << char(175);
				yPos++;
				gotoXY(20, yPos); cout << "Save";
				yPos++;
				gotoXY(20, yPos); cout << "Back";
				yPos = 13;
				if (curPos == 10 || curPos == 11) yPos += 2;
				gotoXY(18, curPos + yPos); cout << cursor;
				yPos = 13;
			}
			else {
				notifyBox("Empty List...");
				return;
			}
		}
		else {
			notifyBox("Courses registration session has expired from " + dateToStr(listCourses.endDate));
			return;
		}
	} while (registerCoursesCommand(curPos, 0, 11, page, numberPages, registerCoursesOption));
}
void viewEnrolledCourses() {
	const int width = 40;
	int height = 5;
	const int left = 40;
	const int top = 8;
	int curPos = 0;
	int yPos = 10;

	do {
		system("cls");
		height = 5;
		height += enrolledCourses.size;
		gotoXY(55, 5); cout << "HCMUS Portal";
		gotoXY(53, 7); cout << "Register Courses";
		drawBox(width, height, left, top);
		if (enrolledCourses.head != NULL) {
			Course* temp = enrolledCourses.head;
			while (temp != NULL) {
				gotoXY(43, yPos); cout << temp->id << "   " << temp->courseName;
				yPos++;
				temp = temp->next;
			}
			yPos++;
			gotoXY(58, yPos); cout << "Back";
			yPos = 10;
			if (curPos == enrolledCourses.size) yPos++;
			gotoXY(78, curPos + yPos); cout << cursor;
			yPos = 10;
		}
		else {
			notifyBox("Empty List...");
			return;
		}
	} while (command(curPos, 0, enrolledCourses.size, studentOption));
}
void coursesReg() {
	const int width = 40;
	const int height = 10;
	const int left = 40;
	const int top = 8;

	int curPos = 0;
	int yPos = 10;
	do {
		getListCourses();
		getEnrolledCourses();
		getPosibleCourses();
		hideCursor(true);
		schoolYearPath = "./data/" + currentSchoolYear;
		system("cls");
		drawBox(width, height, left, top);
		gotoXY(55, 5); cout << "HCMUS Portal";
		gotoXY(51, 7); cout << "Courses Registration";
		gotoXY(48, yPos); cout << "Register Courses";
		yPos++;
		gotoXY(48, yPos); cout << "View Enrolled Courses";
		yPos++;
		yPos++;
		gotoXY(48, yPos); cout << "Back";
		yPos = 10;
		if (curPos == 2) yPos++;
		gotoXY(46, curPos + yPos); cout << cursor;
		yPos = 10;
	} while (command(curPos, 0, 2, coursesRegOption));
}


int studentOption(int curPos) {
	switch (curPos) {
	case 0:
		userAccount();
		break;
	case 1:
		Profile();
		break;
	case 2:
		coursesReg();
		break;
	case 3:
		setting();
		break;
	case 4:
		exit(0);
		break;
	}
	return 1;
}
int coursesRegOption(int curPos) {
	switch (curPos) {
	case 0:
		registerCourses();
		break;
	case 1:
		viewEnrolledCourses();
		break;
	case 2:
		return 0;
		break;
	case 3:
		setting();
		break;
	}
	return 1;
}

void saveRegistedCourses() {
	ofstream fout(semesterPath + "/student/" + currentUser->id + ".dat");
	Course* temp = registedCourses.head;
	while (temp != NULL) {
		toUpper(temp->wDay);
		string session = temp->session[0] + "-" + temp->session[1];
		fout << temp->id << "," << temp->courseName << "," << temp->teacherName << ","
			<< temp->credits << "," << temp->academicYear << "," << temp->maxStudents << "," << temp->wDay << "," << session << endl;
		temp = temp->next;
	}
	fout.close();
}
void getEnrolledCourses() {
	ifstream fin(semesterPath + "/student/" + currentUser->id + ".dat");
	initList(enrolledCourses);
	if (!fin) return;
	while (true) {
		Course* course = convertCourseData(fin);
		if (fin.eof()) break;
		addCourse(enrolledCourses, course);
	}
}