#include "MainScreen.h"
void drawQuitOptions() {
	wstring message = getwstring(language, L"quit_message") , confirm = getwstring(language, L"quit_confirm"), cancel = getwstring(language, L"quit_cancel");
	int x1 = 120 - (int(confirm.length() + cancel.length()) + 3) / 2 - int(confirm.length() / 2), 
		x2= 123 - (int(confirm.length() + cancel.length()) + 3) / 2 + int(cancel.length() / 2);
	drawPanel(90, 18, 4);

	RGBPrint(118-int(message.length()/2), 22, message, white, light_pink, true);
	RGBPrint(x1, 24, L"\033[4m" + confirm + L"\033[0m", white, light_pink, true);
	RGBPrint(x2, 24, cancel , white, light_pink, true);
	bool check = true;
	while (true) {
		if (_kbhit()) {
			int n = tolower(_getch());
			if ((n == 13 || n == 'w' || n == 'a' || n == 's' || n == 'd' || n == 'e') && enableSFX) playSound(3, 0);
			if (n == 13) break;
			if (n == 'w' || n == 'a' || n == 's' || n == 'd') {
				check = !check;
				if (check) {
					RGBPrint(x1, 24, L"\033[4m" + confirm + L"\033[0m", white, light_pink, true);
					RGBPrint(x2, 24, cancel, white, light_pink, true);
				}
				else {
					RGBPrint(x1, 24, confirm, white, light_pink, true);
					RGBPrint(x2, 24, L"\033[4m" + cancel + L"\033[0m", white, light_pink, true);
				}
			}
		}
	}
	if (check) ExitProcess(0);
	else {
		removePanel(90, 18, 4);
		MainScreen(3, 0, false);
	}
}
void MainScreen(int currentSelect, bool playBGM, bool clear) {
	if (playBGM) playSound(1, true);
	if (clear) for (int i = 16; i < 42; i++) clearLine(i);
	int previousSelect =0;
	drawMainMenu_Play(35, 20);
	drawMainMenu_Options(35, 25);
	drawMainMenu_Authors(35, 30);
	drawMainMenu_Out(35, 35);
	drawTriagle(30, 20 + currentSelect * 5, true);
	//ve gi do vui vui
	drawPineTree(15, 30, white_pink, 1);
	drawPineTree(75, 13, white_pink, 1);
	drawPineTree(129,6, white_pink, 1);

	drawSnowFlake(5, 12, white_pink);
	drawSnowFlake(65, 0, white_pink);
	drawSnowFlake(105, 13, white_pink);
	drawSnowFlake(150, 35, white_pink);

	drawGift(151, 18, white_pink);
	drawCandy(160, 4, white_pink);
	drawReindeer(43, 13, white_pink);
	int n, index = 0;
	bool draw_tria = true;
	while (true) {
		if (_kbhit()) {
			n = _getch();
			n = tolower(n);
			if ((n == 13 || n == 'w' || n == 'a' || n == 's' || n == 'd' || n == 'e') && enableSFX) playSound(3, 0);
			if (n == 13)
			{
				drawTriagle(30, 20 + currentSelect * 5, true);
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
			drawTriagle(30, 20 + previousSelect * 5, false);
			//đánh dấu mới
			drawTriagle(30, 20 + currentSelect * 5, true);
			index = 400;
		}
		Sleep(50);
		index += 50;
		if (index <= 400) {
			drawTriagle(30, 20 + currentSelect * 5, false);
			draw_tria = false;
		}
		else {
			drawTriagle(30, 20 + currentSelect * 5, true);
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