#include "SettingsScreen.h"
bool enableSFX = true, enableBGM = true;
void drawVolume(bool isCurrent) {
	wstring text = getwstring(language, L"settings_volume");
	if (isCurrent) RGBPrint(100, 22, L">> " + text + L":", black, light_pink, true);
	else  RGBPrint(100, 22, L"   " + text+L":", black, light_pink, true);
	int n = getVolume() / 50;
	drawSlider(113,22,24,n);
	drawDOT(114 + n+1, 22);
}
void drawSFX(bool isCurrent) {
	wstring text = getwstring(language, L"settings_sfx");
	if (isCurrent) RGBPrint(100, 26, L">> " + text+L":", black, light_pink, true);
	else RGBPrint(100, 26, L"   "+text+L":", black, light_pink, true);
	if (enableSFX) drawCheckBox(108 + 12, 26, pink);
	else drawCheckBox(108 + 12, 26, white_pink);
}
void drawBGM(bool isCurrent) {
	wstring text = getwstring(language, L"settings_bgm");
	if (isCurrent) RGBPrint(100, 29, L">> " + text+L":", black, light_pink, true);
	else RGBPrint(100, 29, L"   " + text +L":", black, light_pink, true);
	if (enableBGM) drawCheckBox(108 + 12, 29, pink);
	else drawCheckBox(108 + 12, 29, white_pink);
}
void drawLanguage(bool isCurrent) {
	wstring text = getwstring(language, L"settings_language"),
		language_name = getwstring(language, L"name");
	if (isCurrent) RGBPrint(100, 32, L">> " + text + L": " + language_name, black, light_pink, true);
	else RGBPrint(100, 32, L"   " + text + L": " + language_name, black, light_pink, true);
}
void drawBackOption(bool isCurrent) {
	wstring text = getwstring(language, L"back_to_main");
	int x = 116 - sizeOfText(text)/2;
	if (isCurrent) RGBPrint(x, 34, L">> "+ text, black, light_pink, true);
	else RGBPrint(x, 34, L"   "+ text, black, light_pink, true);
}

void SettingsScreen() {
	int current = 0, previous = 0;
	drawPanel(90, 18, 12);
	drawVolume(true);
	drawSFX(false);
	drawBGM(false);
	drawLanguage(false);
	drawBackOption(false);
	while (true) {
		if (_kbhit()) {
			int n = tolower(_getch());
			if ((n == 'a' || n == 'd') && current <=3) {
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
				else if (current == 3) {
					fclose(language);
					fopen_s(&language, "./Languages/vi-vn.txt", "r");
					loadConfiguration(language);
					drawLanguage(true);
				}
			}
			if ((n == 'w' || n == 'a' || n == 's' || n == 'd' || n == 'e') && enableSFX) playSound(3, 0);
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
				if (enableSFX) playSound(9, 0);
				removePanel(90, 18, 12);
				MainScreen(1, 0, false);
			}
		}
	}
} 