﻿#include "GameScreen.h"
GAME game;
bool key_w = false, key_a = false, key_s = false, key_d = false;
/*Kiểm tra thắng / thua / hòa*/
bool rowCheck(int i, int j, int& count) {
	count = 0; 
	int value = game.turn ? 1 : 2;
	while (i < BOARD_SIZE_HEIGHT && j < BOARD_SIZE_WIDTH) {
		if (game.point[i][j].c == value) {
			count++;
			j++;
		}
		else break;
	}
	return count >= 5;
}
bool colCheck(int i, int j, int& count) {
	count = 0;
	int value = game.turn ? 1 : 2;
	while (i < BOARD_SIZE_HEIGHT) {
		if (game.point[i][j].c == value) {
			count++;
			i++;
		}
		else break;
	}
	return count >= 5;
}
bool leftDiagonalCheck(int i, int j, int& count) {
	count = 0;
	int value = game.turn ? 1 : 2;
	while (i < BOARD_SIZE_HEIGHT && j < BOARD_SIZE_WIDTH) {
		if (game.point[i][j].c == value) {
			count++;
			i++;
			j++;
		}
		else break;
	}
	return count >= 5;
}
bool rightDiagonalCheck(int i, int j, int& count) {
	count = 0;
	int value = game.turn ? 1 : 2;
	while (i < BOARD_SIZE_HEIGHT && j >= 0) {
		if (game.point[i][j].c == value) {
			count++;
			i++;
			j--;
		}
		else break;
	}
	return count >= 5;
}
/*Xử lí thắng / thua / hòa*/
void drawWinEffect(bool isWin, int winType, int row, int col, int streak) {
	int i,
		time = 8,
		timer = 0,
		_col = col,
		_row = row,
		color = 0;
	wstring win_header[5] = {
			L"▐▄• ▄     ▄▄▌ ▐ ▄▌       ▐ ▄ ",
			L" █▌█▌▪    ██· █▌▐█▪     •█▌▐█",
			L" ·██·     ██▪▐█▐▐▌ ▄█▀▄ ▐█▐▐▌",
			L"▪▐█·█▌    ▐█▌██▐█▌▐█▌.▐▌██▐█▌",
			L"•▀▀ ▀▀     ▀▀▀▀ ▀▪ ▀█▄▀▪▀▀ █▪"
	};
	if (!game.turn) {
		win_header[0] = L"          ▄▄▌ ▐ ▄▌       ▐ ▄ ";
		win_header[1] = L"▪         ██· █▌▐█▪     •█▌▐█";
		win_header[2] = L" ▄█▀▄     ██▪▐█▐▐▌ ▄█▀▄ ▐█▐▐▌";
		win_header[3] = L"▐█▌.▐▌    ▐█▌██▐█▌▐█▌.▐▌██▐█▌";
		win_header[4] = L" ▀█▄▀▪     ▀▀▀▀ ▀▪ ▀█▄▀▪▀▀ █▪";
	};
	drawInGamePanel_1A(120, 4, black, white_aqua, white, white_aqua);
	if (enableBGM) {
		stopSound(7);
		playSound(5, false);
	}
	if (isWin) {
		while (true) {
			_col = col; _row = row; 
			color++;
			if (color >= 20) color = 0;
			streak = (streak > 5) ? streak : 5;
			for (i = 0; i < streak; i++) {
				RGBPrint(128,  6 + i % 5, win_header[i % 5], rainbows[(color + i) % 16], white_aqua, false);
				if (winType == 5) {//time out
					RGBPrint(game.point[7][5].x, game.point[7][7].y, "TIME OUT!!", rainbows[(color + i) % 16], white_aqua);
				}
				else {
					if (color <= 15 || color % 2 != 0) RGBPrint(game.point[_row][_col].x, game.point[_row][_col].y, (game.point[_row][_col].c == 1 ? "X" : "O"), rainbows[(color + i) % 16], white_aqua);
					else RGBPrint(game.point[_row][_col].x, game.point[_row][_col].y, " ", white_aqua, white_aqua);

					switch (winType)
					{
					case 1:
						_col++;
						break;
					case 2:
						_row++;
						break;
					case 3:
						_row++;
						_col++;
						break;
					case 4:
						_row++;
						_col--;
						break;
					}
				}
			}
			if (color <= 15) Sleep(100);
			else Sleep(200);
			timer += 1;
			if (timer >= time*10) break;
		}
	}
	drawContinueOption(false);
}
void drawDrawEffect() {
	int i,
		time = 4,
		timer = 0,
		color = 0;
	wstring textBanner[] = {
		L"·▄▄▄▄  ▄▄▄   ▄▄▄· ▄▄▌ ▐ ▄▌",
		L"██▪ ██ ▀▄ █·▐█ ▀█ ██· █▌▐█",
		L"▐█· ▐█▌▐▀▀▄ ▄█▀▀█ ██▪▐█▐▐▌",
		L"██. ██ ▐█•█▌▐█ ▪▐▌▐█▌██▐█▌",
		L"▀▀▀▀▀• .▀  ▀ ▀  ▀  ▀▀▀▀ ▀▪"
	};
	drawInGamePanel_1A(120, 4, black, white_aqua, white, white_aqua);
	while (true) {
		color++;
		for (i = 0; i < 5; i++) RGBPrint(128, 6 + i % 5, textBanner[i], rainbows[(color+i) % 16], white_aqua, false);
		if (color <= 15) Sleep(100);
		else Sleep(200);
		timer += 1;
		if (timer >= time * 10) break;
	}
}
void drawContinueOption(bool saveOption) {
	int i, color =0;
	bool playAgain = false;
	wstring header[5] = {
	   L" ▄▄▄·  ▄▄ •  ▄▄▄· ▪   ▐ ▄ ",
	   L"▐█ ▀█ ▐█ ▀ ▪▐█ ▀█ ██ •█▌▐█",
	   L"▄█▀▀█ ▄█ ▀█▄▄█▀▀█ ▐█·▐█▐▐▌",
	   L"▐█ ▪▐▌▐█▄▪▐█▐█ ▪▐▌▐█▌██▐█▌",
	   L" ▀  ▀ ·▀▀▀▀  ▀  ▀ ▀▀▀▀▀ █▪"
	};
	drawInGamePanel_5(64, 14, black, white_aqua, white_aqua, white_aqua);
	RGBPrint(73, 23, L"Play again?", black, white_aqua, false);
	RGBPrint(78, 25, L">> NO <<", black, light_aqua, false);
	RGBPrint(78, 26, L"   YES  ", black, white_aqua, false);
	if (enableBGM) {
		stopSound(7);
		playSound(8, 1);
	}
	while (true) {
		color++;
		for (i = 0; i < 5; i++) RGBPrint(73, 16 + i % 5, header[i%5], rainbows[color % 16], white_aqua, false);
		if (_kbhit()) {
			int n = tolower(_getch());
			if (n == 'w' || n == 'a' || n == 's' || n == 'd') {
				if (enableSFX) playSound(3, 0);
				playAgain = !playAgain;
				if (playAgain) {
					RGBPrint(78, 25, L"   NO   ", black, white_aqua, false);
					RGBPrint(78, 26, L">> YES <<", black, light_aqua, false);
				}
				else {
					RGBPrint(78, 25, L">> NO <<", black, light_aqua, false);
					RGBPrint(78, 26, L"   YES   ", black, white_aqua, false);
				}
			}
			if (n == 13) {
				if (enableSFX) playSound(9, 0);
				break;
			}
		}
		Sleep(100);
	}
	if (enableBGM) stopSound(8);
	if (playAgain) {
		short a[2] = { 0 };
		resetBoard();
		setupGame(game.name, game._X, game._Y, game.turn, game.gamemode, 15, game.ratio, a, {});
		drawGameBoard(55, 6, 61, 31, black, white_aqua);
		updateScreen();
		removePanel(120, 4, 2);
		drawInGamePanel_3(125, 5, black, white_aqua, white, white_aqua);
		drawTurn(game.turn, 125, 5, light_aqua, aqua, white_aqua);
		StartGame(false, 1);
	}
	else {
		drawGameBoard(55, 6, 61, 31, black, white_aqua);
		if (saveOption) saveGameScreen(true);
		//cái qq j đay?
		system("cls");
		fill(white_aqua);
		drawLOGO((172 - 73) / 2, 5);
		drawMainScreen(0);
		if (enableBGM) playSound(4, 1);
		newGameOptionsScreen();
	}
}
bool checkWin() {
	int count = 0, winType = 0, streak = 0, boardSum = 0;
	for (int i = 0; i < BOARD_SIZE_HEIGHT; i++) {
		for (int j = 0; j < BOARD_SIZE_WIDTH; j++) {
			count = 0;
			/*Kiểm tra xem đã có người chơi thắng hay chưa, đồng thời nếu có
			thì sẽ lưu lại vị trí và chuỗi thắng*/
			if (game.point[i][j].c != 0) boardSum++;
			if (rowCheck(i, j, count)) { winType = 1; streak = count; }
			if (colCheck(i, j, count)) { winType = 2; streak = count; }
			if (leftDiagonalCheck(i, j, count)) { winType = 3; streak = count; }
			if (rightDiagonalCheck(i, j, count)) { winType = 4; streak = count; }
			if (winType != 0) {
				if (game.turn) game.ratio[0]++;
				else game.ratio[1]++;
				updateScreen();
				drawWinEffect(true, winType, i, j, streak);
				return true;
			}
		}
	}
	/*Nếu đánh toàn bộ bảng nhưng vẫn chưa có người thắng thì nghĩa là hòa*/
	if (boardSum == BOARD_SIZE_HEIGHT * BOARD_SIZE_WIDTH) {
		drawDrawEffect();
		drawContinueOption(false);
		return true;
	}
	return false;
}
/*Nạp và lưu trò chơi*/
bool fileExists(string filename) {
	FILE* file;
	fopen_s(&file, ("./Saves/" + filename + ".txt").c_str(), "r");
	if (file) {
		fclose(file);
		return 1;
	}
	return 0;
}
bool loadGame(string filename) {
	if (!fileExists(filename)) return 0;
	bool isLoaded = false;
	FILE* savef;
	fopen_s(&savef, ("./Saves/" + filename + ".txt").c_str(), "r");
	if (loadConfiguration(savef)) {
		wstring text;
		game = {};
		game.name = filename;
		/*Nạp dữ liệu thời gian, lượt đi, chế độ và vị trí con trỏ*/
		game.time = getInt(savef, L"time-left");
		game.turn = getInt(savef, L"turn");
		game.gamemode = getInt(savef, L"gamemode") == 1 ? 1 :  0;
		game._X = getInt(savef, L"Board_X");
		game._Y = getInt(savef, L"Board_Y");
		/*Nạp tỉ số*/
		text = getwstring(savef, L"ratio");
		for (int i = 0; i < text.size(); i++) if (text[i] == ' ') {
			game.ratio[0] = stoi(text.substr(0, i).c_str());
			game.ratio[1] = stoi(text.substr(i + 1));
			break;
		};
		/*Nạp số lượt đánh*/
		text = getwstring(savef, L"hits");
		for (int i = 0; i < text.size(); i++) if (text[i] == ' ') {
			game.hits[0] = stoi(text.substr(0, i).c_str());
			game.hits[1] = stoi(text.substr(i + 1));
			break;
		};
		/*Nạp lịch sử đánh*/
		for (int i = 0; i < 5; i++) {
			text = getwstring(savef, L"history-" + to_wstring(i + 1));
			if (text == L"No data") break;
			game.history.resize(i + 1);

			game.history[i].first = char(stoi(text.substr(0, 2)));
			game.history[i].second = stoi(text.substr(2));
		};
		/*Nạp bảng*/
		for (int i = 0; i < BOARD_SIZE_HEIGHT; i++) {
			text = getwstring(savef, (wstring(L"board-line-") + ((i < 9) ? L"0" : L"") + to_wstring(i + 1)));
			for (int j = 0; j < BOARD_SIZE_WIDTH; j++) {
				game.point[i][j].c = stoi(text.substr(2 * j, 1));
			}
		}
		isLoaded = true;
	}
	fclose(savef);
	return isLoaded; /*Trả về xem là file đã được nạp thành công hay không*/
}
bool saveGame() {
	if (fileExists(game.name)) return 0;
	FILE* savef;
	fopen_s(&savef, ("./Saves/" + game.name + ".txt").c_str(), "w");
	if (savef == NULL) return false;
	/*Lưu các thông số*/
	fprintf_s(savef, ("time-left: " + to_string(game.time) + "\n").c_str());
	fprintf_s(savef, ("gamemode: " + to_string(game.gamemode ? 1 : 0) + "\n").c_str());
	fprintf_s(savef, ("Board_X: " + to_string(game._X) +"\n").c_str());
	fprintf_s(savef, ("Board_Y: " + to_string(game._Y)+"\n").c_str());
	fprintf_s(savef, (game.turn == 1) ? "turn: 1\n" : "turn: 0\n");
	fprintf_s(savef, ("ratio: " + to_string(game.ratio[0]) + " " + to_string(game.ratio[1]) + "\n").c_str());
	fprintf_s(savef, ("hits: " + to_string(game.hits[0]) + " " + to_string(game.hits[1]) + "\n").c_str());
	for (int i = 0; i < 5; i++) {
		fprintf_s(savef, ("history-" + to_string(i + 1) + ": ").c_str());
		fprintf_s(savef, (i < game.history.size()) ?
			(to_string(game.history[i].first) + to_string(game.history[i].second) + "\n").c_str() :
			((string)"No data\n").c_str());
	}
	for (int i = 0; i < BOARD_SIZE_HEIGHT; i++) {
		fprintf(savef, (string("board-line-") + ((i < 9) ? "0" : "") + to_string(i + 1) + ": ").c_str());
		for (int j = 0; j < BOARD_SIZE_WIDTH; j++) {
			fprintf_s(savef, (to_string(game.point[i][j].c) + " ").c_str());
		}
		fprintf_s(savef, "\n");
	}
	fclose(savef);
	return 1;
}
void saveGameScreen(bool refresh) {
	if (refresh) drawMiniPopUp(69, 14, black, white_aqua, white_aqua, white_aqua);
	/*In nội dung cho Popup*/
	RGBPrint(71, 16, L"✍  ", black, light_aqua, false);
	RGBPrint(74, 16, getwstring(language, L"save_name") + L":", black, light_aqua, true);
	RGBPrint(76 + (int)getwstring(language, L"save_name").size(), 16, wstring_convert<codecvt_utf8<wchar_t>>().from_bytes(game.name), black, white_aqua, false);
	RGBPrint(90, 18, getwstring(language, L"save_save"), black, white_aqua, true);
	RGBPrint(75, 18, getwstring(language, L"save_cancel"), black, white_aqua, true);
	//bool isEditing = false;
	string oldname = game.name;
	int curSel = 0, prevSel = 0;
	while (true) {
		if (_kbhit()) {
			int n = tolower(_getch());
			if ((n == 13 || n == 'w' || n == 'a' || n == 's' || n == 'd') && enableSFX) playSound(3, 0); /*Âm thanh di chuyển*/
			/*Vẽ lại các lựa chọn của con trỏ, xóa đánh dấu cũ và in đậm đánh dấu mới*/
			prevSel = curSel;
			if (n == 'w' || n == 'a') {
				curSel = (curSel == 0) ? 2 : curSel - 1;
			}
			if (n == 's' || n == 'd') {
				curSel = (curSel == 2) ? 0 : curSel + 1;
			}
			if (curSel != prevSel) {
				switch (prevSel) {
				case 0:
					RGBPrint(71, 16, L"✍  ", black, white_aqua, false);
					RGBPrint(74, 16, getwstring(language, L"save_name") + L": " + wstring_convert<codecvt_utf8<wchar_t>>().from_bytes(game.name), black, white_aqua, true);
					break;
				case 1:
					RGBPrint(75, 18, getwstring(language, L"save_cancel"), black, white_aqua, true);
					break;
				case 2:
					RGBPrint(90, 18, getwstring(language, L"save_save"), black, white_aqua, true);
					break;
				}
				switch (curSel) {
				case 0:
					RGBPrint(71, 16, L"✍  ", black, light_aqua, false);
					RGBPrint(74, 16, getwstring(language, L"save_name") + L":", black, light_aqua, true);
					break;
				case 1:
					RGBPrint(75, 18, getwstring(language, L"save_cancel"), black, light_aqua, true);
					break;
				case 2:
					RGBPrint(90, 18, getwstring(language, L"save_save"), black, light_aqua, true);
					break;
				}
			}
			/*Xử lí khi ấn enter*/
			if (n == 13) {
				if (curSel != 0) break; /*Nếu con trỏ đang ở vị trí sửa tên thì sẽ khởi động chế độ sửa tên bản lưu*/
				game.name = gameEditor_name(74, 16, black, white_aqua, light_aqua);
				RGBPrint(71, 16, L"✍  ", black, light_aqua, false);
				RGBPrint(74, 16, getwstring(language, L"save_name") + L":", black, light_aqua, true);
				RGBPrint(76 + (int)getwstring(language, L"save_name").size(), 16,game.name, black, white_aqua);
			}
		}
	}
	/*Xử lí tùy chọn lưu hoặc hủy*/
	switch (curSel) {
	case 1:
		game.name = oldname;
		break;
	case 2:
		if (game.name != oldname) {
			try {
				fs::rename("./Saves/" + oldname + ".txt", "./Saves/" + game.name + ".txt");
			}
			catch (const fs::filesystem_error) {
				saveGame();
			}
		}
	}
	if (enableSFX) playSound(9, 0);
}
/*Đếm số lượng bản lưu, đồng thời sắp xếp các bảng lưu theo thời gian đến từng miliseconds*/
int loadAllSaves(vector<string>& saves) {
	int dem = 0;
	vector<pair<string, long>> _saves = {};
	for (const auto& entry : fs::directory_iterator("./Saves")) {
		long s = (long)std::chrono::duration_cast<std::chrono::milliseconds>(fs::last_write_time(entry).time_since_epoch()).count();
		_saves.push_back({ entry.path().filename().string(), s });
		auto ftime = fs::last_write_time(entry);
		dem += 1;
	}
	for (int i = 0; i < _saves.size(); i++) {
		for (int j = i + 1; j < _saves.size(); j++) {
			if (_saves[i].second < _saves[j].second) swap(_saves[i], _saves[j]);
		}
	}
	for (int i = 0; i < _saves.size(); i++) saves.push_back(_saves[i].first.substr(0, _saves[i].first.size() - 4));
	return dem;
}
/*Menu escape*/
bool escapeMenu(int curSel) {
	drawInGameEscPanel(75, 10);
	wstring texts[] = { 
		getwstring(language, L"esc_continue"),  
		getwstring(language, L"esc_options"), 
		getwstring(language, L"esc_draw"), 
		getwstring(language, L"esc_save"),  
		getwstring(language, L"esc_quit") };
	for (int i = 0; i < 5; i++) {
		RGBPrint(86 - sizeOfText(texts[i]) / 2, 12 + 2 * i, texts[i], black, white_aqua, true);
	}
	int  prevSel = 0;
	RGBPrint(83 - sizeOfText(texts[curSel]) / 2, 12 + 2 * curSel,L">> " +  texts[curSel] + L" <<", black, light_aqua, true);
	while (true) {
		if (_kbhit()) {
			char c = tolower(_getch());
			if (c == 'w' || c == 'a' || c == 's' || c == 'd') {
				prevSel = curSel;
				if (c == 'w' || c == 'a') curSel = (curSel == 0) ? 4 : curSel - 1;
				else curSel = (curSel == 4) ? 0 : curSel + 1;
				RGBPrint(83 - sizeOfText(texts[prevSel]) / 2, 12 + 2 * prevSel, L"   " + texts[prevSel] + L"   ", black, white_aqua, true);
				RGBPrint(83 - sizeOfText(texts[curSel]) / 2, 12 + 2 * curSel, L">> " + texts[curSel] + L" <<", black, light_aqua, true);
			}
			if (c == 13) {
				if (enableSFX) playSound(3, 0);
				break;
			}
			if (c == 27) {
				if (enableSFX) playSound(3, 0);
				curSel = 0;
				break;
			}
		}
	}
	switch (curSel) {
	case 0:
		drawGameBoard(55, 6, 61, 31, black, white_aqua);
		StartGame(0,0);
		return 0;
	case 1:
		settingsPopup();
		drawGameBoard(55, 6, 61, 31, black, white_aqua);
		return escapeMenu(curSel);
	case 2:
		DrawOption();
		return escapeMenu(curSel);
	case 3:
		saveGameScreen(true);
		drawGameBoard(55, 6, 61, 31, black, white_aqua);
		return escapeMenu(curSel);
	case 4:
		if (enableSFX) playSound(3, 0);
		if (game.name.size() == 0) saveGameScreen(true);
		return 1;
	}


}
/*Xin hòa, dùng 'o'*/
bool DrawOption() {
	bool draw = false;
	wstring
		text_drawmsg = getwstring(language, L"draw_msg"),
		text_drawacp = getwstring(language, L"draw_accept"),
		text_drawdeny = getwstring(language, L"draw_deny");
	//Thay kí tự %p thành người chơi
	for (int i = 0; i < (int)text_drawmsg.size() - 1; i++) {
		if (text_drawmsg[i] == '%' && text_drawmsg[i + 1] == 'p') {
			text_drawmsg = text_drawmsg.substr(0, i) + (game.turn ? L"X" : L"O") + text_drawmsg.substr(i + 2);
			break;
		}
	}
	//Vẽ
	drawMiniPopUp(69, 14, black, white_aqua, white_aqua, white_aqua);
	RGBPrint(85 - sizeOfText(text_drawmsg)/2, 16, text_drawmsg, black, white_aqua, true);
	RGBPrint(85 - sizeOfText(text_drawacp)/2, 18, text_drawacp, black, white_aqua, true);
	RGBPrint(82 - sizeOfText(text_drawdeny)/2, 19, L">> " + text_drawdeny + L" <<", black, white_aqua, true);
	//Xử lí
	if (enableBGM) {
		stopSound(7);
		playSound(8, 1);
	}
	while (true) {
		if (_kbhit()) {
			int n = tolower(_getch());
			if (n == 'w' || n == 'a' || n == 's' || n == 'd') {
				playSound(3, 0);
				draw = !draw;
				if (draw) {
					RGBPrint(82 - sizeOfText(text_drawacp) / 2, 18, L">> " + text_drawacp + L" <<", black, white_aqua, true);
					RGBPrint(82 - sizeOfText(text_drawdeny) / 2, 19, L"   " + text_drawdeny + L"   ", black, white_aqua, true);
				}
				else {
					RGBPrint(82 - sizeOfText(text_drawacp) / 2, 18,L"   "+ text_drawacp + L"   ", black, white_aqua, true);
					RGBPrint(82 - sizeOfText(text_drawdeny) / 2, 19, L">> " + text_drawdeny + L" <<", black, white_aqua, true);
				}
			}
			if (n == 13) {
				playSound(9, 0);
				break;
			}
		}
	}
	if (draw) {
		drawGameBoard(55, 6, 61, 31, black, white_aqua);
		drawDrawEffect();
		drawContinueOption(false);
	}
	else {
		drawGameBoard(55, 6, 61, 31, black, white_aqua);
		return false;
	}
	return true;
}
/*Xin tạm ngưng, dùng 'p'*/
bool PauseOption() {
	bool pause = false;
	wstring
		text_pausemsg = getwstring(language, L"pause_msg"),
		text_pauseacp = getwstring(language, L"pause_accept"),
		text_pausedeny = getwstring(language, L"pause_deny");
	//Thay kí tự %p thành người chơi
	for (int i = 0; i < (int)text_pausemsg.size() - 1; i++) {
		if (text_pausemsg[i] == '%' && text_pausemsg[i + 1] == 'p') {
			text_pausemsg = text_pausemsg.substr(0, i) + (game.turn ? L"X" : L"O") + text_pausemsg.substr(i + 2);
			break;
		}
	}
	//Vẽ
	drawMiniPopUp(69, 14, black, white_aqua, white_aqua, white_aqua);
	RGBPrint(85 - sizeOfText(text_pausemsg) / 2, 16, text_pausemsg, black, white_aqua, true);
	RGBPrint(82 - sizeOfText(text_pauseacp)/2, 18, L"   " + text_pauseacp + L"   ", black, white_aqua, true);
	RGBPrint(82 - sizeOfText(text_pausedeny) / 2, 19, L">> " + text_pausedeny + L" <<", black, white_aqua, true);
	//Xử lí
	if (enableBGM) {
		stopSound(7);
		playSound(8, 1);
	}
	while (true) {
		if (_kbhit()) {
			int n = tolower(_getch());
			if (n == 'w' || n == 'a' || n == 's' || n == 'd') {
				if (enableSFX) playSound(3, 0);
				pause = !pause;
				if (pause) {
					RGBPrint(82 - sizeOfText(text_pauseacp) / 2, 18, L">> " + text_pauseacp + L" <<", black, white_aqua, true);
					RGBPrint(82 - sizeOfText(text_pausedeny) / 2, 19, L"   " + text_pausedeny + L"   ", black, white_aqua, true);
				}
				else {
					RGBPrint(82 - sizeOfText(text_pauseacp) / 2, 18, L"   " + text_pauseacp + L"   ", black, white_aqua, true);
					RGBPrint(82 - sizeOfText(text_pausedeny) / 2, 19, L">> " + text_pausedeny + L" <<", black, white_aqua, true);
				}
			}
			if (n == 13) {
				if (enableSFX) playSound(9, 0);
				break;
			}
		}
	}
	//_getch();
	drawGameBoard(55, 6, 61, 31, black, white_aqua);
	if (pause) {
		wstring text_continueMsg = getwstring(language, L"pause_continue");
		drawInGamePanel_1A(120, 4, black, white_aqua, white, white_aqua);
		RGBPrint(140 - sizeOfText(text_continueMsg)/2, 10, text_continueMsg, black, white_aqua, true);
		drawPauseText(124, 5, white_aqua);
		return true;
	}
	return false;
}
/*Xử lí đồ họa*/
void fixKeyboard() {
	if (key_w) {
		key_w = !key_w;
		drawInGameKeyboard(124 + 13, 14 + 1, 'w', key_w, black, white_aqua);
	}
	if (key_a) {
		key_a = !key_a;
		drawInGameKeyboard(124 + 3, 14 + 5, 'a', key_a, black, white_aqua);
	}
	if (key_s) {
		key_s = !key_s;
		drawInGameKeyboard(124 + 13, 14 + 6, 's', key_s, black, white_aqua);
	}
	if (key_d) {
		key_d = !key_d;
		drawInGameKeyboard(124 + 24, 14 + 5, 'd', key_d, black, white_aqua);
	}
}
void updateScreen() {
	wstring
		ingame_ratio = getwstring(language, L"ingame_ratio"),
		ingame_time = getwstring(language, L"ingame_time"),
		ingame_hits = getwstring(language, L"ingame_hits");
	RGBPrint(16, 12, ingame_ratio, black, white_aqua, true);
	RGBPrint(32-9, 13,
		wstring(L"[X]: ") + ((game.ratio[0] < 10) ? L"0" : L"") + to_wstring(game.ratio[0]) +
		wstring(L" | [O]: ") + ((game.ratio[1] < 10) ? wstring(L"0") : wstring(L"")) + to_wstring(game.ratio[1])
		, black, white_aqua, false);

	RGBPrint(16, 15,
		ingame_time + L": " + wstring((game.time < 10) ? L"0" : L"") + to_wstring(game.time) + L"s",
		black, white_aqua, true);

	RGBPrint(16, 17, ingame_hits + L":", black, white_aqua, true);
	RGBPrint(32-9 , 18	,
		wstring(L"[X]: " + wstring((game.hits[0] < 10) ? L"0" : L"")) + to_wstring(game.hits[1]) +
		wstring(L" | [O]: ") + wstring((game.hits[1] < 10) ? L"0" : L"") + to_wstring(game.hits[0]),
		black, white_aqua, false);
	bool c = !game.turn;
	for (int i = 0; i < game.history.size(); i++) {
		if (i == 5) break;
		string text = (c) ? "[X]" : "[O]";
		c = !c;
		RGBPrint(20, 25 + 2 * i, text, black, white_aqua);
		RGBPrint(30, 25 + 2 * i,
			char(game.history[i].first) + string((game.history[i].second < 10) ? "0" : "") + to_string(game.history[i].second)
			, black, white_aqua);
	}
}
void updateFullBoard() {
	for (int i = 0; i < BOARD_SIZE_HEIGHT; i++) {
		for (int j = 0; j < BOARD_SIZE_WIDTH; j++) {
			RGBPrint(game.point[i][j].x, game.point[i][j].y,
				(game.point[i][j].c  == 0 ? L" " : game.point[i][j].c  == 1 ? L"X" : L"O"),
				black, white_aqua, false);
		}
	}
}
void drawTheScreen() {
	fill(white_aqua);
	//background
	drawInGameHeader(3, 1);
	//match statistics
	drawInGamePanel_1(9, 10, black, white_aqua, white, white_aqua);
	//history
	drawInGamePanel_2(12, 22, black, white_aqua, white, white_aqua);
	//turn
	drawInGamePanel_3(125, 5, black, white_aqua, white, white_aqua);
	//

	drawSnowFlake(116, 18, white_aqua);
	//keyboard
	drawInGamePanel_4(124, 14, black, white_aqua, white, white_aqua);
	drawInGameKeyboard(124 + 13, 14 + 1, 'w', key_w, black, white_aqua);
	drawInGameKeyboard(124 + 3, 14 + 5, 'a', key_a, black, white_aqua);
	drawInGameKeyboard(124 + 13, 14 + 6, 's', key_s, black, white_aqua);
	drawInGameKeyboard(124 + 24, 14 + 5, 'd', key_d, black, white_aqua);
	//keybinds
	drawInGamePanel_1(120, 27, black, white_aqua, white, white_aqua);

	RGBPrint(129, 30, getwstring(language, L"ingame_keybind_wasd"), black, white_aqua, true);
	RGBPrint(129, 31, getwstring(language, L"ingame_keybind_p"), black, white_aqua, true);
	RGBPrint(129, 32, getwstring(language, L"ingame_keybind_o"), black, white_aqua, true);
	RGBPrint(129, 33, getwstring(language, L"ingame_keybind_l"), black, white_aqua, true);
	RGBPrint(129, 34, getwstring(language, L"ingame_keybind_q"), black, white_aqua, true);
	//
	drawReindeer(25, 3, white_aqua);
	drawSnowFlake(48, 5, white_aqua);
	drawPineTree(117, 23, white_aqua, 1);
	//
	drawGameBoard(55, 6, 61, 31, black, white_aqua);
	updateScreen();
}
void reRenderCursor(bool boldColor) {
	RGBPrint(game.point[game._Y][game._X].x, game.point[game._Y][game._X].y,
		(game.point[game._Y][game._X].c == 0 ? L" " : game.point[game._Y][game._X].c == 1 ? L"X" : L"O"),
		black, (boldColor ? light_aqua : white_aqua), false);
}
//PVE
int getRandom(int a, int b) {
	return a + std::rand() % (b - a + 1);
}
bool botHitRandom() {
	bool check = false;

	Sleep(400);
	reRenderCursor(false);
	while (!check) {
		game._Y = getRandom(0, 9), game._X = getRandom(0,14);
		if (game.point[game._Y][game._X].c == 0) {
			game.point[game._Y][game._X].c = 2;
			game.history.insert(game.history.begin(), { 65 + game._Y, game._X + 1 });
			check = true;
		}
	}
	reRenderCursor(true);
	if (checkWin()) {
		if (game.turn) game.ratio[0]++;
		else game.ratio[1]++;
		return true;
	}
	game.hits[0]++;
	game.turn = !game.turn;
	game.time = 15;
	drawTurn(game.turn, 125, 5, light_aqua, aqua, white_aqua);
	return false;
}
//Xừ lí trò chơi
bool boardTick() {
	if (game.point[game._Y][game._X].c == 0) {
		if (enableSFX) playSound(11, 0);
		//đánh dấu lên bảng & thêm vào lịch xử
		game.point[game._Y][game._X].c = game.turn ? 1 : 2;
		game.history.insert(game.history.begin(), { 65 + game._X, game._Y + 1 });
		reRenderCursor(true);
		//cập nhật lượt đánh
		if (game.turn) game.hits[1]++;
		else game.hits[0]++;
		//kiểm tra thắng
		if (checkWin()) return true;
		else {

		}
		//đổi lượt
		game.turn = !game.turn;
		game.time = 15;

		drawTurn(game.turn, 125, 5, light_aqua, aqua, white_aqua);
		if (game.gamemode == 1) {
			if (botHitRandom()) return true;
		}
		return false;
	}
	return false;
}
/*Xử lí trò chơi khi người dùng nhập*/
bool inputProcessing(char c) {
	if (c == 27) { /*escape: mở menu escape trong game*/
		bool _tmp = escapeMenu(0);
		if (_tmp == 0) {
			drawTheScreen();
		}
		return _tmp;
	}
	if (c == 'l') {/*Lưu trò chơi*/
		saveGameScreen(true);
		drawGameBoard(55, 6, 61, 31, black, white_aqua);
		StartGame(0, 1);
		return false;
	}
	if (c == 'q') {/*Thoát*/
		if (enableSFX) playSound(3, 0);
		if (game.name.size() == 0) saveGameScreen(true);
		return true;
	}
	if (c == 'o') {/*xin hòa*/
		DrawOption();
		if (enableBGM) {
			stopSound(8);
			playSound(7, 1);
		}
		updateFullBoard();
		reRenderCursor(true);
		return false;
	}
	if (c == 'p') {/*Xin tạm dừng*/
		if (PauseOption()) {
			removePanel(120, 4, 2);
			drawInGamePanel_3(125, 5, black, white_aqua, white, white_aqua);
			drawTurn(game.turn, 125, 5, light_aqua, aqua, white_aqua);
		}
		if (enableBGM) {
			stopSound(8);
			playSound(7, 1);
		}
		updateFullBoard();
		reRenderCursor(true);
		return false;
	}
	if (c == 13) {/*Đánh dấu lên bảng*/
		return boardTick();
	}
	/*Xử lí di chuyển*/
	if (c == 'w' || c == 'a' || c == 's' || c == 'd') movementProcessing(c);
	return false;
}
void movementProcessing(char c) {
	if (enableSFX) playSound(10, 0);
	reRenderCursor(false); //ẩn con trỏ cũ
	switch (c) {
	case 'w':
		game._Y = (game._Y == 0) ? game._Y : game._Y - 1;
		key_w = !key_w;
		drawInGameKeyboard(124 + 13, 14 + 1, 'w', key_w, black, white_aqua);
		break;
	case 'a':
		game._X = (game._X == 0) ? game._X : game._X - 1;
		key_a = !key_a;
		drawInGameKeyboard(124 + 3, 14 + 5, 'a', key_a, black, white_aqua);
		break;
	case 'd':
		game._X = (game._X == BOARD_SIZE_WIDTH - 1) ? game._X : game._X + 1;
		key_d = !key_d;
		drawInGameKeyboard(124 + 24, 14 + 5, 'd', key_d, black, white_aqua);
		break;
	case 's':
		game._Y = (game._Y == BOARD_SIZE_HEIGHT - 1) ? game._Y : game._Y + 1;
		key_s = !key_s;
		drawInGameKeyboard(124 + 13, 14 + 6, 's', key_s, black, white_aqua);
		break;
	}
	reRenderCursor(true);//tô đậm lại vị trí mới
}
bool timeProcessing(int& count) {
	count += 50;
	if (count >= 1000) {
		game.time -= 1;
		count = 0;
		if (game.time < 0) {
			game.time = 0;
			game.turn = !game.turn;
			if (game.turn) game.ratio[0]++;
			else game.ratio[1]++;
			updateScreen();
			drawTurn(game.turn, 125, 5, light_aqua, aqua, white_aqua);
			drawWinEffect(true, 5, 0, 0, 0);
			return true;
		}
	}
	return false;
}
void resetPosOnBoard() {
	for (int i = 0; i < BOARD_SIZE_HEIGHT; i++) for (int j = 0; j < BOARD_SIZE_WIDTH; j++) {
		game.point[i][j].x = 57 + j * 4;
		game.point[i][j].y = 7 + 2 * i;
	}
}
void resetBoard() {
	resetPosOnBoard();
	for (int i = 0; i < BOARD_SIZE_HEIGHT; i++) for (int j = 0; j < BOARD_SIZE_WIDTH; j++) {
		game.point[i][j].c = 0;
	}
}
void StartGame(bool drawBackground, bool startBGM) {
	int count = 0;
	if (enableBGM && startBGM) {
		stopSound(4);
		playSound(7, 1);
	}
	//vẽ lại nền
	resetPosOnBoard();
	if (drawBackground) {
		system("cls");
		drawTheScreen();
		updateFullBoard();
		drawTurn(game.turn, 125, 5, light_aqua, aqua, white_aqua);
	}
	reRenderCursor(true);
	//xử lí
	while (true) {
		if (_kbhit()) {
			int n = _getch();
			char c = tolower(n);
			if (inputProcessing(c)) break;
		}
		Sleep(50);
		if (timeProcessing(count)) break;
		updateScreen();
		fixKeyboard();
	}
	//cái qq j đay?
	system("cls");
	fill(white_aqua);
	drawLOGO((172 - 73) / 2, 5);
	drawMainScreen(0);
	if (enableBGM) {
		stopSound(7);
		playSound(4, 1);
	}
	newGameOptionsScreen();
}
//Game SETUP
void setupGame(string name, int _x, int _y, bool turn,bool gamemode, short time, short ratio[2], short hits[2], vector<pair<short, short>> history) {
	game.name = name;
	game._X = _x;
	game._Y = _y;
	game.turn = turn;
	game.gamemode = gamemode;
	game.time = time;
	game.ratio[0] = ratio[0]; game.ratio[1] = ratio[1];
	game.hits[0] = hits[0]; game.hits[1] = hits[1];
	game.history = history;
	resetPosOnBoard();
}

string gameEditor_name(int x, int y, RGB text_color, RGB background_color, RGB selected_color) {//default: x=112, y=27
	ShowConsoleCursor(true);
	string newname = game.name;
	GotoXY(x + 2 + (int)getwstring(language, L"save_name").size() + (int)game.name.size(), y);//fix here
	int n;
	while (true) {///8: delete, 13: enter, 27: escape
		if (_kbhit()) {
			n = _getch();
			/*Xử lí khi nhập*/
			if ((n >= 'A' && n <= 'Z') || (n >= 'a' && n <= 'z') || (n >= '0' && n <= '9') || n == '_') {
				if (newname.size() < 12) {/*Giới hạn 12 kí tự*/
					newname.push_back(n);
					RGBPrint(x, y, L"            ", text_color, background_color, false);
					RGBPrint(x-3, y, L"✍  ", text_color, selected_color, false);
					RGBPrint(x + 0, y, getwstring(language, L"save_name") + L":", text_color, selected_color, true);
					RGBPrint(x +2 + (int)getwstring(language, L"save_name").size(), y, wstring_convert<codecvt_utf8<wchar_t>>().from_bytes(newname) + L" ", text_color, background_color, false);
				}
			}
			/*Xử lí khi xóa*/
			if (n == 8) {
				if (newname.size() > 0) {
					newname.pop_back();
					RGBPrint(x, y, L"            ", text_color, background_color, false);
					RGBPrint(x-3, y, L"✍  ", text_color, selected_color, false);
					RGBPrint(x + 0, y, getwstring(language, L"save_name") + L":", text_color, selected_color, true);
					RGBPrint(x + 2 + (int)getwstring(language, L"save_name").size(), y, wstring_convert<codecvt_utf8<wchar_t>>().from_bytes(newname) + L" ", text_color, background_color, false);
				}
			}
			/*Thông báo bản lưu đã tồn tại*/
			if (fileExists(newname) && newname != game.name) {
				RGBPrint(x + 8, y - 1, getwstring(language, L"save_exists"), { 255,0,0 }, background_color, true);
			}
			else {
				RGBPrint(x + 8, y - 1, L"              ", { 255,0,0 }, background_color, false);
				if (n == 13) {
					if (newname.size() == 0) {/*Tên bản lưu phải có ít nhất 1 kí tự*/
						RGBPrint(x + 8, y - 1, getwstring(language, L"save_invalidName"), { 255,0,0 }, background_color, true);
					}
					else {
						RGBPrint(x-3, y, L"✍  ", text_color, selected_color, false);
						RGBPrint(x + 0, y, getwstring(language, L"save_name") + L":", text_color, selected_color, true);

						RGBPrint(x + 2 + (int)getwstring(language, L"save_name").size(), y, L"            ", text_color, background_color, false);
						RGBPrint(x + 2 + (int)getwstring(language, L"save_name").size(), y, wstring_convert<codecvt_utf8<wchar_t>>().from_bytes(newname) + L" ", text_color, background_color, false);
						break;
					}
				}
				if (n == 27) {/*Thoát khỏi chế độ nhập tên*/
					newname = game.name;
					RGBPrint(x + 2 + (int)getwstring(language, L"save_name").size(), y, L"            ", text_color, background_color, false);
					break;
				}
			}
			GotoXY(x + 2 + (int)getwstring(language, L"save_name").size() + (int)newname.size(), y);
		}
	}
	ShowConsoleCursor(false);
	return newname;
}
/*Đếm ngược để xóa bản lưu, ấn phím bất kì để hủy*/
void gameEditor_remove(string savename) {
	int second_to_remove = 7000;/*Thời gian để người dùng có thể hủy trước khi xóa, tính theo miliseconds*/
	wstring _message = getwstring(language, L"save_remove_countdown"), message;
	int index = 0;
	/*Thay lại %d thành thời gian tương ứng*/
	for (int i = 0; i < _message.size(); i++) if (_message[i] == '%') {
		index = i;
		message = _message.substr(0, index) + to_wstring(second_to_remove/1000) + _message.substr(index + 2);
		break;
	}
	RGBPrint(118 - sizeOfText(message) / 2, 33, message, black, light_aqua, true);

	while (true) {
		/*Nếu ấn 1 phím bất kì thì sẽ dừng việc xóa bản lưu*/
		if (_kbhit()) {
			_getch();
			GotoXY(118 - sizeOfText(message) / 2, 33);
			for (int i = 0; i < sizeOfText(message); i++) cout << " ";
			break;
		}
		/*Cập nhật lại thông báo*/
		message = _message.substr(0, index) + to_wstring(second_to_remove/1000) + _message.substr(index + 2);
		RGBPrint(118-sizeOfText(message)/2, 33, message, black, light_aqua, true);
		/*Bộ đếm*/
		second_to_remove -= 50;
		Sleep(50);
		if (second_to_remove <= 0) {/*Khi đã hết thời gian thì xóa bản lưu*/
			try {
				fs::remove("./Saves/" + savename + ".txt");
			}
			catch (const fs::filesystem_error& e) {
				std::cerr << "Error: " << e.what() << std::endl;
			}
			break;
		}
	}
	/*Nếu bản lưu đã xóa thì quay lại giao diện danh sách các bản lưu,
	không thì quay trở lại phần chỉnh sửa bản lưu*/
	if (second_to_remove <= 0) loadGameScreen();
	else loadSaveGameEditor(savename, false, 2);

}
/*Chỉnh sửa bản lưu*/
void loadSaveGameEditor(string savename, bool refresh, int curSel) {
	loadGame(savename);
	int x = 100, y = 25;
	int n, prevSel = 0;
	/*Nạp các dòng văn bản*/
	wstring
		text_save_editor = getwstring(language, L"save_editor"),
		text_save_load = getwstring(language, L"save_load"),
		text_save_remove = getwstring(language, L"save_remove"),
		text_save_back = getwstring(language, L"save_back");
	/*Tùy chọn tải lại giao diện*/
	if (refresh) {
		removePanel(90, 18, 13);
		drawPanel(90, 18, 11);
		RGBPrint(118-sizeOfText(text_save_editor)/2, 21, text_save_editor, black, light_aqua, true);
	}
	/*In ra các nội dung*/
	RGBPrint(118-sizeOfText(text_save_load)/2, y - 2, text_save_load, black, (curSel==0) ? aqua : light_aqua, true);
	RGBPrint(x-3, y, L"✍  ", black, (curSel == 1) ? aqua : light_aqua, false);
	RGBPrint(x, y, getwstring(language, L"ingame_name") + L":", black, (curSel == 1) ? aqua : light_aqua, true);
	RGBPrint(x+2+ getwstring(language, L"ingame_name").size(), y, wstring_convert<codecvt_utf8<wchar_t>>().from_bytes(savename), black, light_aqua, true);
	RGBPrint(x, y+1, getwstring(language, L"ingame_turn") + wstring(L": ") + wstring((game.turn) ? L"[X]" : L"[O]"), black, light_aqua, true);
	RGBPrint(x, y+2, getwstring(language, L"ingame_timeleft") + wstring(L": ") + wstring((game.time < 10) ? L"0" : L"") + to_wstring(game.time) + L"s", black, light_aqua, true);
	RGBPrint(x, y+3, getwstring(language, L"ingame_ratio") + wstring(L": ") + wstring(L"[X]: ") + ((game.ratio[0] < 10) ? L"0" : L"") + to_wstring(game.ratio[0]) + wstring(L" | [O]: ") + wstring((game.ratio[1] < 0) ? L"0" : L"") + to_wstring(game.ratio[1]), black, light_aqua, true);
	RGBPrint(x, y+4, getwstring(language, L"ingame_hits") + wstring(L": [X]: ") + wstring((game.hits[0] < 10) ? L"0" : L"") + to_wstring(game.hits[0]) + wstring(L" | [O]: ") + wstring((game.hits[1] < 10) ? L"0" : L"") + to_wstring(game.hits[1]), black, light_aqua, true);
	RGBPrint(118-sizeOfText(text_save_remove)/2, y + 6, text_save_remove, black, (curSel == 2) ? aqua : light_aqua, true);
	RGBPrint(118-sizeOfText(text_save_back)/2, y + 8, text_save_back, black, (curSel == 3) ? aqua : light_aqua, true);
	/*Xử lí di khi di chuyển giữa các mục*/
	while (true) {
		if (_kbhit()) {
			n = _getch();
			n = tolower(n);
			if ((n == 13 || n == 'w' || n == 'a' || n == 's' || n == 'd') && enableSFX) playSound(3, 0);
			if (n == 13) break;
			prevSel = curSel;
			if (n == 'w' || n == 'a') {
				curSel = (curSel == 0) ? 3 : curSel - 1;
			}
			if (n == 's' || n == 'd') {
				curSel = (curSel == 3) ? 0 : curSel + 1;
			}
			if (curSel != prevSel) {
				switch (prevSel) {
				case 0:
					RGBPrint(118 - sizeOfText(text_save_load) / 2, y - 2, text_save_load, black, light_aqua, true);
					break;
				case 1:
					RGBPrint(x-3, y, L"✍  ", black, light_aqua, false);
					RGBPrint(x, y, getwstring(language, L"ingame_name") + L":", black, light_aqua, true);
					break;
				case 2:
					RGBPrint(118 - sizeOfText(text_save_remove)/2, y + 6, text_save_remove, black, light_aqua, true);
					break;
				case 3:
					RGBPrint(118 - sizeOfText(text_save_back) / 2, y + 8, text_save_back, black, light_aqua, true);
					break;
				}
				switch (curSel) {
				case 0:
					RGBPrint(118 - sizeOfText(text_save_load) / 2, y - 2, text_save_load, black, aqua, true);
					break;
				case 1:
					RGBPrint(x-3, y, L"✍  ", black, aqua, false);
					RGBPrint(x, y, getwstring(language, L"ingame_name") + L":", black, aqua, true);
					break;
				case 2:
					RGBPrint(118 - sizeOfText(text_save_remove)/2, y + 6, text_save_remove, black, aqua, true);
					break;
				case 3:
					RGBPrint(118 - sizeOfText(text_save_back) / 2, y + 8, text_save_back, black, aqua, true);
					break;
				}
			}
		}
	}	
	/*Xử lí mục đang chọn*/
	switch (curSel) {
	case 0:/*Xác nhận nạp bản lưu*/
		loadGame(savename);
		if (enableSFX) playSound(6, 0);
		StartGame(1, 1);
		break;
	case 1: {/*Bật chế độ sửa tên bản lưu*/
		string oldname = game.name;
		game.name = gameEditor_name(x, y, black, light_aqua, aqua);
		try {
			fs::rename("./Saves/" + oldname + ".txt", "./Saves/" + game.name + ".txt");
		}
		catch (const fs::filesystem_error& e) {
			std::cerr << "Error: " << e.what() << std::endl;
		}
		loadSaveGameEditor(game.name, false, curSel);
		break;
	}
	case 2:/*Bật chế độ xóa bản lưu đếm ngược*/
		gameEditor_remove(savename);
		break;
	case 3:/*Quay về menu danh sách bản lưu*/
		removePanel(90, 18, 11);
		if (enableSFX) playSound(9, 0);
		loadGameScreen();
		break;
	}
}
/*Menu tùy chọn tạo ván mới hay nạp bản lưu*/
void newGameOptionsScreen() {
	drawPanel(90, 18, 5);/*Vẽ khung*/
	/*Nạp văn bản*/
	wstring options[3] = { getwstring(language, L"play_newgame"), getwstring(language, L"play_loadgame"), getwstring(language, L"back_to_main") };
	int curSel = 0, prevSel = 0;
	int n, size = sizeof(options) / sizeof(wstring);
	/*In văn bản*/
	for (int i = 0; i < size; i++) {
		if (i == 0) RGBPrint(115 - sizeOfText(options[i])/2, 21 + 2 * i, L">> " + options[i] + L" <<", black, light_aqua, true);
		else RGBPrint(115 - sizeOfText(options[i]) / 2, 21 + 2 * i, L"   " + options[i] + L"   ", black, light_aqua, true);
	}
	/*Xử lí di chuyển và cập nhật đồ họa*/
	while (true) {
		if (_kbhit()) {
			n = _getch();
			n = tolower(n);
			if ((n == 13 || n == 'w' || n == 'a' || n == 's' || n == 'd' || n == 'e') && enableSFX) playSound(3, 0);
			if (n == 13) {
				if (enableSFX) playSound(9, 0);
				break;
			}
			prevSel = curSel;
			if (n == 'w' or n == 'a') {//go up
				curSel--;
				curSel = (curSel < 0) ? size - 1 : curSel;
			}
			else if (n == 's' or n == 'd') {//go down
				curSel++;
				curSel = (curSel > size - 1) ? 0 : curSel;
			}
			RGBPrint(115 - sizeOfText(options[prevSel]) / 2, 21 + 2 * prevSel, L"   " + options[prevSel] + L"   ", black, light_aqua, true);
			RGBPrint(115 - sizeOfText(options[curSel]) / 2, 21 + 2 * curSel, L">> " + options[curSel] + L" <<", black, light_aqua, true);
		}
	}
	switch (curSel) {
	case 0: {/*Tạo một trò chơi mới*/
		selectModeScreen();
		break;
	}
	case 1: /*Nạp bản lưu*/
		loadGameScreen();
		break;
	case 2:/*Quay lại menu trước đó*/
		removePanel(90, 18, 5);
		MainScreen(0, 0, false);
		break;
	}
}
/*Menu chọn chế độ chơi*/
void selectModeScreen() {
	/*Nạp văn b ản*/
	wstring options[3] = { getwstring(language, L"play_pvp"),getwstring(language, L"play_pve"), getwstring(language, L"play_back") };
	int curSel = 0, prevSel = 0;
	int n, size = sizeof(options) / sizeof(wstring);
	/*Xóa khung cũ và vẽ khung mới, đồng thời in văn bản*/
	removePanel(90, 18, 5);
	drawPanel(90, 18, 4);
	for (int i = 0; i < size; i++) {
		if (i == 0) RGBPrint(115 - sizeOfText(options[i]) / 2, 21 + 2 * i, L">> " + options[i] + L" <<", black, light_aqua, true);
		else RGBPrint(115 - sizeOfText(options[i]) / 2, 21 + 2 * i, L"   " + options[i] + L"   ", black, light_aqua, true);
	}
	/*Xử lí di chuyển và đồ họa*/
	while (true) {
		if (_kbhit()) {
			n = _getch();
			n = tolower(n);
			if ((n == 13 || n == 'w' || n == 'a' || n == 's' || n == 'd' || n == 'e') && enableSFX) playSound(3, 0);
			if (n == 13) {
				if (enableSFX) playSound(9, 0);
				break;
			}
			prevSel = curSel;
			if (n == 'w' or n == 'a') {//go up
				curSel--;
				curSel = (curSel < 0) ? size - 1 : curSel;
			}
			else if (n == 's' or n == 'd') {//go down
				curSel++;
				curSel = (curSel > size - 1) ? 0 : curSel;
			}
			RGBPrint(115 - sizeOfText(options[prevSel]) / 2, 21 + 2 * prevSel, L"   " + options[prevSel] + L"   ", black, light_aqua, true);
			RGBPrint(115 - sizeOfText(options[curSel]) / 2, 21 + 2 * curSel, L">> " + options[curSel] + L" <<", black, light_aqua, true);
		}
	}
	switch (curSel) {
	case 0: {/*Chế độ PVP*/
		short a[2] = { 0 };
		resetBoard();
		setupGame("",7,5, 1, 0, 15, a, a, {});
		StartGame(1,1);
		break;
	}
	case 1: {/*Chế độ  PVE*/
		short a[2] = { 0 };
		resetBoard();
		setupGame("", 7,5,1, 1, 15, a, a, {});
		StartGame(1,1);
		break;
	}
	case 2:/*Quay lại Menu trước*/
		removePanel(90, 18, 4);
		newGameOptionsScreen();
		break;
	}
}
/*Giao diện menu danh sách bản lưu*/
void loadGameScreen() {
	/*Lấy thông tin cơ bản như số bản lưu, tên các bản lưu, từ đó phân chia cho 
	số bản lưu mỗi trang và số trang tất cả*/
	vector<string> saves_names = {};
	int saves = loadAllSaves(saves_names);
	int currentpage = 1,
		maxpages = int(ceil((double)saves / 5)),
		index = 0,
		previousSelect = 0,
		maxindex = (saves - 5 * currentpage >= 0) ? 5 : saves,
		x = 98,
		y = 22;
	if (maxpages == 0) maxpages++;
	/*Nạp văn bản*/
	wstring text_name = getwstring(language, L"save_name"),
			text_back = getwstring(language, L"play_back");
	/*Xóa khung cũ và vẽ khung mới*/
	removePanel(90, 18, 5);
	drawPanel(90, 18, 13);
	//TO DO: MOVE SANG MODELUTIL
	RGBPrint(x, y-1, L"      ║                                    ", black, light_aqua, false);
	RGBPrint(x, y, L"══════╬════════════════════════════════════", black, light_aqua, false);
	int _i = 0;
	for (int i = 0; i < 2 * 5; i++) {
		if (i % 2 == 0) {
			RGBPrint(x, y + i + 1, L"      ║                                    ", black, light_aqua, false);
			if (_i < saves_names.size() && _i <= maxindex - 1) {
				RGBPrint(x + 2, y + i + 1, string((_i + 1 < 10) ? "0" : "") + to_string(_i + 1), black, light_aqua);
				RGBPrint(x + 7 + (14 - (int)saves_names[_i].size() / 2), y + i + 1, saves_names[_i], black, light_aqua);
				_i++;
			}
		}
		else RGBPrint(x, y + i + 1, L"══════╬════════════════════════════════════", black, light_aqua, false);
	}
	RGBPrint(x, y+10, L"══════╩════════════════════════════════════", black, light_aqua, false);
	RGBPrint(x, y + 11, L"                                           ", black, light_aqua, false);
	RGBPrint(x + 1, y + 11, L"<<", black, light_aqua, false);
	RGBPrint(x + 18, y + 11, L"01/" + wstring((saves / 5 < 10) ? L"0" : L"") + to_wstring(maxpages), black, light_aqua, false);
	RGBPrint(x + 38, y + 11, L">>", black, light_aqua, false);

	RGBPrint(x, y + 12, L"═══════════════════════════════════════════", black, light_aqua, false);
	RGBPrint(115 - sizeOfText(text_back)/2, y + 13, L"   " + text_back + L"   ", black, light_aqua, true);
	//
	if (saves_names.size() >= 1) {
		RGBPrint(x + 2, y + 2 * index + 1, string((index + 1 < 10) ? "0" : "") + to_string(index + 1), black, aqua);
		RGBPrint(x + 7 + (14 - (int)saves_names[index].size() / 2), y + 2 * index + 1, saves_names[index], black, aqua);
	}
	int n;
	/*Xử lí di chuyển và cập nhật đồ họa*/
	while (true) {//từ đây trở đi tôi đã mất não.
		if (_kbhit()) {
			n = _getch();
			n = tolower(n);
			if ((n == 'w' || n == 'a' || n == 's' || n == 'd' || n == 'e' || n == 'x') && enableSFX) playSound(3, 0);
			if (n == 13) break;
			if (n == 'w' || n == 's') {
				previousSelect = index;
				if (n == 'w') index = (index <= 0) ? maxindex : index - 1;
				else index = (index >= maxindex) ? 0 : index + 1;
				int d = 5 * (currentpage - 1);
				if (previousSelect < maxindex) {
					RGBPrint(x + 2, y + 2 * previousSelect + 1, string((previousSelect + 1 + d < 10) ? "0" : "") + to_string(previousSelect + d + 1), black, light_aqua);
					RGBPrint(x + 7 + (14 - (int)saves_names[previousSelect + d].size() / 2), y + 2 * previousSelect + 1, saves_names[previousSelect + d], black, light_aqua);
				}
				else RGBPrint(115 - sizeOfText(text_back) / 2, y + 13, L"   " + text_back + L"   ", black, light_aqua, true);

				if (index < maxindex) {
					RGBPrint(x + 2, y + 2 * index + 1, string((index + d + 1 < 10) ? "0" : "") + to_string(index + d + 1), black, aqua);
					RGBPrint(x + 7 + (14 - (int)saves_names[index + d].size() / 2), y + 2 * index + 1, saves_names[index + d], black, aqua);
				}
				else RGBPrint(115 - sizeOfText(text_back) / 2, y + 13, L">> " + text_back + L" <<", black, light_aqua, true);
			}
			if ((n == 'a' || n == 'd') && index < maxindex) {
				if (n == 'a') currentpage = (currentpage == 1) ? maxpages : currentpage - 1;
				else currentpage = (currentpage == maxpages) ? 1 : currentpage + 1;
				index = 0;
				previousSelect = 0;
				maxindex = (saves - 5 * currentpage >= 0) ? 5 : saves - 5 * (currentpage - 1);
				_i = 5 * (currentpage - 1);
				for (int i = 0; i < 2 * 5; i++) {
					if (i % 2 == 0) {
						RGBPrint(x, y + i + 1, L"      ║                                    ", black, light_aqua, false);
						if (_i < saves_names.size()) {
							if (_i <= maxindex + 5 * (currentpage - 1)) {
								RGBPrint(x + 7 + (14 - (int)saves_names[_i].size() / 2), y + i + 1, saves_names[_i], black, light_aqua);
								RGBPrint(x + 2, y + i + 1, string((_i + 1 < 10) ? "0" : "") + to_string(_i + 1), black, light_aqua);
								_i++;
							}
						}
					}
					else RGBPrint(x, y + i + 1, L"══════╬════════════════════════════════════", black, light_aqua, false);
				}
				RGBPrint(x + 18, y + 11, wstring((currentpage < 10) ? L"0" : L"") + to_wstring(currentpage) + L"/" + wstring((saves / 5 < 10) ? L"0" : L"") + to_wstring(maxpages), black, light_aqua, false);

				_i = 5 * (currentpage - 1);
				RGBPrint(x + 7 + (14 - (int)saves_names[_i].size() / 2), y + 1, saves_names[_i], black, aqua);
				RGBPrint(x + 2, y + 1, string((_i + 1 < 10) ? "0" : "") + to_string(_i + 1), black, aqua);
			}
		}
	}
	if (enableSFX) playSound(9, 0);
	if (index < maxindex) {
		loadSaveGameEditor(saves_names[index + 5 * (currentpage - 1)], true, 0);
	}
	else {
		removePanel(90, 18, 13);
		newGameOptionsScreen();
	}
}

