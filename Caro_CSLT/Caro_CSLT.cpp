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
	while (true) {
		if (_kbhit()) {//kiểm tra có phím được nhấn không
			int n = _getch();//lấy giá trị phím được nhấn
			char c = (char)n;
			if (c == 'w') y--;
			if (c == 'a') x--;
			if (c == 's') y++;
			if (c == 'd') x++;
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