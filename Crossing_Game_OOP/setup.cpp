#include "setup.h"
#include "Graphics.h"

void gotoXY(int x, int y) {
    static HANDLE h = NULL;
    if (!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = { x, y };
    SetConsoleCursorPosition(h, c);
}



void printCharacter(wstring content, COORD spot, Color textColor, Color backgroundColor, short maxlength) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD Written;

    int color = int(textColor) + int(backgroundColor) * 16;


    if (maxlength == -1) {
        //content = content.substr(0, maxlength) + L"...";
    }

    for (int i = 0; i < content.length(); i++) {
        if (content[i] == L' ') {
            spot.X++;
            continue;
        }
        FillConsoleOutputAttribute(hOut, color, 1, spot, &Written);
        FillConsoleOutputCharacterW(hOut, content[i], 1, spot, &Written);
        spot.X++;
    }
}

void printCharacter2(wstring content, COORD spot, Color textColor, Color backgroundColor, short maxlength) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD Written;

    int color = int(textColor) + int(backgroundColor) * 16;


    if (maxlength == -1) {
        //content = content.substr(0, maxlength) + L"...";
    }

    for (int i = 0; i < content.length(); i++) {
        FillConsoleOutputAttribute(hOut, color, 1, spot, &Written);
        FillConsoleOutputCharacterW(hOut, content[i], 1, spot, &Written);
        spot.X++;
    }
}



void printCenterCharacters(wstring content, Color textColor, Color backgroundColor, short y, SMALL_RECT box, short maxlength) {
    short centerX = (short(box.Left) + short(box.Right)) / 2 - content.length() / 2;

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD Written;

    int color = int(textColor) + int(backgroundColor) * 16;

    if (maxlength == -1) {
        //content = content.substr(0, maxlength) + L"...";
    }

    for (int i = 0; i < content.length(); i++) {
        FillConsoleOutputAttribute(hOut, color, 1, { centerX, y }, &Written);
        FillConsoleOutputCharacterW(hOut, content[i], 1, { centerX, y }, &Written);
        centerX++;
    }
}


void printCharacter2(COORD pos, wstring content, int R, int G, int B) {
    gotoXY(pos.X, pos.Y);
    CONSOLE_SCREEN_BUFFER_INFOEX info;
    info.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfoEx(hConsole, &info);

    info.ColorTable[15] = RGB(R, G, B);

    SetConsoleScreenBufferInfoEx(hConsole, &info);
    SetConsoleTextAttribute(hConsole, 3);
    wcout << content;
    info.ColorTable[15] = COLORREF(Color::bright_white);
}

void drawPlay(Color color) {
    wstring content1[8];
    content1[0] = L"▀███▀▀▀██▄▀████▀         ██     ▀███▀   ▀██▀";
    content1[1] = L"  ██   ▀██▄ ██          ▄██▄      ███   ▄█  ";
    content1[2] = L"  ██   ▄██  ██         ▄█▀██▄      ███ ▄█   ";
    content1[3] = L"  ███████   ██        ▄█  ▀██       ████    ";
    content1[4] = L"  ██        ██     ▄  ████████       ██     ";
    content1[5] = L"  ██        ██    ▄█ █▀      ██      ██     ";
    content1[6] = L"▄████▄    █████████████▄   ▄████▄  ▄████▄   ";
    content1[7] = L"━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━";

    for (int i = 0; i < 8; i++) {
        printCenterCharacters(content1[i], color, Color::bright_white, short(25 + i), My_Windows);
    }
}

void drawLoad(Color color) {
    wstring content2[8];
    content2[0] = L" ▀████▀     ▄▄█▀▀██▄       ██     ▀███▀▀▀██▄  ";
    content2[1] = L"   ██     ▄██▀    ▀██▄    ▄██▄      ██    ▀██▄";
    content2[2] = L"   ██     ██▀      ▀██   ▄█▀██▄     ██     ▀██";
    content2[3] = L"   ██     ██        ██  ▄█  ▀██     ██      ██";
    content2[4] = L"   ██     ▄█▄      ▄██  ████████    ██     ▄██";
    content2[5] = L"   ██    ▄███▄    ▄██▀ █▀      ██   ██    ▄██▀";
    content2[6] = L" ██████████ ▀▀████▀▀ ▄███▄   ▄████▄████████▀  ";
    content2[7] = L"━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━";


    for (int i = 0; i < 8; i++) {
        printCenterCharacters(content2[i], color, Color::bright_white, short(40 + i), My_Windows);
    }
}

void drawSetting(Color color) {
    wstring content3[8];
    content3[0] = L" ▄█▀▀▀█▄████▀▀▀██████▀▀██▀▀█████▀▀██▀▀███████▀███▄   ▀███▀ ▄▄█▀▀▀█▄█ ▄█▀▀▀█▄█ ";
    content3[1] = L"▄██    ▀█ ██    ▀██▀   ██   ▀█▀   ██   ▀█ ██   ███▄    █ ▄██▀     ▀█▄██    ▀█ ";
    content3[2] = L"▀███▄     ██   █       ██         ██      ██   █ ███   █ ██▀       ▀▀███▄     ";
    content3[3] = L"  ▀█████▄ ██████       ██         ██      ██   █  ▀██▄ █ ██           ▀█████▄ ";
    content3[4] = L"▄     ▀██ ██   █  ▄    ██         ██      ██   █   ▀██▄█ ██▄    ▀████     ▀██ ";
    content3[5] = L"██     ██ ██     ▄█    ██         ██      ██   █     ███ ▀██▄     ████     ██▀";
    content3[6] = L" █▀█████▀▄██████████  ▄████▄     ▄████▄  ▄████▄███▄    ██   ▀▀████████▀█████▀ ";
    content3[7] = L"━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━";



    for (int i = 0; i < 8; i++) {
        printCenterCharacters(content3[i], color, Color::bright_white, short(55 + i), My_Windows);
    }
}

void drawScoreBoard(Color color) {
    wstring content3[8];
    content3[0] = L" ▄█▀▀▀█▄█ ▄▄█▀▀▀█▄█ ▄▄█▀▀██▄ ▀███▀▀▀██▄ ▀███▀▀▀███▀███▀▀▀██▄ ▄▄█▀▀██▄       ██     ▀███▀▀▀██▄ ▀███▀▀▀██▄  ";
    content3[1] = L"▄██    ▀███▀     ▀███▀    ▀██▄ ██   ▀██▄  ██    ▀█  ██    ████▀    ▀██▄    ▄██▄      ██   ▀██▄  ██    ▀██▄";
    content3[2] = L"▀███▄   ██▀       ▀█▀      ▀██ ██   ▄██   ██   █    ██    ███▀      ▀██   ▄█▀██▄     ██   ▄██   ██     ▀██";
    content3[3] = L"  ▀█████▄█        ██        ██ ███████    ██████    ██▀▀▀█▄▄█        ██  ▄█  ▀██     ███████    ██      ██";
    content3[4] = L"▄     ▀███▄       ██▄      ▄██ ██  ██▄    ██   █  ▄ ██    ▀██▄      ▄██  ████████    ██  ██▄    ██     ▄██";
    content3[5] = L"██     ████▄     ▄▀██▄    ▄██▀ ██   ▀██▄  ██     ▄█ ██    ▄███▄    ▄██▀ █▀      ██   ██   ▀██▄  ██    ▄██▀";
    content3[6] = L"█▀█████▀  ▀▀█████▀  ▀▀████▀▀ ▄████▄ ▄███▄██████████████████  ▀▀████▀▀ ▄███▄   ▄████▄████▄ ▄███▄████████▀  ";
    content3[7] = L"━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━";



    for (int i = 0; i < 8; i++) {
        printCenterCharacters(content3[i], color, Color::bright_white, short(70 + i), My_Windows);
    }
}

void drawBorder(Color color)
{
    wstring border[4];
    border[0] = L"┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓";
    border[1] = L"┠━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫";
    border[2] = L"┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛";

    printCenterCharacters(border[0], color, Color::bright_white, short(21), My_Windows);
    printCenterCharacters(border[1], color, Color::bright_white, short(21 + 15), My_Windows);
    printCenterCharacters(border[1], color, Color::bright_white, short(21 + 30), My_Windows);
    printCenterCharacters(border[1], color, Color::bright_white, short(21 + 45), My_Windows);
    printCenterCharacters(border[2], color, Color::bright_white, short(21 + 60), My_Windows);

    short centerX = (short(My_Windows.Left) + short(My_Windows.Right)) / 2;

    for (int i = 0; i < 61; i++) {
        if (i == 0 || i == 15 || i == 30 || i == 45 || i == 60) {
            continue;
        }
        printCharacter(L"┃", { short(centerX - short(117 / 2)), short(i + 21) }, color, Color::bright_white);
        printCharacter(L"┃", { short(centerX + short(117 / 2)), short(i + 21) }, color, Color::bright_white);
	}
}

void drawLine(int y) {
    wstring line = L"━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━";
    printCenterCharacters(line, Color::light_green, Color::bright_white, short(y), My_Windows);
}

void eraseLine() {
    wstring line = L"                                                                              ";
    for (int i = 0; i < 3; i++) {
        printCenterCharacters(line, Color::bright_white, Color::bright_white, short(34 + 15*i), My_Windows);
    }
}

void drawMainMenu(int choice) {

    Color color[5] = { Color::light_red, Color::light_blue, Color::light_purple, Color::yellow, Color::light_green };
    
    short yLine = 34;

    drawGameTitle();
    drawBorder(color[2]);
    if (choice == 0) {
        eraseLine();
        drawLine(yLine);
        drawPlay(color[3]);
        drawLoad(color[2]);
        drawSetting(color[1]);
        drawScoreBoard(color[4]);
    }
    else if (choice == 1) {
        eraseLine();
        drawLine(yLine + 15);
        drawPlay(color[0]);
        drawLoad(color[3]);
        drawSetting(color[1]);
        drawScoreBoard(color[4]);
    }
    else if (choice == 2) {
        eraseLine();
        drawLine(yLine + 30);
        drawPlay(color[0]);
        drawLoad(color[2]);
        drawSetting(color[3]);
        drawScoreBoard(color[4]);
    }
    else if (choice == 4) {
        eraseLine();
        drawLine(yLine + 45);
        drawPlay(color[0]);
        drawLoad(color[2]);
        drawSetting(color[1]);
        drawScoreBoard(color[3]);
    }
    //else {
    //    drawBorder(color[0]);
    //    drawPlay(color[0]);
    //    drawLoad(color[1]);
    //    drawSetting(color[2]);
    //}
   
}

void drawSettingMenu(int choice, bool On) {
    Color color[5] = { Color::light_red, Color::light_blue, Color::light_purple, Color::yellow, Color::light_green };

    drawGameTitle();

    wstring content[9];
    content[0] = L"                                               ▄▄         ";
    content[1] = L" ▄█▀▀▀█▄█                                    ▀███         ";
    content[2] = L"▄██    ▀█                                      ██         ";
    content[3] = L"▀███▄     ▄██▀██▄▀███  ▀███ ▀████████▄    ▄█▀▀███  ▄██▀███";
    content[4] = L"  ▀█████▄██▀   ▀██ ██    ██   ██    ██  ▄██    ██  ██   ▀▀";
    content[5] = L"▄     ▀████     ██ ██    ██   ██    ██  ███    ██  ▀█████▄";
    content[6] = L"██     ████▄   ▄██ ██    ██   ██    ██  ▀██    ██  █▄   ██";
    content[7] = L"█▀█████▀  ▀█████▀  ▀████▀███▄████  ████▄ ▀████▀███▄██████▀";
    content[8] = L"━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━";


    for (int i = 0; i < 9; i++) {
        printCenterCharacters(content[i], color[0], Color::bright_white, short(25 + i), My_Windows);
    }

    
    wstring state[8];
    state[0] = L"            ▄▄▄▄   ▄▄▄▄                                       ";
    state[1] = L"          ▄█▀ ▀▀ ▄█▀ ▀▀                                       ";
    state[2] = L"          ██▀    ██▀                                          ";
    state[3] = L" ▄██▀██▄ █████  █████                      ▄██▀██▄▀████████▄  ";
    state[4] = L"██▀   ▀██ ██     ██                       ██▀   ▀██ ██    ██  ";
    state[5] = L"██     ██ ██     ██                       ██     ██ ██    ██  ";
    state[6] = L"██▄   ▄██ ██     ██                       ██▄   ▄██ ██    ██  ";
    state[7] = L" ▀█████▀▄████▄ ▄████▄                      ▀█████▀▄████  ████▄";


    for (int i = 0; i < 8; i++) {
        printCenterCharacters(state[i], color[1], Color::bright_white, short(40 + i), My_Windows);
    }



    wstring button1[8];

    button1[0] = L"▄███████████████████████████████████████████████████▄";
    button1[1] = L"███▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓███";
    button1[2] = L"██▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒███████████████████████▓██";
    button1[3] = L"██▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒███████████████████████▓██";
    button1[4] = L"██▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒███████████████████████▓██";
    button1[5] = L"██▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒███████████████████████▓██";
    button1[6] = L"███▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓███";
    button1[7] = L"▀███████████████████████████████████████████████████▀";



    wstring button2[8];

    button2[0] = L"▄███████████████████████████████████████████████████▄";
    button2[1] = L"███▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓███";
    button2[2] = L"██▓███████████████████████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓██";
    button2[3] = L"██▓███████████████████████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓██";
    button2[4] = L"██▓███████████████████████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓██";
    button2[5] = L"██▓███████████████████████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓██";
    button2[6] = L"███▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓███";
    button2[7] = L"▀███████████████████████████████████████████████████▀";


    wstring exit[8];

    exit[0] = L"    ▄   ▄   ▀███▀▀▀██▄     ██       ▄▄█▀▀▀█▄█████▀ ▀███▀       ";
    exit[1] = L"   █   █      ██    ██    ▄██▄    ▄██▀     ▀█ ██   ▄█▀         ";
    exit[2] = L" ▄█  ▄█       ██    ██   ▄█▀██▄   ██▀       ▀ ██ ▄█▀           ";
    exit[3] = L"██  ██        ██▀▀▀█▄▄  ▄█  ▀██   ██          █████▄           ";
    exit[4] = L" ▀█  ▀█       ██    ▀█  ████████  ██▄         ██  ███          ";
    exit[5] = L"   █   █      ██    ▄█ █▀      ██ ▀██▄     ▄▀ ██   ▀██▄        ";
    exit[6] = L"    ▀   ▀   ▄████████▄███▄   ▄████▄ ▀▀█████▀▄████▄   ███▄      ";



    if (choice == 1) {
        if (On) {
            for (int i = 0; i < 8; i++) {
                printCenterCharacters(button1[i], color[3], Color::bright_white, short(50 + i), My_Windows);
            }
        }
        else if (!On) {
            for (int i = 0; i < 8; i++) {
                printCenterCharacters(button2[i], color[3], Color::bright_white, short(50 + i), My_Windows);
            }
        }
        for (int i = 0; i < 8; i++) {
            printCenterCharacters(exit[i], color[2], Color::bright_white, short(70 + i), My_Windows);
        }
    }
    else if (choice == 2) {
        if (On) {
            for (int i = 0; i < 8; i++) {
                printCenterCharacters(button1[i], color[1], Color::bright_white, short(50 + i), My_Windows);
            }
        }
        else if (!On) {
            for (int i = 0; i < 8; i++) {
                printCenterCharacters(button2[i], color[1], Color::bright_white, short(50 + i), My_Windows);
            }
        }
        for (int i = 0; i < 8; i++) {
            printCenterCharacters(exit[i], color[3], Color::bright_white, short(70 + i), My_Windows);
        }
    }
}

void drawLoadMenu(int choice) {
    Color color[5] = { Color::light_red, Color::light_blue, Color::light_purple, Color::yellow, Color::light_green };

    drawGameTitle();
    
    wstring content[8];
    content[0] = L" ▄█▀▀▀█▄█                                  ";
    content[1] = L"▄██    ▀█                                  ";
    content[2] = L"▀███▄    ▄█▀██▄ ▀██▀   ▀██▀  ▄▄█▀██ ▄██▀███";
    content[3] = L"  ▀█████▄█   ██   ██   ▄█   ▄█▀   ████   ▀▀";
    content[4] = L"▄     ▀██▄█████    ██ ▄█    ██▀▀▀▀▀▀▀█████▄";
    content[5] = L"██     ███   ██     ███     ██▄    ▄█▄   ██";
    content[6] = L"█▀█████▀▀████▀██▄    █       ▀█████▀██████▀";
    content[7] = L"━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━";

    for (int i = 0; i < 8; i++) {
        printCenterCharacters(content[i], color[1], Color::bright_white, short(15 + i), My_Windows);
    }

    wstring border[4];
    border[0] = L"┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓";
    border[1] = L"┠━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫";
    border[2] = L"┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛";

    printCenterCharacters(border[0], color[0], Color::bright_white, short(25), My_Windows);
    printCenterCharacters(border[1], color[0], Color::bright_white, short(25 + 15), My_Windows);
    printCenterCharacters(border[1], color[0], Color::bright_white, short(25 + 30), My_Windows);
    printCenterCharacters(border[1], color[0], Color::bright_white, short(25 + 45), My_Windows);
    printCenterCharacters(border[1], color[0], Color::bright_white, short(25 + 60), My_Windows);
    printCenterCharacters(border[2], color[0], Color::bright_white, short(25 + 75), My_Windows);

    short centerX = (short(My_Windows.Left) + short(My_Windows.Right)) / 2;

    for (int i = 0; i < 76; i++) {
        if (i == 0 || i == 15 || i == 30 || i == 45 || i == 60 || i == 75) {
            continue;
        }
        printCharacter(L"┃", { short(centerX - short(117 / 2)), short(i + 25) }, color[0], Color::bright_white);
        printCharacter(L"┃", { short(centerX + short(117 / 2)), short(i + 25) }, color[0], Color::bright_white);
    }



    wstring exit[8];

    exit[0] = L"    ▄   ▄   ▀███▀▀▀██▄     ██       ▄▄█▀▀▀█▄█████▀ ▀███▀       ";
    exit[1] = L"   █   █      ██    ██    ▄██▄    ▄██▀     ▀█ ██   ▄█▀         ";
    exit[2] = L" ▄█  ▄█       ██    ██   ▄█▀██▄   ██▀       ▀ ██ ▄█▀           ";
    exit[3] = L"██  ██        ██▀▀▀█▄▄  ▄█  ▀██   ██          █████▄           ";
    exit[4] = L" ▀█  ▀█       ██    ▀█  ████████  ██▄         ██  ███          ";
    exit[5] = L"   █   █      ██    ▄█ █▀      ██ ▀██▄     ▄▀ ██   ▀██▄        ";
    exit[6] = L"    ▀   ▀   ▄████████▄███▄   ▄████▄ ▀▀█████▀▄████▄   ███▄      ";

    for (int i = 0; i < 7; i++) {
        printCenterCharacters(exit[i], color[2], Color::bright_white, short(105 + i), My_Windows);
    }

    if (choice == 1) {

    }
    else if (choice == 2) {

    }
    else if (choice == 3) {

    }
    else if (choice == 4) {

    }
    else if (choice == 5) {

    }
    else if (choice == 6) {
        for (int i = 0; i < 7; i++) {
            printCenterCharacters(exit[i], color[3], Color::bright_white, short(105 + i), My_Windows);
        }
    }

}

void drawScoreboardMenu() {
    Color color[5] = { Color::light_red, Color::light_blue, Color::light_purple, Color::yellow, Color::light_green };

    drawGameTitle();

    wstring content[8];
    content[0] = L" ▄█▀▀▀█▄█                                ▄██                                      ▀███  ";
    content[1] = L"▄██    ▀█                                 ██                                        ██  ";
    content[2] = L"▀███▄    ▄██▀██  ▄██▀██▄▀███▄███  ▄▄█▀██  ██▄████▄   ▄██▀██▄ ▄█▀██▄ ▀███▄███   ▄█▀▀███  ";
    content[3] = L"  ▀█████▄█▀  ██ ██▀   ▀██ ██▀ ▀▀ ▄█▀   ██ ██    ▀██ ██▀   ▀███   ██   ██▀ ▀▀ ▄██    ██  ";
    content[4] = L"▄     ▀███      ██     ██ ██     ██▀▀▀▀▀▀ ██     ██ ██     ██▄█████   ██     ███    ██  ";
    content[5] = L"██     ███▄    ▄██▄   ▄██ ██     ██▄    ▄ ██▄   ▄██ ██▄   ▄███   ██   ██     ▀██    ██  ";
    content[6] = L"█▀█████▀ █████▀  ▀█████▀▄████▄    ▀█████▀ █▀█████▀   ▀█████▀▀████▀██▄████▄    ▀████▀███▄";
    content[7] = L"━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━";

    for (int i = 0; i < 8; i++) {
        printCenterCharacters(content[i], color[1], Color::bright_white, short(15 + i), My_Windows);
    }

    wstring border[4];
    border[0] = L"┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓";
    border[1] = L"┠━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫";
    border[2] = L"┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛";

    printCenterCharacters(border[0], color[0], Color::bright_white, short(25), My_Windows);
    printCenterCharacters(border[1], color[0], Color::bright_white, short(25 + 15), My_Windows);
    printCenterCharacters(border[1], color[0], Color::bright_white, short(25 + 30), My_Windows);
    printCenterCharacters(border[1], color[0], Color::bright_white, short(25 + 45), My_Windows);
    printCenterCharacters(border[1], color[0], Color::bright_white, short(25 + 60), My_Windows);
    printCenterCharacters(border[2], color[0], Color::bright_white, short(25 + 75), My_Windows);

    short centerX = (short(My_Windows.Left) + short(My_Windows.Right)) / 2;

    for (int i = 0; i < 76; i++) {
        if (i == 0 || i == 15 || i == 30 || i == 45 || i == 60 || i == 75) {
            continue;
        }
        printCharacter(L"┃", { short(centerX - short(117 / 2)), short(i + 25) }, color[0], Color::bright_white);
        printCharacter(L"┃", { short(centerX + short(117 / 2)), short(i + 25) }, color[0], Color::bright_white);
    }



    wstring exit[8];

    exit[0] = L"    ▄   ▄   ▀███▀▀▀██▄     ██       ▄▄█▀▀▀█▄█████▀ ▀███▀       ";
    exit[1] = L"   █   █      ██    ██    ▄██▄    ▄██▀     ▀█ ██   ▄█▀         ";
    exit[2] = L" ▄█  ▄█       ██    ██   ▄█▀██▄   ██▀       ▀ ██ ▄█▀           ";
    exit[3] = L"██  ██        ██▀▀▀█▄▄  ▄█  ▀██   ██          █████▄           ";
    exit[4] = L" ▀█  ▀█       ██    ▀█  ████████  ██▄         ██  ███          ";
    exit[5] = L"   █   █      ██    ▄█ █▀      ██ ▀██▄     ▄▀ ██   ▀██▄        ";
    exit[6] = L"    ▀   ▀   ▄████████▄███▄   ▄████▄ ▀▀█████▀▄████▄   ███▄      ";

    for (int i = 0; i < 7; i++) {
        printCenterCharacters(exit[i], color[3], Color::bright_white, short(105 + i), My_Windows);
    }



}

void drawGameTitle() {
    wstring content[9];
    content[0] = L"▄████████    ▄████████  ▄██████▄     ▄████████    ▄████████  ▄█  ███▄▄▄▄      ▄██████▄          ▄████████  ▄██████▄     ▄████████  ████████▄  ";
    content[1] = L"███    ███   ███    ███ ███    ███   ███    ███   ███    ███ ███  ███▀▀▀██▄   ███    ███        ███    ███ ███    ███   ███    ███ ███   ▀███ ";
    content[2] = L"███    █▀    ███    ███ ███    ███   ███    █▀    ███    █▀  ███▌ ███   ███   ███    █▀         ███    ███ ███    ███   ███    ███ ███    ███ "; 
    content[3] = L"███         ▄███▄▄▄▄██▀ ███    ███   ███          ███        ███▌ ███   ███  ▄███              ▄███▄▄▄▄██▀ ███    ███   ███    ███ ███    ███ ";
    content[4] = L"███        ▀▀███▀▀▀▀▀   ███    ███ ▀███████████ ▀███████████ ███▌ ███   ███ ▀▀███ ████▄       ▀▀███▀▀▀▀▀   ███    ███ ▀███████████ ███    ███ ";
    content[5] = L"███    █▄  ▀███████████ ███    ███          ███          ███ ███  ███   ███   ███    ███      ▀███████████ ███    ███   ███    ███ ███    ███ ";
    content[6] = L"███    ███   ███    ███ ███    ███    ▄█    ███    ▄█    ███ ███  ███   ███   ███    ███        ███    ███ ███    ███   ███    ███ ███   ▄███ "; 
    content[7] = L"████████▀    ███    ███  ▀██████▀   ▄████████▀   ▄████████▀  █▀    ▀█   █▀    ████████▀         ███    ███  ▀██████▀    ███    █▀  ████████▀  ";  
    content[8] = L"             ███    ███                                                                         ███    ███                                    ";

    Color color[9] = { Color::red, Color::light_red, Color::blue, Color::light_blue, Color::green, Color::aqua, Color::light_aqua, Color::light_purple, Color::light_purple};
    for (int i = 0; i < 9; i++) {
        printCenterCharacters(content[i], color[i], Color::bright_white, short(1 + i), My_Windows);
	}
    
}

void drawLosingTitle() {
    wstring content[6];
    content[0] = L"██╗░░░██╗░█████╗░██╗░░░██╗  ██╗░░░░░░█████╗░░██████╗███████╗";
    content[1] = L"╚██╗░██╔╝██╔══██╗██║░░░██║  ██║░░░░░██╔══██╗██╔════╝██╔════╝";
    content[2] = L"░╚████╔╝░██║░░██║██║░░░██║  ██║░░░░░██║░░██║╚█████╗░█████╗░░";
    content[3] = L"░░╚██╔╝░░██║░░██║██║░░░██║  ██║░░░░░██║░░██║░╚═══██╗██╔══╝░░";
    content[4] = L"░░░██║░░░╚█████╔╝╚██████╔╝  ███████╗╚█████╔╝██████╔╝███████╗";
    content[5] = L"░░░╚═╝░░░░╚════╝░░╚═════╝░  ╚══════╝░╚════╝░╚═════╝░╚══════╝";

    for (int i = 0; i < 6; i++) {
        printCenterCharacters(content[i], Color::red, Color::bright_white, 8 + i, My_Windows);
    }
}


void clearConsole() {
    COORD topLeft = { 0, 0 };
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD written;

    GetConsoleScreenBufferInfo(console, &screen);
    FillConsoleOutputCharacterA(
        console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
    );
    FillConsoleOutputAttribute(
        console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
        screen.dwSize.X * screen.dwSize.Y, topLeft, &written
    );
    SetConsoleCursorPosition(console, topLeft);
    system("color f0");
}

vector<vector<unsigned char>> loadTexture(string filename)
{
    ifstream ifs;
    ifs.open(filename);

    vector <vector<unsigned char>> res;
    if (ifs.is_open()) {
        int x;
        ifs >> x;
        res.resize(x);
        ifs >> x;
        for (int i = 0; i < res.size(); i++)
        {
            res[i].resize(x);
            for (int j = 0; j < x; j++)
            {
                ifs >> res[i][j];
            }
        }
    }
    ifs.close();
    return res;
}
