#include "Audio.h"
bool loaded[NUMSONGS] = { 0 };
short volume = 400;
//Songs:
//0: None
//1: BG1
//2: BG2
//3: POP
wstring getSongbyNum(short song) {
	switch (song) {
	case 1:
		return L"./Sounds/bg1.mp3";
	case 2:
		return L"./Sounds/bg2.mp3";
	case 3:
		return L"./Sounds/pop.mp3";
	default:
		return L"";
	}
}
void setVolume(short value) {
	value = (value > 1000) ? 1000 : (value < 0) ? 0 : value;
	volume = value;
	for (int i = 0; i < NUMSONGS; i++) {
		wstring name = getSongbyNum(i);
		mciSendString((L"setaudio " + name + L" volume to " + to_wstring(value)).c_str(), NULL, 0, NULL);
	}
}
short getVolume() {
	return volume;
}
void openSound(short song) {
	wstring name = getSongbyNum(song);
	mciSendString((L"open " + name + L"  type mpegvideo alias " + name).c_str(), NULL, 0, NULL);
	loaded[song] = true;
}
void pauseSound(short song) {
	if (loaded[song]) {
		wstring name = getSongbyNum(song);
		mciSendString((L"pause " + name).c_str(), NULL, 0, NULL);
	}
}
void resumeSound(short song) {
	if (loaded[song]) {
		wstring name = getSongbyNum(song);
		mciSendString((L"resume " + name).c_str(), NULL, 0, NULL);
	}
}
void stopSound(short song) {
	wstring name = getSongbyNum(song);
	mciSendString((L"stop " + name).c_str(), NULL, 0, NULL);
	mciSendString((L"close " + name).c_str(), NULL, 0, NULL);
	loaded[song] = false;
}
void restartSound(short song) {
	wstring name = getSongbyNum(song);
	mciSendString((L"seek " + name + L" to 0").c_str(), NULL, 0, NULL);
}
void playSound(short song, bool repeat) {
	if (song != 0) {
		if (loaded[song] == false) openSound(song);
		restartSound(song);
		wstring name = getSongbyNum(song);
		mciSendString((L"play " + name + (repeat ? L" repeat" : L"")).c_str(), NULL, 0, NULL);
		setVolume(volume);
	}
}