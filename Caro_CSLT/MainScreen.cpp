#include "MainScreen.h"
void drawQuitOptions() {
	for (int i = 16; i < 30; i++) {
		clearLine(i);
	}
	string options[2] = { "I WANT TO QUIT", "NO, TAKE ME BACK" };
	int a=0, b=0;
	drawOptions(options, 2, a, b, 16);
	if (a == 0) ExitProcess(0);
	else MainScreen(3,0);
}
void MainScreen(int current, bool playBGM) {
	if (playBGM) playSound(1, true);
	for (int i = 16; i < 42; i++) {
		clearLine(i);
	}
	string options[4] = {"START GAME", "SETTINGS", "CONTRIBUTORS", "QUIT"};
	int  previous=0;
	drawOptions(options, 4, current, previous, 16);
	switch (current) {
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