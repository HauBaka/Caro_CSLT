#include "MainScreen.h"
void drawQuitOptions() {
	for (int i = 16; i < 30; i++) {
		clearLine(i);
	}
	string options[2] = { "I WANT TO QUIT", "NO, TAKE ME BACK" };
	int a=0, b=0;
	drawOptions(90,16,options, 2, a, b);
	if (a == 0) ExitProcess(0);
	else MainScreen(3,0, false);
}
void MainScreen(int currentSelect, bool playBGM, bool clear) {
	if (playBGM) playSound(1, true);
	if (clear) for (int i = 16; i < 42; i++) {
		clearLine(i);
	}
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
			drawTriagle(55, 20 + currentSelect * 5, draw_tria);
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