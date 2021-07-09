#include "Student.h"

ListCourses enrolledCourses;
ListCourses registedCourses;
const char cursor = char(175);

void userAccount();
void Profile();
void coursesReg();
void setting();

void saveEnrolledCourses();
void getEnrolledCourses();
int command(int&, int, int, function<int(int)>);
int studentOption(int);
int coursesRegOption(int);


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
int registerCoursesOption(int curPos) {
	int count = 0;
	
	Course* temp = listCourses.head;
	Course* courseChoosed = NULL;
	while (temp != NULL) {
		if (count == curPos) {
			courseChoosed = temp;
			break;
		}
		count++;
		temp = temp->next;
	}
	if (courseChoosed == NULL) {
		return 0;
	}
	else {
		if (isRegistered(courseChoosed) != NULL) deleteCourse(registedCourses, isRegistered(courseChoosed));
		else if (registedCourses.size >= 5) notifyBox("You can enroll in at most 5 courses in a semester.");
		else if (isConflicted(courseChoosed)) notifyBox("This course is conflicted with another course in your list of courses registed.");
		else {
			addCourse(registedCourses, copyCourseData(courseChoosed));
		}
		return 1;
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

	initList(registedCourses);
	do {
		if (isOnRegSession()) {
			system("cls");
			height = 7;
			height += listCourses.size;
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
			if (listCourses.head != NULL) {
				Course* temp = listCourses.head;
				while (temp != NULL) {
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
					temp = temp->next;
				}
				yPos++;
				gotoXY(20, yPos); cout << "Back";
				yPos = 13;
				if (curPos == listCourses.size) yPos++;
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
	} while (command(curPos, 0, listCourses.size, registerCoursesOption));
}
void viewEnrolledCourses() {
	const int width = 40;
	int height = 5;
	const int left = 40;
	const int top = 8;
	int curPos = 0;
	int yPos = 10;
	
	getEnrolledCourses();
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

void saveEnrolledCourses() {
	ofstream fout(semesterPath + "/student/" + currentUser->id + ".dat", ios::binary);
	Course* temp = enrolledCourses.head;
	while (temp != NULL) {
		Course data = *temp;
		fout.write((char*)&data, sizeof(Course));
	}
	fout.close();
}
void getEnrolledCourses() {
	initList(enrolledCourses);
	saveEnrolledCourses();
}