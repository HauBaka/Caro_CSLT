#include "terminalUtils.h"
void FixConsoleWindow() {//khong thay doi kich thuoc cua so
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);

	MoveWindow(consoleWindow, 1280/8,720/8, 1280, 720, TRUE);//ngang 172, doc 42 ki tu
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
void printColoredText(int x, int y, wstring text, int textColor, int bgColor) {	//in text tại vị trí x,y với màu textColor
	int OldMode = _setmode(_fileno(stdout), _O_WTEXT);							//bgColor nền
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int colorAttribute = textColor + (bgColor << 4);
	SetConsoleTextAttribute(hConsole, colorAttribute);
	GotoXY(x, y);
	wcout << text;
	SetConsoleTextAttribute(hConsole, 3 + (14 << 4));
	_setmode(_fileno(stdout), OldMode);
}
void printColoredText(int x, int y, string text, int textColor, int bgColor) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int colorAttribute = textColor + (bgColor << 4);
	SetConsoleTextAttribute(hConsole, colorAttribute);
	GotoXY(x, y);
	cout << text;
	SetConsoleTextAttribute(hConsole, 3 + (14 << 4));
}
void clearLine(int line) {
	GotoXY(0, line);
	for (int i = 0; i < 173; i++) {
		cout << " ";
	}
}
void drawOptions(string options[], int size, int& currentSelect, int& previousSelect, int startLine) {
	for (int i = 0; i < size; i++) {
		if (currentSelect == i) {
			printColoredText((172 - (int)options[i].length() - 6) / 2, startLine + 2 * i, ">> " + options[i] + " <<", 3, 14);
		}
		else {
			GotoXY((172 - (int)options[i].length()) / 2, startLine + 2 * i);
			cout << options[i];
		}
	}
	int n;
	while (true) {
		if (_kbhit()) {
			n = _getch();
			GotoXY(0, 0);
			cout << n;
			if ((n == 13 || n == 'w' || n == 'a' || n == 's' || n == 'd' || n == 'e') && enableSFX) playSound(3, 0);
			if (n == 13) break;
			previousSelect = currentSelect;
			if (n == 'w' or n == 'a') {//go up
				currentSelect--;
				currentSelect = (currentSelect < 0) ? size - 1 : currentSelect;
			}
			else if (n == 's' or n == 'd') {//go down
				currentSelect++;
				currentSelect = (currentSelect > size - 1) ? 0 : currentSelect;
			}
			clearLine(startLine + 2 * previousSelect);
			printColoredText((172 - (int)options[previousSelect].length()) / 2, startLine + 2 * previousSelect, options[previousSelect], 3, 14);
			clearLine(startLine + 2 * currentSelect);
			printColoredText((172 - (int)options[currentSelect].length() - 6) / 2, startLine + 2 * currentSelect, ">> " + options[currentSelect] + " <<", 3, 14);
		}
	}
}
void SetUpWindow() {
	FixConsoleWindow();
	ShowConsoleCursor(false);
	system("color e1");
}