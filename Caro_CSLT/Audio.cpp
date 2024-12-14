#include "Audio.h"
bool audio_loaded[NUMSONGS] = { 0 };
short volume = 400;
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
void setVolume(int value) {
	value = (value > 1000) ? 1000 : (value < 0) ? 0 : value;
	volume = value;
	for (int i = 0; i < NUMSONGS; i++) {
		wstring name = getSongbyNum(i);
		mciSendString((L"setaudio " + name + L" volume to " + to_wstring(value)).c_str(), NULL, 0, NULL);
	}
}
int getVolume() {
	return volume;
}
void openSound(short song) {
	wstring name = getSongbyNum(song);
	mciSendString((L"open " + name + L"  type mpegvideo alias " + name).c_str(), NULL, 0, NULL);
	audio_loaded[song] = true;
}
void pauseSound(short song) {
	if (audio_loaded[song]) {
		wstring name = getSongbyNum(song);
		mciSendString((L"pause " + name).c_str(), NULL, 0, NULL);
	}
}
void resumeSound(short song) {
	if (audio_loaded[song]) {
		wstring name = getSongbyNum(song);
		mciSendString((L"resume " + name).c_str(), NULL, 0, NULL);
	}
}
void stopSound(short song) {
	if (audio_loaded[song]) {
		wstring name = getSongbyNum(song);
		mciSendString((L"stop " + name).c_str(), NULL, 0, NULL);
		mciSendString((L"close " + name).c_str(), NULL, 0, NULL);
		audio_loaded[song] = false;
	}
}
void restartSound(short song) {
	wstring name = getSongbyNum(song);
	mciSendString((L"seek " + name + L" to 0").c_str(), NULL, 0, NULL);
}
void playSound(short song, bool repeat) {
	if (song != 0) {
		if (audio_loaded[song] == false) openSound(song);
		restartSound(song);
		wstring name = getSongbyNum(song);
		mciSendString((L"play " + name + (repeat ? L" repeat" : L"")).c_str(), NULL, 0, NULL);
		setVolume(volume);
	}
}