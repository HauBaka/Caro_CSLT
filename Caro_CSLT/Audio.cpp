#include "Audio.h"
bool audio_loaded[NUMSONGS] = { 0 };
short volume = 400;
/*Lấy tên bản lưu*/
wstring getSongbyNum(short song) {
	switch (song) {
	case 1:
		return L"./Sounds/intro.mp3";
	case 2:
		return L"./Sounds/intro.mp3";
	case 3:
		return L"./Sounds/pop.mp3";
	case 4:
		return L"./Sounds/bgmusic.mp3";
	case 5:
		return L"./Sounds/win.mp3";
	case 6:
		return L"./Sounds/loadsave.mp3";
	case 7:
		return L"./Sounds/ingame.mp3";
	case 8:
		return L"./Sounds/paused.mp3";
	case 9:
		return L"./Sounds/select.mp3";
	case 10:
		return L"./Sounds/move.mp3";
	case 11:
		return L"./Sounds/hit.mp3";
	default:
		return L"";
	}
}
/*Đặt âm lượng*/
void setVolume(int value) {
	value = (value > 1000) ? 1000 : (value < 0) ? 0 : value;
	volume = value;
	for (int i = 0; i < NUMSONGS; i++) {
		wstring name = getSongbyNum(i);
		mciSendString((L"setaudio " + name + L" volume to " + to_wstring(value)).c_str(), NULL, 0, NULL);
	}
}
/*Lấy giá trị âm lượng*/
int getVolume() {
	return volume;
}
/*Mở file*/
void openSound(short song) {
	wstring name = getSongbyNum(song);
	mciSendString((L"open " + name + L"  type mpegvideo alias " + name).c_str(), NULL, 0, NULL);
	audio_loaded[song] = true;
}
/*Tạm dừng*/
void pauseSound(short song) {
	if (audio_loaded[song]) {
		wstring name = getSongbyNum(song);
		mciSendString((L"pause " + name).c_str(), NULL, 0, NULL);
	}
}
/*Tiếp tục*/
void resumeSound(short song) {
	if (audio_loaded[song]) {
		wstring name = getSongbyNum(song);
		mciSendString((L"resume " + name).c_str(), NULL, 0, NULL);
	}
}
/*Tắt*/
void stopSound(short song) {
	if (audio_loaded[song]) {
		wstring name = getSongbyNum(song);
		mciSendString((L"stop " + name).c_str(), NULL, 0, NULL);
		mciSendString((L"close " + name).c_str(), NULL, 0, NULL);
		audio_loaded[song] = false;
	}
}
/*Chạy lại*/
void restartSound(short song) {
	wstring name = getSongbyNum(song);
	mciSendString((L"seek " + name + L" to 0").c_str(), NULL, 0, NULL);
}
/*Chạy*/
void playSound(short song, bool repeat) {
	if (song != 0) {
		if (audio_loaded[song] == false) openSound(song);
		restartSound(song);
		wstring name = getSongbyNum(song);
		mciSendString((L"play " + name + (repeat ? L" repeat" : L"")).c_str(), NULL, 0, NULL);
		setVolume(volume);
	}
}
/*Đóng tất cả file nhạc đã mở*/
void closeAllSound() {
	for (int i =0;i<NUMSONGS;i++) {
		stopSound(i);
	}
}