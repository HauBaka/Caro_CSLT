#include "IntroScreen.h"
#include "MainScreen.h"
void drawLOGO(int x, int y) {
	printColoredText(x, y, L" ██████╗ █████╗ ██████╗  ██████╗      ██████╗  █████╗ ███╗   ███╗███████╗", 1, 14);
	printColoredText(x, y+1, L"██╔════╝██╔══██╗██╔══██╗██╔═══██╗    ██╔════╝ ██╔══██╗████╗ ████║██╔════╝", 1, 14);
	printColoredText(x, y+2, L"██║     ███████║██████╔╝██║   ██║    ██║  ███╗███████║██╔████╔██║█████╗  ", 1, 14);
	printColoredText(x, y+3, L"██║     ██╔══██║██╔══██╗██║   ██║    ██║   ██║██╔══██║██║╚██╔╝██║██╔══╝  ", 1, 14);
	printColoredText(x, y + 4, L"╚██████╗██║  ██║██║  ██║╚██████╔╝    ╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗", 1, 14);
	printColoredText(x, y + 5, L" ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝      ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝", 1, 14);

	printColoredText(x + 16, y + 1, L"▀", 7, 4);
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

	static Audio  introMusic;
	introMusic.play(Audio::BACKGROUND_2, true);
	drawLOGO((172-73)/2, 5);
	int count = 0;
	while (true) {
		count++;
		GotoXY(74, 21);
		printColoredText(74, 21, animatedText("PRESS ANY KEY TO START!", count), 3, 14);
		if (_kbhit()) {
			_getch();
			break;
		}
		Sleep(200);
	}
	introMusic.close();
	MainScreen(0);
}