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

void hideCursor() {
	CONSOLE_CURSOR_INFO cursor;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
	cursor.bVisible = !cursor.bVisible;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);

}