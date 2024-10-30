#include "IntroScreen.h"
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
	drawMainMenu_Play(10, 2, true);

	drawMainMenu_Options(10, 7, true);

	drawMainMenu_Authors(10, 12, true);
	playSound(2, true);
	drawLOGO(100, 5);
	int count = 0, index =0;
	GotoXY(0, 30);
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