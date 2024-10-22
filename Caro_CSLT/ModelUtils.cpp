#include "ModelUtils.h"
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
    printColoredText(x, y, L" ██████╗ █████╗ ██████╗  ██████╗      ██████╗  █████╗ ███╗   ███╗███████╗", 1, 14);
    printColoredText(x, y + 1, L"██╔════╝██╔══██╗██╔══██╗██╔═══██╗    ██╔════╝ ██╔══██╗████╗ ████║██╔════╝", 1, 14);
    printColoredText(x, y + 2, L"██║     ███████║██████╔╝██║   ██║    ██║  ███╗███████║██╔████╔██║█████╗  ", 1, 14);
    printColoredText(x, y + 3, L"██║     ██╔══██║██╔══██╗██║   ██║    ██║   ██║██╔══██║██║╚██╔╝██║██╔══╝  ", 1, 14);
    printColoredText(x, y + 4, L"╚██████╗██║  ██║██║  ██║╚██████╔╝    ╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗", 1, 14);
    printColoredText(x, y + 5, L" ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝      ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝", 1, 14);
}
void veMay(int x, int y) {
    printColoredText(x - 1, y + 3, L" ", 3, 14);
    printColoredText(x - 1, y + 4, L" ", 3, 14);
    printColoredText(x - 1, y + 5, L" ", 3, 14);

    printColoredText(x, y, L"          ▄█▀▀", 0, 14);
    printColoredText(x + 14, y, L"▀▀", 0, 7);
    printColoredText(x + 16, y, L"█▄", 0, 14);
    //2
    printColoredText(x, y + 1, L"        ▄█▀     ", 0, 14);
    printColoredText(x + 15, y + 1, L"▀", 7, 14);
    printColoredText(x + 16, y + 1, L"▀", 7, 7);
    printColoredText(x + 17, y + 1, L"▀", 0, 7);
    printColoredText(x + 18, y + 1, L"█", 0, 14);
    //3
    printColoredText(x, y + 2, L"  ▄▄▄▄▄ █        ", 0, 14);
    printColoredText(x + 17, y + 2, L"▀", 7, 14);
    printColoredText(x + 18, y + 2, L"▀▄█▀▀", 0, 14);
    printColoredText(x + 18 + 5, y + 2, L"▀▀", 0, 7);
    printColoredText(x + 18 + 5 + 2, y + 2, L"█▄", 0, 14);
    //4
    printColoredText(x, y + 3, L"▄█▀  ", 0, 14);
    printColoredText(x + 5, y + 3, L"▀▀", 7, 14);
    printColoredText(x + 7, y + 3, L"██          ▀   ", 0, 14);
    printColoredText(x + 7 + 17, y + 3, L"▀▀", 7, 14);
    printColoredText(x + 7 + 17 + 2, y + 3, L"█", 0, 14);
    //5
    printColoredText(x, y + 4, L"█                         ▀▄", 0, 14);
    //6
    printColoredText(x, y + 5, L"▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀", 0, 14);
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
        drawPlayer(true, true, x, y, 1, 14);//x
        printColoredText(x + 1, y + 6, "TURN X", 1, 14);
        drawPlayer(false, false, x, y + 10, 9, 14);//o
    }
    else {
        drawPlayer(true, false, x, y, 9, 14);//x
        drawPlayer(false, true, x, y + 10, 1, 14);//o
        printColoredText(x + 1, y + 10 + 5 + 1, "TURN O", 1, 14);
    }
}
void drawGameBoard(int x, int y, int length, int width) {
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            if (i == 0 && j == 0) printColoredText(x + i, y + j, L"╔", 3, 14);
            else if (i == 0 && j == width - 1) printColoredText(x + i, y + j, L"╚", 3, 14);
            else if (i == length - 1 && j == 0)  printColoredText(x + i, y + j, L"╗", 3, 14);
            else if (i == length - 1 && j == width - 1)  printColoredText(x + i, y + j, L"╝", 3, 14);
            else if ((i == 0 or i == length - 1) && (j != 0 && j != width - 1))  printColoredText(x + i, y + j, L"║", 3, 14);
            else if ((i != 0 && i != length - 1) && (j == 0 or j == width - 1))   printColoredText(x + i, y + j, L"═", 3, 14);
            else {
                if ((j % 2 == 1 && i % 4 == 1)) printColoredText(x + i, y + j, L"   │", 3, 14);
                if (j % 2 == 0 && i % 4 == 1) printColoredText(x + i, y + j, L"───┼", 3, 14);
            }
        }
    }
}