#ifndef _AUDIO_H_  
#define _AUDIO_H_
#include <iostream>
#include <windows.h>
#include <string>
#pragma comment(lib, "Winmm.lib")
using namespace std;
class Audio {
private:
	wstring current;
	int volume = 50;
public:
	enum Song {
		BACKGROUND_1,
		BACKGROUND_2,
		POP
	};
	wstring getNamebySong(Song song);
	bool open();
	void play(Song song, bool repeat);//bắt đầu chạy từ đầu
	void pause();//tạm dừng nhạc
	void resume();//tiếp tục chạy bài nhạc
	void close();//đóng(giải phóng giữ liệu)
	void stop();//dừng nhạc(không thể resume, chỉ có thể play lại từ đầu)
	void setVolume(int value);
	int getVolume();
};
#endif