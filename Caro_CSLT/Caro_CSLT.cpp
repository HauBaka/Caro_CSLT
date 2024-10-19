#include "Caro_CSLT.h"
#include "terminalUtils.h"
#include "Audio.h"
int main()
{
	FixConsoleWindow();
	ShowConsoleCursor(true);
	int x = 5, y = 5;
	system("color f5");//f: nền trắng, 5: chữ tím
	bool turn = true;//true=x,false=0
	Audio  SFX, audio1;
	audio1.play(Audio::BACKGROUND_1, true);
	printColoredText(0, 0, L"Mức âm lượng hiện tại: " + to_wstring(audio1.getVolume()), 0, 15);
	printColoredText(0, 1, L"a: Giảm 10%, d: tăng 10%", 0, 15);
	printColoredText(0, 2, L"m: pause, n: resume, x: close, p: stop, q:play", 0, 15);
	GotoXY(x, y);
	while (true) {
		if (_kbhit()) {//kiểm tra có phím được nhấn không
			int n = _getch();//lấy giá trị phím được nhấn
			char c = (char)n;
			if (c == 'm') audio1.pause();
			if (c == 'n') audio1.resume();
			if (c == 'x') audio1.close();
			if (c == 'p') audio1.stop();
			if (c == 'q') audio1.play(Audio::BACKGROUND_1, true);
			if (c == 'w') y--;
			if (c == 'a') {
				x = (x==0) ? 0 : x-1;
				audio1.setVolume(audio1.getVolume() - 100);
				GotoXY(0, 0);
				cout << "                            " << endl;
				printColoredText(0, 0, L"Mức âm lượng hiện tại: " + to_wstring(audio1.getVolume()),0,15);
			}
			if (c == 's') y++;
			if (c == 'd') {
				x++;
				audio1.setVolume(audio1.getVolume() + 100);
				GotoXY(0, 0);
				cout << "                            " << endl;
				printColoredText(0, 0, L"Mức âm lượng hiện tại: " + to_wstring(audio1.getVolume()), 0, 15);
			}
			GotoXY(x, y);
			if (n == 32) {
				SFX.play(Audio::POP, false);
				if (turn == true) cout << "X";
				else cout << "O";
				turn = !turn;
			}
		}
	}
	return 0;
}