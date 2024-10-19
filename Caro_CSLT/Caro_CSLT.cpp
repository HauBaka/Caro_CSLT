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
	Audio audio;
	audio.play(Audio::Memaybeo);
	printColoredText(0, 0, L"Mức âm lượng hiện tại: " + to_wstring(audio.getVolume()), 0, 15);
	printColoredText(0, 1, L"a: Giảm 10%, d: tăng 10%", 0, 15);
	printColoredText(0, 2, L"m: pause, n: resume, x: close, p: stop, q:play", 0, 15);
	GotoXY(x, y);

	while (true) {
		if (_kbhit()) {//kiểm tra có phím được nhấn không
			int n = _getch();//lấy giá trị phím được nhấn
			char c = (char)n;
			if (c == 'm') audio.pause();
			if (c == 'n') audio.resume();
			if (c == 'x') audio.close();
			if (c == 'p') audio.stop();
			if (c == 'q') audio.play(Audio::Memaybeo);
			if (c == 'w') y--;
			if (c == 'a') {
				x = (x==0) ? 0 : x-1;
				audio.setVolume(audio.getVolume() - 100);
				GotoXY(0, 0);
				cout << "                            " << endl;
				printColoredText(0, 0, L"Mức âm lượng hiện tại: " + to_wstring(audio.getVolume()),0,15);
			}
			if (c == 's') y++;
			if (c == 'd') {
				x++;
				audio.setVolume(audio.getVolume() + 100);
				GotoXY(0, 0);
				cout << "                            " << endl;
				printColoredText(0, 0, L"Mức âm lượng hiện tại: " + to_wstring(audio.getVolume()), 0, 15);
			}
			GotoXY(x, y);
			if (n == 32) {
				if (turn == true) cout << "X";
				else cout << "O";
				turn = !turn;
			}
		}
	}
	return 0;
}