#include "setup.h"

void textColor(int color) {
    HANDLE mau;
    mau = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(mau, color);
}


void fillPixel(wchar_t ch, COORD pos, int color) {

}


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

void drawBorder(Color color)
{
    wstring border[3];
    border[0] = L"┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓";
    border[1] = L"┠━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫";
    border[2] = L"┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛";

    printCenterCharacters(border[0], color, Color::bright_white, short(21), My_Windows);
    printCenterCharacters(border[1], color, Color::bright_white, short(21 + 15), My_Windows);
    printCenterCharacters(border[1], color, Color::bright_white, short(21 + 30), My_Windows);
    printCenterCharacters(border[2], color, Color::bright_white, short(21 + 45), My_Windows);

    short centerX = (short(My_Windows.Left) + short(My_Windows.Right)) / 2;

    for (int i = 0; i < 46; i++) {
        if (i == 0 || i == 15 || i == 30 || i == 45) {
            continue;
        }
        printCharacter(L"┃", { short(centerX - short(105 / 2)), short(i + 21) }, color, Color::bright_white);
        printCharacter(L"┃", { short(centerX + short(105 / 2)), short(i + 21) }, color, Color::bright_white);
	}
}

void drawLine(int y) {
    wstring line = L"━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━";
    printCenterCharacters(line, Color::light_green, Color::bright_white, short(y), My_Windows);
}

void eraseLine() {
    wstring line = L"                                                                        ";
    for (int i = 0; i < 3; i++) {
        printCenterCharacters(line, Color::bright_white, Color::bright_white, short(34 + 15*i), My_Windows);
    }
}

void drawMainMenu(int choice)
{

    Color color[9] = { Color::light_red, Color::light_blue, Color::light_purple, Color::yellow };
    
    short yLine = 34;

    drawGameTitle();
    drawBorder(color[2]);
    if (choice == 0) {
        eraseLine();
        drawLine(yLine);
        drawPlay(color[3]);
        drawLoad(color[2]);
        drawSetting(color[1]);
    }
    else if (choice == 1) {
        eraseLine();
        drawLine(yLine + 15);
        drawPlay(color[0]);
        drawLoad(color[3]);
        drawSetting(color[2]);
    }
    else if (choice == 2) {
        eraseLine();
        drawLine(yLine + 30);
        drawPlay(color[0]);
        drawLoad(color[1]);
        drawSetting(color[3]);
    }
    //else {
    //    drawBorder(color[0]);
    //    drawPlay(color[0]);
    //    drawLoad(color[1]);
    //    drawSetting(color[2]);
    //}
   
}

void drawFrame() {
    for (int i = 5; i < 266; i++) {
        printCharacter(L" ", { short(i), 4 }, Color::aqua, Color::aqua);
    }
    for (int i = 5; i < 64; i++) {
        printCharacter(L"  ", { 5, short(i) }, Color::aqua, Color::aqua);
		printCharacter(L"  ", { 200, short(i) }, Color::aqua, Color::aqua);
        printCharacter(L"  ", { 264, short(i) }, Color::aqua, Color::aqua);

    }
    for (int i = 5; i < 200; i++) {
        printCharacter(L" ", { short(i), 28 }, Color::aqua, Color::aqua);
    }
    
    for (int i = 10; i <= 64; i += 6) {
        for (int j = 5; j < 266; j++) {
			printCharacter(L" ", { short(j), short(i) }, Color::black, Color::black);
		}
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

void drawCharacter(COORD pos) {
    //printCharacter(L"  ");
    wstring content[5];
    content[0] = L"   ▄▀▀▀▀▀───▄█▀▀▀█▄  ";
    content[1] = L"  ▐▄▄▄▄▄▄▄▄██▌▀▄▀▐██ ";
    content[2] = L"  ▐▒▒Lion▒▒███▌▀▐███ ";
    content[3] = L"   ▌▒▓▒▒▒▒▓▒██▌▀▐██  ";
    content[4] = L"   ▌▓▐▀▀▀▀▌▓─▀▀▀▀▀   ";
    for (int i = pos.Y; i < pos.Y + 5; i++) {
		printCharacter(content[i - pos.Y], { pos.X, short(i) }, Color::yellow, Color::bright_white);
	}
}

void drawSpacing(COORD pos) {
    wstring spacing[5];
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 19; j++) {
			spacing[i] += L" ";
		}
	}
    for (int i = pos.Y; i < pos.Y + 5; i++) {
		printCharacter(spacing[i - pos.Y], { pos.X, short(i) }, Color::bright_white, Color::bright_white);
	}
}

void moveTestting() {

    for (int i = -20; i < 240; i++) {
        for (int j = 0; j < 10; j++) {
            drawCharacter({ short(i), short(50) });
            Sleep(40);
            i++;
        }
        Sleep(200);
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