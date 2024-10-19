#include "SettingsScreen.h"
void SettingsScreen() {
	for (int i = 16; i < 30; i++) {
		GotoXY(0, i);
		clearLine();
	}
	printColoredText(47, 18, ">> Sound Effects:\t" + to_string(getSFX().getVolume() / 10) + "/100", 3, 14);
	printColoredText(50, 20, "Music:\t" + to_string(getBGMusic().getVolume() / 10) + "/100", 3, 14);
	printColoredText(50, 22, "Language:(coming soon)\t", 4, 14);
	printColoredText(50, 25, "BACK TO MAIN MENU", 3, 14);
	clearLine();
	int current = 0, previous = 0;
	while (true) {
		if (_kbhit()) {
			int n = tolower(_getch());
			char c = (char)n;
			GotoXY(0, 0);
			if ((c == 'a' || c == 'd') && current <=1) {
				if (current == 0) {
					getSFX().setVolume(getSFX().getVolume() + 10);
					GotoXY(0, 0);
					cout << getSFX().getVolume();
					GotoXY(0, 18);
					clearLine();
					printColoredText(47, 18, ">> Sound Effects:\t" + to_string(getSFX().getVolume() / 10) + "/100", 3, 14);
				}
				else if (current == 1) {
					getBGMusic().setVolume(getBGMusic().getVolume() + 10);
					GotoXY(0, 20);
					clearLine();
					printColoredText(47, 20, ">> Music:\t" + to_string(getBGMusic().getVolume() / 10) + "/100", 3, 14);
				}
			}
			if (c == 's') {
				previous = current;
				current = (current == 3) ? 0 : current + 1;
			}
			if (c == 'w') {
				previous = current;
				current = (current == 0) ? 3 : current - 1;
			}
			switch (current) {
			case 0:
				GotoXY(0, 18);
				clearLine();
				printColoredText(47, 18, ">> Sound Effects:\t" + to_string(getSFX().getVolume() / 10) +"/100", 3, 14);
				break;
			case 1:
				GotoXY(0, 20);
				clearLine();
				printColoredText(47, 20, ">> Music:\t" + to_string(getBGMusic().getVolume() / 10)+"/100", 3, 14);
				break;
			case 2:
				GotoXY(0, 22);
				clearLine();
				printColoredText(47, 22, ">> Language:(coming soon)\t", 4, 14);
				break;
			case 3:
				GotoXY(0, 25);
				clearLine();
				printColoredText(47, 25, ">> BACK TO MAIN MENU <<", 3, 14);
				break;
			}
			switch (previous) {
			case 0:
				GotoXY(0, 18);
				clearLine();
				printColoredText(50, 18, "Sound Effects:\t" + to_string(getSFX().getVolume() / 10) + "/100", 3, 14);
				break;
			case 1:
				GotoXY(0, 20);
				clearLine();
				printColoredText(50, 20, "Music:\t" + to_string(getBGMusic().getVolume() / 10) + "/100", 3, 14);
				break;
			case 2:
				GotoXY(0, 22);
				clearLine();
				printColoredText(50, 22, "Language:(coming soon)\t", 4, 14);
				break;
			case 3:
				GotoXY(0, 25);
				clearLine();
				printColoredText(50, 25, "BACK TO MAIN MENU", 3, 14);
				break;
			}
			if (n == 32 && current == 3) MainScreen(1);
		}
	}
}