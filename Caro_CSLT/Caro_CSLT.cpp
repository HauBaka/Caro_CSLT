#include "Caro_CSLT.h"
#include "FileConfiguration.h"
FILE* language, *config;
int main()
{
	SetUpWindow();
	startIntroScreen();
	closeProgram();
	return 0;
}

void closeProgram() {
	closeAllFiles();
	closeAllSound();
}
