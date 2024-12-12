#include "GameScreen.h"
GAME game;
bool key_w = false, key_a = false, key_s = false, key_d = false;
//Kiểm tra thắng/thua/hòa
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
//Xử lí thắng/thua/hòa
void drawWinEffect(bool isWin, int winType, int row, int col, int streak) {
	int i,
		time = 8,
		timer = 0,
		_col = col,
		_row = row,
		color = 0;
	RGB colors[16] = {
	{199,66,79},
	{224,107,81},
	{242,165,97},
	{242,165,97},
	{177,212,128},
	{128,184,120},
	{128,184,120},
	{137,217,217},
	{137,217,217},
	{92,139,168},
	{78,102,121},
	{70,73,105},
	{68,53,93},
	{61,0,61},
	{98,23,72},
	{148,44,75}
	};
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
	drawInGamePanel_1A(120, 4, black, white_pink, white, white_pink);
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
				RGBPrint(128,  6 + i % 5, win_header[i % 5], colors[(color + i) % 16], white_pink, false);
				if (winType == 5) {//time out
					RGBPrint(game.point[7][5].x, game.point[7][7].y, "TIME OUT!!", colors[(color + i) % 16], white_pink);
				}
				else {
					if (color <= 15 || color % 2 != 0) RGBPrint(game.point[_row][_col].x, game.point[_row][_col].y, (game.point[_row][_col].c == 1 ? "X" : "O"), colors[(color + i) % 16], white_pink);
					else RGBPrint(game.point[_row][_col].x, game.point[_row][_col].y, " ", white_pink, white_pink);

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
	RGB colors[16] = {
	{199,66,79},
	{224,107,81},
	{242,165,97},
	{242,165,97},
	{177,212,128},
	{128,184,120},
	{128,184,120},
	{137,217,217},
	{137,217,217},
	{92,139,168},
	{78,102,121},
	{70,73,105},
	{68,53,93},
	{61,0,61},
	{98,23,72},
	{148,44,75}
	};
	wstring textBanner[] = {
		L"·▄▄▄▄  ▄▄▄   ▄▄▄· ▄▄▌ ▐ ▄▌",
		L"██▪ ██ ▀▄ █·▐█ ▀█ ██· █▌▐█",
		L"▐█· ▐█▌▐▀▀▄ ▄█▀▀█ ██▪▐█▐▐▌",
		L"██. ██ ▐█•█▌▐█ ▪▐▌▐█▌██▐█▌",
		L"▀▀▀▀▀• .▀  ▀ ▀  ▀  ▀▀▀▀ ▀▪"
	};
	drawInGamePanel_1A(120, 4, black, white_pink, white, white_pink);
	while (true) {
		color++;
		for (i = 0; i < 5; i++) RGBPrint(128, 6 + i % 5, textBanner[i], colors[(color+i) % 16], white_pink, false);
		if (color <= 15) Sleep(100);
		else Sleep(200);
		timer += 1;
		if (timer >= time * 10) break;
	}
}
void drawContinueOption(bool saveOption) {
	int i, color =0;
	bool playAgain = false;
	RGB colors[16] = {
	{199,66,79},
	{224,107,81},
	{242,165,97},
	{242,165,97},
	{177,212,128},
	{128,184,120},
	{128,184,120},
	{137,217,217},
	{137,217,217},
	{92,139,168},
	{78,102,121},
	{70,73,105},
	{68,53,93},
	{61,0,61},
	{98,23,72},
	{148,44,75}
	};
	wstring header[5] = {
	   L" ▄▄▄·  ▄▄ •  ▄▄▄· ▪   ▐ ▄ ",
	   L"▐█ ▀█ ▐█ ▀ ▪▐█ ▀█ ██ •█▌▐█",
	   L"▄█▀▀█ ▄█ ▀█▄▄█▀▀█ ▐█·▐█▐▐▌",
	   L"▐█ ▪▐▌▐█▄▪▐█▐█ ▪▐▌▐█▌██▐█▌",
	   L" ▀  ▀ ·▀▀▀▀  ▀  ▀ ▀▀▀▀▀ █▪"
	};
	drawInGamePanel_5(64, 14, black, white_pink, white_pink, white_pink);
	RGBPrint(73, 23, L"Play again?", black, white_pink, false);
	RGBPrint(78, 25, L">> NO <<", black, light_pink, false);
	RGBPrint(78, 26, L"   YES  ", black, white_pink, false);
	if (enableBGM) {
		stopSound(7);
		playSound(8, 1);
	}
	while (true) {
		color++;
		for (i = 0; i < 5; i++) RGBPrint(73, 16 + i % 5, header[i%5], colors[color % 16], white_pink, false);
		if (_kbhit()) {
			int n = tolower(_getch());
			if (n == 'w' || n == 'a' || n == 's' || n == 'd') {
				playSound(3, 0);
				playAgain = !playAgain;
				if (playAgain) {
					RGBPrint(78, 25, L"   NO   ", black, white_pink, false);
					RGBPrint(78, 26, L">> YES <<", black, light_pink, false);
				}
				else {
					RGBPrint(78, 25, L">> NO <<", black, light_pink, false);
					RGBPrint(78, 26, L"   YES   ", black, white_pink, false);
				}
			}
			if (n == 13) {
				playSound(9, 0);
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
		drawGameBoard(55, 6, 61, 31, black, white_pink);
		updateScreen();
		removePanel(120, 4, 2);
		drawInGamePanel_3(125, 5, black, white_pink, white, white_pink);
		drawTurn(game.turn, 125, 5, light_pink, pink, white_pink);
		StartGame(false);
	}
	else {
		drawGameBoard(55, 6, 61, 31, black, white_pink);
		if (saveOption) saveGameScreen(true);
		//cái qq j đay?
		system("cls");
		fill(white_pink);
		drawLOGO((172 - 73) / 2, 5);
		drawMainScreen(0);
		GameScreen(0);
	}
}
bool checkWin() {
	int count = 0, winType = 0, streak = 0, boardSum = 0;
	for (int i = 0; i < BOARD_SIZE_HEIGHT; i++) {
		for (int j = 0; j < BOARD_SIZE_WIDTH; j++) {
			count = 0;
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
	if (boardSum == BOARD_SIZE_HEIGHT * BOARD_SIZE_WIDTH) {
		drawDrawEffect();
		return true;
	}
	return false;
}
//Tải & lưu game
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
		//load time, turn, gamemode
		game.time = getInt(savef, L"time-left");
		game.turn = getInt(savef, L"turn");
		game.gamemode = getInt(savef, L"gamemode") == 1 ? 1 :  0;
		game._X = getInt(savef, L"Board_X");
		game._Y = getInt(savef, L"Board_Y");
		//load ratio
		text = getwstring(savef, L"ratio");
		for (int i = 0; i < text.size(); i++) if (text[i] == ' ') {
			game.ratio[0] = stoi(text.substr(0, i).c_str());
			game.ratio[1] = stoi(text.substr(i + 1));
			break;
		};
		//load hits
		text = getwstring(savef, L"hits");
		for (int i = 0; i < text.size(); i++) if (text[i] == ' ') {
			game.hits[0] = stoi(text.substr(0, i).c_str());
			game.hits[1] = stoi(text.substr(i + 1));
			break;
		};
		//load history
		for (int i = 0; i < 5; i++) {
			text = getwstring(savef, L"history-" + to_wstring(i + 1));
			if (text == L"No data") break;
			game.history.resize(i + 1);

			game.history[i].first = char(stoi(text.substr(0, 2)));
			game.history[i].second = stoi(text.substr(2));
		};
		//load board
		for (int i = 0; i < BOARD_SIZE_HEIGHT; i++) {
			text = getwstring(savef, (wstring(L"board-line-") + ((i < 9) ? L"0" : L"") + to_wstring(i + 1)));
			for (int j = 0; j < BOARD_SIZE_WIDTH; j++) {
				game.point[i][j].c = stoi(text.substr(2 * j, 1));
			}
		}
		isLoaded = true;
	}
	fclose(savef);
	return isLoaded;
}
bool saveGame() {
	if (fileExists(game.name)) return 0;
	FILE* savef;
	fopen_s(&savef, ("./Saves/" + game.name + ".txt").c_str(), "w");
	if (savef == NULL) return false;
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
	if (refresh) drawMiniPopUp(69, 14, black, white_pink, white_pink, white_pink);
	RGBPrint(71, 16, L"✍  ", black, light_pink, false);
	RGBPrint(74, 16, getwstring(language, L"save_name") + L":", black, light_pink, true);
	RGBPrint(76 + (int)getwstring(language, L"save_name").size(), 16, wstring_convert<codecvt_utf8<wchar_t>>().from_bytes(game.name), black, white_pink, false);
	RGBPrint(90, 18, getwstring(language, L"save_save"), black, white_pink, true);
	RGBPrint(75, 18, getwstring(language, L"save_cancel"), black, white_pink, true);
	bool isEditing = false;
	string oldname = game.name;
	int curSel = 0, prevSel = 0;
	while (true) {
		if (_kbhit()) {
			int n = tolower(_getch());
			if ((n == 13 || n == 'w' || n == 'a' || n == 's' || n == 'd') && enableSFX) playSound(3, 0);

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
					RGBPrint(71, 16, L"✍  ", black, white_pink, false);
					RGBPrint(74, 16, getwstring(language, L"save_name") + L": " + wstring_convert<codecvt_utf8<wchar_t>>().from_bytes(game.name), black, white_pink, true);
					break;
				case 1:
					RGBPrint(75, 18, getwstring(language, L"save_cancel"), black, white_pink, true);
					break;
				case 2:
					RGBPrint(90, 18, getwstring(language, L"save_save"), black, white_pink, true);
					break;
				}
				switch (curSel) {
				case 0:
					RGBPrint(71, 16, L"✍  ", black, light_pink, false);
					RGBPrint(74, 16, getwstring(language, L"save_name") + L":", black, light_pink, true);
					break;
				case 1:
					RGBPrint(75, 18, getwstring(language, L"save_cancel"), black, light_pink, true);
					break;
				case 2:
					RGBPrint(90, 18, getwstring(language, L"save_save"), black, light_pink, true);
					break;
				}
			}
			if (n == 13) {
				if (curSel != 0) break;
				game.name = gameEditor_name(74, 16, black, white_pink, light_pink);
				RGBPrint(71, 16, L"✍  ", black, light_pink, false);
				RGBPrint(74, 16, getwstring(language, L"save_name") + L":", black, light_pink, true);
				RGBPrint(76 + (int)getwstring(language, L"save_name").size(), 16,game.name, black, white_pink);
			}
		}
	}
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
	//drawGameBoard(55, 6, 61, 31, black, white_pink);
	//StartGame(0);
}
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
//Xin hòa (Dùng 'o')
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
	drawMiniPopUp(69, 14, black, white_pink, white_pink, white_pink);
	RGBPrint(85 - sizeOfText(text_drawmsg)/2, 16, text_drawmsg, black, white_pink, true);
	RGBPrint(85 - sizeOfText(text_drawacp)/2, 18, text_drawacp, black, white_pink, true);
	RGBPrint(82 - sizeOfText(text_drawdeny)/2, 19, L">> " + text_drawdeny + L" <<", black, white_pink, true);
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
					RGBPrint(82 - sizeOfText(text_drawacp) / 2, 18, L">> " + text_drawacp + L" <<", black, white_pink, true);
					RGBPrint(82 - sizeOfText(text_drawdeny) / 2, 19, L"   " + text_drawdeny + L"   ", black, white_pink, true);
				}
				else {
					RGBPrint(82 - sizeOfText(text_drawacp) / 2, 18,L"   "+ text_drawacp + L"   ", black, white_pink, true);
					RGBPrint(82 - sizeOfText(text_drawdeny) / 2, 19, L">> " + text_drawdeny + L" <<", black, white_pink, true);
				}
			}
			if (n == 13) {
				playSound(9, 0);
				break;
			}
		}
	}
	if (draw) {
		drawGameBoard(55, 6, 61, 31, black, white_pink);
		drawDrawEffect();
		drawContinueOption(false);
	}
	else {
		drawGameBoard(55, 6, 61, 31, black, white_pink);
		return false;
	}
	return true;
}
//Xin dừng (Dùng 'p')
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
	drawMiniPopUp(69, 14, black, white_pink, white_pink, white_pink);
	RGBPrint(85 - sizeOfText(text_pausemsg) / 2, 16, text_pausemsg, black, white_pink, true);
	RGBPrint(82 - sizeOfText(text_pauseacp)/2, 18, L"   " + text_pauseacp + L"   ", black, white_pink, true);
	RGBPrint(82 - sizeOfText(text_pausedeny) / 2, 19, L">> " + text_pausedeny + L" <<", black, white_pink, true);
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
				pause = !pause;
				if (pause) {
					RGBPrint(82 - sizeOfText(text_pauseacp) / 2, 18, L">> " + text_pauseacp + L" <<", black, white_pink, true);
					RGBPrint(82 - sizeOfText(text_pausedeny) / 2, 19, L"   " + text_pausedeny + L"   ", black, white_pink, true);
				}
				else {
					RGBPrint(82 - sizeOfText(text_pauseacp) / 2, 18, L"   " + text_pauseacp + L"   ", black, white_pink, true);
					RGBPrint(82 - sizeOfText(text_pausedeny) / 2, 19, L">> " + text_pausedeny + L" <<", black, white_pink, true);
				}
			}
			if (n == 13) {
				playSound(9, 0);
				break;
			}
		}
	}
	//_getch();
	drawGameBoard(55, 6, 61, 31, black, white_pink);
	if (pause) {
		wstring text_continueMsg = getwstring(language, L"pause_continue");
		drawInGamePanel_1A(120, 4, black, white_pink, white, white_pink);
		RGBPrint(140 - sizeOfText(text_continueMsg)/2, 10, text_continueMsg, black, white_pink, true);
		drawPauseText(124, 5, white_pink);
		return true;
	}
	return false;
}
//Cập nhật màn hình
void fixKeyboard() {
	if (key_w) {
		key_w = !key_w;
		drawInGameKeyboard(124 + 13, 14 + 1, 'w', key_w, black, white_pink);
	}
	if (key_a) {
		key_a = !key_a;
		drawInGameKeyboard(124 + 3, 14 + 5, 'a', key_a, black, white_pink);
	}
	if (key_s) {
		key_s = !key_s;
		drawInGameKeyboard(124 + 13, 14 + 6, 's', key_s, black, white_pink);
	}
	if (key_d) {
		key_d = !key_d;
		drawInGameKeyboard(124 + 24, 14 + 5, 'd', key_d, black, white_pink);
	}
}
void updateScreen() {
	wstring
		ingame_ratio = getwstring(language, L"ingame_ratio"),
		ingame_time = getwstring(language, L"ingame_time"),
		ingame_hits = getwstring(language, L"ingame_hits");
	RGBPrint(16, 12, ingame_ratio, black, white_pink, true);
	RGBPrint(32-9, 13,
		wstring(L"[X]: ") + ((game.ratio[0] < 10) ? L"0" : L"") + to_wstring(game.ratio[0]) +
		wstring(L" | [O]: ") + ((game.ratio[1] < 10) ? wstring(L"0") : wstring(L"")) + to_wstring(game.ratio[1])
		, black, white_pink, false);

	RGBPrint(16, 15,
		ingame_time + L": " + wstring((game.time < 10) ? L"0" : L"") + to_wstring(game.time) + L"s",
		black, white_pink, true);

	RGBPrint(16, 17, ingame_hits + L":", black, white_pink, true);
	RGBPrint(32-9 , 18	,
		wstring(L"[X]: " + wstring((game.hits[0] < 10) ? L"0" : L"")) + to_wstring(game.hits[1]) +
		wstring(L" | [O]: ") + wstring((game.hits[1] < 10) ? L"0" : L"") + to_wstring(game.hits[0]),
		black, white_pink, false);
	bool c = !game.turn;
	for (int i = 0; i < game.history.size(); i++) {
		if (i == 5) break;
		string text = (c) ? "[X]" : "[O]";
		c = !c;
		RGBPrint(20, 25 + 2 * i, text, black, white_pink);
		RGBPrint(30, 25 + 2 * i,
			char(game.history[i].first) + string((game.history[i].second < 10) ? "0" : "") + to_string(game.history[i].second)
			, black, white_pink);
	}
}
void updateFullBoard() {
	for (int i = 0; i < BOARD_SIZE_HEIGHT; i++) {
		for (int j = 0; j < BOARD_SIZE_WIDTH; j++) {
			RGBPrint(game.point[i][j].x, game.point[i][j].y,
				(game.point[i][j].c  == 0 ? L" " : game.point[i][j].c  == 1 ? L"X" : L"O"),
				black, white_pink, false);
		}
	}
}
void drawTheScreen() {
	fill(white_pink);
	//background
	drawInGameHeader(3, 1);
	//match statistics
	drawInGamePanel_1(10, 10, black, white_pink, white, white_pink);
	//history
	drawInGamePanel_2(12, 22, black, white_pink, white, white_pink);
	//turn
	drawInGamePanel_3(125, 5, black, white_pink, white, white_pink);
	//

	drawSnowFlake(116, 18, white_pink);
	//keyboard
	drawInGamePanel_4(124, 14, black, white_pink, white, white_pink);
	drawInGameKeyboard(124 + 13, 14 + 1, 'w', key_w, black, white_pink);
	drawInGameKeyboard(124 + 3, 14 + 5, 'a', key_a, black, white_pink);
	drawInGameKeyboard(124 + 13, 14 + 6, 's', key_s, black, white_pink);
	drawInGameKeyboard(124 + 24, 14 + 5, 'd', key_d, black, white_pink);
	//keybinds
	drawInGamePanel_1(120, 27, black, white_pink, white, white_pink);

	RGBPrint(129, 30, getwstring(language, L"ingame_keybind_wasd"), black, white_pink, true);
	RGBPrint(129, 31, getwstring(language, L"ingame_keybind_p"), black, white_pink, true);
	RGBPrint(129, 32, getwstring(language, L"ingame_keybind_o"), black, white_pink, true);
	RGBPrint(129, 33, getwstring(language, L"ingame_keybind_l"), black, white_pink, true);
	RGBPrint(129, 34, getwstring(language, L"ingame_keybind_q"), black, white_pink, true);
	//
	drawReindeer(25, 3, white_pink);
	drawSnowFlake(48, 5, white_pink);
	drawPineTree(117, 23, white_pink, 1);
	//
	drawGameBoard(55, 6, 61, 31, black, white_pink);
	updateScreen();
}
void reRenderCursor(bool boldColor) {
	RGBPrint(game.point[game._Y][game._X].x, game.point[game._Y][game._X].y,
		(game.point[game._Y][game._X].c == 0 ? L" " : game.point[game._Y][game._X].c == 1 ? L"X" : L"O"),
		black, (boldColor ? light_pink : white_pink), false);
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
	drawTurn(game.turn, 125, 5, light_pink, pink, white_pink);
	return false;
}
//Xừ lí trò chơi
bool boardTick() {
	if (game.point[game._Y][game._X].c == 0) {
		playSound(11, 0);
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

		drawTurn(game.turn, 125, 5, light_pink, pink, white_pink);
		if (game.gamemode == 1) {
			if (botHitRandom()) return true;
		}
		return false;
	}
	return false;
}
bool inputProcessing(char c) {
	if (c == 'l') {
		saveGameScreen(true);
		drawGameBoard(55, 6, 61, 31, black, white_pink);
		StartGame(0);
		return false;
	}
	if (c == 'q') {
		if (enableSFX) playSound(3, 0);
		if (game.name.size() == 0) saveGameScreen(true);
		return true;
	}
	if (c == 'o') {
		if (DrawOption()) {/*
			removePanel(54, 5, 3);
			drawInGamePanel_3(125, 5, black, white_pink, white, white_pink);*/
		}
		if (enableBGM) {
			stopSound(8);
			playSound(7, 1);
		}
		updateFullBoard();
		reRenderCursor(true);
		return false;
	}
	if (c == 'p') {
		if (PauseOption()) {
			removePanel(120, 4, 2);
			drawInGamePanel_3(125, 5, black, white_pink, white, white_pink);
			drawTurn(game.turn, 125, 5, light_pink, pink, white_pink);
		}
		if (enableBGM) {
			stopSound(8);
			playSound(7, 1);
		}
		updateFullBoard();
		reRenderCursor(true);
		return false;
	}
	if (c == 13) {
		return boardTick();
	}
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
		drawInGameKeyboard(124 + 13, 14 + 1, 'w', key_w, black, white_pink);
		break;
	case 'a':
		game._X = (game._X == 0) ? game._X : game._X - 1;
		key_a = !key_a;
		drawInGameKeyboard(124 + 3, 14 + 5, 'a', key_a, black, white_pink);
		break;
	case 'd':
		game._X = (game._X == BOARD_SIZE_WIDTH - 1) ? game._X : game._X + 1;
		key_d = !key_d;
		drawInGameKeyboard(124 + 24, 14 + 5, 'd', key_d, black, white_pink);
		break;
	case 's':
		game._Y = (game._Y == BOARD_SIZE_HEIGHT - 1) ? game._Y : game._Y + 1;
		key_s = !key_s;
		drawInGameKeyboard(124 + 13, 14 + 6, 's', key_s, black, white_pink);
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
			drawTurn(game.turn, 125, 5, light_pink, pink, white_pink);
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
void StartGame(bool drawBackground) {
	int count = 0;
	if (enableBGM) {
		stopSound(4);
		playSound(7, 1);
	}
	//vẽ lại nền
	resetPosOnBoard();
	if (drawBackground) {
		system("cls");
		drawTheScreen();
		updateFullBoard();
		drawTurn(game.turn, 125, 5, light_pink, pink, white_pink);
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
	fill(white_pink);
	drawLOGO((172 - 73) / 2, 5);
	drawMainScreen(0);
	if (enableBGM) {
		stopSound(7);
		playSound(4, 1);
	}
	GameScreen(0);
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
			if ((n >= 'A' && n <= 'Z') || (n >= 'a' && n <= 'z') || (n >= '0' && n <= '9') || n == '_') {//write
				if (newname.size() < 12) {
					newname.push_back(n);
					RGBPrint(x, y, L"            ", text_color, background_color, false);
					RGBPrint(x-3, y, L"✍  ", text_color, selected_color, false);
					RGBPrint(x + 0, y, getwstring(language, L"save_name") + L":", text_color, selected_color, true);
					RGBPrint(x +2 + (int)getwstring(language, L"save_name").size(), y, wstring_convert<codecvt_utf8<wchar_t>>().from_bytes(newname) + L" ", text_color, background_color, false);
				}
			}
			if (n == 8) {//delete
				if (newname.size() > 0) {
					newname.pop_back();
					RGBPrint(x, y, L"            ", text_color, background_color, false);
					RGBPrint(x-3, y, L"✍  ", text_color, selected_color, false);
					RGBPrint(x + 0, y, getwstring(language, L"save_name") + L":", text_color, selected_color, true);
					RGBPrint(x + 2 + (int)getwstring(language, L"save_name").size(), y, wstring_convert<codecvt_utf8<wchar_t>>().from_bytes(newname) + L" ", text_color, background_color, false);
				}
			}
			if (fileExists(newname) && newname != game.name) {
				RGBPrint(x + 8, y - 1, getwstring(language, L"save_exists"), { 255,0,0 }, background_color, true);
			}
			else {
				RGBPrint(x + 8, y - 1, L"              ", { 255,0,0 }, background_color, false);
				if (n == 13) {
					if (newname.size() == 0) {
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
				if (n == 27) {
					newname = game.name;
					RGBPrint(x + 2 + (int)getwstring(language, L"save_name").size(), y, L"            ", text_color, background_color, false);
					break;
				}
			}
			GotoXY(x + 2 + (int)getwstring(language, L"save_name").size() + (int)newname.size(), y);
		}
	}
	/*
	RGBPrint(x-3, y, L"✍      :", text_color, selected_color, false);
	RGBPrint(x + 0, y, getwstring(language, L"save_name"), text_color, selected_color, true);
	RGBPrint(x + 2 + (int)getwstring(language, L"save_name").size(), y, wstring_convert<codecvt_utf8<wchar_t>>().from_bytes(newname) + L" ", text_color, background_color, false);
	*/
	ShowConsoleCursor(false);
	return newname;
}
void gameEditor_remove(string savename) {
	int second_to_remove = 7000;
	wstring _message = getwstring(language, L"save_remove_countdown"), message;
	int index = 0;
	for (int i = 0; i < _message.size(); i++) if (_message[i] == '%') {
		index = i;
		message = _message.substr(0, index) + to_wstring(second_to_remove/1000) + _message.substr(index + 2);
		break;
	}
	RGBPrint(118 - sizeOfText(message) / 2, 33, message, black, light_pink, true);
	while (true) {
		if (_kbhit()) {
			_getch();
			GotoXY(118 - sizeOfText(message) / 2, 33);
			for (int i = 0; i < sizeOfText(message); i++) cout << " ";
			break;
		}
		message = _message.substr(0, index) + to_wstring(second_to_remove/1000) + _message.substr(index + 2);
		RGBPrint(118-sizeOfText(message)/2, 33, message, black, light_pink, true);
		second_to_remove -= 50;
		Sleep(50);
		if (second_to_remove <= 0) {
			try {
				fs::remove("./Saves/" + savename + ".txt");
			}
			catch (const fs::filesystem_error& e) {
				std::cerr << "Error: " << e.what() << std::endl;
			}
			break;
		}
	}
	if (second_to_remove <= 0) GameScreen(2);
	else loadSaveGameEditor(savename, false, 2);

}
void loadSaveGameEditor(string savename, bool refresh, int curSel) {
	loadGame(savename);
	int x = 100, y = 25;
	int n, prevSel = 0;
	wstring
		text_save_editor = getwstring(language, L"save_editor"),
		text_save_load = getwstring(language, L"save_load"),
		text_save_remove = getwstring(language, L"save_remove"),
		text_save_back = getwstring(language, L"save_back");
	if (refresh) {
		removePanel(90, 18, 13);
		drawPanel(90, 18, 11);
		RGBPrint(118-sizeOfText(text_save_editor)/2, 21, text_save_editor, black, light_pink, true);
	}
	RGBPrint(118-sizeOfText(text_save_load)/2, y - 2, text_save_load, black, (curSel==0) ? pink : light_pink, true);
	RGBPrint(x-3, y, L"✍  ", black, (curSel == 1) ? pink : light_pink, false);
	RGBPrint(x, y, getwstring(language, L"ingame_name") + L":", black, (curSel == 1) ? pink : light_pink, true);
	RGBPrint(x+2+ getwstring(language, L"ingame_name").size(), y, wstring_convert<codecvt_utf8<wchar_t>>().from_bytes(savename), black, light_pink, true);
	RGBPrint(x, y+1, getwstring(language, L"ingame_turn") + wstring(L": ") + wstring((game.turn) ? L"[X]" : L"[O]"), black, light_pink, true);
	RGBPrint(x, y+2, getwstring(language, L"ingame_timeleft") + wstring(L": ") + wstring((game.time < 10) ? L"0" : L"") + to_wstring(game.time) + L"s", black, light_pink, true);
	RGBPrint(x, y+3, getwstring(language, L"ingame_ratio") + wstring(L": ") + wstring(L"[X]: ") + ((game.ratio[0] < 10) ? L"0" : L"") + to_wstring(game.ratio[0]) + wstring(L" | [O]: ") + wstring((game.ratio[1] < 0) ? L"0" : L"") + to_wstring(game.ratio[1]), black, light_pink, true);
	RGBPrint(x, y+4, getwstring(language, L"ingame_hits") + wstring(L": [X]: ") + wstring((game.hits[0] < 10) ? L"0" : L"") + to_wstring(game.hits[0]) + wstring(L" | [O]: ") + wstring((game.hits[1] < 10) ? L"0" : L"") + to_wstring(game.hits[1]), black, light_pink, true);
	RGBPrint(118-sizeOfText(text_save_remove)/2, y + 6, text_save_remove, black, (curSel == 2) ? pink : light_pink, true);
	RGBPrint(118-sizeOfText(text_save_back)/2, y + 8, text_save_back, black, (curSel == 3) ? pink : light_pink, true);
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
					RGBPrint(118 - sizeOfText(text_save_load) / 2, y - 2, text_save_load, black, light_pink, true);
					break;
				case 1:
					RGBPrint(x-3, y, L"✍  ", black, light_pink, false);
					RGBPrint(x, y, getwstring(language, L"ingame_name") + L":", black, light_pink, true);
					break;
				case 2:
					RGBPrint(118 - sizeOfText(text_save_remove)/2, y + 6, text_save_remove, black, light_pink, true);
					break;
				case 3:
					RGBPrint(118 - sizeOfText(text_save_back) / 2, y + 8, text_save_back, black, light_pink, true);
					break;
				}
				switch (curSel) {
				case 0:
					RGBPrint(118 - sizeOfText(text_save_load) / 2, y - 2, text_save_load, black, pink, true);
					break;
				case 1:
					RGBPrint(x-3, y, L"✍  ", black, pink, false);
					RGBPrint(x, y, getwstring(language, L"ingame_name") + L":", black, pink, true);
					break;
				case 2:
					RGBPrint(118 - sizeOfText(text_save_remove)/2, y + 6, text_save_remove, black, pink, true);
					break;
				case 3:
					RGBPrint(118 - sizeOfText(text_save_back) / 2, y + 8, text_save_back, black, pink, true);
					break;
				}
			}
		}
	}	
	switch (curSel) {
	case 0:
		loadGame(savename);
		if (enableSFX) playSound(6, 0);
		StartGame(1);
		break;
	case 1: {
		string oldname = game.name;
		game.name = gameEditor_name(x, y, black, light_pink, pink);
		try {
			fs::rename("./Saves/" + oldname + ".txt", "./Saves/" + game.name + ".txt");
		}
		catch (const fs::filesystem_error& e) {
			std::cerr << "Error: " << e.what() << std::endl;
		}
		loadSaveGameEditor(game.name, false, curSel);
		break;
	}
	case 2:
		gameEditor_remove(savename);
		break;
	case 3:
		removePanel(90, 18, 11);
		if (enableSFX) playSound(9, 0);
		GameScreen(2);
		break;
	}
}

void newGameOptionsScreen() {
	drawPanel(90, 18, 5);

	wstring options[3] = { getwstring(language, L"play_newgame"), getwstring(language, L"play_loadgame"), getwstring(language, L"back_to_main") };
	int curSel = 0, prevSel = 0;
	int n, size = sizeof(options) / sizeof(wstring);
	for (int i = 0; i < size; i++) {
		if (i == 0) RGBPrint(115 - sizeOfText(options[i])/2, 21 + 2 * i, L">> " + options[i] + L" <<", black, light_pink, true);
		else RGBPrint(115 - sizeOfText(options[i]) / 2, 21 + 2 * i, L"   " + options[i] + L"   ", black, light_pink, true);
	}
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
			RGBPrint(115 - sizeOfText(options[prevSel]) / 2, 21 + 2 * prevSel, L"   " + options[prevSel] + L"   ", black, light_pink, true);
			RGBPrint(115 - sizeOfText(options[curSel]) / 2, 21 + 2 * curSel, L">> " + options[curSel] + L" <<", black, light_pink, true);
		}
	}
	switch (curSel) {
	case 0: {//new game menu
		GameScreen(1);
		break;
	}
	case 1: //load game menu
		GameScreen(2);
		break;
	case 2://back
		removePanel(90, 18, 5);
		MainScreen(0, 0, false);
		break;
	}
}
void selectModeScreen() {
	wstring options[3] = { getwstring(language, L"play_pvp"),getwstring(language, L"play_pve"), getwstring(language, L"play_back") };
	int curSel = 0, prevSel = 0;
	int n, size = sizeof(options) / sizeof(wstring);
	removePanel(90, 18, 5);
	drawPanel(90, 18, 4);
	for (int i = 0; i < size; i++) {
		if (i == 0) RGBPrint(115 - sizeOfText(options[i]) / 2, 21 + 2 * i, L">> " + options[i] + L" <<", black, light_pink, true);
		else RGBPrint(115 - sizeOfText(options[i]) / 2, 21 + 2 * i, L"   " + options[i] + L"   ", black, light_pink, true);
	}
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
			RGBPrint(115 - sizeOfText(options[prevSel]) / 2, 21 + 2 * prevSel, L"   " + options[prevSel] + L"   ", black, light_pink, true);
			RGBPrint(115 - sizeOfText(options[curSel]) / 2, 21 + 2 * curSel, L">> " + options[curSel] + L" <<", black, light_pink, true);
		}
	}
	switch (curSel) {
	case 0: {//start new game (PVP)
		short a[2] = { 0 };
		resetBoard();
		setupGame("",7,5, 1, 0, 15, a, a, {});
		StartGame(1);
		break;
	}
	case 1: {//start new game (PVE)
		short a[2] = { 0 };
		resetBoard();
		setupGame("", 7,5,1, 1, 15, a, a, {});
		StartGame(1);
		break;
	}
	case 2:
		removePanel(90, 18, 4);
		GameScreen(0);
		break;
	}
}
void loadGameScreen() {
	//lay thong tin tu folder
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
	//ve
	wstring text_name = getwstring(language, L"save_name"),
			text_back = getwstring(language, L"play_back");
	removePanel(90, 18, 5);
	drawPanel(90, 18, 13);
	RGBPrint(x, y-1, L"      ║                                    ", black, light_pink, false);
	RGBPrint(x, y, L"══════╬════════════════════════════════════", black, light_pink, false);
	int _i = 0;
	for (int i = 0; i < 2 * 5; i++) {
		if (i % 2 == 0) {
			RGBPrint(x, y + i + 1, L"      ║                                    ", black, light_pink, false);
			if (_i < saves_names.size() && _i <= maxindex - 1) {
				RGBPrint(x + 2, y + i + 1, string((_i + 1 < 10) ? "0" : "") + to_string(_i + 1), black, light_pink);
				RGBPrint(x + 7 + (14 - (int)saves_names[_i].size() / 2), y + i + 1, saves_names[_i], black, light_pink);
				_i++;
			}
		}
		else RGBPrint(x, y + i + 1, L"══════╬════════════════════════════════════", black, light_pink, false);
	}
	RGBPrint(x, y+10, L"══════╩════════════════════════════════════", black, light_pink, false);
	RGBPrint(x, y + 11, L"                                           ", black, light_pink, false);
	RGBPrint(x + 1, y + 11, L"<<", black, light_pink, false);
	RGBPrint(x + 18, y + 11, L"01/" + wstring((saves / 5 < 10) ? L"0" : L"") + to_wstring(maxpages), black, light_pink, false);
	RGBPrint(x + 38, y + 11, L">>", black, light_pink, false);

	RGBPrint(x, y + 12, L"═══════════════════════════════════════════", black, light_pink, false);
	RGBPrint(115 - sizeOfText(text_back)/2, y + 13, L"   " + text_back + L"   ", black, light_pink, true);
	//
	if (saves_names.size() >= 1) {
		RGBPrint(x + 2, y + 2 * index + 1, string((index + 1 < 10) ? "0" : "") + to_string(index + 1), black, pink);
		RGBPrint(x + 7 + (14 - (int)saves_names[index].size() / 2), y + 2 * index + 1, saves_names[index], black, pink);
	}
	int n;
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
					RGBPrint(x + 2, y + 2 * previousSelect + 1, string((previousSelect + 1 + d < 10) ? "0" : "") + to_string(previousSelect + d + 1), black, light_pink);
					RGBPrint(x + 7 + (14 - (int)saves_names[previousSelect + d].size() / 2), y + 2 * previousSelect + 1, saves_names[previousSelect + d], black, light_pink);
				}
				else RGBPrint(115 - sizeOfText(text_back) / 2, y + 13, L"   " + text_back + L"   ", black, light_pink, true);

				if (index < maxindex) {
					RGBPrint(x + 2, y + 2 * index + 1, string((index + d + 1 < 10) ? "0" : "") + to_string(index + d + 1), black, pink);
					RGBPrint(x + 7 + (14 - (int)saves_names[index + d].size() / 2), y + 2 * index + 1, saves_names[index + d], black, pink);
				}
				else RGBPrint(115 - sizeOfText(text_back) / 2, y + 13, L">> " + text_back + L" <<", black, light_pink, true);
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
						RGBPrint(x, y + i + 1, L"      ║                                    ", black, light_pink, false);
						if (_i < saves_names.size()) {
							if (_i <= maxindex + 5 * (currentpage - 1)) {
								RGBPrint(x + 7 + (14 - (int)saves_names[_i].size() / 2), y + i + 1, saves_names[_i], black, light_pink);
								RGBPrint(x + 2, y + i + 1, string((_i + 1 < 10) ? "0" : "") + to_string(_i + 1), black, light_pink);
								_i++;
							}
						}
					}
					else RGBPrint(x, y + i + 1, L"══════╬════════════════════════════════════", black, light_pink, false);
				}
				RGBPrint(x + 18, y + 11, wstring((currentpage < 10) ? L"0" : L"") + to_wstring(currentpage) + L"/" + wstring((saves / 5 < 10) ? L"0" : L"") + to_wstring(maxpages), black, light_pink, false);

				_i = 5 * (currentpage - 1);
				RGBPrint(x + 7 + (14 - (int)saves_names[_i].size() / 2), y + 1, saves_names[_i], black, pink);
				RGBPrint(x + 2, y + 1, string((_i + 1 < 10) ? "0" : "") + to_string(_i + 1), black, pink);
			}
		}
	}
	if (enableSFX) playSound(9, 0);
	if (index < maxindex) {
		loadSaveGameEditor(saves_names[index + 5 * (currentpage - 1)], true, 0);
	}
	else {
		removePanel(90, 18, 13);
		GameScreen(0);
	}
}
void GameScreen(int state) {//0: game menu, 1:new game menu, 2: load game menu
	if (state == 0) {//new/load game options
		newGameOptionsScreen();
	}
	else if (state == 1) {//select mode
		selectModeScreen();
	}
	else if (state == 2) {//load game screen
		loadGameScreen();
	}
}

