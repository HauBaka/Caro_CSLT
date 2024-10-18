#ifndef _AUDIO_H_  
#define _AUDIO_H_
#include <iostream>
#include <windows.h>
#pragma comment(lib, "Winmm.lib")
using namespace std;
class Audio {
private:
	wstring current;
public:
	enum Song {
		Memaybeo
	};
	wstring getNamebySong(Song song);
	bool open();
	void play(Song song);
	void pause();
	void resume();
	void close();
};
#endif