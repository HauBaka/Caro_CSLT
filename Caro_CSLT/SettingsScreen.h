#ifndef _SETTINGSSCREEN_H_
#define _SETTINGSSCREEN_H_
#include "ModelUtils.h"
#include "MainScreen.h"
void SettingsScreen();
extern bool enableSFX, enableBGM ;
void drawVolume(bool, int, int, RGB);
void drawSFX(bool, int, int, RGB);
void drawBGM(bool, int, int, RGB);
void drawLanguage(bool, int, int, RGB);
void drawBackOption(bool, int, int, RGB);
void settingsPopup();
void SettingsScreen();
#endif
