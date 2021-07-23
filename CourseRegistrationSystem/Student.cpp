#include "Student.h"

ListCourses enrolledCourses;
ListCourses posibleCourses;
const char cursorLeft = char(175);
const char cursorRight = char(174);

void coursesReg();

Course* copyCourseData(Course* src);
void saveEnrolledCourses();
void getEnrolledCourses();
void getPosibleCourses();
void addStudentInCourses();
ListStudent getListOfStudentInCourse(Course* course);
void saveListCourses(ListCourses);
void saveListOfStudentInCourse(Course* course, ListStudent list);
int command(int&, int, int, function<int(int)>);
int studentOption(int);
int viewCoursesCommand(int&, int, int, int&, int, function<int(int, int)>);
int updateCourseCommand(int&, int, int, Course*, function<int(int, Course*)>);
void courseDetail(Course* course);
int coursesRegOption(int);

void studentMenu() {
	const int width = 40;
	const int height = 12;
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
		gotoXY(52, yPos); cout << "Scoreboard";
		yPos++;
		gotoXY(52, yPos); cout << "List of classes";
		yPos++;
		gotoXY(52, yPos); cout << "List of courses";
		yPos++;
		gotoXY(52, yPos); cout << "Setting";
		yPos++;
		yPos++;
		gotoXY(52, yPos); cout << "Exit";
		yPos = 10;
		if (curPos == 7) yPos++;
		gotoXY(50, curPos + yPos); cout << cursorLeft;
		gotoXY(75, curPos + yPos); cout << cursorRight;
		yPos = 10;
	} while (command(curPos, 0, 7, studentOption));
}

//Courses Registration
void removeStudentInCourse(ListStudent& list, Student* student) {
	Student* temp = list.head;
	while (temp != NULL) {
		if (temp->studentID == student->studentID) {
			removeStudent(list, temp);
			return;
		}
		temp = temp->next;
	}
}
Student* toStudent(User* user) {
	Student* student = new Student;
	student->studentID = user->id;
	student->socialID = user->password;
	student->lastName = user->lastName;
	student->firstName = user->firstName;
	student->gender = user->gender;
	student->dateOfBirth = user->dateOfBirth;
	student->academicYear = user->academicYear;
	student->prev = NULL;
	student->next = NULL;
	return student;
}
Course* copyCourseData(Course* src) {
	Course* newCourse = new Course;
	newCourse->id = src->id;
	newCourse->courseName = src->courseName;
	newCourse->teacherName = src->teacherName;
	newCourse->credits = src->credits;
	newCourse->maxStudents = src->maxStudents;
	newCourse->numberRegistered = src->numberRegistered;
	newCourse->wDay = src->wDay;
	newCourse->session[0] = src->session[0];
	newCourse->session[1] = src->session[1];
	newCourse->academicYear = src->academicYear;
	newCourse->next = NULL;
	return newCourse;
}
bool isConflicted(Course* course) {
	Course* temp = enrolledCourses.head;
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
	Course* temp = enrolledCourses.head;
	while (temp != NULL) {
		if (temp->id == course->id) return temp;
		temp = temp->next;
	}
	return NULL;
}
int registerCoursesOption(int curPos, int maxPos, int page) {
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
		int n = maxPos - curPos;
		switch (n) {
		case 1:
			loading("Saving...");
			saveEnrolledCourses();
			saveListCourses(posibleCourses);
			addStudentInCourses();
			return 0;
		case 0:
			return 0;
		}
	}
	else {
		if (isRegistered(courseSelected) != NULL) notifyBox("You have already registered this course.");
		else if (enrolledCourses.size >= 5) notifyBox("You can enroll in at most 5 courses in a semester.");
		else if (isConflicted(courseSelected)) notifyBox("This course is conflicted with another course in your list of courses registed.");
		else {
			if (courseSelected->numberRegistered >= courseSelected->maxStudents) notifyBox("This course is full");
			else {
				courseSelected->numberRegistered++;
				addCourse(enrolledCourses, copyCourseData(courseSelected));
			}
		}
		return 1;
	}
}
int registerCoursesCommand(int& curPos, int minPos, int maxPos, int& page, int numberPages, function<int(int, int, int)> option) {
	int key = _getch();
	switch (key) {
	case 13:
		return option(curPos, maxPos, page);
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
	int height = 10;
	const int left = 17;
	const int top = 8;
	int curPos = 0;
	int yPos = 13;
	int numberPages;
	int page = 1;
	int i = 0;

	getListCourses();
	getPosibleCourses();
	do {
		height = 10;
		i = 0;
		numberPages = (posibleCourses.size / 10) + 1;
		if (isOnRegSession()) {
			system("cls");
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
				height += i;
				drawBox(width, height, left, top);
				yPos++;
				gotoXY(58, yPos);
				if (page > 1) cout << char(174);
				cout << char(174) << "  " << page << "  " << char(175);
				if (page < numberPages) cout << char(175);
				yPos++;
				gotoXY(59, yPos); cout << "Save";
				yPos++;
				gotoXY(59, yPos); cout << "Back";
				yPos = 13;
				if (curPos == i || curPos == i + 1) {
					yPos += 2;
					gotoXY(57, curPos + yPos); cout << cursorLeft;
					gotoXY(64, curPos + yPos); cout << cursorRight;
				}
				else {
					gotoXY(18, curPos + yPos); cout << cursorLeft;
					gotoXY(102, curPos + yPos); cout << cursorRight;
				}
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
	} while (registerCoursesCommand(curPos, 0, i + 1, page, numberPages, registerCoursesOption));
}
int updateEnrolledListOption(int curPos, Course* course) {
	switch (curPos)
	{
	case 0:
		courseDetail(course);
		return 1;
		break;
	case 1:
		if (confirmBox()) {
			ListStudent list = getListOfStudentInCourse(course);
			course->numberRegistered--;
			saveListCourses(enrolledCourses);
			removeStudentInCourse(list, toStudent(currentUser));
			saveListOfStudentInCourse(course, list);
			removeCourse(enrolledCourses, course);
		}
		else return 1;
		break;
	case 2:
		break;
	}
	
	saveEnrolledCourses();
	return 0;
}
void updateEnrolledList(Course* course) {
	const int width = 30;
	const int height = 7;
	const int left = 45;
	const int top = 8;
	int curPos = 0;
	int yPos = 10;

	do {
		system("cls");
		gotoXY(55, 5); cout << "HCMUS Portal";
		gotoXY(55, 7); cout << "Update Course";
		drawBox(width, height, left, top);
		gotoXY(58, yPos); cout << "Detail";
		yPos++;
		gotoXY(58, yPos); cout << "Remove";
		yPos++;
		yPos++;
		gotoXY(58, yPos); cout << "Back";
		yPos = 10;
		if (curPos == 2) yPos++;
		gotoXY(56, curPos + yPos); cout << cursorLeft;
		gotoXY(65, curPos + yPos); cout << cursorRight;
		yPos = 10;
	} while (updateCourseCommand(curPos, 0, 2, course, updateEnrolledListOption));

	saveCourses();
}
int viewEnrolledListOption(int curPos, int page) {
	int count = 0;

	Course* temp = enrolledCourses.head;
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
		return 0;
	}
	else {
		if (isOnRegSession()) updateEnrolledList(courseSelected);
		else courseDetail(courseSelected);
	}
	return 1;
}
void viewEnrolledList() {
	const int width = 50;
	int height = 9;
	const int left = 35;
	const int top = 8;
	int curPos = 0;
	int yPos = 13;
	int numberPages;
	int page = 1;
	int i = 0;

	do {
		numberPages = (enrolledCourses.size / 10) + 1;
		i = 0;
		height = 9;
		system("cls");
		gotoXY(55, 5); cout << "HCMUS Portal";
		gotoXY(55, 7); cout << "List Course";
		gotoXY(38, 10); cout << "ID";
		gotoXY(48, 10); cout << "Course name";
		gotoXY(73, 10); cout << "Schedule";
		if (enrolledCourses.head != NULL) {
			Course* temp = enrolledCourses.head;
			for (int i = 0; i < (page - 1) * 10; i++) {
				temp = temp->next;
			}
			while (i < 10 && temp != NULL) {
				gotoXY(38, yPos); cout << temp->id;
				string courseName = temp->courseName;
				if (courseName.length() > 24) courseName = courseName.substr(0, 24);
				gotoXY(48, yPos); cout << courseName;
				string schedule = temp->wDay + "(" + temp->session[0] + "-" + temp->session[1] + ")";
				gotoXY(73, yPos); cout << schedule;
				yPos++;
				i++;
				temp = temp->next;
			}
			height += i;
			drawBox(width, height, left, top);
			yPos++;
			gotoXY(58, yPos);
			if (page > 1) cout << char(174);
			cout << char(174) << "  " << page << "  " << char(175);
			if (page < numberPages) cout << char(175);
			yPos++;
			gotoXY(59, yPos); cout << "Back";
			yPos = 13;
			if (curPos == i) {
				yPos += 2;
				gotoXY(57, curPos + yPos); cout << cursorLeft;
				gotoXY(64, curPos + yPos); cout << cursorRight;
			}
			else {
				gotoXY(36, curPos + yPos); cout << cursorLeft;
				gotoXY(84, curPos + yPos); cout << cursorRight;
			}
			yPos = 13;
		}
		else {
			notifyBox("Empty List...");
			return;
		}
	} while (viewCoursesCommand(curPos, 0, i, page, numberPages, viewEnrolledListOption));
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
		gotoXY(52, yPos); cout << "Register Courses";
		yPos++;
		gotoXY(52, yPos); cout << "View Enrolled Courses";
		yPos++;
		yPos++;
		gotoXY(52, yPos); cout << "Back";
		yPos = 10;
		if (curPos == 2) yPos++;
		gotoXY(50, curPos + yPos); cout << cursorLeft;
		gotoXY(76, curPos + yPos); cout << cursorRight;
		yPos = 10;
	} while (command(curPos, 0, 2, coursesRegOption));
}

//View classes list
void viewScoreboard(Class* c);
void viewListOfStudent(Class* c);
int classDetailCommand(int& curPos, int minPos, int maxPos, Class* c, function<int(int, Class*)> option) {
	int key = _getch();
	switch (key) {
	case 13:
		return option(curPos, c);
	case 224:
		key = _getch();
		switch (key) {
		case 72:
			if (curPos > minPos) curPos--;
			else {
				curPos = maxPos;
			}
			break;
		case 80:
			if (curPos < maxPos) curPos++;
			else {
				curPos = minPos;
			}
			break;
		}
	}
	return 1;
}
int classDetailOption(int curPos, Class *c) {
	switch (curPos) {
	case 0:
		viewListOfStudent(c);
		break;
	case 1:
		viewScoreboard(c);
		break;
	case 2:
		return 0;
		break;
	}
	return 1;
}
void classDetail(Class* c) {
	const int width = 30;
	const int height = 7;
	const int left = 45;
	const int top = 8;
	int curPos = 0;
	int yPos = 10;

	do {
		system("cls");
		gotoXY(55, 5); cout << "HCMUS Portal";
		gotoXY(55, 7); cout << "Class Option";
		drawBox(width, height, left, top);
		textAlignCenter("List Of Student", left, width, yPos);
		yPos++;
		textAlignCenter("Scoreboard Of Class", left, width, yPos);
		yPos++;
		yPos++;
		gotoXY(58, yPos); cout << "Back";
		yPos = 10;
		if (curPos == 2) yPos++;
		if (curPos == 2) {
			gotoXY(56, curPos + yPos); cout << cursorLeft;
			gotoXY(65, curPos + yPos); cout << cursorRight;
		}
		else {
			gotoXY(48, curPos + yPos); cout << cursorLeft;
			gotoXY(73, curPos + yPos); cout << cursorRight;
		}
		yPos = 10;
	} while (classDetailCommand(curPos, 0, 2, c, classDetailOption));

}
string studentYear(int year);
ListStudent getListOfStudentInClass(Class* c) {
	ListStudent list;
	initList(list);
	ifstream fin(c->path);
	if (fin.fail()) {
		return list;
	}
	string s;
	getline(fin, s);
	while (!fin.eof()) {
		addStudent(list, convertStudentData(fin));
	}
	return list;
}
int viewListOfStudentOption(int curPos, int page) {
	return 0;
}
void viewListOfStudent(Class* c) {
	const int width = 54;
	int height = 9;
	const int left = 33;
	const int top = 8;
	int curPos = 0;
	int yPos = 12;
	int numberPages;
	int page = 1;
	int i = 0;
	int no;
	ListStudent list = getListOfStudentInClass(c);
	do {
		numberPages = (list.size / 10) + 1;
		i = 0;
		height = 9;
		system("cls");
		gotoXY(55, 5); cout << "HCMUS Portal";
		gotoXY(58, 7); cout << c->className;
		gotoXY(36, 10); cout << "No";
		gotoXY(42, 10); cout << "ID";
		gotoXY(52, 10); cout << "Last name";
		gotoXY(77, 10); cout << "First name";
		if (list.head != NULL) {
			Student* temp = list.head;
			for (int i = 0; i < (page - 1) * 10; i++) {
				temp = temp->next;
			}
			while (i < 10 && temp != NULL) {
				no = (page - 1) * 10 + i + 1;
				gotoXY(36, yPos); cout << no;
				gotoXY(42, yPos); cout << temp->studentID;
				string lastName = temp->lastName;
				if (lastName.length() > 24) lastName = lastName.substr(0, 24);
				gotoXY(52, yPos); cout << lastName;
				gotoXY(77, yPos); cout << temp->firstName;
				yPos++;
				i++;
				temp = temp->next;
			}
			height += i;
			drawBox(width, height, left, top);
			yPos++;
			gotoXY(58, yPos);
			if (page > 1) cout << char(174);
			cout << char(174) << "  " << page << "  " << char(175);
			if (page < numberPages) cout << char(175);
			yPos++;
			gotoXY(59, yPos); cout << "Back";
			gotoXY(57, curPos + yPos); cout << cursorLeft;
			gotoXY(64, curPos + yPos); cout << cursorRight;
			yPos = 12;
		}
		else {
			notifyBox("Empty List...");
			return;
		}
	} while (viewCoursesCommand(curPos, 0, 0, page, numberPages, viewListOfStudentOption));
}
int viewListOfClassesCommand(int& curPos, int minPos, int maxPos, int& page, int numberPages, function<int(int, int)> option) {
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
int viewListOfClassesOption(int curPos, int page) {
	int count = 0;

	Class* temp = listClasses.head;
	for (int i = 0; i < (page - 1) * 10; i++) {
		temp = temp->next;
	}
	Class* classSelected = NULL;
	while (count < 10 && temp != NULL) {
		if (count == curPos) {
			classSelected = temp;
			break;
		}
		count++;
		temp = temp->next;
	}
	if (classSelected == NULL) {
		return 0;
	}
	else {
		if (currentUser->isStaff) classDetail(classSelected);
		else viewListOfStudent(classSelected);
	}
	return 1;
}
void viewListOfClasses(string year) {
	const int width = 40;
	int height = 6;
	const int left = 40;
	const int top = 8;
	int curPos = 0;
	int yPos = 10;
	int numberPages;
	int page = 1;
	int i = 0;

	getListClasses(year);
	do {
		numberPages = (listClasses.size / 10) + 1;
		i = 0;
		height = 6;
		system("cls");
		gotoXY(55, 5); cout << "HCMUS Portal";
		gotoXY(52, 7); cout << year;
		if (listClasses.head != NULL) {
			Class* temp = listClasses.head;
			for (int i = 0; i < (page - 1) * 10; i++) {
				temp = temp->next;
			}
			while (i < 10 && temp != NULL) {
				gotoXY(58, yPos); cout << temp->className;
				yPos++;
				i++;
				temp = temp->next;
			}
			height += i;
			drawBox(width, height, left, top);
			yPos++;
			gotoXY(58, yPos);
			if (page > 1) cout << char(174);
			cout << char(174) << "  " << page << "  " << char(175);
			if (page < numberPages) cout << char(175);
			yPos++;
			gotoXY(59, yPos); cout << "Back";
			yPos = 10;
			if (curPos == i) {
				yPos += 2;
				gotoXY(57, curPos + yPos); cout << cursorLeft;
				gotoXY(64, curPos + yPos); cout << cursorRight;
			}
			else {
				gotoXY(56, curPos + yPos); cout << cursorLeft;
				gotoXY(66, curPos + yPos); cout << cursorRight;
			}
			yPos = 10;
		}
		else {
			notifyBox("Empty List...");
			return;
		}
	} while (viewListOfClassesCommand(curPos, 0, i, page, numberPages, viewListOfClassesOption));
}
int viewListOfClassesInSchoolYearOption(int curPos) {
	switch (curPos) {
	case 0:
		viewListOfClasses(studentYear(1));
		break;
	case 1:
		viewListOfClasses(studentYear(2));
		break;
	case 2:
		viewListOfClasses(studentYear(3));
		break;
	case 3:
		viewListOfClasses(studentYear(4));
		break;
	case 4:
		return 0;
		break;
	}
	return 1;
}
void viewListOfClasses() {
	if (!dirExists(schoolYearPath)) {
		notifyBox("Please create school year !");
		return;
	}
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
		gotoXY(53, 7); cout << "List Of Classes";
		gotoXY(52, yPos); cout << "First-year Classes";
		yPos++;
		gotoXY(52, yPos); cout << "Second-year Classes";
		yPos++;
		gotoXY(52, yPos); cout << "Third-year Classes";
		yPos++;
		gotoXY(52, yPos); cout << "Final-year Classes";
		yPos++;
		yPos++;
		gotoXY(52, yPos); cout << "Back";
		yPos = 10;
		if (curPos == 4) yPos++;
		gotoXY(50, curPos + yPos); cout << cursorLeft;
		gotoXY(76, curPos + yPos); cout << cursorRight;
		yPos = 10;
	} while (command(curPos, 0, 4, viewListOfClassesInSchoolYearOption));
}

//View courses list
void viewListOfStudent(Course* c) {
	const int width = 54;
	int height = 9;
	const int left = 33;
	const int top = 8;
	int curPos = 0;
	int yPos = 12;
	int numberPages;
	int page = 1;
	int i = 0;
	int no;
	ListStudent list = getListOfStudentInCourse(c);
	do {
		numberPages = (list.size / 10) + 1;
		i = 0;
		height = 9;
		system("cls");
		gotoXY(55, 5); cout << "HCMUS Portal";
		textAlignCenter(c->courseName, left, width, 7);
		gotoXY(36, 10); cout << "No";
		gotoXY(42, 10); cout << "ID";
		gotoXY(52, 10); cout << "Last name";
		gotoXY(77, 10); cout << "First name";
		if (list.head != NULL) {
			Student* temp = list.head;
			for (int i = 0; i < (page - 1) * 10; i++) {
				temp = temp->next;
			}
			while (i < 10 && temp != NULL) {
				no = (page - 1) * 10 + i + 1;
				gotoXY(36, yPos); cout << no;
				gotoXY(42, yPos); cout << temp->studentID;
				string lastName = temp->lastName;
				if (lastName.length() > 24) lastName = lastName.substr(0, 24);
				gotoXY(52, yPos); cout << lastName;
				gotoXY(77, yPos); cout << temp->firstName;
				yPos++;
				i++;
				temp = temp->next;
			}
			height += i;
			drawBox(width, height, left, top);
			yPos++;
			gotoXY(58, yPos);
			if (page > 1) cout << char(174);
			cout << char(174) << "  " << page << "  " << char(175);
			if (page < numberPages) cout << char(175);
			yPos++;
			gotoXY(59, yPos); cout << "Back";
			gotoXY(57, curPos + yPos); cout << cursorLeft;
			gotoXY(64, curPos + yPos); cout << cursorRight;
			yPos = 12;
		}
		else {
			notifyBox("Empty List...");
			return;
		}
	} while (viewCoursesCommand(curPos, 0, 0, page, numberPages, viewListOfStudentOption));
}
int viewListOfCourseOption(int curPos, int page) {
	int count = 0;

	Course* temp = listCourses.head;
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
		return 0;
	}
	else {
		if (!isOnRegSession() || currentUser->isStaff) viewListOfStudent(courseSelected);
		else notifyBox("Registration session has not ended");
	}
	return 1;
}
void viewListOfCourses() {
	const int width = 40;
	int height = 8;
	const int left = 40;
	const int top = 8;
	int curPos = 0;
	int yPos = 12;
	int numberPages;
	int page = 1;
	int i = 0;

	do {
		numberPages = (listCourses.size / 10) + 1;
		i = 0;
		height = 8;
		system("cls");
		gotoXY(55, 5); cout << "HCMUS Portal";
		gotoXY(53, 7); cout << "List Of Courses";
		gotoXY(43, 10); cout << "ID";
		gotoXY(54, 10); cout << "Course name";
		if (listCourses.head != NULL) {
			Course* temp = listCourses.head;
			for (int i = 0; i < (page - 1) * 10; i++) {
				temp = temp->next;
			}
			while (i < 10 && temp != NULL) {
				gotoXY(43, yPos); cout << temp->id;
				string courseName = temp->courseName;
				if (courseName.length() > 25) courseName = courseName.substr(0, 24);
				gotoXY(54, yPos); cout << courseName;
				yPos++;
				i++;
				temp = temp->next;
			}
			height += i;
			drawBox(width, height, left, top);
			yPos++;
			gotoXY(58, yPos);
			if (page > 1) cout << char(174);
			cout << char(174) << "  " << page << "  " << char(175);
			if (page < numberPages) cout << char(175);
			yPos++;
			gotoXY(59, yPos); cout << "Back";
			yPos = 12;
			if (curPos == i) {
				yPos += 2;
				gotoXY(57, curPos + yPos); cout << cursorLeft;
				gotoXY(64, curPos + yPos); cout << cursorRight;
			}
			else {
				gotoXY(41, curPos + yPos); cout << cursorLeft;
				gotoXY(80, curPos + yPos); cout << cursorRight;
			}
			yPos = 12;
		}
		else {
			notifyBox("Empty List...");
			return;
		}
	} while (viewListOfClassesCommand(curPos, 0, i, page, numberPages, viewListOfCourseOption));
}

//View Scoreboard
int generalOption(int curPos);
ListStudent getListOfStudentScoreboard(Course* course);
void viewScoreboard() {
	const int width = 70;
	int height = 16;
	const int left = 25;
	const int top = 8;
	int curPos = 0;
	int yPos = 13;
	int no = 0;

	getEnrolledCourses();
	ListStudent list;
	Student* s = toStudent(currentUser);
	do {
		no = 0;
		system("cls");
		gotoXY(55, 5); cout << "HCMUS Portal";
		gotoXY(56, 7); cout << "Scoreboard";
		gotoXY(28, 10); cout << "No";
		gotoXY(32, 10); cout << "ID";
		gotoXY(42, 10); cout << "Course name";
		gotoXY(67, 10); cout << "Other";
		gotoXY(67, 11); cout << "Mark";
		gotoXY(73, 10); cout << "Midterm";
		gotoXY(73, 11); cout << "Mark";
		gotoXY(81, 10); cout << "Final";
		gotoXY(81, 11); cout << "Mark";
		gotoXY(87, 10); cout << "Total";
		gotoXY(87, 11); cout << "Mark";
		if (enrolledCourses.head != NULL) {
			Course* course = enrolledCourses.head;
			while (course != NULL) {
				list = getListOfStudentScoreboard(course);
				Student* temp = list.head;
				while (temp != NULL) {
					if (temp->studentID == s->studentID) break;
					temp = temp->next;
				}
				no++;
				gotoXY(28, yPos); cout << no;
				gotoXY(32, yPos); cout << course->id;
				string courseName;
				if (course->courseName.length() > 25) courseName = course->courseName.substr(0, 25);
				else courseName = course->courseName;
				gotoXY(42, yPos); cout << courseName;
				CourseMark courseMark;
				if (temp != NULL) courseMark = temp->courseMark;
				gotoXY(67, yPos); cout << courseMark.otherMark;
				gotoXY(73, yPos); cout << courseMark.midtermMark;
				gotoXY(81, yPos); cout << courseMark.finalMark;
				gotoXY(87, yPos); cout << courseMark.totalMark;
				yPos++;
				course = course->next;
			}
			s->enrolledCourses = enrolledCourses;
			calcGPA(s);
			yPos++;
			gotoXY(53, yPos); 
			cout << "Semester GPA: ";
			cout << s->semesterMark.GPA;
			yPos++;
			gotoXY(53, yPos);
			cout << "Overall GPA: ";
			cout << s->semesterMark.overallGPA;
			yPos++;
			drawBox(width, height, left, top);
			yPos++;
			gotoXY(59, yPos); cout << "Back";
			gotoXY(57, yPos); cout << cursorLeft;
			gotoXY(64, yPos); cout << cursorRight;
			yPos = 13;
		}
		else {
			notifyBox("Empty List...");
			return;
		}
	} while (command(curPos, 0, 0, generalOption));
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
		viewScoreboard();
		break;
	case 4:
		viewListOfClasses();
		break;
	case 5:
		viewListOfCourses();
		break;
	case 6:
		setting();
		break;
	case 7:
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
		viewEnrolledList();
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
	ofstream fout(semesterPath + "/student/" + currentUser->id + ".dat");
	Course* temp = enrolledCourses.head;
	while (temp != NULL) {
		toUpper(temp->wDay);
		string session = temp->session[0] + "-" + temp->session[1];
		fout << temp->id << "," << temp->courseName << "," << temp->teacherName << ","
			<< temp->credits << "," << temp->academicYear << "," << temp->maxStudents << ","
			<< temp->numberRegistered << "," << temp->wDay << "," << session;
		temp = temp->next;
		if (temp != NULL) fout << endl;
	}
	fout.close();
}
void getEnrolledCourses() {
	ifstream fin(semesterPath + "/student/" + currentUser->id + ".dat");
	initList(enrolledCourses);
	if (!fin) return;
	while (!fin.eof()) {
		addCourse(enrolledCourses, convertCourseData(fin));
	}
}
void getPosibleCourses() {
	initList(posibleCourses);
	Course* temp = listCourses.head;
	while (temp != NULL) {
		if (currentUser->academicYear <= temp->academicYear)
			addCourse(posibleCourses, copyCourseData(temp));
		temp = temp->next;
	}
}
void saveListCourses(ListCourses list) {
	Course* temp = list.head;
	Course* curr = listCourses.head;
	while (curr != NULL && temp != NULL) {
		if (temp->id == curr->id) {
			curr->numberRegistered = temp->numberRegistered;
			temp = temp->next;
		}
		curr = curr->next;
	}
	saveCourses();
}
ListStudent getListOfStudentInCourse(Course* course) {
	ListStudent list;
	initList(list);
	ifstream fin("./data/" + currentSchoolYear + "/semester " +
		to_string(currentSemester.semester) + "/courses/" + course->id + ".dat");
	if (fin.fail()) {
		return list;
	}
	while (!fin.eof()) {
		addStudent(list, convertStudentData(fin));
	}
	return list;
}
void saveListOfStudentInCourse(Course* course, ListStudent list) {
	ofstream fout("./data/" + currentSchoolYear + "/semester " +
		to_string(currentSemester.semester) + "/courses/" + course->id + ".dat");
	Student* temp = list.head;
	int no = 1;
	while (temp != NULL) {
		fout << no << "," << temp->studentID << "," << temp->lastName << "," << temp->firstName << ","
			<< temp->gender << "," << dateToStr(temp->dateOfBirth) << "," << temp->socialID << "," << temp->academicYear;
		temp = temp->next;
		if (temp != NULL) fout << endl;
		no++;
	}
	fout.close();
}
bool isEnrolled(ListStudent list) {
	Student* temp = list.head;
	while (temp != NULL) {
		if (temp->studentID == currentUser->id) return true;
		temp = temp->next;
	}
	return false;
}
void addStudentInCourses() {
	Course* temp = enrolledCourses.head;
	while (temp != NULL) {
		ListStudent list = getListOfStudentInCourse(temp);
		if (!isEnrolled(list)) {
			addStudent(list, toStudent(currentUser));
			saveListOfStudentInCourse(temp, list);
		}
		temp = temp->next;
	}
}