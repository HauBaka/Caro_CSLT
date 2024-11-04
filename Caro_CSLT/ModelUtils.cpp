#include "ModelUtils.h"
#include "terminalUtils.h"
RGB pink = { 255,89,199 }, white_pink = { 255,217,254 }, light_pink = { 255,129,216 }, black = { 0,0,0 }, white = { 255,255,255 }, default_white = { 242,242,242 };
void RGBPrint(int x, int y, wstring text, RGB textColor, RGB bgColor, bool bold) {
    GotoXY(x, y);
    int OldMode = _setmode(_fileno(stdout), _O_WTEXT);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    wcout << "\x1b[38;2;" << textColor.R << ";" << textColor.G << ";" << textColor.B << "m";//text color
    wcout << "\x1b[48;2;" << bgColor.R << ";" << bgColor.G << ";" << bgColor.B << "m";//bg color
    if (bold) wcout << "\x1b[1m";
    wcout << text;
    _setmode(_fileno(stdout), OldMode);
}
void printColoredText(int x, int y, wstring text, int textColor, int bgColor) {	//in text tại vị trí x,y với màu textColor
    int OldMode = _setmode(_fileno(stdout), _O_WTEXT);							//bgColor nền
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int colorAttribute = textColor + (bgColor << 4);
    SetConsoleTextAttribute(hConsole, colorAttribute);
    GotoXY(x, y);
    wcout << text;
    SetConsoleTextAttribute(hConsole, 3 + (15 << 4));
    _setmode(_fileno(stdout), OldMode);
}
void printColoredText(int x, int y, string text, int textColor, int bgColor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int colorAttribute = textColor + (bgColor << 4);
    SetConsoleTextAttribute(hConsole, colorAttribute);
    GotoXY(x, y);
    cout << text;
    SetConsoleTextAttribute(hConsole, 3 + (15 << 4));
}
void BetterDraw(int x, int y, string text, int bgcolor) {
    short positions[MaxSize] = { 0 };
    short n =(short) text.find('&',0);
    short dem = 0;
    while (n != string::npos) {
        positions[dem++] = n;
        n =(short) text.find('&', n + 1);
    }
    short _xpos = 0;
    string _preText;
    for (int i = 0; i < dem; i++) {
        string _text;
        if (positions[i + 1] != 0) _text = text.substr(positions[i] + 2, positions[i + 1] - positions[i] - 2);
        else _text  = text.substr(positions[i] + 2);
        char c = text[positions[i] + 1];
        if(i>0) _xpos +=(int) _preText.length();
        switch (c) {
        case 'a':
            printColoredText(x + _xpos, y, _text, 10, bgcolor);
            break;
        case 'b':
            printColoredText(x + _xpos, y, _text, 9, bgcolor);
            break;
        case 'c':
            printColoredText(x + _xpos, y, _text, 12, bgcolor);
            break;
        case 'd':
            printColoredText(x + _xpos, y, _text, 13, bgcolor);
            break;
        case 'e':
            printColoredText(x + _xpos, y, _text, 14, bgcolor);
            break;
        case 'f':
            printColoredText(x + _xpos, y, _text, 15, bgcolor);
            break;
        default:
            if (c <= '9' && c >= '0') printColoredText(x + _xpos, y, _text, c-'0', bgcolor);
        }
        _preText = _text;
    }
}
void BetterDraw(int x, int y, wstring text, int bgcolor) {
    short positions[MaxSize] = { 0 };
    short n = (short)text.find('&', 0);
    short dem = 0;
    while (n != wstring::npos) {
        positions[dem++] = n;
        n = (short)text.find('&', n + 1);
    }
    short _xpos = 0;
    wstring _preText;
    for (int i = 0; i < dem; i++) {
        wstring _text;
        if (positions[i + 1] != 0) _text = text.substr(positions[i] + 2, positions[i + 1] - positions[i] - 2);
        else _text = text.substr(positions[i] + 2);
        wchar_t c = text[positions[i] + 1];
        if (i > 0) _xpos += (int)_preText.length();
        switch (c) {
        case 'a':
            printColoredText(x + _xpos, y, _text, 10, bgcolor);
            break;
        case 'b':
            printColoredText(x + _xpos, y, _text, 9, bgcolor);
            break;
        case 'c':
            printColoredText(x + _xpos, y, _text, 12, bgcolor);
            break;
        case 'd':
            printColoredText(x + _xpos, y, _text, 13, bgcolor);
            break;
        case 'e':
            printColoredText(x + _xpos, y, _text, 14, bgcolor);
            break;
        case 'f':
            printColoredText(x + _xpos, y, _text, 15, bgcolor);
            break;
        default:
            if (c <= '9' && c >= '0') printColoredText(x + _xpos, y, _text, c - '0', bgcolor);
        }
        _preText = _text;
    }
}
void drawLOGO(int x, int y) {
    printColoredText(x, y,     L" ██████╗ █████╗ ██████╗  ██████╗      ██████╗  █████╗ ███╗   ███╗███████╗", 1, 15);
    printColoredText(x, y + 1, L"██╔════╝██╔══██╗██╔══██╗██╔═══██╗    ██╔════╝ ██╔══██╗████╗ ████║██╔════╝", 1, 15);
    printColoredText(x, y + 2, L"██║     ███████║██████╔╝██║   ██║    ██║  ███╗███████║██╔████╔██║█████╗  ", 1, 15);
    printColoredText(x, y + 3, L"██║     ██╔══██║██╔══██╗██║   ██║    ██║   ██║██╔══██║██║╚██╔╝██║██╔══╝  ", 1, 15);
    printColoredText(x, y + 4, L"╚██████╗██║  ██║██║  ██║╚██████╔╝    ╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗", 1, 15);
    printColoredText(x, y + 5, L" ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝      ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝", 1, 15);
}
void veMay(int x, int y) {
    printColoredText(x - 1, y + 3, L" ", 3, 15);
    printColoredText(x - 1, y + 4, L" ", 3, 15);
    printColoredText(x - 1, y + 5, L" ", 3, 15);

    printColoredText(x, y, L"          ▄█▀▀", 0, 15);
    printColoredText(x + 14, y, L"▀▀", 0, 7);
    printColoredText(x + 16, y, L"█▄", 0, 15);
    //2
    printColoredText(x, y + 1, L"        ▄█▀     ", 0, 15);
    printColoredText(x + 15, y + 1, L"▀", 7, 15);
    printColoredText(x + 16, y + 1, L"▀", 7, 7);
    printColoredText(x + 17, y + 1, L"▀", 0, 7);
    printColoredText(x + 18, y + 1, L"█", 0, 15);
    //3
    printColoredText(x, y + 2, L"  ▄▄▄▄▄ █        ", 0, 15);
    printColoredText(x + 17, y + 2, L"▀", 7, 15);
    printColoredText(x + 18, y + 2, L"▀▄█▀▀", 0, 15);
    printColoredText(x + 18 + 5, y + 2, L"▀▀", 0, 7);
    printColoredText(x + 18 + 5 + 2, y + 2, L"█▄", 0, 15);
    //4
    printColoredText(x, y + 3, L"▄█▀  ", 0, 15);
    printColoredText(x + 5, y + 3, L"▀▀", 7, 15);
    printColoredText(x + 7, y + 3, L"██          ▀   ", 0, 15);
    printColoredText(x + 7 + 17, y + 3, L"▀▀", 7, 15);
    printColoredText(x + 7 + 17 + 2, y + 3, L"█", 0, 15);
    //5
    printColoredText(x, y + 4, L"█                         ▀▄", 0, 15);
    //6
    printColoredText(x, y + 5, L"▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀", 0, 15);
    //          ▄█▀▀▀▀█▄
    //        ▄█▀      ▀█
    //  ▄▄▄▄▄ █         ▀▄█▀▀▀▀█▄
    //▄█▀    ██          ▀      █
    //█                         ▀▄
    //▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
}
void drawPlayer(bool player, bool border, int x, int y, int color, int bgcolor) {
    if (player) {//turn x
        if (border) {
            printColoredText(x, y, L"██╗  ██╗", color, bgcolor);
            printColoredText(x, y + 1, L"╚██╗██╔╝", color, bgcolor);
            printColoredText(x, y + 2, L" ╚███╔╝ ", color, bgcolor);
            printColoredText(x, y + 3, L" ██╔██╗ ", color, bgcolor);
            printColoredText(x, y + 4, L"██╔╝ ██╗", color, bgcolor);
            printColoredText(x, y + 5, L"╚═╝  ╚═╝", color, bgcolor);
        }
        else {
            printColoredText(x, y, L"         ", color, bgcolor);
            printColoredText(x, y + 1, L" ██   ██ ", color, bgcolor);
            printColoredText(x, y + 2, L"  ██ ██  ", color, bgcolor);
            printColoredText(x, y + 3, L"   ███   ", color, bgcolor);
            printColoredText(x, y + 4, L"  ██ ██  ", color, bgcolor);
            printColoredText(x, y + 5, L" ██   ██ ", color, bgcolor);
            printColoredText(x, y + 6, L"         ", color, bgcolor);
        }
    }
    else {
        if (border) {
            printColoredText(x, y, L" ██████╗ ", color, bgcolor);
            printColoredText(x, y + 1, L"██╔═══██╗", color, bgcolor);
            printColoredText(x, y + 2, L"██║   ██║", color, bgcolor);
            printColoredText(x, y + 3, L"██║   ██║", color, bgcolor);
            printColoredText(x, y + 4, L"╚██████╔╝", color, bgcolor);
            printColoredText(x, y + 5, L" ╚═════╝ ", color, bgcolor);
        }
        else {
            printColoredText(x, y, L"          ", color, bgcolor);
            printColoredText(x, y + 1, L"  ██████  ", color, bgcolor);
            printColoredText(x, y + 2, L" ██    ██ ", color, bgcolor);
            printColoredText(x, y + 3, L" ██    ██ ", color, bgcolor);
            printColoredText(x, y + 4, L" ██    ██ ", color, bgcolor);
            printColoredText(x, y + 5, L"  ██████  ", color, bgcolor);
            printColoredText(x, y + 6, L"          ", color, bgcolor);
        }
    }
}
void drawTurn(bool turn, int x, int y) {
    if (turn) {
        drawPlayer(true, true, x, y, 1, 15);//x
        printColoredText(x + 1, y + 6, "TURN X", 1, 15);
        drawPlayer(false, false, x, y + 10, 9, 15);//o
    }
    else {
        drawPlayer(true, false, x, y, 9, 15);//x
        drawPlayer(false, true, x, y + 10, 1, 15);//o
        printColoredText(x + 1, y + 10 + 5 + 1, "TURN O", 1, 15);
    }
}
void drawGameBoard(int x, int y, int length, int width) {
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            if (i == 0 && j == 0) printColoredText(x + i, y + j, L"╔", 3, 15);
            else if (i == 0 && j == width - 1) printColoredText(x + i, y + j, L"╚", 3, 15);
            else if (i == length - 1 && j == 0)  printColoredText(x + i, y + j, L"╗", 3, 15);
            else if (i == length - 1 && j == width - 1)  printColoredText(x + i, y + j, L"╝", 3, 15);
            else if ((i == 0 or i == length - 1) && (j != 0 && j != width - 1))  printColoredText(x + i, y + j, L"║", 3, 15);
            else if ((i != 0 && i != length - 1) && (j == 0 or j == width - 1))   printColoredText(x + i, y + j, L"═", 3, 15);
            else {
                if ((j % 2 == 1 && i % 4 == 1)) printColoredText(x + i, y + j, L"   │", 3, 15);
                if (j % 2 == 0 && i % 4 == 1) printColoredText(x + i, y + j, L"───┼", 3, 15);
            }
        }
    }
}
void drawStartButton(int x, int y) {
    /*
 ▄▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▄
█      ▄▄                   █
█     █   █▄ ▀▀▄ ▄▄  █▄     █
█      ▀▄ █  █▀█ █ ▀ █      █
█    ▀▀▀  ▀▀ ▀▀  ▀   ▀▀     █
 ▀▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▀
    */
    printColoredText(x+1, y, L"▄", 0, 15);
    printColoredText(x+27, y, L"▄", 0, 15);
    BetterDraw(x+2, y, L"&0▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀", 8);

    BetterDraw(x, y+1, L"&0█      &f▄▄&0                   █", 8);
    BetterDraw(x, y+2, L"&0█&f     █   █▄ ▀▀▄ ▄▄  █▄     &0█", 8);
    BetterDraw(x, y+3, L"&0█&f      ▀▄ █  █▀█ █ ▀ █      &0█", 8);
    BetterDraw(x, y+4, L"&0█&f    ▀▀▀  ▀▀ ▀▀  ▀   ▀▀     &0█", 8);


    printColoredText(x + 1, y+5, L"▀", 0, 15);
    printColoredText(x + 27, y+5, L"▀", 0, 15);
    BetterDraw(x + 2, y+5, L"&0▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄", 8);
}
void drawMainMenu_Play(int x, int y, bool check) {
// ▄▀▀▀▀▀█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▄
//█ ▄█▄█▄ █       █▀▄ █   ▄▀▄ ▀▄▀         █
//█  ▀█▀  █       █▀  █▄▄ █▀█  █          █
// ▀▄▄▄▄▄█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▀
    
    printColoredText(x, y, L" ", 15, 15);
    RGBPrint(x+1, y, L"▄▀▀▀▀▀█", black, white, false);
    RGBPrint(x+1+7, y, L"▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀", black, white_pink, false);
    printColoredText(x+1+7+31, y, L"▄", 0, 15);
    //
    printColoredText(x, y+1, L"█", 0, 15);
    RGBPrint(x+1, y+1, L" ▄█▄█▄ ", pink, white, false);
    printColoredText(x+1+7, y+1, L"█ ", 0, 15);
    RGBPrint(x+1+7+1, y+1, L"     █▀▄ █   ▄▀▄ ▀▄▀           ", white, light_pink, false);
    printColoredText(x+1+7+1+30+1, y+1, L"█", 0, 15);
    //
    printColoredText(x, y+2, L"█", 0, 15);
    RGBPrint(x+1, y+2, L"  ▀█▀  ", pink, white, false);
    printColoredText(x+1+7, y+2, L"█", 0, 15);
    RGBPrint(x+1+7+1, y+2, L"     █▀  █▄▄ █▀█  █            ", white, light_pink, false);
    printColoredText(x+1+7+1+31, y+2, L"█", 0, 15);
    //
    printColoredText(x, y+3, L" ", 0, 15);
    RGBPrint(x+1, y+3, L"▀▄▄▄▄▄█", black, white, false);
    RGBPrint(x+1+7, y+3, L"▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄", black, pink, false);
    printColoredText(x+1+7+31, y+3, L"▀", 0, 15);
}
void drawMainMenu_Options(int x, int y, bool check) {
// ▄▀▀▀▀▀█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▄
//█ ▄█▄█▄ █  ▄▀▄ █▀▄ ▀█▀ ▀ ▄▀▄ █▄ █ ▄▀    █
//█  ▀█▀  █  ▀▄▀ █▀   █  █ ▀▄▀ █ ▀█ ▄▀    █
// ▀▄▄▄▄▄█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▀

    printColoredText(x, y, L" ", 0, 15);
    RGBPrint(x + 1, y, L"▄▀▀▀▀▀█", black, white, false);
    RGBPrint(x + 1 + 7, y, L"▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀", black, white_pink, false);
    RGBPrint(x + 1 + 7 + 31, y, L"▄", black, white, false);
    //
    printColoredText(x, y + 1, L"█", 0, 15);
    RGBPrint(x + 1, y + 1, L" ▄█▄█▄ ", pink, white, false);
    printColoredText(x + 1 + 7, y + 1, L"█ ", 0, 15);
    RGBPrint(x + 1 + 7 + 1, y + 1, L"  ▄▀▄ █▀▄ ▀█▀ ▀ ▄▀▄ █▄ █ ▄▀    ", white, light_pink, false);
    printColoredText(x + 1 + 7 + 1 + 31, y + 1, L"█", 0, 15);
    //
    printColoredText(x, y + 2, L"█", 0, 15);
    RGBPrint(x + 1, y + 2, L"  ▀█▀  ", pink, white, false);
    printColoredText(x + 1 + 7, y + 2, L"█", 0, 15);
    RGBPrint(x + 1 + 7 + 1, y + 2, L"  ▀▄▀ █▀   █  █ ▀▄▀ █ ▀█ ▄▀    ", white, light_pink, false);
    printColoredText(x + 1 + 7 + 1 + 31, y + 2, L"█", 0, 15);
    //
    printColoredText(x, y + 3, L" ", 0, 15);
    RGBPrint(x + 1, y + 3, L"▀▄▄▄▄▄█", black, white, false);
    RGBPrint(x + 1 + 7, y + 3, L"▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄", black, pink, false);
    printColoredText(x + 1 + 7 + 31, y + 3, L"▀", 0, 15);
}
void drawMainMenu_Authors(int x, int y, bool check) {
// ▄▀▀▀▀▀█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▄
//█ ▄█▄█▄ █  ▄▀▄ █ █ ▀█▀ █ █ ▄▀▄ █▀▄ ▄▀   █ 
//█  ▀█▀  █  █▀█ ▀▄▀  █  █▀█ ▀▄▀ █▀▄ ▄▀   █
// ▀▄▄▄▄▄█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▀


    printColoredText(x, y, L" ", 0, 15);
    RGBPrint(x + 1, y, L"▄▀▀▀▀▀█", black, white, false);
    RGBPrint(x + 1 + 7, y, L"▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀", black, white_pink, false);
    RGBPrint(x + 1 + 7 + 31, y, L"▄", black, white, false);
    //
    printColoredText(x, y + 1, L"█", 0, 15);
    RGBPrint(x + 1, y + 1, L" ▄█▄█▄ ", pink, white, false);
    printColoredText(x + 1 + 7, y + 1, L"█ ", 0, 15);
    RGBPrint(x + 1 + 7 + 1, y + 1, L"  ▄▀▄ █ █ ▀█▀ █ █ ▄▀▄ █▀▄ ▄▀   ", white, light_pink, false);
    printColoredText(x + 1 + 7 + 1 + 31, y + 1, L"█", 0, 15);
    //
    printColoredText(x, y + 2, L"█", 0, 15);
    RGBPrint(x + 1, y + 2, L"  ▀█▀  ", pink, white, false);
    printColoredText(x + 1 + 7, y + 2, L"█", 0, 15);
    RGBPrint(x + 1 + 7 + 1, y + 2, L"  █▀█ ▀▄▀  █  █▀█ ▀▄▀ █▀▄ ▄▀   ", white, light_pink, false);
    printColoredText(x + 1 + 7 + 1 + 31, y + 2, L"█", 0, 15);
    //
    printColoredText(x, y + 3, L" ", 0, 15);
    RGBPrint(x + 1, y + 3, L"▀▄▄▄▄▄█", black, white, false);
    RGBPrint(x + 1 + 7, y + 3, L"▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄", black, pink, false);
    printColoredText(x + 1 + 7 + 31, y + 3, L"▀", 0, 15);
}
void drawMainMenu_Out(int x, int y, bool check) {
// ▄▀▀▀▀▀█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▄
//█ ▄█▄█▄ █        ▄▀▄ █ █ ▀█▀            █
//█  ▀█▀  █        ▀▄▀ ▀▄▀  █             █
// ▀▄▄▄▄▄█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▀


    printColoredText(x, y, L" ", 0, 15);
    RGBPrint(x + 1, y, L"▄▀▀▀▀▀█", black, white, false);
    RGBPrint(x + 1 + 7, y, L"▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀", black, white_pink, false);
    RGBPrint(x + 1 + 7 + 31, y, L"▄", black, white, false);
    //
    printColoredText(x, y + 1, L"█", 0, 15);
    RGBPrint(x + 1, y + 1, L" ▄█▄█▄ ", pink, white, false);
    printColoredText(x + 1 + 7, y + 1, L"█ ", 0, 15);
    RGBPrint(x + 1 + 7 + 1, y + 1, L"        ▄▀▄ █ █ ▀█▀            ", white, light_pink, false);
    printColoredText(x + 1 + 7 + 1 + 31, y + 1, L"█", 0, 15);
    //
    printColoredText(x, y + 2, L"█", 0, 15);
    RGBPrint(x + 1, y + 2, L"  ▀█▀  ", pink, white, false);
    printColoredText(x + 1 + 7, y + 2, L"█", 0, 15);
    RGBPrint(x + 1 + 7 + 1, y + 2, L"        ▀▄▀ ▀▄▀  █             ", white, light_pink, false);
    printColoredText(x + 1 + 7 + 1 + 31, y + 2, L"█", 0, 15);
    //
    printColoredText(x, y + 3, L" ", 0, 15);
    RGBPrint(x + 1, y + 3, L"▀▄▄▄▄▄█", black, white, false);
    RGBPrint(x + 1 + 7, y + 3, L"▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄", black, pink, false);
    printColoredText(x + 1 + 7 + 31, y + 3, L"▀", 0, 15);
}
void drawTriagle(int x, int y, bool show) {
    if (show) {
        printColoredText(x, y, L"  ▄", 0, 15);
        printColoredText(x, y + 1, L"▄██", 0, 15);
        printColoredText(x, y + 2, L" ▀█", 0, 15);
    }
    else {
        printColoredText(x, y, L"   ", 0, 15);
        printColoredText(x, y + 1, L"   ", 0, 15);
        printColoredText(x, y + 2, L"   ", 0, 15);
    }

}
void drawPanel(int x, int y, int lines) {//52 in length
    RGBPrint(x, y, L" ▄", black, default_white, false);
    RGBPrint(x+2, y, L"▀▀▀", black, white, false);
    RGBPrint(x +5, y, L"▄                                             ▄", black, default_white, false);
    RGBPrint(x + 52, y, L"▀▀▀", black, white, false);
    RGBPrint(x + 55, y, L"▄", black, default_white, false);
    //
    RGBPrint(x, y+1, L"█", black, default_white, false);
    RGBPrint(x+1, y + 1, L" ▄█▄ ", light_pink, white, false);
    RGBPrint(x+1+5, y + 1, L"█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█", black, default_white, false);
    RGBPrint(x + 1 + 5+45, y + 1, L" ▄█▄ ", light_pink, white, false);
    RGBPrint(x + 1 + 5 + 45+5, y + 1, L"█", black, default_white, false);
    //
    RGBPrint(x, y + 2,          L"▀", black, default_white, false);
    RGBPrint(x+1, y + 2,        L"▄ ▀ ▄", black, white, false);
    RGBPrint(x + 1+2, y + 2,    L"▀", light_pink, white, false);

    RGBPrint(x + 1+5, y + 2, L"▀", black, light_pink, false);
    RGBPrint(x + 1 + 5+1, y + 2, L"▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀", white_pink, light_pink, false);
    RGBPrint(x + 1 + 5+1+43, y + 2, L"▀", black, light_pink, false);
    RGBPrint(x + 1+5+1+43+1, y + 2, L"▄ ▀ ▄▀", black, white, false);
    RGBPrint(x + 1 + 5 + 1 + 43 + 1+5, y + 2, L"▀", black, default_white, false);
    RGBPrint(x + 1 + 5 + 1 + 43 + 1+2, y + 2, L"▀", light_pink, white, false);
    //
    RGBPrint(x + 2, y + 3, L"▀█                                                 █▀", black, default_white, false);
    RGBPrint(x + 4, y + 3, L"▀                                               ▀", black, light_pink, false);
    //
    for (int i = 0; i < lines; i++) {
        RGBPrint(x+3, y + 4 + i, L"█                                                 █", black, light_pink, false);
    }
    //
    RGBPrint(x, y + 4 + lines, L" ▄", black, default_white, false);
    RGBPrint(x + 2, y + 4 + lines, L"▀▀▀", black, white, false);
    RGBPrint(x + 5, y + 4 + lines, L"▄                                             ▄", black, light_pink, false);
    RGBPrint(x + 52, y + 4 + lines, L"▀▀▀", black, white, false);
    RGBPrint(x + 55, y + 4 + lines, L"▄", black, default_white, false);
    //
    RGBPrint(x, y + 4 + lines + 1, L"█", black, default_white, false);
    RGBPrint(x + 1, y + 4 + lines + 1, L" ▄█▄ ", light_pink, white, false);
    RGBPrint(x + 1 + 5, y + 4 + lines + 1, L"█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█", black, pink, false);
    RGBPrint(x + 1 + 5 + 45, y + 4 + lines + 1, L" ▄█▄ ", light_pink, white, false);
    RGBPrint(x + 1 + 5 + 45 + 5, y + 4 + lines + 1, L"█", black, default_white, false);
    //
    RGBPrint(x,y+4+lines+1+1, L"▀▄ ▀ ▄▀                                           ▀▄ ▀ ▄▀", black, default_white, false);

    RGBPrint(x+3, y + 4 + lines + 1 + 1, L"▀", light_pink, default_white, false);
    RGBPrint(x+53, y + 4 + lines + 1 + 1, L"▀", light_pink, default_white, false);
    //
    RGBPrint(x + 2, y + 4 + lines + 1 + 1 + 1, L"▀▀▀                                               ▀▀▀", black, default_white, false);
}
void removePanel(int x, int y, int lines) {
    for (int i = 0; i < lines + 8; i++) {
        RGBPrint(x, y + i, L"                                                         ", 
            black, default_white, false);
    }
 }
void drawSlider(int x, int y, int length, int value) {
    RGBPrint(x, y, L"█", black, light_pink, false);
    for (int i = 1; i <= length; i++) {
        RGBPrint(x + i, y - 1, L"▄", black, light_pink, false);
        RGBPrint(x + i, y + 1, L"▀", black, light_pink, false);
        if (i <= value) {
            RGBPrint(x + i, y, L"█", { 250, 177, 247 }, {250, 177, 247}, false);
        }
        else {
            RGBPrint(x + i, y, L"▄", {250,227,250}, white_pink, false);
        }
    }

    RGBPrint(x+length+1, y, L"█", black, light_pink, false);
}
void drawDOT(int x, int y) {
    RGBPrint(x+1, y-1,  L"▄▄", black, light_pink, false);
    RGBPrint(x - 1, y, L"█  █", black, { 250, 177, 247 }, false);

    RGBPrint(x + 1, y, L"▄", { 250, 177, 247 }, white_pink, false);
    RGBPrint(x + 1, y + 1, L"▀▀", black, light_pink, false);
}
void drawCheckBox(int x, int y, RGB color) {
    RGBPrint(x, y - 1, L" ▄▄▄", black, light_pink, false);
    RGBPrint(x, y,     L"█ ▄ █", black, color, false);
    RGBPrint(x, y + 1, L"▀   ▀", black, light_pink, false);
    RGBPrint(x, y + 1, L" ▄▄▄ ", black, color, false);
}