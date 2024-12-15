#include "IntroScreen.h"
wstring animatedText(wstring s, int& index) {
	if (index >= s.size() && index <= s.size() + 4) {
		if (index % 2 == 0) {
			return s;
		}
		else {
			wstring result = L"";
			for (int i = 0; i < s.size(); i++) {
				result += L" ";
			}
			return result;
		}
	}
	else if (index > s.size() + 4) index = 0;
	index = index % s.size();
	return s.substr(0, index) + L" " + s.substr(index + 1, s.size());
}
void startIntroScreen() {
	if (enableBGM) playSound(2, true);
	fill(white_pink);
	drawLOGO(50, 5);
	int count = 0, index =0;
	GotoXY(0, 30);
	wstring message = getwstring(language, L"press_any_key_to_start");
	while (true) {
		drawSanta(index, 30, white_pink);
		index++;
		if (index == 173) {
			for (int i = 30; i < 42; i++) clearLine(i);
			index = 0;
		}
		count++;
		RGBPrint(74, 21, animatedText(message, count), black, white_pink, true);
		if (_kbhit()) {
			int _t = _getch();
			if (enableSFX) playSound(9, 0);
			break;
		}
		Sleep(200);
	}
	stopSound(2);
	MainScreen(0, true, true);
}