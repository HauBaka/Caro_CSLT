#include "Audio.h"

wstring Audio::getNamebySong(Song song) {
	switch (song) {
	case Memaybeo:
		return L"NoSurprises.wav";
	}
	return L"NoSurprises.wav";
}
bool Audio::open() {
	if (this->current.empty()) return 0;
	wstring text = L"open \"" + this->current + L"\"  type mpegvideo alias wav";
	mciSendString(text.c_str(), NULL, 0, NULL);
	mciSendString(L"play wav", NULL, 0, NULL);
	return 1;
}
void Audio::play(Song song) {
	this->current = getNamebySong(song);
	open();
}
