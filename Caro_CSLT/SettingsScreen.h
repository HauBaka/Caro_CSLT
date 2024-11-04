#ifndef _SETTINGSSCREEN_H_
#define _SETTINGSSCREEN_H_
#include "ModelUtils.h"
#include "MainScreen.h"
void SettingsScreen();
extern bool enableSFX, enableBGM ;
void drawVolume(bool);
void drawSFX(bool);
void drawBGM(bool);
void drawLanguage(bool);
void drawBackOption(bool);
void SettingsScreen();
#endif
