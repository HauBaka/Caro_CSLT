#include "Audio.h"

wstring Audio::getNamebySong(Song song) {
	switch (song) {
	case BACKGROUND_1:
		return L"./Sounds/bg1.mp3";
	case BACKGROUND_2:
		return L"./Sounds/bg2.mp3";
	case POP:
		return L"./Sounds/pop.mp3";
	}
	return L"None";
}
bool Audio::open() {
	if (this->current.empty()) return 0;
	mciSendString((L"open " + this->current + L"  type mpegvideo alias " + this->current).c_str(), NULL, 0, NULL);
	return 1;
}
void Audio::play(Song song, bool repeat) {
	if (!this->current.empty()) this->close();
	this->current = getNamebySong(song);
	open();
	mciSendString((L"play " + this->current + (repeat ? L" repeat":L"")).c_str(), NULL, 0, NULL);
	mciSendString((L"setaudio mp3 volume to " + to_wstring(this->volume)).c_str(), NULL, 0, NULL);
}
void Audio::setVolume(int value) {
	value = (value > 1000) ? 1000 : (value < 0) ? 0 : value;
	this->volume = value; 
	mciSendString((L"setaudio " + this->current + L" volume to " + to_wstring(this->volume)).c_str(), NULL, 0, NULL);
}
int Audio::getVolume() {
	return this->volume;
}
void Audio::pause() {
	mciSendString((L"pause " + this->current).c_str(), NULL, 0, NULL);
}
void Audio::resume() {
	mciSendString((L"resume " + this->current).c_str(), NULL, 0, NULL);
}
void Audio::close() {
	this->stop();
	mciSendString((L"close " + this->current).c_str(), NULL, 0, NULL);
}
void Audio::stop() {
	mciSendString((L"stop " + this->current).c_str(), NULL, 0, NULL);
}