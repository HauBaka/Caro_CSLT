#include "Caro_CSLT.h"
#include "terminalUtils.h"
#include "Audio.h"
#include "IntroScreen.h"
int main()
{
	SetUpWindow();
	startIntroScreen();
	while (true) {
		if (_kbhit()) {
		}
	}
	return 0;
}
