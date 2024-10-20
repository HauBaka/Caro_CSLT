#include "MainScreen.h"
Audio backgroundMusic, SFX;
Audio getBGMusic() {
	return backgroundMusic;
}
Audio getSFX() {
	return SFX;
}
void drawQuitOptions() {
	for (int i = 16; i < 30; i++) {
		GotoXY(0, i);
		clearLine();
	}
	string options[2] = { "I WANT TO QUIT", "NO, TAKE ME BACK" };
	int a=0, b=0;
	drawOptions(options, 2, a, b, 16);
	if (a == 0) ExitProcess(0);
	else MainScreen(3);
}
void MainScreen(int current) {
	backgroundMusic.play(Audio::BACKGROUND_1, true);
	for (int i = 16; i < 30; i++) {
		GotoXY(0, i);
		clearLine();
	}
	clearLine();
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
	}

}