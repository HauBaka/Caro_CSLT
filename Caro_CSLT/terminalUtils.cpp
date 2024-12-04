#include "terminalUtils.h"
void FixConsoleWindow() {//khong thay doi kich thuoc cua so
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);

	MoveWindow(consoleWindow, 0,0, 1280, 720, TRUE);//ngang 172, doc 42 ki tu
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
void clearLine(int line) {
	RGBPrint(0, line, "                                                                                                                                                                             ", white_pink, white_pink);
}
void SetUpWindow() {
	FixConsoleWindow();
	ShowConsoleCursor(false);
	system("color F1");
	SetConsoleTitleA("GROUP 6 | 24CTT3 | HCMUS");
	SetConsoleOutputCP(CP_UTF8);
	
	fopen_s(&language, "./Languages/en-us.txt", "r");
	loadConfiguration(language);
}