#include "Globals.h"

RECT* consoleRect = new RECT;

void gotoXY(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void getConsoleSize() {
	HWND hwnd = GetConsoleWindow();
	GetWindowRect(hwnd, consoleRect);
}

void hideCursor(bool isHiden) {
	CONSOLE_CURSOR_INFO cursor;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
	cursor.bVisible = !isHiden;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}

void drawTable(int width, int height, int left, int top) {
	gotoXY(left, top);
	cout << char(201);
	for (int i = 0; i < width; i++) {
		cout << char(205);
	}
	cout << char(187);
	for (int i = top + 1; i < height + top; i++) {
		gotoXY(left, i);
		cout << char(186);
	}
	gotoXY(left, height + top);
	cout << char(200);
	for (int i = 0; i < width; i++) {
		cout << char(205);
	}
	cout << char(188);
	for (int i = height + top - 1; i > top; i--) {
		gotoXY(left + width + 1, i);
		cout << char(186);
	}
}