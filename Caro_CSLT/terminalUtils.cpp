#include "terminalUtils.h"
void FixConsoleWindow() {/*Cố định cửa sổ*/
	/*Không cho thay đồi kích thước cửa sổ*/
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
	/*Di chuyển cửa sổ đến góc trái trên và đặt kích thước là 1280x720 px*/
	MoveWindow(consoleWindow, 0,0, 1280, 720, TRUE);//ngang 172, doc 42 ki tu
	/*Tắt thanh kéo*/
	ShowScrollBar(GetConsoleWindow(), SB_VERT, 0);//TO DO: Not work
}
/*Bật/tắt con trỏ chuột nhấp nhấy*/
void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag;
	SetConsoleCursorInfo(out, &cursorInfo);
}
/*Đi đến tọa độ x,y trên cửa sổ*/
void GotoXY(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
/*Đếm số kí tự của text ở kiểu wstring*/
int sizeOfText(wstring text) {
	int count = 0;
	bool c = false;
	for (const wchar_t& ch : text) {
		if (ch <= 127) {
			count++;
			c = false;
			continue;
		}
		if (!c) {
			count++;
			c = true;
		}
	}
	return count;
}
/*Xóa cả 1 dòng*/
void clearLine(int line) {
	RGBPrint(0, line, "                                                                                                                                                                             ", white_pink, white_pink);
}
/*Thiết lập trò chơi*/
void SetUpWindow() {
	FixConsoleWindow();
	ShowConsoleCursor(false);
	system("color F1");
	SetConsoleTitleA("GROUP 6 | 24CTT3 | HCMUS");
	SetConsoleOutputCP(CP_UTF8);
	fopen_s(&config, "config.txt", "r");
	loadConfiguration(config);

	enableSFX = getBool(config, L"enable_SFX");
	enableBGM = getBool(config, L"enable_BGM");
	setVolume(getInt(config, L"sound_volume"));
	currentLang = (getwstring(config, L"language") == L"vi-vn"); 
	wstring wlang = getwstring(config, L"language");
	string lang(wlang.begin(), wlang.end());
	string path = "./Languages/" + lang + ".txt";
	fopen_s(&language, path.c_str(), "r");
	loadConfiguration(language);
}

