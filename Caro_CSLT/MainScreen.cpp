#include "MainScreen.h"
void drawQuitOptions() {
	drawPanel(100, 20, 4);
	RGBPrint(122, 24, L"Want to quit?", white, light_pink, true);
	RGBPrint(123, 26, L"\033[4mYES\033[0m", white, light_pink, true);
	RGBPrint(131, 26, L"NO", white, light_pink, true);
	bool check = true;
	while (true) {
		if (_kbhit()) {
			int n = tolower(_getch());
			if ((n == 13 || n == 'w' || n == 'a' || n == 's' || n == 'd' || n == 'e') && enableSFX) playSound(3, 0);
			if (n == 13) break;
			if (n == 'w' || n == 'a' || n == 's' || n == 'd') {
				check = !check;
				if (check) {
					RGBPrint(123, 26, L"\033[4mYES\033[0m", white, light_pink, true);
					RGBPrint(131, 26, L"NO", white, light_pink, true);
				}
				else {
					RGBPrint(123, 26, L"YES", white, light_pink, true);
					RGBPrint(131, 26, L"\033[4mNO\033[0m", white, light_pink, true);
				}
			}
		}
	}
	if (check) ExitProcess(0);
	else {
		removePanel(100, 20, 4);
		MainScreen(3, 0, false);
	}
}
void MainScreen(int currentSelect, bool playBGM, bool clear) {
	if (playBGM) playSound(1, true);
	if (clear) for (int i = 16; i < 42; i++) clearLine(i);
	int previousSelect =0;
	drawMainMenu_Play(10, 20, true);
	drawMainMenu_Options(10, 25, true);
	drawMainMenu_Authors(10, 30, true);
	drawMainMenu_Out(10, 35, true);
	drawTriagle(55, 20 + currentSelect * 5, true);
	int n, index = 0;
	bool draw_tria = true;
	while (true) {
		if (_kbhit()) {
			n = _getch();
			n = tolower(n);
			if ((n == 13 || n == 'w' || n == 'a' || n == 's' || n == 'd' || n == 'e') && enableSFX) playSound(3, 0);
			if (n == 13)
			{
				drawTriagle(55, 20 + currentSelect * 5, true);
				break;
			}
			previousSelect = currentSelect;
			if (n == 'w' or n == 'a') {//go up
				currentSelect--;
				currentSelect = (currentSelect < 0) ? 4 - 1 : currentSelect;
			}
			else if (n == 's' or n == 'd') {//go down
				currentSelect++;
				currentSelect = (currentSelect > 4 - 1) ? 0 : currentSelect;
			}
			//xóa đánh dấu cũ
			drawTriagle(55, 20 + previousSelect * 5, false);
			//đánh dấu mới
			drawTriagle(55, 20 + currentSelect * 5, true);
			index = 400;
		}
		Sleep(50);
		index += 50;
		if (index <= 400) {
			drawTriagle(55, 20 + currentSelect * 5, false);
			draw_tria = false;
		}
		else {
			drawTriagle(55, 20 + currentSelect * 5, true);
			draw_tria = true;
			if (index >= 800) index = 0;
		}
	}
	switch (currentSelect) {
	case 3:
		GotoXY(0, 0);
		drawQuitOptions();
		break;
	case 2:
		ContributorsScreen();
		break;
	case 1:
		SettingsScreen();
		break;
	case 0:
		GameScreen(0);
		break;
	}
}