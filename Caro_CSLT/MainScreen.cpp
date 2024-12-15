#include "MainScreen.h"
void drawQuitOptions() {
	wstring message = getwstring(language, L"quit_message") , confirm = getwstring(language, L"quit_confirm"), cancel = getwstring(language, L"quit_cancel");
	int width = sizeOfText(confirm) + sizeOfText(cancel) + 8,
		x1 = 118 - width/2 - sizeOfText(confirm) / 2,
		x2 = 118 + 4 + sizeOfText(cancel) / 2;
	bool isConfirm = true;
	drawPanel(90, 18, 4);
	RGBPrint(118-int(sizeOfText(message)/2), 22, message, black, light_pink, true);
	RGBPrint(x1, 24, L"\033[4m" + confirm + L"\033[0m", black, light_pink, true);
	RGBPrint(x2, 24, cancel , black, light_pink, true);

	while (true) {
		if (_kbhit()) {
			int n = tolower(_getch());
			if (( n == 'w' || n == 'a' || n == 's' || n == 'd' || n == 'e') && enableSFX) playSound(3, 0);
			if (n == 13) {
				if (enableSFX) playSound(9, 0);
				break;
			}
			if (n == 'w' || n == 'a' || n == 's' || n == 'd') {
				isConfirm = !isConfirm;
				if (isConfirm) {
					RGBPrint(x1, 24, L"\033[4m" + confirm + L"\033[0m", black, light_pink, true);
					RGBPrint(x2, 24, cancel, black, light_pink, true);
				}
				else {
					RGBPrint(x1, 24, confirm, black, light_pink, true);
					RGBPrint(x2, 24, L"\033[4m" + cancel + L"\033[0m", black, light_pink, true);
				}
			}
		}
	}
	if (isConfirm) ExitProcess(0);
	else {
		removePanel(90, 18, 4);
		MainScreen(4, 0, false);
	}
}
void helpScreen() {
	drawPanel(90, 18, 14);
	int lines = getInt(language, L"help");
	wstring back_text = getwstring(language, L"back_to_main");
	for (int i = 0; i < lines; i++) {
		RGBPrint(96, 21 + i, getwstring(language, L"help_" + to_wstring(i + 1)), black, light_pink, true);
	}
	RGBPrint(116- sizeOfText(back_text)/2, 36, L">> " + back_text +L" <<", black, light_pink, true);
	while (true) {
		if (_kbhit()) {
			if (_getch() == 13) {
				if (enableSFX) playSound(9, 0);
				break;
			}
		}
	}
	removePanel(90, 18, 14);
	MainScreen(2, 0, false);
}
void drawMainScreen(int curSel) {
	drawMainMenu_Play(35, 15);
	drawMainMenu_Options(35, 20);
	drawMainMenu_Help(35, 25);
	drawMainMenu_Authors(35, 30);
	drawMainMenu_Out(35, 35);
	drawTriagle(30, 15 + curSel * 5, true);
	//ve gi do vui vui
	drawPineTree(32, 11, white_pink, 1);
	drawPineTree(72, 11, white_pink, 1);
	drawPineTree(82, 32, white_pink, 1);

	drawSnowFlake(5, 12, white_pink);
	drawSnowFlake(65, 0, white_pink);
	drawSnowFlake(105, 13, white_pink);
	drawSnowFlake(150, 35, white_pink);

	drawGift(151, 18, white_pink);
	drawCandy(160, 4, white_pink);
	drawReindeer(17, 22, white_pink);
	drawSnowman(10, 29, white_pink);	
}
void MainScreen(int curSel, bool playBGM, bool clear) {
	int prevSel = 0;
	int n, index = 0;
	bool draw_tria = true;
	if (enableBGM && playBGM) playSound(4, true);
	if (clear) for (int i = 16; i < 42; i++) clearLine(i);
	drawMainScreen(curSel);
	while (true) {
		if (_kbhit()) {
			n = _getch();
			n = tolower(n);
			if (( n == 'w' || n == 'a' || n == 's' || n == 'd' ) && enableSFX) playSound(3, 0);
			if (n == 13)
			{
				if (enableSFX) playSound(9, 0);
				drawTriagle(30, 15 + curSel * 5, true);
				break;
			}
			prevSel = curSel;
			if (n == 'w' or n == 'a') {//go up
				curSel--;
				curSel = (curSel < 0) ? 4 : curSel;
			}
			else if (n == 's' or n == 'd') {//go down
				curSel++;
				curSel = (curSel > 4) ? 0 : curSel;
			}
			//xóa đánh dấu cũ
			drawTriagle(30, 15 + prevSel * 5, false);
			//đánh dấu mới
			drawTriagle(30, 15 + curSel * 5, true);
			index = 400;
		}
		Sleep(50);
		index += 50;
		if (index <= 400) {
			drawTriagle(30, 15 + curSel * 5, false);
			draw_tria = false;
		}
		else {
			drawTriagle(30, 15 + curSel * 5, true);
			draw_tria = true;
			if (index >= 800) index = 0;
		}
	}
	switch (curSel) {
	case 4:
		GotoXY(0, 0);
		drawQuitOptions();
		break;
	case 3:
		ContributorsScreen();
		break;
	case 2:
		helpScreen();
		break;
	case 1:
		SettingsScreen();
		break;
	case 0:
		GameScreen(0);
		break;
	}
}