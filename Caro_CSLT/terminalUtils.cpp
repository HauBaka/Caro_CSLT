#include "terminalUtils.h"
#include "MainScreen.h"
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
void clearLine() {
	for (int i = 0; i < 172; i++) {
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
			getSFX().play(Audio::POP, false);
			if (n == 32) break;
			GotoXY(0, 0);
			cout << n;
			previousSelect = currentSelect;
			if (n == 119 or n == 97 or n == 724 or n == 754) {//go up
				currentSelect--;
				currentSelect = (currentSelect < 0) ? size - 1 : currentSelect;
			}
			else if (n == 115 or n == 100 or n == 804 or n == 774) {//go down
				currentSelect++;
				currentSelect = (currentSelect > size - 1) ? 0 : currentSelect;
			}
			GotoXY(0, startLine + 2 * previousSelect);
			clearLine();
			printColoredText((172 - (int)options[previousSelect].length()) / 2, startLine + 2 * previousSelect, options[previousSelect], 3, 14);
			GotoXY(0, startLine + 2 * currentSelect);
			clearLine();
			printColoredText((172 - (int)options[currentSelect].length() - 6) / 2, startLine + 2 * currentSelect, ">> " + options[currentSelect] + " <<", 3, 14);
		}
	}
}
void SetUpWindow() {
	FixConsoleWindow();
	ShowConsoleCursor(false);
	system("color e1");
}