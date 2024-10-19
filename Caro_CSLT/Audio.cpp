#include "Audio.h"

wstring Audio::getNamebySong(Song song) {
	switch (song) {
	case Memaybeo:
		return L"NoSurprises.wav";
	}
	return L"None";
}
bool Audio::open() {
	if (this->current.empty()) return 0;
	wstring text = L"open \"" + this->current + L"\"  type mpegvideo alias wav";
	mciSendString(text.c_str(), NULL, 0, NULL);
	return 1;
}
void Audio::play(Song song) {
	this->current = getNamebySong(song);
	open();
	mciSendString(L"play wav", NULL, 0, NULL);
	wstring text = L"setaudio wav volume to " + to_wstring(this->volume);
	mciSendString(text.c_str(), NULL, 0, NULL);
}
void Audio::setVolume(int value) {
	value = (value > 1000) ? 1000 : (value < 0) ? 0 : value;
	this->volume = value; 
	wstring text = L"setaudio wav volume to " + to_wstring(this->volume);
	mciSendString(text.c_str(), NULL, 0, NULL);
}
int Audio::getVolume() {
	return this->volume;
}
void Audio::pause() {
	mciSendString(L"pause wav", NULL, 0, NULL);
}
void Audio::resume() {
	mciSendString(L"resume wav", NULL, 0, NULL);
}
void Audio::close() {
	mciSendString(L"close wav", NULL, 0, NULL);
}
void Audio::stop() {
	mciSendString(L"stop wav", NULL, 0, NULL);
	this->close();
}