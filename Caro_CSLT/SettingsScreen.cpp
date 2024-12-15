#include "SettingsScreen.h"
bool enableSFX = true, enableBGM = true, currentLang = false;
wstring settings_volume, settings_sfx, settings_bgm, settings_language, back_to_main;
void loadTexts() {
	settings_volume = getwstring(language, L"settings_volume");
	settings_sfx = getwstring(language, L"settings_sfx");
	settings_bgm = getwstring(language, L"settings_bgm");
	settings_language = getwstring(language, L"settings_language");
	back_to_main = getwstring(language, L"back_to_main");
}
void drawVolume(bool isCurrent, int x, int y, RGB bg_color) {
	if (isCurrent) RGBPrint(x, y, L">> " + settings_volume + L":", black, bg_color, true);
	else  RGBPrint(x, y, L"   " + settings_volume +L":", black, bg_color, true);
	int n = getVolume() / 50;
	drawSlider(x+13,y,24,n, bg_color);
	drawDOT(x+15 + n, y, bg_color);
}
void drawSFX(bool isCurrent, int x, int y, RGB bg_color) {
	if (isCurrent) RGBPrint(x, y, L">> " + settings_sfx +L":", black, bg_color, true);
	else RGBPrint(x, y, L"   "+ settings_sfx +L":", black, bg_color, true);
	if (enableSFX) drawCheckBox(x+20, y, pink, bg_color);
	else drawCheckBox(x+20, y, white_pink, bg_color);
}
void drawBGM(bool isCurrent, int x, int y, RGB bg_color) {
	if (isCurrent) RGBPrint(x, y, L">> " + settings_bgm +L":", black, bg_color, true);
	else RGBPrint(x, y, L"   " + settings_bgm +L":", black, bg_color, true);
	if (enableBGM) drawCheckBox(x+20, y, pink, bg_color);
	else drawCheckBox(x+20, y, white_pink, bg_color);
}
void drawLanguage(bool isCurrent, int x, int y, RGB bg_color) {
	fclose(language);
	if (currentLang) fopen_s(&language, "./Languages/vi-vn.txt", "r");
	else fopen_s(&language, "./Languages/en-us.txt", "r");
	loadConfiguration(language);
	wstring language_name = getwstring(language, L"name") + L"      ";
	if (isCurrent) RGBPrint(x, y, L">> " + settings_language + L": " + language_name, black, bg_color, true);
	else RGBPrint(x, y, L"   " + settings_language + L": " + language_name, black, bg_color, true);
}
void drawBackOption(bool isCurrent, int x, int y, RGB bg_color) {
	int _x = x+16 - sizeOfText(back_to_main)/2;
	if (isCurrent) RGBPrint(_x, y, L">> "+ back_to_main, black, bg_color, true);
	else RGBPrint(_x, y, L"   "+ back_to_main, black, bg_color, true);
}
void saveConfig() {
	fclose(config);
	fopen_s(&config, "config.txt", "w");
	fprintf_s(config, ("language: " + string(currentLang ? "vi-vn" : "en-us") + "\n").c_str());
	fprintf_s(config, ("sound_volume: " + to_string(getVolume()) + "\n").c_str());
	fprintf_s(config, ("enable_BGM: " + string(enableBGM ? "true" : "false") + "\n").c_str());
	fprintf_s(config, ("enable_SFX: " + string(enableSFX ? "true" : "false") + "\n").c_str());
	fclose(config);
	fopen_s(&config, "config.txt", "r");
}
void settingsPopup() {
	drawInGameEscPanel_Settings(64, 10);
	int current = 0, previous = 0;
	loadTexts();
	drawVolume(true, 67, 12, white_pink);
	drawSFX(false, 67, 15, white_pink);
	drawBGM(false, 67, 18, white_pink);
	drawLanguage(false, 67, 20, white_pink);
	drawBackOption(false, 67, 22, white_pink);
	while (true) {
		if (_kbhit()) {
			int n = tolower(_getch());
			if ((n == 'a' || n == 'd') && current <= 3) {
				if (current == 0) {
					setVolume(getVolume() + (n == 'd' ? 50 : -50));
					drawVolume(true, 67, 12, white_pink);
				}
				else if (current == 1) {
					enableSFX = !enableSFX;
					drawSFX(true, 67, 15, white_pink);
				}
				else if (current == 2) {
					enableBGM = !enableBGM;
					if (!enableBGM) stopSound(7);
					else playSound(7, 1);
					drawBGM(true, 67, 18, white_pink);
				}
				else if (current == 3) {
					currentLang = !currentLang;
					drawLanguage(true, 67, 20, white_pink);
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
					drawVolume(false, 67, 12, white_pink);
					break;
				case 1:
					drawSFX(false, 67, 15, white_pink);
					break;
				case 2:
					drawBGM(false, 67, 18, white_pink);
					break;
				case 3:
					drawLanguage(false, 67, 20, white_pink);
					break;
				case 4:
					drawBackOption(false, 67, 22, white_pink);
					break;
				}
				switch (current) {
				case 0:
					drawVolume(true, 67, 12, white_pink);
					break;
				case 1:
					drawSFX(true, 67, 15, white_pink);
					break;
				case 2:
					drawBGM(true, 67, 18, white_pink);
					break;
				case 3:
					drawLanguage(true, 67, 20, white_pink);
					break;
				case 4:
					drawBackOption(true, 67, 22, white_pink);
					break;
				}
			}
			if (n == 13 && current == 4) {
				if (enableBGM == false) stopSound(1);
				if (enableSFX) playSound(9, 0);
				//keybinds
				drawInGamePanel_1(120, 27, black, white_pink, white, white_pink);
				RGBPrint(129, 30, getwstring(language, L"ingame_keybind_wasd"), black, white_pink, true);
				RGBPrint(129, 31, getwstring(language, L"ingame_keybind_p"), black, white_pink, true);
				RGBPrint(129, 32, getwstring(language, L"ingame_keybind_o"), black, white_pink, true);
				RGBPrint(129, 33, getwstring(language, L"ingame_keybind_l"), black, white_pink, true);
				RGBPrint(129, 34, getwstring(language, L"ingame_keybind_q"), black, white_pink, true);
				drawPineTree(117, 23, white_pink, 1);
				//match statistics
				drawInGamePanel_1(10, 10, black, white_pink, white, white_pink);
				updateScreen();
				saveConfig();
				break;
			}
		}
	}
}
void SettingsScreen() {
	int current = 0, previous = 0;
	drawPanel(90, 18, 12);
	loadTexts();
	drawVolume(true, 100, 22, light_pink);
	drawSFX(false,100,26, light_pink);
	drawBGM(false, 100, 29, light_pink);
	drawLanguage(false,100,32, light_pink);
	drawBackOption(false,100,34, light_pink);
	while (true) {
		if (_kbhit()) {
			int n = tolower(_getch());
			if ((n == 'a' || n == 'd') && current <=3) {
				if (current == 0) {
					setVolume(getVolume() + (n == 'd' ? 50 : -50));
					drawVolume(true, 100, 22, light_pink);
				}
				else if (current == 1) {
					enableSFX = !enableSFX;
					drawSFX(true, 100, 26, light_pink);
				}
				else if (current == 2) {
					enableBGM = !enableBGM;
					if (enableBGM) playSound(4, 1);
					else stopSound(4);
					drawBGM(true,100,29, light_pink);
				}
				else if (current == 3) {
					currentLang = !currentLang;
					drawLanguage(true,100,32, light_pink);
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
					drawVolume(false,100,22, light_pink);
					break;
				case 1:
					drawSFX(false,100,26, light_pink);
					break;
				case 2:
					drawBGM(false,100,29, light_pink);
					break;
				case 3:
					drawLanguage(false,100,32, light_pink);
					break;
				case 4:
					drawBackOption(false,100,34, light_pink);
					break;
				}
				switch (current) {
				case 0:
					drawVolume(true,100,22, light_pink);
					break;
				case 1:
					drawSFX(true,100,26, light_pink);
					break;
				case 2:
					drawBGM(true,100,29, light_pink);
					break;
				case 3:
					drawLanguage(true,100,32, light_pink);
					break;
				case 4:
					drawBackOption(true,100,34, light_pink);
					break;
				}
			}
			if (n == 13 && current == 4) {
				//if (enableBGM == false) stopSound(1);
				if (enableSFX) playSound(9, 0);
				saveConfig();
				removePanel(90, 18, 12);
				MainScreen(1, 0, false);
			}
		}
	}
} 
