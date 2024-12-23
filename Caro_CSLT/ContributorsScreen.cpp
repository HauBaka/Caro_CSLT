#include "ContributorsScreen.h"
void ContributorsScreen() {
	drawPanel(90, 18, 13);
	wstring text_name = getwstring(language, L"authors_name"), 
		text_id = getwstring(language, L"authors_id"), 
		text_back = getwstring(language, L"back_to_main");
	wstring contributors[5][2] = {{L"Bùi Ngọc Hiệp	", L"24120309"},
						 {L"Phạm Đình Hải	", L"24120303"},
						 {L"Vòng Sau Hậu	", L"24120307"},
						 {L"Nguyễn Minh Hoàng	", L"24120314"},
						 {L"Đặng Thái Hòa	", L"24120312"} };
	int x = 101, _d =0, n;
	/*Vẽ khung*/
	RGBPrint(x, 22, L"                 ║                 ", black, light_aqua, false);
	RGBPrint(x +(17-(int)text_name.size())/2, 22, text_name, black, light_aqua, true);
	RGBPrint(x + 18 + (17 - (int)text_id.size()) / 2, 22, text_id, black, light_aqua, true);
	for (int i = 0; i < 10; i++) {
		if (i % 2 == 0) RGBPrint(x, 23 + i, L"═════════════════╬═════════════════", black, light_aqua, false);
		else {
			RGBPrint(x, 23+i, L"                 ║                 ", black, light_aqua, false);
			RGBPrint(x +(17-(int) contributors[_d][0].size())/2, 23+i, contributors[_d][0], black, light_aqua, false);
			RGBPrint(x+18 + (17 - (int)contributors[_d][1].size()) / 2, 23+i, contributors[_d][1], black, light_aqua, false);
			_d++;
		}
	}
	RGBPrint(x, 33, L"═════════════════╩═════════════════", black, light_aqua, false);
	RGBPrint(116-sizeOfText(text_back)/2, 34, L">> " + text_back + L" <<", black, light_aqua, true);
	while (true) {
		if (_kbhit()) {
			n = tolower(_getch());
			if (n == 13) {
				if (enableSFX) playSound(9, 0);
				break;
			}
		}
	}
	removePanel(90, 18, 13);
	MainScreen(3,0, false);
}