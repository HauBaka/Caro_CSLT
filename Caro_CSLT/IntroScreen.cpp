#include "IntroScreen.h"
void drawLOGO(int x, int y) {
	printColoredText(x, y, L" ██████╗ █████╗ ██████╗  ██████╗      ██████╗  █████╗ ███╗   ███╗███████╗", 1, 14);
	printColoredText(x, y+1, L"██╔════╝██╔══██╗██╔══██╗██╔═══██╗    ██╔════╝ ██╔══██╗████╗ ████║██╔════╝", 1, 14);
	printColoredText(x, y+2, L"██║     ███████║██████╔╝██║   ██║    ██║  ███╗███████║██╔████╔██║█████╗  ", 1, 14);
	printColoredText(x, y+3, L"██║     ██╔══██║██╔══██╗██║   ██║    ██║   ██║██╔══██║██║╚██╔╝██║██╔══╝  ", 1, 14);
	printColoredText(x, y + 4, L"╚██████╗██║  ██║██║  ██║╚██████╔╝    ╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗", 1, 14);
	printColoredText(x, y + 5, L" ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝      ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝", 1, 14);
}
void veMay(int x, int y) {
	printColoredText(x-1, y+3, L" ", 3, 14);
	printColoredText(x - 1, y + 4, L" ", 3, 14);
	printColoredText(x - 1, y + 5, L" ", 3, 14);

	printColoredText(x, y, L"          ▄█▀▀", 0, 14);
	printColoredText(x + 14, y, L"▀▀", 0, 7);
	printColoredText(x + 16, y, L"█▄", 0, 14);
	//2
	printColoredText(x, y + 1, L"        ▄█▀     ", 0, 14);
	printColoredText(x + 15, y + 1, L"▀", 7, 14);
	printColoredText(x + 16, y + 1, L"▀", 7, 7);
	printColoredText(x + 17, y + 1, L"▀", 0, 7);
	printColoredText(x + 18, y + 1, L"█", 0, 14);
	//3
	printColoredText(x, y + 2, L"  ▄▄▄▄▄ █        ", 0, 14);
	printColoredText(x + 17, y + 2, L"▀", 7, 14);
	printColoredText(x + 18, y + 2, L"▀▄█▀▀", 0, 14);
	printColoredText(x + 18 + 5, y + 2, L"▀▀", 0, 7);
	printColoredText(x + 18 + 5 + 2, y + 2, L"█▄", 0, 14);
	//4
	printColoredText(x, y + 3, L"▄█▀  ", 0, 14);
	printColoredText(x + 5, y + 3, L"▀▀", 7, 14);
	printColoredText(x + 7, y + 3, L"██          ▀   ", 0, 14);
	printColoredText(x + 7 + 17, y + 3, L"▀▀", 7, 14);
	printColoredText(x + 7 + 17 + 2, y + 3, L"█", 0, 14);
	//5
	printColoredText(x, y + 4, L"█                         ▀▄", 0, 14);
	//6
	printColoredText(x, y + 5, L"▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀", 0, 14);
	//          ▄█▀▀▀▀█▄
	//        ▄█▀      ▀█
	//  ▄▄▄▄▄ █         ▀▄█▀▀▀▀█▄
	//▄█▀    ██          ▀      █
	//█                         ▀▄
	//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
}
string animatedText(string s, int& index) {
	if (index >= s.size() && index <= s.size() + 4) {
		if (index % 2 == 0) {
			return s;
		}
		else {
			string result = "";
			for (int i = 0; i < s.size(); i++) {
				result += " ";
			}
			return result;
		}
	}
	else if (index > s.size() + 4) index = 0;
	index = index % s.size();
	return s.substr(0, index) + " " + s.substr(index + 1, s.size());
}
void startIntroScreen() {
	playSound(2, true);
	drawLOGO((172-73)/2, 5);
	int count = 0, index =0;
	while (true) {
		veMay(index, 30);

		index++;
		if (index == 173) {
			for (int i = 30; i < 42; i++) clearLine(i);
			index = 0;
		}
		count++;
		GotoXY(74, 21);
		printColoredText(74, 21, animatedText("PRESS ANY KEY TO START!", count), 3, 14);
		if (_kbhit()) {
			_getch();
			if (enableSFX) playSound(3, 0);
			break;
		}
		Sleep(200);
	}
	stopSound(2);
	MainScreen(0, true);
}