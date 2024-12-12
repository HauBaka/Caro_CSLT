#ifndef _AUDIO_H_  
#define _AUDIO_H_
#include <iostream>
#include <windows.h>
#include <string>
#pragma comment(lib, "Winmm.lib")
using namespace std;
#define NUMSONGS 12
extern bool audio_loaded[];
extern short volume;
wstring getSongbyNum(short);
void setVolume(int);
int getVolume();
void openSound(short);
void pauseSound(short);
void resumeSound(short);
void stopSound(short);
void restartSound(short);
void playSound(short, bool);
#endif