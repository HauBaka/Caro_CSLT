#include "GameScreen.h"

GAME game;
bool key_w = false, key_a = false, key_s = false, key_d = false;
bool rowCheck(int value, int i, int j) {
	int count = 0;
	while (i < game.board_heigh && j < game.board_width) {
		if (game.board[i][j] == value) count++;
		else return count >= 5;
		j++;
	}
	return count >= 5;
}
bool colCheck(int value, int i, int j) {
	int count = 0;
	while (i < game.board_heigh) {
		if (game.board[i][j]==value) count++;
		else return count >= 5;
		i++;
	}
	return count >= 5;
}
bool leftDiagonalCheck(int value, int i, int j) {
	int count = 0;
	while (i < game.board_heigh && j < game.board_width) {
		if (game.board[i][j] == value) count++;
		else return count >= 5;
		i++;
		j++;
	}
	return count >= 5;
}
bool rightDiagonalCheck(int value, int i, int j) {
	int count = 0;
	while (i < game.board_heigh && j >= 0) {
		if (game.board[i][j] == value) count++;
		else return count >= 5;
		i++;
		j--;
	}
	return count >= 5;
}
bool checkWin(int value, int& xpos, int& ypos) {//0=None,1=X,2=O
	for (int i = 0; i < game.board_heigh; i++) {
		for (int j = 0; j < game.board_width; j++) {
			if (rowCheck(value, i, j) || colCheck(value, i, j) || 
				leftDiagonalCheck(value, i, j) || rightDiagonalCheck(value, i, j)) {
				xpos = j;
				ypos = i;
				return 1;
			}
		}
	}
	return 0;
}

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
	FILE* savef;
	fopen_s(&savef, ("./Saves/" + filename + ".txt").c_str(), "r");
	if (loadConfiguration(savef)) {
		wstring text;
		game = {};
		game.name = filename;
		game.board_heigh = 10; game.board_width = 15;
	   //load time & turn
		game.time = getInt(savef, L"time-left");
		game.turn = getInt(savef, L"turn");
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
		game.board  = vector<vector<int>>(game.board_heigh, vector<int>(game.board_width));
		for (int i = 0; i < game.board_heigh; i++) {
			text = getwstring(savef, (wstring(L"board-line-") + ((i < 9) ? L"0" : L"") + to_wstring(i + 1)));
			for (int j = 0; j < game.board_width; j++) {
				game.board[i][j] = stoi(text.substr(2*j,1));
			}
		}
		fclose(savef);
		return 1;
	}
	fclose(savef);
	return 0;
}
bool saveGame() {
	if (fileExists(game.name)) return 0;
	FILE* savef;
	fopen_s(&savef, ("./Saves/" + game.name + ".txt").c_str(), "w");

	fprintf_s(savef, ("time-left: " + to_string(game.time) + "\n").c_str());
	fprintf_s(savef, (game.turn == 1) ? "turn: 1\n" : "turn: 0\n");
	fprintf_s(savef, ("ratio: "+to_string(game.ratio[0]) + " " + to_string(game.ratio[1]) + "\n").c_str());
	fprintf_s(savef, ("hits: " +to_string(game.hits[0]) + " " + to_string(game.hits[1]) + "\n").c_str());
	for (int i = 0; i < 5; i++) {
		fprintf_s(savef, ("history-" + to_string(i + 1) + ": ").c_str());
		fprintf_s(savef, (i < game.history.size()) ?
			(to_string(game.history[i].first) + to_string(game.history[i].second) + "\n").c_str() :
			((string)"No data\n").c_str());
	}
	for (int i = 0; i < game.board_heigh; i++) {
		fprintf(savef, (string("board-line-") + ((i < 9) ? "0" : "") + to_string(i+1) + ": ").c_str());
		for (int j = 0; j < game.board_width; j++) {
			fprintf_s(savef, (to_string(game.board[i][j]) + " ").c_str());
		}
		fprintf_s(savef, "\n");
	}
	fclose(savef);
	return 1;
}
void saveGameScreen(bool refresh) {
	if (refresh) drawSavingGamePanel(69, 22, black, white_pink, white_pink, white_pink);
	RGBPrint(71, 24, L"✍  ", black, light_pink, false);
	RGBPrint(74, 24, getwstring(language, L"save_name")+L":", black, light_pink, true);
	RGBPrint(76+(int) getwstring(language, L"save_name").size(), 24, wstring_convert<codecvt_utf8<wchar_t>>().from_bytes(game.name), black, white_pink, false);
	RGBPrint(90, 26, getwstring(language, L"save_save"), black, white_pink, true);
	RGBPrint(75, 26, getwstring(language, L"save_cancel"), black, white_pink, true);
	bool isEditing = false;
	string oldname = game.name;
	int currentSelect = 0, previousSelect = 0;
	while (true) {
		if (_kbhit()) {
			int n = tolower(_getch());
			if ((n == 13 || n == 'w' || n == 'a' || n == 's' || n == 'd') && enableSFX) playSound(3, 0);

			previousSelect = currentSelect;
			if (n == 'w' || n == 'a') {
				currentSelect = (currentSelect == 0) ? 2 : currentSelect - 1;
			}
			if (n == 's' || n == 'd') {
				currentSelect = (currentSelect == 2) ? 0 : currentSelect + 1;
			}
			if (currentSelect != previousSelect) {
				switch (previousSelect) {
				case 0:
					RGBPrint(71, 24, L"✍  ", black, white_pink, false);
					RGBPrint(74, 24, getwstring(language, L"save_name")+L": " + wstring_convert<codecvt_utf8<wchar_t>>().from_bytes(game.name), black, white_pink, true);
					break;
				case 1:
					RGBPrint(75, 26, getwstring(language, L"save_cancel"), black, white_pink, true);
					break;
				case 2:
					RGBPrint(90, 26, getwstring(language, L"save_save"), black, white_pink, true);
					break;
				}
				switch (currentSelect) {
				case 0:
					RGBPrint(71, 24, L"✍  ", black, light_pink, false);
					RGBPrint(74, 24, getwstring(language, L"save_name")+L":", black, light_pink, true);
					break;
				case 1:
					RGBPrint(75, 26, getwstring(language, L"save_cancel"), black, light_pink, true);
					break;
				case 2:
					RGBPrint(90, 26, getwstring(language, L"save_save"), black, light_pink, true);
					break;
				}
			}
			if (n == 13) {
				if (currentSelect != 0) break;
				game.name = gameEditor_name(71, 24, black, white_pink, light_pink);
			}
		}
	}
	switch (currentSelect) {
	case 1:
		game.name = oldname;
		break;
	case 2:
		if (game.name != oldname)  {
			try {
				fs::rename("./Saves/" + oldname + ".txt", "./Saves/" + game.name + ".txt");
			}
			catch (const fs::filesystem_error) {
				saveGame();
			}
		}
	}
	drawGameBoard(55, 16, 61, 21, black, white_pink);
	for (int i = 0; i < game.board_heigh; i++)
		for (int j = 0; j < game.board_width; j++) RGBPrint(55 + 2 + j * 4, 16 + 2 * i + 1, (game.board[i][j] == 0 ? L" " : game.board[i][j] == 1 ? L"X" : L"O"), black, white_pink, false);
	StartGame(0);
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

void fixKeyboard() {
	if (key_w) {
		key_w = !key_w;
		drawInGameKeyboard(123 + 13, 10 + 1, 'w', key_w, black, white_pink);
	}
	if (key_a) {
		key_a = !key_a;
		drawInGameKeyboard(123 + 3, 10 + 5, 'a', key_a, black, white_pink);
	}
	if (key_s) {
		key_s = !key_s;
		drawInGameKeyboard(123 + 13, 10 + 6, 's', key_s, black, white_pink);
	}
	if (key_d) {
		key_d = !key_d;
		drawInGameKeyboard(123 + 24, 10 + 5, 'd', key_d, black, white_pink);
	}
}
void updateScreen() {
	RGBPrint(16, 12, getwstring(language, L"ingame_ratio"), black, white_pink, true);
	RGBPrint(22, 13, 
		wstring(L"[X]: ") + ((game.ratio[0] < 10) ? L"0" : L"") + to_wstring(game.ratio[0]) + 
		wstring(L" | [O]: ") + ((game.ratio[1] < 0) ? wstring(L"0") : wstring(L"")) + to_wstring(game.ratio[1])
		, black, white_pink, false);
	
	RGBPrint(16, 15,
		getwstring(language, L"ingame_time") + L": " + wstring((game.time < 10) ? L"0" : L"") + to_wstring(game.time) + L"s", 
		black, white_pink, true);
	
	RGBPrint(16, 17,getwstring(language, L"ingame_hits")+ L":", black, white_pink, true);
	RGBPrint(16 + (int)getwstring(language, L"ingame_hits").size(), 17,
		wstring(L"[X]: " + wstring((game.hits[0] < 10) ? L"0" : L"")) + to_wstring(game.hits[0]) + 
		wstring(L" | [O]: ") + wstring((game.hits[1] < 10) ? L"0" : L"") + to_wstring(game.hits[1]), 
		black, white_pink, false);
	bool c = !game.turn;
	for (int i = 0; i < game.history.size(); i++) {
		if (i == 5) break;
		string text = (c) ? "[X]" : "[O]";
		c = !c;
		RGBPrint(20, 25 + 2 * i, text, black, white_pink);
		RGBPrint(30, 25 + 2 * i, 
			char(game.history[i].first) +string((game.history[i].second < 10) ? "0":"") + to_string(game.history[i].second)
			, black, white_pink);
	}
}
void drawTheScreen() {
	fill(white_pink);
	drawInGameHeader(3, 1);
	//match statistics
	drawInGamePanel_1(10,10, black, white_pink, white, white_pink);
	//history
	drawInGamePanel_2(12, 22, black, white_pink, white, white_pink);
	//turn
	drawInGamePanel_3(69, 6, black, white_pink, white, white_pink);
	//keyboard
	drawInGamePanel_4(123, 10, black, white_pink, white, white_pink);
	drawInGameKeyboard(123 + 13, 10 + 1, 'w', key_w, black, white_pink);
	drawInGameKeyboard(123 + 3, 10 + 5, 'a', key_a, black, white_pink);
	drawInGameKeyboard(123 + 13, 10 + 6, 's', key_s, black, white_pink);
	drawInGameKeyboard(123 + 24, 10 + 5, 'd', key_d, black, white_pink);
	//
	drawGameBoard(55, 16, 61, 21, black, white_pink);
	updateScreen();
}

void StartGame(bool drawBackground) {
	int loc_x = 7, loc_y = 5;//[0,14] -> ứng với đồ thị Oxy
	int length = 61, width = 21;//10x15 cells
	int x = 55, y = 16, count = 0;
	if (drawBackground) {
		system("cls");
		drawTheScreen();
		//nếu game đc nạp lại thì load cả board
		for (int i = 0; i < game.board_heigh; i++)
			for (int j = 0; j < game.board_width; j++) RGBPrint(x + 2 + j * 4, y + 2 * i + 1, (game.board[i][j] == 0 ? L" " : game.board[i][j] == 1 ? L"X" : L"O"), black, white_pink, false);
		drawTurn(game.turn, 69, 6, light_pink, pink, white_pink);
	}
	RGBPrint(x + 2 + loc_x * 4, y + 2 * loc_y + 1, (game.board[loc_y][loc_x] == 0 ? L" " : game.board[loc_y][loc_x] == 1 ? L"X" : L"O"), black, light_pink, false);
	bool check = false;
	while (true) {
		if (_kbhit()) {
			int n = _getch();
			char c = (char)tolower(n);
			if (c == 'q') {
				if (enableSFX) playSound(3, 0);
				break;
			}
			if (c == 'l') {
				saveGameScreen(true);
				break;
			}
			if (n == 13) {
				if (enableSFX) playSound(3, 0);
				if (check) continue;
				if (game.board[loc_y][loc_x] == 0) {
					game.history.insert(game.history.begin(), {65+loc_y, loc_x+1});
					game.board[loc_y][loc_x] = game.turn ? 1 : 2;
					RGBPrint(x + 2 + loc_x * 4, y + 2 * loc_y + 1, (game.board[loc_y][loc_x] == 0 ? L" " : game.board[loc_y][loc_x] == 1 ? L"X":L"O"), black, light_pink, false);
					int x, y;//???????????????????????
					if (game.turn) check = checkWin(1, x, y);
					else  check = checkWin(2, x, y);

					if (check) {
						if (game.turn) {
							RGBPrint(80, 15, "X WONNNNNNNNNN", {255,0,0}, white_pink);
							game.ratio[0]++;
							game.hits[0]++;
						}
						else {
							RGBPrint(80, 15, "O WONNNNNNNNNN", { 255,0,0 }, white_pink);
							game.ratio[1]++;
							game.hits[1]++;
						}
					}
					else {
						if (game.time >= 0) {
							game.time = 15;
							count = 0;
							if (game.turn) game.hits[0]++;
							else game.hits[1]++;
							game.turn = !game.turn;
							drawTurn(game.turn, 69, 6, light_pink, pink, white_pink);
						}
					}
				}
			}
			else if (c == 'w' or c == 'a' or c == 's' or c == 'd') {
				if (enableSFX) playSound(3, 0);
				RGBPrint(x + 2 + loc_x * 4, y + 2 * loc_y + 1, 
					(game.board[loc_y][loc_x] == 0 ? L" " : game.board[loc_y][loc_x] == 1 ? L"X":L"O"), 
					black, white_pink, false);
				switch (c) {
				case 'w':
					loc_y = (loc_y == 0) ? loc_y : loc_y - 1;
					key_w = !key_w;
					drawInGameKeyboard(123 + 13, 10 + 1, 'w', key_w, black, white_pink);
					break;
				case 'a':
					loc_x = (loc_x == 0) ? loc_x : loc_x - 1;
					key_a = !key_a;
					drawInGameKeyboard(123 + 3, 10 + 5, 'a', key_a, black, white_pink);
					break;
				case 'd':
					loc_x = (loc_x == game.board_width - 1) ? loc_x : loc_x + 1;
					key_d = !key_d;
					drawInGameKeyboard(123 + 24, 10 + 5, 'd', key_d, black, white_pink);
					break;
				case 's':
					loc_y = (loc_y == game.board_heigh - 1) ? loc_y : loc_y + 1;
					key_s = !key_s;
					drawInGameKeyboard(123 + 13, 10 + 6, 's', key_s, black, white_pink);
					break;
				}
				RGBPrint(x + 2 + loc_x * 4, y + 2 * loc_y + 1, 
					(game.board[loc_y][loc_x] == 0 ? L" " : (game.board[loc_y][loc_x] == 1 ? L"X":L"O")), 
					black, light_pink, false);
			}
		};
		Sleep(50);
		count += 50;
		if (count >= 1000) {
			game.time -= 1;
			if (game.time <= 0) {
				game.time = 0;
				check = true;
				game.turn = !game.turn;
				if (game.turn)  RGBPrint(80, 15, "X WONNNNNNNNNN", { 255,0,0 }, white_pink);
				else RGBPrint(80, 15, "O WONNNNNNNNNN", { 255,0,0 }, white_pink);
		
			}
			count = 0;
		}
		updateScreen();
		fixKeyboard();
	}
	system("cls");
	fill(white_pink);
	drawLOGO((172 - 73) / 2, 5);
	drawMainMenu_Play(10, 20);
	drawMainMenu_Options(10, 25);
	drawMainMenu_Authors(10, 30);
	drawMainMenu_Out(10, 35);
	drawTriagle(55, 20 + 0 * 5, true);
	GameScreen(0);
}
void setupGame(string name,bool turn, short time, short ratio[2], short hits[2], vector<pair<short, short>> history, vector<vector<int>> board) {
	game.name = name;
	game.turn = turn;
	game.time = time;
	game.ratio[0] = ratio[0]; game.ratio[1] = ratio[1];
	game.hits[0] = hits[0]; game.hits[1] = hits[1];
	game.history = history;
	game.board = board;
	game.board_heigh = 10; game.board_width = 15;
}

string gameEditor_name(int x, int y, RGB text_color, RGB background_color, RGB selected_color) {//default: x=112, y=27
	ShowConsoleCursor(true);
	string newname = game.name;
	GotoXY(x  + 2 + (int)getwstring(language, L"save_name").size() + (int)game.name.size(), y);//fix here
	int n;
	while (true) {///8: delete, 13: enter, 27: escape
		if (_kbhit()) {
			n = _getch();
			if ((n >= 'A' && n <= 'Z') || (n>='a' && n<='z') || (n>='0' && n<='9') ||n=='_') {//write
				if (newname.size() < 12) {
					newname.push_back(n);
					RGBPrint(x, y, L"                             ", text_color, background_color, false);
					RGBPrint(x, y, L"✍  ", text_color, selected_color, false);
					RGBPrint(x+3, y, getwstring(language, L"save_name")+L":", text_color, selected_color, true);
					RGBPrint(x+2+ (int)getwstring(language, L"save_name").size(), y, wstring_convert<codecvt_utf8<wchar_t>>().from_bytes(newname) + L" ", text_color, background_color, false);
				}
			}
			if (n == 8) {//delete
				if (newname.size() > 0) {
					newname.pop_back();
					RGBPrint(x, y, L"                             ", text_color, background_color, false);
					RGBPrint(x, y, L"✍  ", text_color, selected_color, false);
					RGBPrint(x + 3, y, getwstring(language, L"save_name")+L":", text_color, selected_color, true);
					RGBPrint(x + 2 + (int)getwstring(language, L"save_name").size(), y, wstring_convert<codecvt_utf8<wchar_t>>().from_bytes(newname) + L" ", text_color, background_color, false);
				}
			}
			if (fileExists(newname) && newname != game.name) {
				RGBPrint(x+8, y-1, getwstring(language, L"save_exists"), {255,0,0}, background_color, true);
			}
			else {
				RGBPrint(x+8, y-1, L"             ", { 255,0,0 }, background_color, false);
				if (n == 13 || n == 27) {
					if (n == 13) {
						if (newname.size() == 0) {
							RGBPrint(x+8, y-1, getwstring(language, L"save_invalidName"), {255,0,0}, background_color, true);
							gameEditor_name(x, y, text_color, background_color, selected_color);
						}
					}
					else {
						newname = game.name;
						RGBPrint(x, y, L"✍  ", text_color, selected_color, false);
						RGBPrint(x+3, y, getwstring(language, L"save_name")+L":", text_color, selected_color, true);

						RGBPrint(x + 2 + (int)getwstring(language, L"save_name").size(), y, L"            ", text_color, background_color, false);
						RGBPrint(x + 2 + (int)getwstring(language, L"save_name").size(), y, wstring_convert<codecvt_utf8<wchar_t>>().from_bytes(newname) + L" ", text_color, background_color, false);
					}
					break;
				}
			}
			GotoXY(x+2 + (int)getwstring(language, L"save_name").size() + (int)newname.size(), y);
		}
	}
	RGBPrint(x, y, L"✍      :", text_color, selected_color, false);
	RGBPrint(x + 3, y, getwstring(language, L"save_name"), text_color, selected_color, true);
	RGBPrint(x + 2 + (int)getwstring(language, L"save_name").size(), y, wstring_convert<codecvt_utf8<wchar_t>>().from_bytes(newname) + L" ", text_color, background_color, false);
	ShowConsoleCursor(false);
	return newname;
}
void gameEditor_remove(string savename) {
	int second_to_remove = 7;
	wstring _message = getwstring(language, L"save_remove_countdown"), message;
	int index = 0;
	for (int i = 0; i < _message.size(); i++) if (_message[i] == '%') {
		index = i;
		message = _message.substr(0, index) + to_wstring(second_to_remove) + _message.substr(index + 2);
		break;
	}
	RGBPrint(123 - 15, 33, message, black, light_pink, true);
	while (true) {
		if (_kbhit()) {
			_getch();
			break;
		}
		message = _message.substr(0, index) + to_wstring(second_to_remove) + _message.substr(index + 2);
		RGBPrint(123 - 15, 33,message, black, light_pink, true);
		second_to_remove -= 1;
		Sleep(1000);
		if (second_to_remove <= 0) {
			try {
				fs::remove("./Saves/" + savename + ".txt");
			} catch (const fs::filesystem_error& e) {
				std::cerr << "Error: " << e.what() << std::endl;
			}
			break;
		}
	}
	GameScreen(2);
}
void loadSaveGameEditor(string savename, bool refresh) {
	loadGame(savename);
	if (refresh) {
		removePanel(100, 20, 13);
		drawPanel(100, 20, 11);
		RGBPrint(120, 23, getwstring(language, L"save_editor"), black, light_pink, true);
	}
	RGBPrint(123, 25, getwstring(language, L"save_load"), black, pink, true);
	RGBPrint(112, 27, L"✍  ", black, light_pink, false);
	RGBPrint(115, 27, getwstring(language, L"ingame_name") +L": " + wstring_convert<codecvt_utf8<wchar_t>>().from_bytes(savename), black, light_pink, true);
	RGBPrint(115, 28, getwstring(language, L"ingame_turn") + wstring(L": ") + wstring((game.turn) ? L"[X]" : L"[O]"), black, light_pink, true);
	RGBPrint(115, 29, getwstring(language, L"ingame_timeleft") + wstring(L": ") + wstring((game.time < 10) ? L"0" : L"") + to_wstring(game.time) + L"s", black, light_pink, true);
	RGBPrint(115, 30, getwstring(language, L"ingame_ratio") + wstring(L": ") + wstring(L"[X]: ") + ((game.ratio[0] < 10) ? L"0" : L"") + to_wstring(game.ratio[0]) + wstring(L" | [O]: ") + wstring((game.ratio[1] < 0) ? L"0" : L"") + to_wstring(game.ratio[1]), black, light_pink, true);
	RGBPrint(115, 31, getwstring(language, L"ingame_hits") + wstring(L": [X]: ") + wstring((game.hits[0] < 10) ? L"0" : L"") + to_wstring(game.hits[0]) + wstring(L" | [O]: ") + wstring((game.hits[1] < 10) ? L"0" : L"") + to_wstring(game.hits[1]), black, light_pink, true);
	RGBPrint(123, 33,getwstring(language, L"save_remove"), black, light_pink, true);
	RGBPrint(123, 35, getwstring(language, L"save_back"), black, light_pink, true);
	int n, currentSelect = 0,previousSelect = 0;
	while (true) {
		if (_kbhit()) {
			n = _getch();
			n = tolower(n);
			if ((n == 13 || n == 'w' || n == 'a' || n == 's' || n == 'd' ) && enableSFX) playSound(3, 0);
			if (n == 13) break;
			previousSelect = currentSelect;
			if (n == 'w' || n == 'a') {
				currentSelect = (currentSelect == 0) ? 3 : currentSelect - 1;
			}
			if (n == 's' || n == 'd') {
				currentSelect = (currentSelect == 3) ? 0 : currentSelect + 1;
			}
			if (currentSelect != previousSelect) {
				switch (previousSelect) {
				case 0:
					RGBPrint(123, 25, getwstring(language, L"save_load"), black, light_pink, true);
					break;
				case 1:
					RGBPrint(112, 27, L"✍  ", black, light_pink, false);
					RGBPrint(115, 27,getwstring(language, L"ingame_name") + L":", black, light_pink, true);
					break;
				case 2:
					RGBPrint(123, 33, getwstring(language, L"save_remove"), black, light_pink, true);
					break;
				case 3:
					RGBPrint(123, 35, getwstring(language, L"save_back"), black, light_pink, true);
					break;
				}
				switch (currentSelect) {
				case 0:
					RGBPrint(123, 25, getwstring(language, L"save_load"), black, pink, true);
					break;
				case 1:
					RGBPrint(112, 27, L"✍  ", black, pink, false);
					RGBPrint(115, 27,  getwstring(language, L"ingame_name") + L":", black, pink, true);
					break;
				case 2:
					RGBPrint(123, 33, getwstring(language, L"save_remove"), black, pink, true);
					break;
				case 3:
					RGBPrint(123, 35, getwstring(language, L"save_back"), black, pink, true);
					break;
			   }
			}
		}
	}
	switch (currentSelect) {
	case 0:
		loadGame(savename);
		StartGame(1);
		break;
	case 1: {
		string oldname = game.name;
		game.name = gameEditor_name(112, 27, black, light_pink, pink);
		try {
			fs::rename("./Saves/" + oldname + ".txt", "./Saves/" + game.name + ".txt");
		}
		catch (const fs::filesystem_error& e) {
			std::cerr << "Error: " << e.what() << std::endl; 
		}
		loadSaveGameEditor(game.name, false);
		break;
	}

	case 2:
		gameEditor_remove(savename);
		break;
	case 3:
		GameScreen(2);
		break;
	}
}

void newGameOptionsScreen() {
	drawPanel(100, 20, 5);

	wstring options[3] = { getwstring(language, L"play_newgame"), getwstring(language, L"play_loadgame"), getwstring(language, L"back_to_main") };
	int currentSelect = 0, previousSelect = 0;
	int n, size = sizeof(options) / sizeof(wstring);
	for (int i = 0; i < size; i++) {
		if (i == 0) RGBPrint(126 - ((int)options[i].length()) / 2, 23 + 2 * i, L">> " + options[i] + L" <<", { 255,255,255 }, { 255,129,216 }, true);
		else RGBPrint(126 - ((int)options[i].length()) / 2, 23 + 2 * i, L"   " + options[i] + L"   ", { 255,255,255 }, { 255,129,216 }, true);
	}
	while (true) {
		if (_kbhit()) {
			n = _getch();
			n = tolower(n);
			if ((n == 13 || n == 'w' || n == 'a' || n == 's' || n == 'd' || n == 'e') && enableSFX) playSound(3, 0);
			if (n == 13) break;
			previousSelect = currentSelect;
			if (n == 'w' or n == 'a') {//go up
				currentSelect--;
				currentSelect = (currentSelect < 0) ? size - 1 : currentSelect;
			}
			else if (n == 's' or n == 'd') {//go down
				currentSelect++;
				currentSelect = (currentSelect > size - 1) ? 0 : currentSelect;
			}
			RGBPrint(126 - ((int)options[previousSelect].length()) / 2, 23 + 2 * previousSelect, L"   " + options[previousSelect] + L"   ", { 255,255,255 }, { 255,129,216 }, true);
			RGBPrint(126 - ((int)options[currentSelect].length()) / 2, 23 + 2 * currentSelect, L">> " + options[currentSelect] + L" <<", { 255,255,255 }, { 255,129,216 }, true);
		}
	}
	switch (currentSelect) {
	case 0: {//new game menu
		GameScreen(1);
		break;
	}
	case 1: //load game menu
		GameScreen(2);
		break;
	case 2://back
		removePanel(100, 20, 5);
		MainScreen(0, 0, false);
		break;
	}
}
void selectModeScreen() {
	removePanel(100, 20, 5);
	drawPanel(100, 20, 4);
	wstring miniOptions[3] = { getwstring(language, L"play_pvp"),getwstring(language, L"play_pve"), getwstring(language, L"play_back") };
	int miniCurrentSelect = 0, miniPreviousSelect = 0;
	int n, size = sizeof(miniOptions) / sizeof(wstring);
	for (int i = 0; i < size; i++) {
		if (i == 0) RGBPrint(126 - ((int)miniOptions[i].length()) / 2, 23 + 2 * i, L">> " + miniOptions[i] + L" <<", { 255,255,255 }, { 255,129,216 }, true);
		else RGBPrint(126 - ((int)miniOptions[i].length()) / 2, 23 + 2 * i, L"   " + miniOptions[i] + L"   ", { 255,255,255 }, { 255,129,216 }, true);
	}
	while (true) {
		if (_kbhit()) {
			n = _getch();
			n = tolower(n);
			if ((n == 13 || n == 'w' || n == 'a' || n == 's' || n == 'd' || n == 'e') && enableSFX) playSound(3, 0);
			if (n == 13) break;
			miniPreviousSelect = miniCurrentSelect;
			if (n == 'w' or n == 'a') {//go up
				miniCurrentSelect--;
				miniCurrentSelect = (miniCurrentSelect < 0) ? size - 1 : miniCurrentSelect;
			}
			else if (n == 's' or n == 'd') {//go down
				miniCurrentSelect++;
				miniCurrentSelect = (miniCurrentSelect > size - 1) ? 0 : miniCurrentSelect;
			}
			RGBPrint(126 - ((int)miniOptions[miniPreviousSelect].length()) / 2, 23 + 2 * miniPreviousSelect, L"   " + miniOptions[miniPreviousSelect] + L"   ", { 255,255,255 }, { 255,129,216 }, true);
			RGBPrint(126 - ((int)miniOptions[miniCurrentSelect].length()) / 2, 23 + 2 * miniCurrentSelect, L">> " + miniOptions[miniCurrentSelect] + L" <<", { 255,255,255 }, { 255,129,216 }, true);
		}
	}
	switch (miniCurrentSelect) {
	case 0: {//start new game (PVP)
		short a[2] = { 0 };
		vector<vector<int>> board = vector<vector<int>>(10, vector<int>(15));
		setupGame("", 1, 15, a, a, {}, board);
		StartGame(1);
		break;
	}
	case 1: {//start new game (PVE)
		short a[2] = { 0 };
		vector<vector<int>> board = vector<vector<int>>(10, vector<int>(15));
		setupGame("", 1, 15, a, a, {}, board);
		StartGame(1);
		break;
	}
	case 2:
		removePanel(100, 20, 4);
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
		maxindex = (saves - 5 * currentpage >= 0) ? 5 : saves;
	if (maxpages == 0) maxpages++;
	//ve
	wstring text_name = getwstring(language, L"save_name");
	removePanel(100, 20, 5);
	drawPanel(100, 20, 13);
	RGBPrint(108, 23, L"      ║                                    ", black, light_pink, false);
	RGBPrint(108, 24, L"══════╬════════════════════════════════════", black, light_pink, false);
	int _i = 0;
	for (int i = 0; i < 2 * 5; i++) {
		if (i % 2 == 0) {
			RGBPrint(108, 24 + i + 1, L"      ║                                    ", black, light_pink, false);
			if (_i < saves_names.size() && _i <= maxindex - 1) {
				RGBPrint(108 + 2, 24 + i + 1, string((_i + 1 < 10) ? "0" : "") + to_string(_i + 1), black, light_pink);
				RGBPrint(108 + 7 + (14 - (int)saves_names[_i].size() / 2), 24 + i + 1, saves_names[_i], black, light_pink);
				_i++;
			}
		}
		else RGBPrint(108, 24 + i + 1, L"══════╬════════════════════════════════════", black, light_pink, false);
	}
	RGBPrint(108, 34, L"══════╩════════════════════════════════════", black, light_pink, false);
	RGBPrint(108, 24 + 11, L"                                           ", black, light_pink, false);
	RGBPrint(108 + 1, 24 + 11, L"<<", black, light_pink, false);
	RGBPrint(108 + 18, 24 + 11, L"01/" + wstring((saves / 5 < 10) ? L"0" : L"") + to_wstring(maxpages), black, light_pink, false);
	RGBPrint(108 + 38, 24 + 11, L">>", black, light_pink, false);

	RGBPrint(108, 24 + 12, L"═══════════════════════════════════════════", black, light_pink, false);
	RGBPrint(115, 24 + 13, L"   " + getwstring(language, L"play_back") + L"   ", black, light_pink, true);
	//
	if (saves_names.size() >= 1) {
		RGBPrint(108 + 2, 24 + 2 * index + 1, string((index + 1 < 10) ? "0" : "") + to_string(index + 1), black, pink);
		RGBPrint(108 + 7 + (14 - (int)saves_names[index].size() / 2), 24 + 2 * index + 1, saves_names[index], black, pink);
	}
	int n;
	while (true) {//từ đây trở đi tôi đã mất não.
		if (_kbhit()) {
			n = _getch();
			n = tolower(n);
			if ((n == 13 || n == 'w' || n == 'a' || n == 's' || n == 'd' || n == 'e' || n == 'x') && enableSFX) playSound(3, 0);
			if (n == 13) break;
			if (n == 'w' || n == 's') {
				previousSelect = index;
				if (n == 'w') index = (index <= 0) ? maxindex : index - 1;
				else index = (index >= maxindex) ? 0 : index + 1;
				int d = 5 * (currentpage - 1);
				if (previousSelect < maxindex) {
					RGBPrint(108 + 2, 24 + 2 * previousSelect + 1, string((previousSelect + 1 + d < 10) ? "0" : "") + to_string(previousSelect + d + 1), black, light_pink);
					RGBPrint(108 + 7 + (14 - (int)saves_names[previousSelect + d].size() / 2), 24 + 2 * previousSelect + 1, saves_names[previousSelect + d], black, light_pink);
				}
				else RGBPrint(115, 24 + 13, L"   " + getwstring(language, L"play_back") + L"   ", black, light_pink, true);

				if (index < maxindex) {
					RGBPrint(108 + 2, 24 + 2 * index + 1, string((index + d + 1 < 10) ? "0" : "") + to_string(index + d + 1), black, pink);
					RGBPrint(108 + 7 + (14 - (int)saves_names[index + d].size() / 2), 24 + 2 * index + 1, saves_names[index + d], black, pink);
				}
				else RGBPrint(115, 24 + 13, L">> " + getwstring(language, L"play_back") + L" <<", black, light_pink, true);
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
						RGBPrint(108, 24 + i + 1, L"      ║                                    ", black, light_pink, false);
						if (_i < saves_names.size()) {
							if (_i <= maxindex + 5 * (currentpage - 1)) {
								RGBPrint(108 + 7 + (14 - (int)saves_names[_i].size() / 2), 24 + i + 1, saves_names[_i], black, light_pink);
								RGBPrint(108 + 2, 24 + i + 1, string((_i + 1 < 10) ? "0" : "") + to_string(_i + 1), black, light_pink);
								_i++;
							}
						}
					}
					else RGBPrint(108, 24 + i + 1, L"══════╬════════════════════════════════════", black, light_pink, false);
				}
				RGBPrint(108 + 18, 24 + 11, wstring((currentpage < 10) ? L"0" : L"") + to_wstring(currentpage) + L"/" + wstring((saves / 5 < 10) ? L"0" : L"") + to_wstring(maxpages), black, light_pink, false);

				_i = 5 * (currentpage - 1);
				RGBPrint(108 + 7 + (14 - (int)saves_names[_i].size() / 2), 24 + 1, saves_names[_i], black, pink);
				RGBPrint(108 + 2, 24 + 1, string((_i + 1 < 10) ? "0" : "") + to_string(_i + 1), black, pink);
			}
		}
	}
	if (index < maxindex) {
		loadSaveGameEditor(saves_names[index + 5 * (currentpage - 1)], true);
	}
	else {
		removePanel(100, 20, 13);
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
