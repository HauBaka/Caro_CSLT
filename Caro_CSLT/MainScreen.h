#ifndef _MAINSCREEN_H_
#define _MAINSCREEN_H_
#include "terminalUtils.h"
#include "IntroScreen.h"
#include "string.h"
#include "ContributorsScreen.h"
#include "SettingsScreen.h"
#include "GameScreen.h"
#include "Audio.h"
void MainScreen(int current);
void drawQuitOptions();
Audio getBGMusic();
Audio getSFX();
#endif
