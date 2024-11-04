#include "SettingsScreen.h"
bool enableSFX = true, enableBGM = true;
void drawVolume(bool isCurrent) {
	if (isCurrent) RGBPrint(105, 24, L">> Volume", white, light_pink, true);
	else  RGBPrint(108, 24, L"Volume", white, light_pink, true);
	int n = getVolume() / 50;
	drawSlider(110+15,24,24,n);
	drawDOT(111 + 15 + n+1, 24);
}
void drawSFX(bool isCurrent) {
	if (isCurrent) RGBPrint(105, 27, L">> Sound Effects:", white, light_pink,true);
	else RGBPrint(108, 27, L"Sound Effects:", white, light_pink, true);
	if (enableSFX) drawCheckBox(110 + 15, 27, light_pink);
	else drawCheckBox(110 + 15, 27, white_pink);
}
void drawBGM(bool isCurrent) {
	string status;
	status = enableBGM ? "ON" : "OFF";
	clearLine(22);
	if (isCurrent) printColoredText(47, 22, ">> Music:\t\t" + status, 3, 15);
	else  printColoredText(50, 22, "Music:\t\t" + status, 3, 15);
}
void drawLanguage(bool isCurrent) {
	clearLine(24);
	if (isCurrent) printColoredText(47, 24, ">> LANGUAGE: COMING SOON", 4, 15);
	else printColoredText(50, 24, "LANGUAGE: COMING SOON", 4, 15);
}
void drawBackOption(bool isCurrent) {
	clearLine(26);
	if (isCurrent) printColoredText(47, 26, ">> BACK TO MAIN MENU", 3, 15);
	else printColoredText(50, 26, "BACK TO MAIN MENU", 3, 15);
}
void SettingsScreen() {
	drawPanel(100, 20, 10);
	//printColoredText(90, 25, L"Ấn W/A để thay đổi tùy chọn",3,15);
	//drawBGM(false);
	//drawLanguage(false);
	//drawBackOption(false);
	drawVolume(true);
	drawSFX(false);
	int current = 0, previous = 0;
	while (true) {
		if (_kbhit()) {
			int n = tolower(_getch());
			if ((n == 'a' || n == 'd') && current <=2) {
				if (current == 0) {
					setVolume(getVolume() + (n == 'd' ? 50 : -50));
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
				MainScreen(1, 0, false);
			}
		}
	}
}