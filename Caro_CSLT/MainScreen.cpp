#include "MainScreen.h"
void drawQuitOptions() {
	wstring message = getwstring(language, L"quit_message") , confirm = getwstring(language, L"quit_confirm"), cancel = getwstring(language, L"quit_cancel");
	int width = sizeOfText(confirm) + sizeOfText(cancel) + 8,
		x1 = 118 - width/2 - sizeOfText(confirm) / 2,
		x2 = 118 + 4 + sizeOfText(cancel) / 2;
	bool isConfirm = true;
	drawPanel(90, 18, 4);
	RGBPrint(118-int(sizeOfText(message)/2), 22, message, black, light_aqua, true);
	RGBPrint(x1, 24, L"\033[4m" + confirm + L"\033[0m", black, light_aqua, true);
	RGBPrint(x2, 24, cancel , black, light_aqua, true);

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
					RGBPrint(x1, 24, L"\033[4m" + confirm + L"\033[0m", black, light_aqua, true);
					RGBPrint(x2, 24, cancel, black, light_aqua, true);
				}
				else {
					RGBPrint(x1, 24, confirm, black, light_aqua, true);
					RGBPrint(x2, 24, L"\033[4m" + cancel + L"\033[0m", black, light_aqua, true);
				}
			}
		}
	}
	if (isConfirm) {
		closeProgram();
		ExitProcess(0);
	}
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
		RGBPrint(96, 21 + i, getwstring(language, L"help_" + to_wstring(i + 1)), black, light_aqua, true);
	}
	RGBPrint(116- sizeOfText(back_text)/2, 36, L">> " + back_text +L" <<", black, light_aqua, true);
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
/*Vẽ giao diện*/
void drawMainScreen(int curSel) {
	/*Vẽ các nút*/
	drawMainMenu_Play(35, 15);
	drawMainMenu_Options(35, 20);
	drawMainMenu_Help(35, 25);
	drawMainMenu_Authors(35, 30);
	drawMainMenu_Out(35, 35);
	drawTriagle(30, 15 + curSel * 5, true);
	/*Vẽ trang trí*/
	drawPineTree(32, 11, white_aqua, 1);
	drawPineTree(72, 11, white_aqua, 1);
	drawPineTree(82, 32, white_aqua, 1);

	drawSnowFlake(5, 12, white_aqua);
	drawSnowFlake(65, 0, white_aqua);
	drawSnowFlake(105, 13, white_aqua);
	drawSnowFlake(150, 35, white_aqua);

	drawGift(151, 18, white_aqua);
	drawCandy(160, 4, white_aqua);
	drawReindeer(17, 22, white_aqua);
	drawSnowman(10, 29, white_aqua);	
}
void MainScreen(int curSel, bool playBGM, bool clear) {
	int prevSel = 0;
	int n, index = 0;
	bool draw_tria = true;
	if (enableBGM && playBGM) playSound(4, true);
	if (clear) for (int i = 16; i < 42; i++) clearLine(i);
	drawMainScreen(curSel);
	/*Xử lí di chuyển và cập nhật đồ họa*/
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
	/*Xử lí tùy chọn*/
	switch (curSel) {
	case 4:/*Mở menu tùy chọn thoát game*/
		GotoXY(0, 0);
		drawQuitOptions();
		break;
	case 3:/*Mở menu các người phát triển*/
		ContributorsScreen();
		break;
	case 2:/*Mở menu hướng dẫn*/
		helpScreen();
		break;
	case 1:/*Mở menu cài đặt*/
		SettingsScreen();
		break;
	case 0:/*Giao diện tùy chọn tạo/nạp trò chơi*/
		newGameOptionsScreen();
		break;
	}
}