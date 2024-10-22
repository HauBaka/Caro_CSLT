#include "SettingsScreen.h"
bool enableSFX = true, enableBGM = true;
void drawVolume(bool isCurrent) {
	wstring status, status_1;
	for (int i = 1; i <= getVolume() / 200; i++) {
		status += L"█";
	}
	for (int i = getVolume() / 200 + 1; i <= 5; i++) {
		status_1 += L"█";
	}
	clearLine(18);
	if (isCurrent) printColoredText(47, 18, ">> Volume:\t", 3, 14);
	else  printColoredText(50, 18, "Volume:\t", 3, 14);
	printColoredText(50 + 22, 18, status, 10, 14);
	printColoredText(50 + 22+ (int) status.length(), 18, status_1, 4, 14);
}
void drawSFX(bool isCurrent) {
	string status ;
	status = enableSFX ? "ON" : "OFF";
	clearLine(20);
	if (isCurrent) printColoredText(47, 20, ">> Sound Effects:\t" + status, 3, 14);
	else  printColoredText(50, 20, "Sound Effects:\t" + status, 3, 14);
}
void drawBGM(bool isCurrent) {
	string status;
	status = enableBGM ? "ON" : "OFF";
	clearLine(22);
	if (isCurrent) printColoredText(47, 22, ">> Music:\t\t" + status, 3, 14);
	else  printColoredText(50, 22, "Music:\t\t" + status, 3, 14);
}
void drawLanguage(bool isCurrent) {
	clearLine(24);
	if (isCurrent) printColoredText(47, 24, ">> LANGUAGE: COMING SOON", 4, 14);
	else printColoredText(50, 24, "LANGUAGE: COMING SOON", 4, 14);
}
void drawBackOption(bool isCurrent) {
	clearLine(26);
	if (isCurrent) printColoredText(47, 26, ">> BACK TO MAIN MENU", 3, 14);
	else printColoredText(50, 26, "BACK TO MAIN MENU", 3, 14);
}
void SettingsScreen() {
	for (int i = 16; i < 30; i++) {
		clearLine(i);
	}
	printColoredText(90, 25, L"Ấn W/A để thay đổi tùy chọn",3,14);
	drawVolume(true);
	drawSFX(false);
	drawBGM(false);
	drawLanguage(false);
	drawBackOption(false);

	int current = 0, previous = 0;
	while (true) {
		if (_kbhit()) {
			int n = tolower(_getch());
			if ((n == 'a' || n == 'd') && current <=2) {
				if (current == 0) {
					setVolume(getVolume() + (n == 'd' ? 200 : -200));
					drawVolume(true);
				}
				else if (current == 1) {
					enableSFX = !enableSFX;
					drawSFX(true);
				}
				else if (current == 2) {
					enableBGM = !enableBGM;
					if (enableBGM) playSound(1, 1);
					else stopSound(1);
					drawBGM(true);
				}
			}
			if ((n == 13 || n == 'w' || n == 'a' || n == 's' || n == 'd' || n == 'e') && enableSFX) playSound(3, 0);
			if (n == 's' or n == 'w') {
				if (n == 's') {
					previous = current;
					current = (current == 4) ? 0 : current + 1;
				}
				if (n == 'w') {
					previous = current;
					current = (current == 0) ? 4 : current - 1;
				}
				switch (previous) {
				case 0:
					drawVolume(false);
					break;
				case 1:
					drawSFX(false);
					break;
				case 2:
					drawBGM(false);
					break;
				case 3:
					drawLanguage(false);
					break;
				case 4:
					drawBackOption(false);
					break;
				}
				switch (current) {
				case 0:
					drawVolume(true);
					break;
				case 1:
					drawSFX(true);
					break;
				case 2:
					drawBGM(true);
					break;
				case 3:
					drawLanguage(true);
					break;
				case 4:
					drawBackOption(true);
					break;
				}
			}
			if (n == 13 && (current == 4 or current == 3)) {
				if (enableBGM == false) stopSound(1);
				MainScreen(1, 0);
			}
		}
	}
}