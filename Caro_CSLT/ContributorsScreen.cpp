#include "ContributorsScreen.h"
void ContributorsScreen() {
	drawPanel(100, 20, 13);
	wstring text_name = getwstring(language, L"authors_name"), 
		text_id = getwstring(language, L"authors_id"), 
		text_back = getwstring(language, L"back_to_main");
	wstring contributors[5][2] = {{L"Bùi Ngọc Hiệp	", L"24120309"},
						 {L"Phạm Đình Hải	", L"24120303"},
						 {L"Vòng Sau Hậu	", L"24120307"},
						 {L"Nguyễn Minh Hoàng	", L"24120314"},
						 {L"Đặng Thái Hòa	", L"24120312"} };

	RGBPrint(111, 24, L"                 ║                 ", black, light_pink, false);
	RGBPrint(111+(17-(int)text_name.size())/2, 24, text_name, black, light_pink, true);
	RGBPrint(111 + 18 + (17 - (int)text_id.size()) / 2, 24, text_id, black, light_pink, true);
	int _d = 0;
	for (int i = 0; i < 10; i++) {
		if (i % 2 == 0) RGBPrint(111, 25 + i, L"═════════════════╬═════════════════", black, light_pink, false);
		else {
			RGBPrint(111, 25+i, L"                 ║                 ", black, light_pink, false);
			RGBPrint(111+(17-(int) contributors[_d][0].size())/2, 25+i, contributors[_d][0], black, light_pink, false);
			RGBPrint(129 + (17 - (int)contributors[_d][1].size()) / 2, 25+i, contributors[_d][1], black, light_pink, false);
			_d++;
		}
	}
	RGBPrint(111, 35, L"═════════════════╩═════════════════", black, light_pink, false);
	RGBPrint(117, 36, L">> "+ text_back + L" <<", black, light_pink, true);
	while (true) {
		if (_kbhit()) {
			_getch();
			break;
		}
	}
	removePanel(100, 20, 13);
	MainScreen(2,0, false);
}