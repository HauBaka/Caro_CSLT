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
	printColoredText(0, line, "                                                                                                                                                                             ", 15, 15);
}
void drawOptions(int x, int y, string options[], int size, int& currentSelect, int& previousSelect) {
	for (int i = 0; i < size; i++) {
		if (currentSelect == i) {
			printColoredText(x+2, y + 2 * i, ">> " + options[i] + " <<", 3, 15);
		}
		else {
			GotoXY((172 - (int)options[i].length()) / 2, y + 2 * i);
			cout << options[i];
		}
	}
	int n;
	while (true) {
		if (_kbhit()) {
			n = _getch();
			if ((n == 13 || n == 'w' || n == 'a' || n == 's' || n == 'd' || n == 'e') && enableSFX) playSound(3, 0);
			if (n == 13) break;
			previousSelect = currentSelect;
			if (n == 'w' or n == 'a') {//go up
				currentSelect--;
				currentSelect = (currentSelect < 0) ? size - 1 : currentSelect;
			} else if (n == 's' or n == 'd') {//go down
				currentSelect++;
				currentSelect = (currentSelect > size - 1) ? 0 : currentSelect;
			}
			clearLine(y + 2 * previousSelect);
			printColoredText((172 - (int)options[previousSelect].length()) / 2, y + 2 * previousSelect, options[previousSelect], 3, 15);
			clearLine(y + 2 * currentSelect);
			printColoredText((172 - (int)options[currentSelect].length() - 6) / 2, y + 2 * currentSelect, ">> " + options[currentSelect] + " <<", 3, 15);
		}
	}
}
char getCharAtCoord(COORD coord) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 
	char ch;
	DWORD charsRead;

	if (ReadConsoleOutputCharacterA(hConsole, &ch, 1, coord, &charsRead)) {
		return ch;  
	}
	return '\0';
}
void SetUpWindow() {
	FixConsoleWindow();
	ShowConsoleCursor(false);
	system("color F1");
	SetConsoleTitleA("GROUP 6 | 24CTT3 | HCMUS");
	SetConsoleOutputCP(CP_UTF8);
}