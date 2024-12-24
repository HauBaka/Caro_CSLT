#include "ModelUtils.h"
#include "terminalUtils.h"
RGB aqua = { 132,179,241 }, white_aqua = { 224,237,250 }, light_aqua = { 174,211,248 }, black = { 0,0,0 }, white = { 255,255,255 }, default_white = { 242,242,242 };
RGB rainbows[16] = {
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
void drawSmallSantaHat(int x, int y) {
    RGB red = { 237,28,36 };
    RGBPrint(x + 2, y, L"▄▄█▀▀▀▀█▄", black, white_aqua, false);
    RGBPrint(x + 5, y, L"▀▀▀▀", black, red, false);
    //
    RGBPrint(x + 1, y+1, L"█▀  ▄    █▄", black, red, false);
    RGBPrint(x + 11, y+1, L"▄", black, white_aqua, false);
    //
    RGBPrint(x, y+2, L"▄█▄█▀█", black, white_aqua, false);
    RGBPrint(x+2, y+2, L"▄", black, red, false);
    RGBPrint(x+6, y+2, L"     █", black, red, false);
    //
    RGBPrint(x, y + 3, L"█▄█", black, white, false);
    RGBPrint(x+4, y + 3, L" ▀▀▀▀▀▀▀", black, white_aqua, false);

}

void drawLOGO(int x, int y) {
    const wstring logo[] = {
        L" ██████╗ █████╗ ██████╗  ██████╗      ██████╗  █████╗ ███╗   ███╗███████╗",
        L"██╔════╝██╔══██╗██╔══██╗██╔═══██╗    ██╔════╝ ██╔══██╗████╗ ████║██╔════╝",
        L"██║     ███████║██████╔╝██║   ██║    ██║  ███╗███████║██╔████╔██║█████╗  ",
        L"██║     ██╔══██║██╔══██╗██║   ██║    ██║   ██║██╔══██║██║╚██╔╝██║██╔══╝  ",
        L"╚██████╗██║  ██║██║  ██║╚██████╔╝    ╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗",
        L" ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝      ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝"
    };
    for (size_t i = 0; i < sizeof(logo) / sizeof(logo[0]); ++i) {
        RGBPrint(x, y + i, logo[i], black, white_aqua, false);
    }
    drawSmallSantaHat(x + 3, y - 3);
    drawSmallSantaHat(x + 41, y - 3);
    RGBPrint(x + 9, y + 0, L"█████", black, white_aqua, false);
    RGBPrint(x + 47, y + 0, L"█████", black, white_aqua, false);

}
void veMay(int x, int y) {
    RGBPrint(x - 1, y + 3, L" ", black, default_white, false);
    RGBPrint(x - 1, y + 4, L" ", black, default_white, false);
    RGBPrint(x - 1, y + 5, L" ", black, default_white, false);

    RGBPrint(x, y, L"          ▄█▀▀", black, white, false);
    RGBPrint(x + 14, y, L"▀▀", black, default_white, false);
    RGBPrint(x + 16, y, L"█▄", black, white, false);
    //2
    RGBPrint(x, y + 1, L"        ▄█▀     ", black, white, false);
    RGBPrint(x + 15, y + 1, L"▀", default_white, white, false);
    RGBPrint(x + 16, y + 1, L"▀", default_white, default_white, false);
    RGBPrint(x + 17, y + 1, L"▀", black, default_white, false);
    RGBPrint(x + 18, y + 1, L"█", black, white, false);
    //3
    RGBPrint(x, y + 2, L"  ▄▄▄▄▄ █        ", black, white, false);
    RGBPrint(x + 17, y + 2, L"▀", default_white, white, false);
    RGBPrint(x + 18, y + 2, L"▀▄█▀▀", black, white, false);
    RGBPrint(x + 18 + 5, y + 2, L"▀▀", black, default_white, false);
    RGBPrint(x + 18 + 5 + 2, y + 2, L"█▄", black, white, false);
    //4
    RGBPrint(x, y + 3, L"▄█▀  ", black, white, false);
    RGBPrint(x + 5, y + 3, L"▀▀", default_white, white, false);
    RGBPrint(x + 7, y + 3, L"██          ▀   ", black, white, false);
    RGBPrint(x + 7 + 17, y + 3, L"▀▀", default_white, white, false);
    RGBPrint(x + 7 + 17 + 2, y + 3, L"█", black, white, false);
    //5
    RGBPrint(x, y + 4, L"█                         ▀▄", black, white, false);
    //6
    RGBPrint(x, y + 5, L"▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀", black, white, false);
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
    for (int i = 0; i < 15; i++) {
        RGBPrint(0, 0, L"", black, white_aqua, true);
        GotoXY(x + 2+4*i, y - 1);
        cout << char('A'+i);
        GotoXY(x - 2, y + 1 + 2 * i);
        cout << i + 1;
    }
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
    updateFullBoard();
}
void drawMainMenuButton(int x, int y) {
    // ▄▀▀▀▀▀█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▄
    //█ ▄█▄█▄ █                               █
    //█  ▀█▀  █                               █
    // ▀▄▄▄▄▄█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▀
    RGBPrint(x + 1, y, L"▄", black, white_aqua, false);
    RGBPrint(x + 2, y, L"▀▀▀▀▀█", black, white, false);
    RGBPrint(x + 1 + 7, y, L"▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀", black, white_aqua, false);
    RGBPrint(x + 1 + 7 + 31, y, L"▄", black, white_aqua, false);
    //
    RGBPrint(x, y + 1, L"█", black, white, false);
    RGBPrint(x + 1, y + 1, L" ▄█▄█▄ ", aqua, white, false);
    RGBPrint(x + 1 + 7, y + 1, L"█ ", black, white, false);
    RGBPrint(x + 1 + 7 + 1, y + 1, L"                               ", white, light_aqua, false);
    RGBPrint(x + 1 + 7 + 1 + 30 + 1, y + 1, L"█", black, white, false);
    //
    RGBPrint(x, y + 2, L"█", black, white, false);
    RGBPrint(x + 1, y + 2, L"  ▀█▀  ", aqua, white, false);
    RGBPrint(x + 1 + 7, y + 2, L"█", black, white, false);
    RGBPrint(x + 1 + 7 + 1, y + 2, L"                               ", white, light_aqua, false);
    RGBPrint(x + 1 + 7 + 1 + 31, y + 2, L"█", black, white, false);
    //
    RGBPrint(x + 1, y + 3, L"▀", black, white_aqua, false);
    RGBPrint(x + 2, y + 3, L"▄▄▄▄▄█", black, white, false);
    RGBPrint(x + 1 + 7, y + 3, L"▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄", black, aqua, false);
    RGBPrint(x + 1 + 7 + 31, y + 3, L"▀", black, white_aqua, false);
}
void drawMainMenu_Play(int x, int y) {
    drawMainMenuButton(x, y);
    RGBPrint(x+1+7+1, y+1, L"     █▀▄ █   ▄▀▄ ▀▄▀           ", white, light_aqua, false);
    RGBPrint(x+1+7+1, y+2, L"     █▀  █▄▄ █▀█  █            ", white, light_aqua, false);
}
void drawMainMenu_Options(int x, int y) {
    drawMainMenuButton(x, y);
    RGBPrint(x + 1 + 7 + 1, y + 1, L"  ▄▀▄ █▀▄ ▀█▀ ▀ ▄▀▄ █▄ █ ▄▀    ", white, light_aqua, false);
    RGBPrint(x + 1 + 7 + 1, y + 2, L"  ▀▄▀ █▀   █  █ ▀▄▀ █ ▀█ ▄▀    ", white, light_aqua, false);
}
void drawMainMenu_Help(int x, int y) {
    drawMainMenuButton(x, y);
    RGBPrint(x + 1 + 7 + 1, y + 1, L" ▀█▀ █ █ ▀█▀ ▄▀▄ █▀▄ ▀ ▄▀▄ █   ", white, light_aqua, false);
    RGBPrint(x + 1 + 7 + 1, y + 2, L"  █  ▀▄▀  █  ▀▄▀ █▀▄ █ █▀█ █▄▄ ", white, light_aqua, false);
}
void drawMainMenu_Authors(int x, int y) {
    drawMainMenuButton(x, y);
    RGBPrint(x + 1 + 7 + 1, y + 1, L"  ▄▀▄ █ █ ▀█▀ █ █ ▄▀▄ █▀▄ ▄▀   ", white, light_aqua, false);
    RGBPrint(x + 1 + 7 + 1, y + 2, L"  █▀█ ▀▄▀  █  █▀█ ▀▄▀ █▀▄ ▄▀   ", white, light_aqua, false);
}
void drawMainMenu_Out(int x, int y) {
// ▄▀▀▀▀▀█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▄
//█ ▄█▄█▄ █        ▄▀▄ █ █ ▀█▀            █
//█  ▀█▀  █        ▀▄▀ ▀▄▀  █             █
// ▀▄▄▄▄▄█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▀
    drawMainMenuButton(x, y);
    RGBPrint(x + 1 + 7 + 1, y + 1, L"        ▄▀▄ █ █ ▀█▀            ", white, light_aqua, false);
    RGBPrint(x + 1 + 7 + 1, y + 2, L"        ▀▄▀ ▀▄▀  █             ", white, light_aqua, false);
}
void drawTriagle(int x, int y, bool show) {
    if (show) {
        RGBPrint(x, y,     L"▄  ", black, white_aqua, false);
        RGBPrint(x, y + 1, L"██▄", black, white_aqua, false);
        RGBPrint(x, y + 2, L"█▀ ", black, white_aqua, false);
    }
    else {
        RGBPrint(x, y, L"   ", black, white_aqua, false);;
        RGBPrint(x, y + 1, L"   ", black, white_aqua, false);
        RGBPrint(x, y + 2, L"   ", black, white_aqua, false);
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
    RGBPrint(x, y, L" ▄", black, white_aqua, false);
    RGBPrint(x+2, y, L"▀▀▀", black, white, false);
    RGBPrint(x +5, y, L"▄                                             ▄", black, white_aqua, false);
    RGBPrint(x + 52, y, L"▀▀▀", black, white, false);
    RGBPrint(x + 55, y, L"▄", black, white_aqua, false);
    //
    RGBPrint(x, y+1, L"█", black, white_aqua, false);
    RGBPrint(x+1, y + 1, L" ▄█▄ ", light_aqua, white, false);
    RGBPrint(x+1+5, y + 1, L"█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█", black, white_aqua, false);
    RGBPrint(x + 1 + 5+45, y + 1, L" ▄█▄ ", light_aqua, white, false);
    RGBPrint(x + 1 + 5 + 45+5, y + 1, L"█", black, white_aqua, false);
    //
    RGBPrint(x, y + 2,          L"▀", black, white_aqua, false);
    RGBPrint(x+1, y + 2,        L"▄ ▀ ▄", black, white, false);
    RGBPrint(x + 1+2, y + 2,    L"▀", light_aqua, white, false);

    RGBPrint(x + 1+5, y + 2, L"▀", black, light_aqua, false);
    RGBPrint(x + 1 + 5+1, y + 2, L"▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀", white_aqua, light_aqua, false);
    RGBPrint(x + 1 + 5+1+43, y + 2, L"▀", black, light_aqua, false);
    RGBPrint(x + 1+5+1+43+1, y + 2, L"▄ ▀ ▄▀", black, white, false);
    RGBPrint(x + 1 + 5 + 1 + 43 + 1+5, y + 2, L"▀", black, white_aqua, false);
    RGBPrint(x + 1 + 5 + 1 + 43 + 1+2, y + 2, L"▀", light_aqua, white, false);
    //
    RGBPrint(x + 2, y + 3, L"▀█                                                 █▀", black, white_aqua, false);
    RGBPrint(x + 4, y + 3, L"▀                                               ▀", black, light_aqua, false);
    //
    for (int i = 0; i < lines; i++) {
        RGBPrint(x+3, y + 4 + i, L"█                                                 █", black, light_aqua, false);
    }
    //
    RGBPrint(x, y + 4 + lines, L" ▄", black, white_aqua, false);
    RGBPrint(x + 2, y + 4 + lines, L"▀▀▀", black, white, false);
    RGBPrint(x + 5, y + 4 + lines, L"▄                                             ▄", black, light_aqua, false);
    RGBPrint(x + 52, y + 4 + lines, L"▀▀▀", black, white, false);
    RGBPrint(x + 55, y + 4 + lines, L"▄", black, white_aqua, false);
    //
    RGBPrint(x, y + 4 + lines + 1, L"█", black, white_aqua, false);
    RGBPrint(x + 1, y + 4 + lines + 1, L" ▄█▄ ", light_aqua, white, false);
    RGBPrint(x + 1 + 5, y + 4 + lines + 1, L"█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█", black, aqua, false);
    RGBPrint(x + 1 + 5 + 45, y + 4 + lines + 1, L" ▄█▄ ", light_aqua, white, false);
    RGBPrint(x + 1 + 5 + 45 + 5, y + 4 + lines + 1, L"█", black, white_aqua, false);
    //
    RGBPrint(x,y+4+lines+1+1, L"▀▄ ▀ ▄▀                                           ▀▄ ▀ ▄▀", black, white_aqua, false);

    RGBPrint(x+3, y + 4 + lines + 1 + 1, L"▀", light_aqua, white_aqua, false);
    RGBPrint(x+53, y + 4 + lines + 1 + 1, L"▀", light_aqua, white_aqua, false);
    //
    RGBPrint(x + 2, y + 4 + lines + 1 + 1 + 1, L"▀▀▀                                               ▀▀▀", black, white_aqua, false);
}
void removePanel(int x, int y, int lines) {
    for (int i = 0; i < lines + 8; i++) {
        RGBPrint(x, y + i, L"                                                         ", 
            black, white_aqua, false);
    }
 }
void drawSlider(int x, int y, int length, int value, RGB bg_color) {
    RGBPrint(x, y, L"█", black, light_aqua, false);
    for (int i = 1; i <= length; i++) {
        RGBPrint(x + i, y - 1, L"▄", black, bg_color, false);
        RGBPrint(x + i, y + 1, L"▀", black, bg_color, false);
        if (i <= value) {
            RGBPrint(x + i, y, L"█", { 85, 148, 230 }, { 85, 148, 230 }, false);
        }
        else {
            RGBPrint(x + i, y, L"▄", aqua, white_aqua, false);
        }
    }

    RGBPrint(x+length+1, y, L"█", black, bg_color, false);
}
void drawDOT(int x, int y, RGB bg_color) {
    RGBPrint(x+1, y-1,  L"▄▄", black, bg_color, false);
    RGBPrint(x - 1, y, L"█  █", black, { 250, 177, 247 }, false);

    RGBPrint(x + 1, y, L"▄", { 250, 177, 247 }, white_aqua, false);
    RGBPrint(x + 1, y + 1, L"▀▀", black, bg_color, false);
}
void drawCheckBox(int x, int y, RGB color, RGB bg_color) {
    RGBPrint(x, y - 1, L" ▄▄▄", black, bg_color, false);
    RGBPrint(x, y,     L"█ ▄ █", black, color, false);
    RGBPrint(x, y + 1, L"▀   ▀", black, bg_color, false);
    RGBPrint(x+1, y + 1, L"   ", black, light_aqua, false);
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
    for (int i = 0; i < sizeof(lines) / sizeof(wstring); i++) RGBPrint(x, y + i, lines[i], white, white_aqua, false);
}
void drawInGameEscPanel(int x, int y) {
    wstring lines[] = {
        L" ▄▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▄",
        L"█                    █",
        L"█                    █",
        L"█                    █",
        L"█                    █",
        L"█                    █",
        L"█                    █",
        L"█                    █",
        L"█                    █",
        L"█                    █",
        L"█                    █",
        L"█                    █",
        L"█                    █",
        L" ▀▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▀"
    };
    for (int i = 0; i <(int) sizeof(lines) / sizeof(wstring); i++) {
        RGBPrint(x, y + i, lines[i], black, white_aqua, false);
    }
}
void drawInGameEscPanel_Settings(int x, int y) {
    wstring lines[] = {
        L" ▄▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▄",
        L"█                                         █",
        L"█                                         █",
        L"█                                         █",
        L"█                                         █",
        L"█                                         █",
        L"█                                         █",
        L"█                                         █",
        L"█                                         █",
        L"█                                         █",
        L"█                                         █",
        L"█                                         █",
        L"█                                         █",
        L" ▀▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▀"
    };    
    for (int i = 0; i < (int)sizeof(lines) / sizeof(wstring); i++) {
        RGBPrint(x, y + i, lines[i], black, white_aqua, false);
    }
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
void drawInGamePanel_1A(int x, int y, RGB border_color, RGB background_color, RGB dot_color, RGB outside_color) {
    //line 1
    RGBPrint(x, y, L" ▄", border_color, outside_color, false);
    RGBPrint(x + 2, y, L"▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀", border_color, background_color, false);
    RGBPrint(x + 2 + 39, y, L"▄ ", border_color, outside_color, false);
    //line n
    for (int i = 0; i < 7; i++) RGBPrint(x, y + i + 1, L"█                                         █", border_color, background_color, false);
    //line n+1
    RGBPrint(x, y + 7, L" ▀▄                                     ▄▀ ", border_color, outside_color, false);
    RGBPrint(x + 2, y + 7, L"▄                                     ▄", border_color, background_color, false);
    //last line
    RGBPrint(x, y + 8, L"   ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀   ", border_color, outside_color, false);
    RGBPrint(x + 3, y + 8, L"▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀", border_color, { 220,220,220 }, false);
    //draw dot
    RGBPrint(x + 3, y + 1, L"▄", dot_color, background_color, false);
    RGBPrint(x + 39, y + 1, L"▄", dot_color, background_color, false);
    RGBPrint(x + 3, y + 6, L"▄", dot_color, background_color, false);
    RGBPrint(x + 39, y + 6, L"▄", dot_color, background_color, false);
}
void drawInGamePanel_5(int x, int y, RGB border_color, RGB background_color, RGB dot_color, RGB outside_color) {
    //line 1
    RGBPrint(x, y, L" ▄", border_color, outside_color, false);
    RGBPrint(x + 2, y, L"▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀", border_color, background_color, false);
    RGBPrint(x + 2 + 39, y, L"▄ ", border_color, outside_color, false);
    //line n
    for (int i = 0; i < 12; i++) RGBPrint(x, y + i + 1, L"█                                         █", border_color, background_color, false);
    //line n+1
    RGBPrint(x, y + 12, L" ▀▄                                     ▄▀ ", border_color, outside_color, false);
    RGBPrint(x + 2, y + 12, L"▄                                     ▄", border_color, background_color, false);
    //last line
    RGBPrint(x, y + 13, L"   ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀   ", border_color, outside_color, false);
    RGBPrint(x + 3, y + 13, L"▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀", border_color, { 220,220,220 }, false);
    //draw dot
    RGBPrint(x + 3, y + 1, L"▄", dot_color, background_color, false);
    RGBPrint(x + 39, y + 1, L"▄", dot_color, background_color, false);
    RGBPrint(x + 3, y + 11, L"▄", dot_color, background_color, false);
    RGBPrint(x + 39, y + 11, L"▄", dot_color, background_color, false);
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
    for (int i = 0; i < 16*3; i++) {
        RGBPrint(x, y,     L"·▄▄▄▄  ▄▄▄   ▄▄▄· ▄▄▌ ▐ ▄▌▄▄ ", rainbows[i%16], background_color, false);
        RGBPrint(x, y + 1, L"██▪ ██ ▀▄ █·▐█ ▀█ ██· █▌▐███▌", rainbows[i % 16], background_color, false);
        RGBPrint(x, y + 2, L"▐█· ▐█▌▐▀▀▄ ▄█▀▀█ ██▪▐█▐▐▌▐█·", rainbows[i % 16], background_color, false);
        RGBPrint(x, y + 3, L"██. ██ ▐█•█▌▐█ ▪▐▌▐█▌██▐█▌.▀ ", rainbows[i % 16], background_color, false);
        RGBPrint(x, y + 4, L"▀▀▀▀▀• .▀  ▀ ▀  ▀  ▀▀▀▀ ▀▪ ▀ ", rainbows[i % 16], background_color, false);
        Sleep(100);//0.1s mỗi màu
    }
}
void drawPauseText(int x, int y, RGB background_color) {
    int i = 0;
    while (true) {
        i++;
        //vẽ
        RGBPrint(x, y,     L" ▄▄▄· ▄▄▄· ▄• ▄▌.▄▄ · ▄▄▄ .·▄▄▄▄  ", rainbows[i % 16], background_color, false);
        RGBPrint(x, y + 1, L"▐█ ▄█▐█ ▀█ █▪██▌▐█ ▀. ▀▄.▀·██▪ ██ ", rainbows[i % 16], background_color, false);
        RGBPrint(x, y + 2, L" ██▀·▄█▀▀█ █▌▐█▌▄▀▀▀█▄▐▀▀▪▄▐█· ▐█▌", rainbows[i % 16], background_color, false);
        RGBPrint(x, y + 3, L"▐█▪·•▐█ ▪▐▌▐█▄█▌▐█▄▪▐█▐█▄▄▌██. ██ ", rainbows[i % 16], background_color, false);
        RGBPrint(x, y + 4, L".▀    ▀  ▀  ▀▀▀  ▀▀▀▀  ▀▀▀ ▀▀▀▀▀• ", rainbows[i % 16], background_color, false);
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
        RGBPrint(x+3, y + 4, L"█", tree_body, background_color, false);
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
void drawGift(int x, int y, RGB background_color) {
//      ▄▄
//    ▄▀▀▀▀▄▀▀▄
//     ▀█▄ █ ▄▄▀
//█▀▀▀▀█▀▀▀▀▀▀▀▀█▀▀█
//█▄▄▄▄█▄▄▄▄▄▄▄▄█▄▄█
//▀█ ▄ ▀█ ▀▄   █▀ █
// █▄ ▀▄█▀▄ ▀▄ █▄ █
// █ ▀▄ █▄ ▀▄ ▀█  █
// █   ▀█ ▀▄ ▀▄█▀ █ 
 //▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
    RGB dark_red = {102,15,43},
        red = {214,56,64},
        border = {78,76,114},
        body_dot = {182,205,216};
    //header
    RGBPrint(x, y, L"      ▄▄", dark_red, background_color, false);
    //

    RGBPrint(x, y+1, L"    ▄", dark_red, background_color, false);
    RGBPrint(x+5, y+1, L"▀", dark_red, red, false);
    RGBPrint(x+6, y+1, L"▀▀", red, white, false);
    RGBPrint(x+8, y+1, L"▀▀▄▀▀", dark_red, red, false);
    RGBPrint(x+10, y+1, L"▄", dark_red, background_color, false);
    RGBPrint(x+13, y+1, L"▄", dark_red, background_color, false);
    //
    RGBPrint(x, y + 2, L"     ▀▄▄ █ ▄▄▀▀", dark_red, background_color, false);
    RGBPrint(x+7, y + 2, L"▄▄ █ ▄▄", dark_red, red, false);
    RGBPrint(x+9, y + 2, L"█", red, red, false);
    //body
    RGBPrint(x, y + 3, L"█▀▀▀▀█▀▀▀▀▀▀▀▀█▀▀█", border, default_white, false);
    RGBPrint(x, y + 4, L"█▄▄▄▄█▄▄▄▄▄▄▄▄█▄▄█", border, default_white, false);
    RGBPrint(x, y + 5, L"▀█ ▄ ▀█ ▀▄   █▀ █", border, background_color, false);
    RGBPrint(x, y + 6, L" █▄ ▀▄█▀▄ ▀▄ █▄ █", border, background_color, false);
    RGBPrint(x, y + 7, L" █ ▀▄ █▄ ▀▄ ▀█  █", border, background_color, false);
    RGBPrint(x, y + 8, L" █   ▀█ ▀▄ ▀▄█▀ █", border, background_color, false);
    RGBPrint(x, y + 9, L" ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀", border, background_color, false);
    //body details
    //red lines

    RGBPrint(x+5, y + 3, L"█", red, background_color, false);
    RGBPrint(x+14, y + 3, L"█", red, background_color, false);

    RGBPrint(x+5, y + 4, L"█", red, background_color, false);
    RGBPrint(x+14, y + 4, L"█", red, background_color, false);
    for (int i = 0; i < 4; i++) {
        RGBPrint(x + 6, y + 5+i, L"█", red, background_color, false);
        RGBPrint(x + 13, y + 5+i, L"█", red, background_color, false);
    }
    //dots
    const wstring texts[4] = {
        L" ▄ ▀",
        L"▄ ▀▄",
        L" ▀▄ ",
        L"   ▀"
    }, texts_2[4] = {
            L" ▀▄   ",
            L"▀▄ ▀▄ ",
            L"▄ ▀▄ ▀",
            L" ▀▄ ▀▄"
    }, texts_3[4] = {
            L"▀ ",
            L"▄ ",
            L"  ",
            L"▀ "
    };
    for (int i = 0; i < 4; i++) {
        RGBPrint(x + 2, y + 5+i, texts[i], body_dot, default_white, false);
        RGBPrint(x + 7, y + 5+i, texts_2[i], body_dot, default_white, false);
        RGBPrint(x + 14, y + 5+i, texts_3[i], body_dot, default_white, false);
    }
}
void drawCandy(int x, int y, RGB background_color) {
//  ▄▀▀▀▀▀▄
//▄▀  ▄▄▄ █▀▄
//█▀██   █ ▄█
//▀▄▄▀   ██▀█
//       █ ▄█
//       ██▀█
//       █ ▄█
//       ██▀█
//       █ ▄█
//       ██▀█
//       ▀▄▄▀
    const wstring border[] = {
        L"  ▄▀▀▀▀▀▄  ",
        L"▄▀  ▄▄▄  ▀▄",
        L"█  █   █  █",
        L"▀▄▄▀   █  █",
        L"       █  █",
        L"       █  █",
        L"       █  █",
        L"       █  █",
        L"       █  █",
        L"       █  █",
        L"       ▀▄▄▀"
    };
    for (int i = 0; i < 11; i++) RGBPrint(x, y + i, border[i], black, background_color, false);

}

void drawReindeer(int x, int y, RGB background_color) {
    RGB dark_brown = { 80,56,32 },
        brown = { 173, 117, 68 },
        light_brown = { 200,161,120 },
        red = { 185,44,34 },
        yellow = { 230,198,75 };
    RGBPrint(x, y, L"    █▄", dark_brown, background_color, false);
    //
    RGBPrint(x+5, y+1, L"▄██", brown, dark_brown, false);
    RGBPrint(x+8, y+1, L"▄", brown, background_color, false);
    //
    RGBPrint(x + 4, y+2, L"▀██▄██▀", brown, black, false);
    RGBPrint(x + 4, y+2, L"▀", brown, background_color, false);
    RGBPrint(x + 10, y+2, L"▀", dark_brown, background_color, false);
    //
    RGBPrint(x+5, y + 3, L"▀▀▀", brown, red, false);
    RGBPrint(x+8, y + 3, L"▀", brown, background_color, false);
    //
    RGBPrint(x, y + 4, L" ▄█▀████▀", brown, background_color, false);
    RGBPrint(x+8, y + 4, L"▀", yellow, background_color, false);
    RGBPrint(x+3, y + 4, L"▀", brown, light_brown, false);
    //

    RGBPrint(x, y + 5, L"▀█▄█▀▀██", brown, background_color, false);
    RGBPrint(x+2, y + 5, L"▄", brown, light_brown, false);
    //
    RGBPrint(x+1, y + 6, L"▀▀", brown, dark_brown, false);
    RGBPrint(x+6, y + 6, L"▀▀", brown, dark_brown, false);

}
/* ▀ █ ▄ 
                                    
   L"          ▄▀▄ ▄▀▄             "
   L"         ▀▄  ▀  ▄▀            "
   L"          ▀▄   ▄▀             "
   L"        ▄▄█ ▀▄▀ █▄▄           "
   L"       ▄▀          ▀▄         "
   L"     ▄▀             ▀▄        "
   L"    ▄▀               ▀▄       "
   L"   ▄▀                 ▀▄      "
   L"   █▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█      "
   L"      ▄▀           ▀▄         "
   L"    ▄▀               ▀▄       " 
   L"   ▄▀                 ▀▄      " 
   L"  ▄▀                   ▀▄     "
   L" ▄▀                      ▀▄   "
   L"▄█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█▄  "  
   L"         ▄█       █▄          " 
   L"       ▄█           █▄        "
   L"     ▄█               █▄      "
   L"   ▄█                   █▄    "
   L"  ▄▀                     ▀▄   "
   L"▄█                         █▄ "
   L"█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█ "
   L"            ████              "
   L"            ████              "                                
*/
void drawPineTree2(int x, int y, RGB background_color) {
   const wstring border1[] = {
   L"          ▄▀▄ ▄▀▄             "
   L"         ▀▄  ▀  ▄▀            "
   L"          ▀▄   ▄▀             "
   L"        ▄▄█ ▀▄▀ █▄▄           "
   L"       ▄▀          ▀▄         "
   L"     ▄▀             ▀▄        "
   L"    ▄▀               ▀▄       "
   L"   ▄▀                 ▀▄      "
   L"   █▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█      "
   L"      ▄▀           ▀▄         "
   L"    ▄▀               ▀▄       "
   L"   ▄▀                 ▀▄      "
   L"  ▄▀                   ▀▄     "
   L" ▄▀                      ▀▄   "
   L"▄█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█▄  "
   L"         ▄█       █▄          "
   L"       ▄█           █▄        "
   L"     ▄█               █▄      "
   L"   ▄█                   █▄    "
   L"  ▄▀                     ▀▄   "
   L"▄█                         █▄ "
   L"█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█ "
   L"            ████              "
   L"            ████              "
    };
    for (int i = 0; i < 23; i++) RGBPrint(x, y + i, border1[i], black, background_color, false);
}

void drawSanta(int x, int y, RGB background_color) {
    RGB skin = { 255, 202, 180 }, gray = { 168, 168, 168 }, red = { 190, 38, 42 };
    RGBPrint(x + 3, y, " ", white_aqua, white_aqua);
    RGBPrint(x , y+1, " ", white_aqua, white_aqua);
    RGBPrint(x-1, y+2, " ", white_aqua, white_aqua);
    RGBPrint(x, y+3, " ", white_aqua, white_aqua);
    RGBPrint(x+1, y+4, " ", white_aqua, white_aqua);
    RGBPrint(x, y+5, " ", white_aqua, white_aqua);
    RGBPrint(x, y+6, " ", white_aqua, white_aqua);
    RGBPrint(x-1, y+7, " ", white_aqua, white_aqua);
    RGBPrint(x-1, y+8, " ", white_aqua, white_aqua);
    RGBPrint(x+1, y+9, " ", white_aqua, white_aqua);
    RGBPrint(x+4, y+10, " ", white_aqua, white_aqua);

    RGBPrint(x + 4, y, L"▄      ▄▄", black, background_color, false);
    RGBPrint(x + 5, y, L"▄▄▄▄▄▄", red, black, false);

    RGBPrint(x + 1, y + 1, L"▄▄", black, background_color, false);
    RGBPrint(x + 3, y + 1, L"▄", red, black, false);
    RGBPrint(x + 4, y + 1, L"▄▄▄▄▄▄▄▄▄", red, red, false);
    RGBPrint(x + 13, y + 1, L"▄", black, black, false);

    RGBPrint(x, y + 2, L"▄  ▄          ▄", black, black, false);
    RGBPrint(x + 1, y + 2, L"▄", gray, gray, false);
    RGBPrint(x + 2, y + 2, L"▄", gray, white, false);
    RGBPrint(x + 4, y + 2, L"▄", black, red, false);
    RGBPrint(x + 5, y + 2, L"▄▄▄▄▄▄▄▄▄", red, red, false);

    RGBPrint(x + 1, y + 3, L"▄▄", background_color, black, false);
    RGBPrint(x + 3, y + 3, L"▄", black, white, false);
    RGBPrint(x + 4, y + 3, L"▄▄", gray, black, false);
    RGBPrint(x + 6, y + 3, L"▄▄▄▄▄▄▄▄▄", white, black, false);
    RGBPrint(x + 15, y + 3, L"▄", black, background_color, false);

    RGBPrint(x + 2, y + 4, L"▄             ▄", black, black, false);
    RGBPrint(x + 3, y + 4, L"▄▄", gray, gray, false);
    RGBPrint(x + 5, y + 4, L"▄▄▄▄", black, gray, false);
    RGBPrint(x + 9, y + 4, L"▄▄▄▄▄", black, white, false);
    RGBPrint(x + 14, y + 4, L"▄▄", white, white, false);

    RGBPrint(x + 1, y + 5, L"▄               ▄", black, background_color, false);
    RGBPrint(x + 2, y + 5, L"▄", gray, black, false);
    RGBPrint(x + 3, y + 5, L"▄", black, gray, false);
    RGBPrint(x + 4, y + 5, L"▄         ▄", skin, black, false);
    RGBPrint(x + 5, y + 5, L"▄       ▄", skin, skin, false);
    RGBPrint(x + 6, y + 5, L"▄", black, skin, false);
    RGBPrint(x + 7, y + 5, L"▄", white, skin, false);
    RGBPrint(x + 11, y + 5, L"▄", black, skin, false);
    RGBPrint(x + 12, y + 5, L"▄", white, skin, false);
    RGBPrint(x + 8, y + 5, L"▄▄▄", skin, skin, false);
    RGBPrint(x + 16, y + 5, L"▄", white, black, false);

    RGBPrint(x + 1, y + 6, L"▄ ▄           ▄ ▄", black, black, false);
    RGBPrint(x + 2, y + 6, L"▄", gray, gray, false);
    RGBPrint(x + 16, y + 6, L"▄", white, white, false);
    RGBPrint(x + 4, y + 6, L"▄▄       ▄▄", skin, skin, false);
    RGBPrint(x + 6, y + 6, L"▄▄   ▄▄", skin, black, false);
    RGBPrint(x + 8, y + 6, L"▄▄▄", red, skin, false);
    RGBPrint(x + 15, y + 5, L"▄", black, white, false);


    RGBPrint(x, y + 7, L"▄   ▄         ▄   ▄", black, black, false);
    RGBPrint(x + 1, y + 7, L"▄ ▄", gray, gray, false);
    RGBPrint(x + 2, y + 7, L"▄", black, gray, false);
    RGBPrint(x + 15, y + 7, L"▄ ▄", white, white, false);
    RGBPrint(x + 16, y + 7, L"▄", black, white, false);
    RGBPrint(x + 5, y + 7, L"▄       ▄", black, skin, false);
    RGBPrint(x + 6, y + 7, L"▄▄   ▄▄", white, black, false);
    RGBPrint(x + 8, y + 7, L"▄ ▄", white, red, false);
    RGBPrint(x + 9, y + 7, L"▄", black, red, false);

    RGBPrint(x, y + 8, L"▄                 ▄", background_color, black, false);
    RGBPrint(x + 1, y + 8, L"▄", black, gray, false);
    RGBPrint(x + 17, y + 8, L"▄", black, white, false);
    RGBPrint(x + 2, y + 8, L"▄", gray, gray, false);
    RGBPrint(x + 16, y + 8, L"▄", white, gray, false);
    RGBPrint(x + 3, y + 8, L"▄           ▄", gray, black, false);
    RGBPrint(x + 4, y + 8, L"▄▄▄▄   ▄▄▄▄", black, white, false);
    RGBPrint(x + 8, y + 8, L"▄ ▄", gray, black, false);
    RGBPrint(x + 9, y + 8, L"▄", gray, gray, false);

    RGBPrint(x + 2, y + 9, L"▄             ▄", background_color, black, false);
    RGBPrint(x + 3, y + 9, L"▄▄", black, gray, false);
    RGBPrint(x + 4, y + 9, L"▄▄", gray, gray, false);
    RGBPrint(x + 6, y + 9, L"▄▄▄ ▄▄▄▄", white, gray, false);
    RGBPrint(x + 9, y + 9, L"▄", white, white, false);
    RGBPrint(x + 14, y + 9, L"▄", black, gray, false);
    RGBPrint(x + 15, y + 9, L"▄", black, white, false);

    RGBPrint(x + 5, y + 10, L"▄▄▄▄▄▄▄▄▄", background_color, black, false);
}

void drawSnowman(int x, int y, RGB background_color) {
    RGB brown_yellow = { 224, 166, 59 }, semi_black = { 46,45,46 }, dark_red_1 = { 160, 10, 8 }, semi_dark_red = { 194, 10, 10 };
    RGB gray_1 = { 123,123,123 }, light_gray = { 203, 203 ,203 }, gray_white = { 230, 230, 230 };
    RGB red_1 = { 250, 10, 11 }, red = { 190, 38, 42 };;
    RGBPrint(x + 8, y, L"▄▄▄▄▄▄▄", black, black, false);
    RGBPrint(x + 15, y, L"▄", semi_black, semi_black, false);

    RGBPrint(x + 8, y + 1, L"▄", dark_red_1, black, false);
    RGBPrint(x + 9, y + 1, L"▄", semi_dark_red, black, false);
    RGBPrint(x + 10, y + 1, L"▄▄▄▄▄▄", red, black, false);

    RGBPrint(x + 4, y + 2, L"▄▄▄          ▄▄▄", black, background_color, false);
    RGBPrint(x + 7, y + 2, L"▄▄▄▄▄▄▄▄▄▄", black, black, false);

    RGBPrint(x + 6, y + 3, L"▄          ▄", gray_1, background_color, false);
    RGBPrint(x + 10, y + 3, L"      ", white, white, false);
    RGBPrint(x + 7, y + 3, L"▄", light_gray, gray_1, false);
    RGBPrint(x + 8, y + 3, L"▄", gray_white, light_gray, false);
    RGBPrint(x + 9, y + 3, L"▄", white, gray_white, false);
    RGBPrint(x + 16, y + 3, L"▄", white, gray_1, false);

    RGBPrint(x + 5, y + 4, L"▄            ▄", gray_1, gray_1, false);
    RGBPrint(x + 6, y + 4, L"▄", light_gray, light_gray, false);
    RGBPrint(x + 7, y + 4, L"▄ ▄▄▄▄ ▄▄▄▄", white, white, false);
    RGBPrint(x + 9, y + 4, L"▄", black, white, false);
    RGBPrint(x + 14, y + 4, L"▄", black, white, false);
    RGBPrint(x + 7, y + 4, L"▄", gray_white, gray_white, false);

    RGBPrint(x + 4, y + 5, L"▄              ▄", gray_1, gray_1, false);
    RGBPrint(x + 5, y + 5, L"▄", light_gray, light_gray, false);
    RGBPrint(x + 6, y + 5, L"▄", gray_white, gray_white, false);
    RGBPrint(x + 7, y + 5, L"▄▄ ▄▄     ▄▄", white, white, false);
    RGBPrint(x + 9, y + 5, L"▄", white, black, false);
    RGBPrint(x + 12, y + 5, L"▄▄ ▄▄", brown_yellow, white, false);
    RGBPrint(x + 14, y + 5, L"▄", brown_yellow, black, false);

    RGBPrint(x + 4, y + 6, L"▄              ▄", background_color, gray_1, false);
    RGBPrint(x + 5, y + 6, L"▄", gray_1, light_gray, false);
    RGBPrint(x + 6, y + 6, L"▄", light_gray, gray_white, false);
    RGBPrint(x + 7, y + 6, L"▄", gray_white, white, false);
    RGBPrint(x + 8, y + 6, L"▄ ▄▄▄▄ ▄▄▄", white, white, false);
    RGBPrint(x + 9, y + 6, L"▄    ▄", gray_1, white, false);
    RGBPrint(x + 18, y + 6, L"▄", gray_1, white, false);

    RGBPrint(x + 5, y + 7, L"▄            ▄", background_color, gray_1, false);
    RGBPrint(x + 6, y + 7, L"▄", gray_1, light_gray, false);
    RGBPrint(x + 7, y + 7, L"▄", light_gray, gray_white, false);
    RGBPrint(x + 8, y + 7, L"▄", gray_white, white, false);
    RGBPrint(x + 9, y + 7, L"▄    ▄▄▄", white, white, false);
    RGBPrint(x + 17, y + 7, L"▄", gray_1, white, false);
    RGBPrint(x + 10, y + 7, L"▄▄▄▄", white, gray_1, false);
    RGBPrint(x + 2, y + 7, L"▄", brown_yellow, background_color, false);
    RGBPrint(x + 21, y + 7, L"▄", brown_yellow, background_color, false);

    RGBPrint(x + 1, y + 8, L"▄▄", background_color, brown_yellow, false);
    RGBPrint(x + 21, y + 8, L"▄▄", background_color, brown_yellow, false);
    RGBPrint(x + 3, y + 8, L"▄", brown_yellow, background_color, false);
    RGBPrint(x + 20, y + 8, L"▄", brown_yellow, background_color, false);

    RGBPrint(x + 4, y + 8, L"▄▄", red_1, dark_red_1, false);
    RGBPrint(x + 6, y + 8, L"▄         ▄", semi_dark_red, semi_dark_red, false);
    RGBPrint(x + 7, y + 8, L"▄▄▄▄▄▄▄▄▄", red_1, red_1, false);

    RGBPrint(x + 1, y + 9, L"▄▄", dark_red_1, background_color, false);
    RGBPrint(x + 3, y + 9, L"▄", red_1, dark_red_1, false);
    RGBPrint(x + 4, y + 9, L"▄", background_color, brown_yellow, false);
    RGBPrint(x + 5, y + 9, L"▄", brown_yellow, background_color, false);
    RGBPrint(x + 6, y + 9, L"▄          ▄", gray_1, gray_1, false);
    RGBPrint(x + 7, y + 9, L"▄", light_gray, light_gray, false);
    RGBPrint(x + 8, y + 9, L"▄", gray_white, gray_white, false);
    RGBPrint(x + 9, y + 9, L"▄▄  ▄▄▄▄", white, white, false);
    RGBPrint(x + 18, y + 9, L"▄", background_color, brown_yellow, false);
    RGBPrint(x + 19, y + 9, L"▄", brown_yellow, background_color, false);
    RGBPrint(x + 11, y + 9, L"▄▄", black, white, false);

    RGBPrint(x, y + 10, L"▄", background_color, dark_red_1, false);
    RGBPrint(x + 1, y + 10, L"▄", red_1, dark_red_1, false);
    RGBPrint(x + 2, y + 10, L"▄", red_1, red_1, false);
    RGBPrint(x + 3, y + 10, L"▄", background_color, red_1, false);
    RGBPrint(x + 5, y + 10, L"▄            ▄", gray_1, gray_1, false);
    RGBPrint(x + 6, y + 10, L"▄", light_gray, light_gray, false);
    RGBPrint(x + 7, y + 10, L"▄", gray_white, gray_white, false);
    RGBPrint(x + 8, y + 10, L"▄▄▄  ▄▄▄▄▄", white, white, false);
    RGBPrint(x + 11, y + 10, L"▄▄", black, white, false);

    RGBPrint(x + 11, y + 11, L"▄▄", black, white, false);
    RGBPrint(x + 1, y + 11, L"▄", background_color, red_1, false);
    RGBPrint(x + 4, y + 11, L"▄", gray_1, background_color, false);
    RGBPrint(x + 5, y + 11, L"▄", light_gray, gray_1, false);
    RGBPrint(x + 6, y + 11, L"▄", gray_white, light_gray, false);
    RGBPrint(x + 7, y + 11, L"▄", white, gray_white, false);
    RGBPrint(x + 8, y + 11, L"▄▄▄  ▄▄▄▄▄", white, white, false);
    RGBPrint(x + 18, y + 11, L"▄", white, gray_1, false);
    RGBPrint(x + 19, y + 11, L"▄", gray_1, background_color, false);

    RGBPrint(x + 4, y + 12, L"▄", gray_1, gray_1, false);
    RGBPrint(x + 19, y + 12, L"▄", gray_1, gray_1, false);
    RGBPrint(x + 5, y + 12, L"▄", light_gray, light_gray, false);
    RGBPrint(x + 6, y + 12, L"▄", gray_white, gray_white, false);
    RGBPrint(x + 7, y + 12, L"▄▄▄▄▄▄▄▄▄▄▄▄", white, white, false);
}
