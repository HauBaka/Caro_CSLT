#include "ContributorsScreen.h"
void ContributorsScreen() {
	for (int i = 16; i < 30; i++) {
		clearLine(i);
	}
	wstring guides[5][2] = { {L"Bùi Ngọc Hiệp	", L"24120309"},
						 {L"Phạm Đình Hải	", L"24120303"},
						 {L"Vòng Sau Hậu	", L"24120307"},
						 {L"Nguyễn Minh Hoàng	", L"24120314"},
						 {L"Đặng Thái Hòa	", L"24120312"} };
	for (int i = 0; i < 5; i++) {
		wstring text = guides[i][0] + L"          " + guides[i][1];
		printColoredText((172 - (int)text.size()) / 2, 16 + i, text, 3, 15);
	}
	string options[1] = { "BACK TO MAIN MENU"};
	int current = 0, previous = 0;
	drawOptions(90,30, options, 1, current, previous);
	MainScreen(2,0, false);
}