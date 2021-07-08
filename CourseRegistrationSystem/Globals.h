#pragma once

#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <conio.h>
#include <windows.h>
#include <functional>
#include <time.h>
#include <direct.h>
#include <io.h>
#include <filesystem>

#include "AcademicStaff.h"
#include "Student.h"
#include "LoginSystem.h"

using namespace std;
namespace fs = filesystem;

struct Date {
	int year;
	int month;
	int day;
	string wDay;
};
struct User {
	string id;
	string password;
	string lastName;
	string firstName;
	string className;
	string gender;
	bool isStaff;
	Date dateOfBirth;
	User* prev;
	User* next;
};
struct ListUser {
	User* pHead;
	User* pTail;
	int size;
};
struct Student {
	string studentID;
	string lastName;
	string firstName;
	string gender;
	string socialID;
	Date dateOfBirth;
	Student* prev;
	Student* next;
};
struct ListStudent {
	Student* pHead;
	Student* pTail;
	string program;
	string className;
	string year;
	int size;
};
struct Semester {
	int semester;
	Date startDate, endDate;
};
struct Course {
	string id;
	string courseName;
	string teacherName;
	int credits;
	int maxStudents = 50;
	string wDay;
	string session[2];
	Course* prev;
	Course* next;
};
struct ListCourses {
	Course* head;
	Course* tail;
	Date startDate, endDate;
	int size;
};

Date strToDate(string str);
string dateToStr(Date date);
void gotoXY(int x, int y);
void toUpper(string& s);
void clearLine(int y);
void hideCursor(bool);
bool dirExists(const std::string& dirName_in);
void copyFolder(string from, string to);

void drawBox(int width, int height, int left, int top);
void loading(string text);
void notifyBox(string msg);

void addUser(ListUser& list, User* user);
void addStudent(ListStudent& list, Student* student);
void addCourse(ListCourses& list, Course* course);
void saveListUser();
void saveClass(string path, ListStudent listStudent);
void saveCourses();

User* convertUserData(ifstream& data);
Student* convertStudentData(ifstream& data);
Course* convertCourseData(ifstream& data);
void initList(ListUser& list);
void initList(ListStudent& list);
void initList(ListCourses& list);
bool isExpired(Date currentDate, Date endDate);
bool isOnRegSession();
void getListCourses();
void getCurrentDate();
void getCurrentSchoolYear();
void getCurrentSemester();

extern User* currentUser;
extern ListUser listUser;
extern Date currentDate;
extern string currentSchoolYear;
extern Semester currentSemester;
extern string semesterPath;
extern ListCourses listCourses;
extern string schoolYearPath;