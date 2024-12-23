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
	if (enableSFX) drawCheckBox(x+20, y, aqua, bg_color);
	else drawCheckBox(x+20, y, white_aqua, bg_color);
}
void drawBGM(bool isCurrent, int x, int y, RGB bg_color) {
	if (isCurrent) RGBPrint(x, y, L">> " + settings_bgm +L":", black, bg_color, true);
	else RGBPrint(x, y, L"   " + settings_bgm +L":", black, bg_color, true);
	if (enableBGM) drawCheckBox(x+20, y, aqua, bg_color);
	else drawCheckBox(x+20, y, white_aqua, bg_color);
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
/*Lưu lại cài đặt của trò chơi*/
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
/*Menu khi ấn esc trong game*/
void settingsPopup() {
	int current = 0, previous = 0;
	/*Vẽ khung và in văn bản*/
	drawInGameEscPanel_Settings(64, 10);
	loadTexts();
	drawVolume(true, 67, 12, white_aqua);
	drawSFX(false, 67, 15, white_aqua);
	drawBGM(false, 67, 18, white_aqua);
	drawLanguage(false, 67, 20, white_aqua);
	drawBackOption(false, 67, 22, white_aqua);
	/*Xử lí*/
	while (true) {
		if (_kbhit()) {
			int n = tolower(_getch());
			if ((n == 'a' || n == 'd') && current <= 3) {/*Xử lí thay đổi tùy chọn*/
				if (current == 0) {/*Thay đổi âm lượng*/
					setVolume(getVolume() + (n == 'd' ? 50 : -50));
					drawVolume(true, 67, 12, white_aqua);
				}
				else if (current == 1) {/*Bật/tắt SFX*/
					enableSFX = !enableSFX;
					drawSFX(true, 67, 15, white_aqua);
				}
				else if (current == 2) {/*Bật/tắt nhạc nền*/
					enableBGM = !enableBGM;
					if (!enableBGM) stopSound(7);
					else playSound(7, 1);
					drawBGM(true, 67, 18, white_aqua);
				}
				else if (current == 3) {/*Thay đổi ngôn ngữ*/
					currentLang = !currentLang;
					drawLanguage(true, 67, 20, white_aqua);
				}
			}
			/*Xử lí di chuyển và âm thanh hiệu ứng*/
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
					drawVolume(false, 67, 12, white_aqua);
					break;
				case 1:
					drawSFX(false, 67, 15, white_aqua);
					break;
				case 2:
					drawBGM(false, 67, 18, white_aqua);
					break;
				case 3:
					drawLanguage(false, 67, 20, white_aqua);
					break;
				case 4:
					drawBackOption(false, 67, 22, white_aqua);
					break;
				}
				switch (current) {
				case 0:
					drawVolume(true, 67, 12, white_aqua);
					break;
				case 1:
					drawSFX(true, 67, 15, white_aqua);
					break;
				case 2:
					drawBGM(true, 67, 18, white_aqua);
					break;
				case 3:
					drawLanguage(true, 67, 20, white_aqua);
					break;
				case 4:
					drawBackOption(true, 67, 22, white_aqua);
					break;
				}
			}
			/*Thoát*/
			if (n == 13 && current == 4) {
				if (enableBGM == false) stopSound(1);
				if (enableSFX) playSound(9, 0);
				//keybinds
				drawInGamePanel_1(120, 27, black, white_aqua, white, white_aqua);
				RGBPrint(129, 30, getwstring(language, L"ingame_keybind_wasd"), black, white_aqua, true);
				RGBPrint(129, 31, getwstring(language, L"ingame_keybind_p"), black, white_aqua, true);
				RGBPrint(129, 32, getwstring(language, L"ingame_keybind_o"), black, white_aqua, true);
				RGBPrint(129, 33, getwstring(language, L"ingame_keybind_l"), black, white_aqua, true);
				RGBPrint(129, 34, getwstring(language, L"ingame_keybind_q"), black, white_aqua, true);
				drawPineTree(117, 23, white_aqua, 1);
				//match statistics
				drawInGamePanel_1(10, 10, black, white_aqua, white, white_aqua);
				updateScreen();/*Cập nhật lại ngôn ngữ trò chơi*/
				saveConfig();
				break;
			}
		}
	}
}
void SettingsScreen() {
	int current = 0, previous = 0;
	/*Vẽ khung và in văn bản*/
	drawPanel(90, 18, 12);
	loadTexts();
	drawVolume(true, 100, 22, light_aqua);
	drawSFX(false,100,26, light_aqua);
	drawBGM(false, 100, 29, light_aqua);
	drawLanguage(false,100,32, light_aqua);
	drawBackOption(false,100,34, light_aqua);
	/*Xử lí*/
	while (true) {
		if (_kbhit()) {
			int n = tolower(_getch());
			if ((n == 'a' || n == 'd') && current <=3) {/*Xử lí thay đổi tùy chọn*/
				if (current == 0) {/*Thay đổi âm lượng*/
					setVolume(getVolume() + (n == 'd' ? 50 : -50));
					drawVolume(true, 100, 22, light_aqua);
				}
				else if (current == 1) {/*Bật/tắt SFX*/
					enableSFX = !enableSFX;
					drawSFX(true, 100, 26, light_aqua);
				}
				else if (current == 2) {/*Bật/tắt nhạc nền*/
					enableBGM = !enableBGM;
					if (enableBGM) playSound(4, 1);
					else stopSound(4);
					drawBGM(true,100,29, light_aqua);
				}
				else if (current == 3) {/*Thay đổi ngôn ngữ*/
					currentLang = !currentLang;
					drawLanguage(true,100,32, light_aqua);
				}
			}
			/*Xử lí di chuyển và âm thanh hiệu ứng*/
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
					drawVolume(false,100,22, light_aqua);
					break;
				case 1:
					drawSFX(false,100,26, light_aqua);
					break;
				case 2:
					drawBGM(false,100,29, light_aqua);
					break;
				case 3:
					drawLanguage(false,100,32, light_aqua);
					break;
				case 4:
					drawBackOption(false,100,34, light_aqua);
					break;
				}
				switch (current) {
				case 0:
					drawVolume(true,100,22, light_aqua);
					break;
				case 1:
					drawSFX(true,100,26, light_aqua);
					break;
				case 2:
					drawBGM(true,100,29, light_aqua);
					break;
				case 3:
					drawLanguage(true,100,32, light_aqua);
					break;
				case 4:
					drawBackOption(true,100,34, light_aqua);
					break;
				}
			}
			/*Thoát*/
			if (n == 13 && current == 4) {
				if (enableSFX) playSound(9, 0);
				saveConfig();
				removePanel(90, 18, 12);
				MainScreen(1, 0, false);
			}
		}
	}
} 
