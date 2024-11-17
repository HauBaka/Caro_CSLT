#include "SettingsScreen.h"
bool enableSFX = true, enableBGM = true;
void drawVolume(bool isCurrent) {
	wstring text = getwstring(language, L"settings_volume");
	if (isCurrent) RGBPrint(105, 24, L">> " + text + L":", white, light_pink, true);
	else  RGBPrint(105, 24, L"   " + text+L":", white, light_pink, true);
	int n = getVolume() / 50;
	drawSlider(110+15,24,24,n);
	drawDOT(111 + 15 + n+1, 24);
}
void drawSFX(bool isCurrent) {
	wstring text = getwstring(language, L"settings_sfx");
	if (isCurrent) RGBPrint(105, 27, L">> " + text+L":", white, light_pink, true);
	else RGBPrint(105, 27, L"   "+text+L":", white, light_pink, false);
	if (enableSFX) drawCheckBox(110 + 15, 27, white_pink);
	else drawCheckBox(110 + 15, 27, {81,81,81});
}
void drawBGM(bool isCurrent) {
	wstring text = getwstring(language, L"settings_bgm");
	if (isCurrent) RGBPrint(105, 30, L">> " + text+L":", white, light_pink, false);
	else RGBPrint(105, 30, L"   " + text +L":", white, light_pink, false);
	if (enableBGM) drawCheckBox(110 + 15, 30, white_pink);
	else drawCheckBox(110 + 15, 30, { 81,81,81 });
}
void drawLanguage(bool isCurrent) {
	wstring text = getwstring(language, L"settings_language");
	if (isCurrent) RGBPrint(105, 32, L">> " + text + L":", white, light_pink, false);
	else RGBPrint(105, 32, L"   " + text + L":", white, light_pink, false);
}
void drawBackOption(bool isCurrent) {
	wstring text = getwstring(language, L"back_to_main");
	if (isCurrent) RGBPrint(105, 34, L">> "+ text, white, light_pink, false);
	else RGBPrint(105, 34, L"   "+ text, white, light_pink, false);
}
void SettingsScreen() {
	drawPanel(100, 20, 12);
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
				removePanel(100, 20, 12);
				MainScreen(1, 0, false);
			}
		}
	}
}