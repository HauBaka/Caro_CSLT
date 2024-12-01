#include "ModelUtils.h"
#include "terminalUtils.h"
//RGB pink = { 255,89,199 }, white_pink = { 255,217,254 }, light_pink = { 255,129,216 }, black = { 0,0,0 }, white = { 255,255,255 }, default_white = { 242,242,242 };
RGB pink = { 132,179,241 }, white_pink = { 224,237,250 }, light_pink = { 174,211,248 }, black = { 0,0,0 }, white = { 255,255,255 }, default_white = { 242,242,242 };
void RGBPrint(int x, int y, wstring text, RGB textColor, RGB bgColor, bool fromFile) {
    GotoXY(x, y);
    int OldMode;
    UINT oldcp;
    if (fromFile) {
        oldcp = GetConsoleOutputCP();
        SetConsoleOutputCP(CP_UTF8);
    } else {
        OldMode = _setmode(_fileno(stdout), _O_WTEXT);
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    }
    wcout << "\x1b[38;2;" << textColor.R << ";" << textColor.G << ";" << textColor.B << "m";//text color
    wcout << "\x1b[48;2;" << bgColor.R << ";" << bgColor.G << ";" << bgColor.B << "m";//bg color
    wcout << text;
    if (fromFile) SetConsoleCP(oldcp);
    if (!fromFile) _setmode(_fileno(stdout), OldMode);
    
}
void RGBPrint(int x, int y, string text, RGB textColor, RGB bgColor) {
    GotoXY(x, y);
    cout << "\x1b[38;2;" << textColor.R << ";" << textColor.G << ";" << textColor.B << "m";//text color
    cout << "\x1b[48;2;" << bgColor.R << ";" << bgColor.G << ";" << bgColor.B << "m";//bg color
    cout << text;
    cout << "\x1b[0m";
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
    RGBPrint(x, y,     L" ██████╗ █████╗ ██████╗  ██████╗      ██████╗  █████╗ ███╗   ███╗███████╗", black, white_pink, false);
    RGBPrint(x, y + 1, L"██╔════╝██╔══██╗██╔══██╗██╔═══██╗    ██╔════╝ ██╔══██╗████╗ ████║██╔════╝", black, white_pink, false);
    RGBPrint(x, y + 2, L"██║     ███████║██████╔╝██║   ██║    ██║  ███╗███████║██╔████╔██║█████╗  ", black, white_pink, false);
    RGBPrint(x, y + 3, L"██║     ██╔══██║██╔══██╗██║   ██║    ██║   ██║██╔══██║██║╚██╔╝██║██╔══╝  ", black, white_pink, false);
    RGBPrint(x, y + 4, L"╚██████╗██║  ██║██║  ██║╚██████╔╝    ╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗", black, white_pink, false);
    RGBPrint(x, y + 5, L" ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝      ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝", black, white_pink, false);
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

void drawPlayer(bool player, bool border, int x, int y, RGB  color, RGB bgcolor) {
    if (player) {//turn x
        if (border) {
            RGBPrint(x, y,     L"██╗  ██╗", color, bgcolor, false);
            RGBPrint(x, y + 1, L"╚██╗██╔╝", color, bgcolor, false);
            RGBPrint(x, y + 2, L" ╚███╔╝ ", color, bgcolor, false);
            RGBPrint(x, y + 3, L" ██╔██╗ ", color, bgcolor, false);
            RGBPrint(x, y + 4, L"██╔╝ ██╗", color, bgcolor, false);
            RGBPrint(x, y + 5, L"╚═╝  ╚═╝", color, bgcolor, false);
        }
        else {
            y--;
            RGBPrint(x, y + 1, L" ██   ██ ", color, bgcolor, false);
            RGBPrint(x, y + 2, L"  ██ ██  ", color, bgcolor, false);
            RGBPrint(x, y + 3, L"   ███   ", color, bgcolor, false);
            RGBPrint(x, y + 4, L"  ██ ██  ", color, bgcolor, false);
            RGBPrint(x, y + 5, L" ██   ██ ", color, bgcolor, false);
            RGBPrint(x, y + 6, L"         ", color, bgcolor, false);
        }
    }
    else {
        if (border) {
            RGBPrint(x, y,     L" ██████╗ ", color, bgcolor, false);
            RGBPrint(x, y + 1, L"██╔═══██╗", color, bgcolor, false);
            RGBPrint(x, y + 2, L"██║   ██║", color, bgcolor, false);
            RGBPrint(x, y + 3, L"██║   ██║", color, bgcolor, false);
            RGBPrint(x, y + 4, L"╚██████╔╝", color, bgcolor, false);
            RGBPrint(x, y + 5, L" ╚═════╝ ", color, bgcolor, false);
        }
        else {
            y--;
            RGBPrint(x, y + 1, L"  ██████  ", color, bgcolor, false);
            RGBPrint(x, y + 2, L" ██    ██ ", color, bgcolor, false);
            RGBPrint(x, y + 3, L" ██    ██ ", color, bgcolor, false);
            RGBPrint(x, y + 4, L" ██    ██ ", color, bgcolor, false);
            RGBPrint(x, y + 5, L"  ██████  ", color, bgcolor, false);
            RGBPrint(x, y + 6, L"          ", color, bgcolor, false);
        }
    }
}
void drawTurn(bool turn, int x, int y, RGB text_color1, RGB text_color2, RGB background_color) {
    if (turn) {//x
        drawPlayer(true, true, x+6, y+1, text_color2, background_color);//x
        drawPlayer(false, false, x+18, y + 1, text_color1, background_color);//o
    }
    else {
        drawPlayer(true, false, x+6, y+1, text_color1, background_color);//x
        drawPlayer(false, true, x+18, y + 1, text_color2, background_color);//o
    }
}
void drawGameBoard(int x, int y, int length, int width, RGB border_color, RGB background_color) {
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            if (i == 0 && j == 0) RGBPrint(x + i, y + j, L"╔",border_color, background_color, false);
            else if (i == 0 && j == width - 1) RGBPrint(x + i, y + j, L"╚", border_color, background_color, false);
            else if (i == length - 1 && j == 0)  RGBPrint(x + i, y + j, L"╗", border_color, background_color, false);
            else if (i == length - 1 && j == width - 1)  RGBPrint(x + i, y + j, L"╝", border_color, background_color, false);
            else if ((i == 0 or i == length - 1) && (j != 0 && j != width - 1))  RGBPrint(x + i, y + j, L"║", border_color, background_color, false);
            else if ((i != 0 && i != length - 1) && (j == 0 or j == width - 1))   RGBPrint(x + i, y + j, L"═", border_color, background_color, false);
            else {
                if ((j % 2 == 1 && i % 4 == 1)) RGBPrint(x + i, y + j, L"   │", border_color, background_color, false);
                if (j % 2 == 0 && i % 4 == 1) RGBPrint(x + i, y + j, L"───┼", border_color, background_color, false);
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
void drawMainMenuButton(int x, int y) {
    // ▄▀▀▀▀▀█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▄
    //█ ▄█▄█▄ █                               █
    //█  ▀█▀  █                               █
    // ▀▄▄▄▄▄█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▀
    RGBPrint(x + 1, y, L"▄", black, white_pink, false);
    RGBPrint(x + 2, y, L"▀▀▀▀▀█", black, white, false);
    RGBPrint(x + 1 + 7, y, L"▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀", black, white_pink, false);
    RGBPrint(x + 1 + 7 + 31, y, L"▄", black, white_pink, false);
    //
    printColoredText(x, y + 1, L"█", 0, 15);
    RGBPrint(x + 1, y + 1, L" ▄█▄█▄ ", pink, white, false);
    printColoredText(x + 1 + 7, y + 1, L"█ ", 0, 15);
    RGBPrint(x + 1 + 7 + 1, y + 1, L"                               ", white, light_pink, false);
    printColoredText(x + 1 + 7 + 1 + 30 + 1, y + 1, L"█", 0, 15);
    //
    printColoredText(x, y + 2, L"█", 0, 15);
    RGBPrint(x + 1, y + 2, L"  ▀█▀  ", pink, white, false);
    printColoredText(x + 1 + 7, y + 2, L"█", 0, 15);
    RGBPrint(x + 1 + 7 + 1, y + 2, L"                               ", white, light_pink, false);
    printColoredText(x + 1 + 7 + 1 + 31, y + 2, L"█", 0, 15);
    //
    RGBPrint(x + 1, y + 3, L"▀", black, white_pink, false);
    RGBPrint(x + 2, y + 3, L"▄▄▄▄▄█", black, white, false);
    RGBPrint(x + 1 + 7, y + 3, L"▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄", black, pink, false);
    RGBPrint(x + 1 + 7 + 31, y + 3, L"▀", black, white_pink, false);
}
void drawMainMenu_Play(int x, int y) {
    drawMainMenuButton(x, y);
    RGBPrint(x+1+7+1, y+1, L"     █▀▄ █   ▄▀▄ ▀▄▀           ", white, light_pink, false);
    RGBPrint(x+1+7+1, y+2, L"     █▀  █▄▄ █▀█  █            ", white, light_pink, false);
}
void drawMainMenu_Options(int x, int y) {
    drawMainMenuButton(x, y);
    RGBPrint(x + 1 + 7 + 1, y + 1, L"  ▄▀▄ █▀▄ ▀█▀ ▀ ▄▀▄ █▄ █ ▄▀    ", white, light_pink, false);
    RGBPrint(x + 1 + 7 + 1, y + 2, L"  ▀▄▀ █▀   █  █ ▀▄▀ █ ▀█ ▄▀    ", white, light_pink, false);
}
void drawMainMenu_Authors(int x, int y) {
    drawMainMenuButton(x, y);
    RGBPrint(x + 1 + 7 + 1, y + 1, L"  ▄▀▄ █ █ ▀█▀ █ █ ▄▀▄ █▀▄ ▄▀   ", white, light_pink, false);
    RGBPrint(x + 1 + 7 + 1, y + 2, L"  █▀█ ▀▄▀  █  █▀█ ▀▄▀ █▀▄ ▄▀   ", white, light_pink, false);
}
void drawMainMenu_Out(int x, int y) {
// ▄▀▀▀▀▀█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▄
//█ ▄█▄█▄ █        ▄▀▄ █ █ ▀█▀            █
//█  ▀█▀  █        ▀▄▀ ▀▄▀  █             █
// ▀▄▄▄▄▄█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▀
    drawMainMenuButton(x, y);
    RGBPrint(x + 1 + 7 + 1, y + 1, L"        ▄▀▄ █ █ ▀█▀            ", white, light_pink, false);
    RGBPrint(x + 1 + 7 + 1, y + 2, L"        ▀▄▀ ▀▄▀  █             ", white, light_pink, false);
}
void drawTriagle(int x, int y, bool show) {
    if (show) {
        RGBPrint(x, y, L"  ▄", black, white_pink, false);
        RGBPrint(x, y + 1, L"▄██", black, white_pink, false);
        RGBPrint(x, y + 2, L" ▀█", black, white_pink, false);
    }
    else {
        RGBPrint(x, y, L"   ", black, white_pink, false);;
        RGBPrint(x, y + 1, L"   ", black, white_pink, false);
        RGBPrint(x, y + 2, L"   ", black, white_pink, false);
    }

}

void drawPanel(int x, int y, int lines) {//52 in length
// ▄▀▀▀▄                                             ▄▀▀▀▄
//█ ▄█▄ █▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█ ▄█▄ █
//▀▄ ▀ ▄▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▄ ▀ ▄▀
//  ▀█▀                                               ▀█▀
//   █                                                 █
// ▄▀▀▀▄                                             ▄▀▀▀▄
//█ ▄█▄ █▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█ ▄█▄ █
//▀▄ ▀ ▄▀                                           ▀▄ ▀ ▄▀
//  ▀▀▀                                               ▀▀▀
    RGBPrint(x, y, L" ▄", black, white_pink, false);
    RGBPrint(x+2, y, L"▀▀▀", black, white, false);
    RGBPrint(x +5, y, L"▄                                             ▄", black, white_pink, false);
    RGBPrint(x + 52, y, L"▀▀▀", black, white, false);
    RGBPrint(x + 55, y, L"▄", black, white_pink, false);
    //
    RGBPrint(x, y+1, L"█", black, white_pink, false);
    RGBPrint(x+1, y + 1, L" ▄█▄ ", light_pink, white, false);
    RGBPrint(x+1+5, y + 1, L"█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█", black, white_pink, false);
    RGBPrint(x + 1 + 5+45, y + 1, L" ▄█▄ ", light_pink, white, false);
    RGBPrint(x + 1 + 5 + 45+5, y + 1, L"█", black, white_pink, false);
    //
    RGBPrint(x, y + 2,          L"▀", black, white_pink, false);
    RGBPrint(x+1, y + 2,        L"▄ ▀ ▄", black, white, false);
    RGBPrint(x + 1+2, y + 2,    L"▀", light_pink, white, false);

    RGBPrint(x + 1+5, y + 2, L"▀", black, light_pink, false);
    RGBPrint(x + 1 + 5+1, y + 2, L"▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀", white_pink, light_pink, false);
    RGBPrint(x + 1 + 5+1+43, y + 2, L"▀", black, light_pink, false);
    RGBPrint(x + 1+5+1+43+1, y + 2, L"▄ ▀ ▄▀", black, white, false);
    RGBPrint(x + 1 + 5 + 1 + 43 + 1+5, y + 2, L"▀", black, white_pink, false);
    RGBPrint(x + 1 + 5 + 1 + 43 + 1+2, y + 2, L"▀", light_pink, white, false);
    //
    RGBPrint(x + 2, y + 3, L"▀█                                                 █▀", black, white_pink, false);
    RGBPrint(x + 4, y + 3, L"▀                                               ▀", black, light_pink, false);
    //
    for (int i = 0; i < lines; i++) {
        RGBPrint(x+3, y + 4 + i, L"█                                                 █", black, light_pink, false);
    }
    //
    RGBPrint(x, y + 4 + lines, L" ▄", black, white_pink, false);
    RGBPrint(x + 2, y + 4 + lines, L"▀▀▀", black, white, false);
    RGBPrint(x + 5, y + 4 + lines, L"▄                                             ▄", black, light_pink, false);
    RGBPrint(x + 52, y + 4 + lines, L"▀▀▀", black, white, false);
    RGBPrint(x + 55, y + 4 + lines, L"▄", black, white_pink, false);
    //
    RGBPrint(x, y + 4 + lines + 1, L"█", black, white_pink, false);
    RGBPrint(x + 1, y + 4 + lines + 1, L" ▄█▄ ", light_pink, white, false);
    RGBPrint(x + 1 + 5, y + 4 + lines + 1, L"█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█", black, pink, false);
    RGBPrint(x + 1 + 5 + 45, y + 4 + lines + 1, L" ▄█▄ ", light_pink, white, false);
    RGBPrint(x + 1 + 5 + 45 + 5, y + 4 + lines + 1, L"█", black, white_pink, false);
    //
    RGBPrint(x,y+4+lines+1+1, L"▀▄ ▀ ▄▀                                           ▀▄ ▀ ▄▀", black, white_pink, false);

    RGBPrint(x+3, y + 4 + lines + 1 + 1, L"▀", light_pink, white_pink, false);
    RGBPrint(x+53, y + 4 + lines + 1 + 1, L"▀", light_pink, white_pink, false);
    //
    RGBPrint(x + 2, y + 4 + lines + 1 + 1 + 1, L"▀▀▀                                               ▀▀▀", black, white_pink, false);
}
void removePanel(int x, int y, int lines) {
    for (int i = 0; i < lines + 8; i++) {
        RGBPrint(x, y + i, L"                                                         ", 
            black, white_pink, false);
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
    RGBPrint(x+1, y + 1, L"▄▄▄", black, color, false);
}

void fill(RGB color) {
    for (int i = 0; i < 42; i++) RGBPrint(0, i, L"                                                                                                                                                                             ", color, color, false);
}

void drawInGameHeader(int x, int y) {
    wstring lines[] =
    {
    L"▄          ▄          ▄          ▄          ▄          ▄          ▄          ▄          ▄          ▄          ▄          ▄          ▄          ▄          ▄          ▄",
    L"",
    L"     ▄▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▄",
    L"   ▄▀                                                                                                                                                            ▀▄     ",
    L"   █                                                                                                                                                              █",
    L"   █                                                                                                                                                              █",
    L"▀  █                                                                                                                                                              █  ▀",
    L"   █                                                                                                                                                              █",
    L"   █                                                                                                                                                              █",
    L"   █                                                                                                                                                              █",
    L"   █                                                                                                                                                              █",
    L"▄  █                                                                                                                                                              █  ▄",
    L"   █                                                                                                                                                              █",
    L"   █                                                                                                                                                              █",
    L"   █                                                                                                                                                              █",
    L"   █                                                                                                                                                              █",
    L"   █                                                                                                                                                              █",
    L"▀  █                                                                                                                                                              █  ▀",
    L"   █                                                                                                                                                              █",
    L"   █                                                                                                                                                              █",
    L"   █                                                                                                                                                              █",
    L"   █                                                                                                                                                              █",
    L"▄  █                                                                                                                                                              █  ▄",
    L"   █                                                                                                                                                              █",
    L"   █                                                                                                                                                              █",
    L"   █                                                                                                                                                              █",
    L"   █                                                                                                                                                              █",
    L"   █                                                                                                                                                              █",
    L"▀  █                                                                                                                                                              █  ▀",
    L"   █                                                                                                                                                              █",
    L"   █                                                                                                                                                              █",
    L"   █                                                                                                                                                              █",
    L"   █                                                                                                                                                              █",
    L"▄  █                                                                                                                                                              █  ▄",
    L"   █                                                                                                                                                              █",
    L"   █                                                                                                                                                              █",
    L"   ▀▄                                                                                                                                                            ▄▀",
    L"     ▀▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▀",
    L"",
    L"▀          ▀          ▀          ▀          ▀          ▀          ▀          ▀          ▀          ▀          ▀          ▀          ▀          ▀          ▀          ▀" 
    };
    for (int i = 0; i < sizeof(lines) / sizeof(wstring); i++) RGBPrint(x, y + i, lines[i], white, white_pink, false);
}
void drawInGamePanel_1(int x, int y, RGB border_color,RGB background_color, RGB dot_color, RGB outside_color) {
    //line 1
    RGBPrint(x, y, L" ▄", border_color, outside_color, false);
    RGBPrint(x + 2, y, L"▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀", border_color, background_color, false);
    RGBPrint(x + 2 + 39, y, L"▄ ", border_color, outside_color, false);
    //line n
    for (int i = 0; i < 9; i++) RGBPrint(x, y + i + 1, L"█                                         █", border_color, background_color, false);
    //line n+1
    RGBPrint(x, y + 9, L" ▀▄                                     ▄▀ ", border_color, outside_color, false);
    RGBPrint(x+2, y + 9, L"▄                                     ▄", border_color, background_color, false);
    //last line
    RGBPrint(x, y + 10, L"   ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀   ", border_color, outside_color, false);
    RGBPrint(x+3, y + 10, L"▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀", border_color, {220,220,220}, false);
    //draw dot
    RGBPrint(x + 3, y + 1, L"▄", dot_color, background_color, false);
    RGBPrint(x + 39, y + 1, L"▄", dot_color, background_color, false);
    RGBPrint(x + 3, y + 8, L"▄", dot_color, background_color, false);
    RGBPrint(x + 39, y + 8, L"▄", dot_color, background_color, false);
}
void drawInGamePanel_2(int x, int y, RGB border_color, RGB background_color, RGB dot_color, RGB outside_color) {
    //line 1
    RGBPrint(x, y, L" ▄", border_color, outside_color, false);
    RGBPrint(x + 2, y, L"▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀", border_color, background_color, false);
    RGBPrint(x + 2 + 24, y, L"▄ ", border_color, outside_color, false);
    //line n
    for (int i = 0; i < 12; i++) RGBPrint(x, y + i + 1, L"█                          █", border_color, background_color, false);
    //line n+1
    RGBPrint(x, y + 13, L" ▀▄                      ▄▀ ", border_color, outside_color, false);
    RGBPrint(x + 2, y + 13, L"▄                      ▄", border_color, background_color, false);
    //last line
    RGBPrint(x, y + 14, L"   ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀   ", border_color, outside_color, false);
    RGBPrint(x + 3, y + 14, L"▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀", border_color, { 220,220,220 }, false);
    //draw dot
    RGBPrint(x + 3, y + 1, L"▄", dot_color, background_color, false);
    RGBPrint(x + 24, y + 1, L"▄", dot_color, background_color, false);
    RGBPrint(x + 3, y + 12, L"▄", dot_color, background_color, false);
    RGBPrint(x + 24, y + 12, L"▄", dot_color, background_color, false);
    //draw inside border
    for (int i = 0; i < 11; i++) {
        if (i % 2 == 0) RGBPrint(x+4, y + 1 + i, L"          ║          ", border_color, background_color, false);
        else RGBPrint(x+4, y + 1 + i, L"══════════╬══════════", border_color, background_color, false);
    }
    RGBPrint(x + 4, y + 12, L"══════════╩══════════", border_color, background_color, false);
}
void drawInGamePanel_3(int x, int y, RGB border_color, RGB background_color, RGB dot_color, RGB outside_color) {
    //line 1
    RGBPrint(x, y, L" ▄", border_color, outside_color, false);
    RGBPrint(x + 2, y, L"▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀", border_color, background_color, false);
    RGBPrint(x + 2 + 29, y, L"▄ ", border_color, outside_color, false);
    //line n
    for (int i = 0; i < 5; i++) {
        RGBPrint(x, y + i + 1, L"█                               █", border_color, background_color, false);
        RGBPrint(x+16, y + i + 1, L"║", border_color, background_color, false);
    }
    //line n+1
    RGBPrint(x, y + 6, L" ▀▄                           ▄▀ ", border_color, outside_color, false);
    RGBPrint(x + 2, y + 6, L"▄                           ▄", border_color, background_color, false);
    //last line
    RGBPrint(x, y + 7, L"   ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀   ", border_color, outside_color, false);
    RGBPrint(x + 3, y + 7, L"▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀", border_color, { 220,220,220 }, false);
    //draw dot
    RGBPrint(x + 3, y + 1, L"▄", dot_color, background_color, false);
    RGBPrint(x + 29, y + 1, L"▄", dot_color, background_color, false);
    RGBPrint(x + 3, y + 5, L"▄", dot_color, background_color, false);
    RGBPrint(x + 29, y + 5, L"▄", dot_color, background_color, false);
}
void drawInGamePanel_4(int x, int y, RGB border_color, RGB background_color, RGB dot_color, RGB outside_color) {
    //line 1
    RGBPrint(x, y, L" ▄", border_color, outside_color, false);
    RGBPrint(x + 2, y, L"▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀", border_color, background_color, false);
    RGBPrint(x + 2 + 31, y, L"▄ ", border_color, outside_color, false);
    //line n
    for (int i = 0; i < 9; i++) RGBPrint(x, y + i + 1, L"█                                 █", border_color, background_color, false);
    //line n+1
    RGBPrint(x, y + 10, L" ▀▄                             ▄▀ ", border_color, outside_color, false);
    RGBPrint(x + 2, y + 10, L"▄                             ▄", border_color, background_color, false);
    //last line
    RGBPrint(x, y + 11, L"   ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀   ", border_color, outside_color, false);
    RGBPrint(x + 3, y + 11, L"▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀", border_color, { 220,220,220 }, false);
    //draw dot
    RGBPrint(x + 3, y + 1, L"▄", dot_color, background_color, false);
    RGBPrint(x + 31, y + 1, L"▄", dot_color, background_color, false);
    RGBPrint(x + 3, y + 9, L"▄", dot_color, background_color, false);
    RGBPrint(x + 31, y + 9, L"▄", dot_color, background_color, false);
}
void drawKeyCap(int x, int y, bool type, RGB color, RGB background_color) {
    if (type) { //vertical
        RGBPrint(x, y,   L"▄█▀▀▀▀▀█▄", color, background_color, false);
        RGBPrint(x, y+1, L"█       █", color, background_color, false);
        RGBPrint(x, y+2, L"█       █", color, background_color, false);
        RGBPrint(x, y+3, L"▀█▄▄▄▄▄█▀", color, background_color, false);
    }
    else {//horizontal
        RGBPrint(x, y,     L"▄█▀▀▀▀█▄", color, background_color, false);
        RGBPrint(x, y + 1, L"█      █", color, background_color, false);
        RGBPrint(x, y + 2, L"█      █", color, background_color, false);
        RGBPrint(x, y + 3, L"█▄    ▄█", color, background_color, false);
        RGBPrint(x, y + 4, L" ▀▀▀▀▀▀", color, background_color, false);
    }
}
void drawInGameKeyboard(int x, int y, char key, bool status, RGB on_color, RGB off_color) {
    switch (key) {
    case 'w':case 's':
        drawKeyCap(x, y, true, on_color, off_color);
        break;
    case 'a':case'd':
        drawKeyCap(x, y, false, on_color, off_color);
        break;
    }
    if (status) on_color = off_color;
    switch (key) {
    case 'w':
        RGBPrint(x + 3, y + 1, L"▄█▄", on_color, off_color, false);
        RGBPrint(x + 2, y + 2, L"▀▀▀▀▀", on_color, off_color, false);
        break;
    case 'a':
        RGBPrint(x + 3, y + 1, L"▄█", on_color, off_color, false);
        RGBPrint(x + 2, y + 2, L"▀██", on_color, off_color, false);
        RGBPrint(x + 4, y + 3, L"▀", on_color, off_color, false);
        break;
    case 's':
        RGBPrint(x + 2, y + 1, L"▄▄▄▄▄", on_color, off_color, false);
        RGBPrint(x + 3, y + 2, L"▀█▀", on_color, off_color, false);
        break;
    case 'd':
        RGBPrint(x + 3, y + 1, L"█▄", on_color, off_color, false);
        RGBPrint(x + 3, y + 2, L"██▀", on_color, off_color, false);
        RGBPrint(x + 3, y + 3, L"▀", on_color, off_color, false);
        break;
    }
}
void drawMiniPopUp(int x, int y, RGB border_color, RGB background_color, RGB dot_color, RGB outside_color) {
    //line 1
    RGBPrint(x, y, L" ▄", border_color, outside_color, false);
    RGBPrint(x + 2, y, L"▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀", border_color, background_color, false);
    RGBPrint(x + 2 + 29, y, L"▄ ", border_color, outside_color, false);
    //line n
    for (int i = 0; i < 5; i++) {
        RGBPrint(x, y + i + 1, L"█                               █", border_color, background_color, false);
    }
    //line n+1
    RGBPrint(x, y + 6, L" ▀▄                           ▄▀ ", border_color, outside_color, false);
    RGBPrint(x + 2, y + 6, L"▄                           ▄", border_color, background_color, false);
    //last line
    RGBPrint(x, y + 7, L"   ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀   ", border_color, outside_color, false);
    RGBPrint(x + 3, y + 7, L"▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀", border_color, { 220,220,220 }, false);
    //draw dot
    RGBPrint(x + 3, y + 1, L"▄", dot_color, background_color, false);
    RGBPrint(x + 29, y + 1, L"▄", dot_color, background_color, false);
    RGBPrint(x + 3, y + 5, L"▄", dot_color, background_color, false);
    RGBPrint(x + 29, y + 5, L"▄", dot_color, background_color, false);
}
void drawDrawText(int x, int y, RGB background_color) {
    RGB colors[16] = {
        {199,66,79}, 
        {224,107,81}, 
        {242,165,97}, 
        {242,165,97}, 
        {177,212,128}, 
        {128,184,120}, 
        {128,184,120}, 
        {137,217,217}, 
        {137,217,217}, 
        {92,139,168}, 
        {78,102,121}, 
        {70,73,105}, 
        {68,53,93}, 
        {61,0,61}, 
        {98,23,72}, 
        {148,44,75}
    };
    for (int i = 0; i < 16*3; i++) {
        RGBPrint(x, y,     L"·▄▄▄▄  ▄▄▄   ▄▄▄· ▄▄▌ ▐ ▄▌▄▄ ", colors[i%16], background_color, false);
        RGBPrint(x, y + 1, L"██▪ ██ ▀▄ █·▐█ ▀█ ██· █▌▐███▌", colors[i % 16], background_color, false);
        RGBPrint(x, y + 2, L"▐█· ▐█▌▐▀▀▄ ▄█▀▀█ ██▪▐█▐▐▌▐█·", colors[i % 16], background_color, false);
        RGBPrint(x, y + 3, L"██. ██ ▐█•█▌▐█ ▪▐▌▐█▌██▐█▌.▀ ", colors[i % 16], background_color, false);
        RGBPrint(x, y + 4, L"▀▀▀▀▀• .▀  ▀ ▀  ▀  ▀▀▀▀ ▀▪ ▀ ", colors[i % 16], background_color, false);
        Sleep(100);//0.1s mỗi màu
    }
}
void drawPauseText(int x, int y, RGB background_color) {
    int i = 0;
    RGB colors[16] = {
        {199,66,79},
        {224,107,81},
        {242,165,97},
        {242,165,97},
        {177,212,128},
        {128,184,120},
        {128,184,120},
        {137,217,217},
        {137,217,217},
        {92,139,168},
        {78,102,121},
        {70,73,105},
        {68,53,93},
        {61,0,61},
        {98,23,72},
        {148,44,75}
    };
    while (true) {
        i++;
        //vẽ
        RGBPrint(x, y,     L" ▄▄▄· ▄▄▄· ▄• ▄▌.▄▄ · ▄▄▄ .·▄▄▄▄  ", colors[i % 16], background_color, false);
        RGBPrint(x, y + 1, L"▐█ ▄█▐█ ▀█ █▪██▌▐█ ▀. ▀▄.▀·██▪ ██ ", colors[i % 16], background_color, false);
        RGBPrint(x, y + 2, L" ██▀·▄█▀▀█ █▌▐█▌▄▀▀▀█▄▐▀▀▪▄▐█· ▐█▌", colors[i % 16], background_color, false);
        RGBPrint(x, y + 3, L"▐█▪·•▐█ ▪▐▌▐█▄█▌▐█▄▪▐█▐█▄▄▌██. ██ ", colors[i % 16], background_color, false);
        RGBPrint(x, y + 4, L".▀    ▀  ▀  ▀▀▀  ▀▀▀▀  ▀▀▀ ▀▀▀▀▀• ", colors[i % 16], background_color, false);
        Sleep(200);//0.1s mỗi màu
        //xử lí
        if (_kbhit()) {
            int n = tolower(_getch());
            if (n == 'p') break;
        }
    }
}

void drawPineTree(int x, int y, RGB background_color, int size) {
    if (size == 1) {
        //  ▄█▄
        // ▄▄█▄▄
        // ▄▄█▄▄
        //▀▀▀█▀▀▀
        //   █
        RGB leaves_color = { 102,138,153 }, tree_body = { 101,17,33 };
        RGBPrint(x, y, L"  ▄█▄", leaves_color, background_color, false);
        //
        RGBPrint(x, y + 1, L" ▄▄█▄▄", leaves_color, background_color, false);
        RGBPrint(x + 3, y + 1, L"▀", tree_body, leaves_color, false);
        //
        RGBPrint(x, y + 2, L" ▄▄█▄▄", leaves_color, background_color, false);
        RGBPrint(x + 3, y + 2, L"▀", tree_body, leaves_color, false);
        //
        RGBPrint(x, y + 3, L"▀▀▀█▀▀▀", leaves_color, background_color, false);
        RGBPrint(x + 3, y + 3, L"▀", leaves_color, tree_body, false);
        //
        RGBPrint(x, y + 4, L"   █", tree_body, background_color, false);
    }
    else if (size == 2) {

    }
}
void drawSnowFlake(int x, int y, RGB background_color) {
    RGBPrint(x, y,   L"    ▄", default_white, background_color, false);
    RGBPrint(x, y+1, L" ▀▄ ▀ ▄▀", default_white, background_color, false);
    RGBPrint(x, y+2, L"▄▄ ▀ ▀ ▄▄", default_white, background_color, false);
    RGBPrint(x, y+3, L"  ▄▀ ▀▄", default_white, background_color, false);
    RGBPrint(x, y+4, L" ▀  █  ▀", default_white, background_color, false);
}
