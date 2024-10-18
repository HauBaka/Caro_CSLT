#include "terminalUtils.h"
void FixConsoleWindow() {//khong thay doi kich thuoc cua so
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);

	MoveWindow(consoleWindow, (1920 - 1280) / 2 - 100, (1080 - 720) / 2 - 100, 1280, 720, TRUE);//ngang 172, doc 42 ki tu
	ShowScrollBar(GetConsoleWindow(), SB_VERT, 0);
}
void ShowConsoleCursor(bool showFlag)// tat con tro chuot
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag;
	SetConsoleCursorInfo(out, &cursorInfo);
}
void GotoXY(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void printColoredText(int x, int y, wstring text, int textColor, int bgColor) {//in text tại vị trí x,y với màu textColor
	int OldMode = _setmode(_fileno(stdout), _O_WTEXT);//bgColor nền
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int colorAttribute = textColor + (bgColor << 4);
	SetConsoleTextAttribute(hConsole, colorAttribute);
	GotoXY(x, y);
	wcout << text;
	SetConsoleTextAttribute(hConsole, 0 + (15 << 4));
	_setmode(_fileno(stdout), OldMode);
}
void printColoredText(int x, int y, string text, int textColor, int bgColor) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int colorAttribute = textColor + (bgColor << 4);
	SetConsoleTextAttribute(hConsole, colorAttribute);
	GotoXY(x, y);
	cout << text;
	SetConsoleTextAttribute(hConsole, 0 + (15 << 4));
}