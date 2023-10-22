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


void printCharacter(COORD pos, wstring content, int R, int G, int B) {
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


void drawMainMenu()
{

    wstring content1[8];
    content1[0] = L"▀███▀▀▀██▄▀████▀         ██     ▀███▀   ▀██▀  ";
    content1[1] = L"  ██   ▀██▄ ██          ▄██▄      ███   ▄█    ";
    content1[2] = L"  ██   ▄██  ██         ▄█▀██▄      ███ ▄█     ";
    content1[3] = L"  ███████   ██        ▄█  ▀██       ████      ";
    content1[4] = L"  ██        ██     ▄  ████████       ██       ";
    content1[5] = L"  ██        ██    ▄█ █▀      ██      ██       ";
    content1[6] = L"▄████▄    █████████████▄   ▄████▄  ▄████▄     ";
    content1[7] = L"━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━  ";

    Color color[9] = { Color::light_red, Color::light_blue, Color::light_purple };
    for (int i = 0; i < 8; i++) {
        printCenterCharacters(content1[i], color[0], Color::bright_white, short(15 + i), My_Windows);
    }


    wstring content2[8];
    content2[0] = L" ▀████▀     ▄▄█▀▀██▄       ██     ▀███▀▀▀██▄    ";
    content2[1] = L"   ██     ▄██▀    ▀██▄    ▄██▄      ██    ▀██▄  ";
    content2[2] = L"   ██     ██▀      ▀██   ▄█▀██▄     ██     ▀██  ";
    content2[3] = L"   ██     ██        ██  ▄█  ▀██     ██      ██  ";
    content2[4] = L"   ██     ▄█▄      ▄██  ████████    ██     ▄██  ";
    content2[5] = L"   ██    ▄███▄    ▄██▀ █▀      ██   ██    ▄██▀  ";
    content2[6] = L" ██████████ ▀▀████▀▀ ▄███▄   ▄████▄████████▀    ";
    content2[7] = L"━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ ";


    for (int i = 0; i < 8; i++) {
        printCenterCharacters(content2[i], color[1], Color::bright_white, short(30 + i), My_Windows);
    }


    wstring content3[8];
    content3[0] = L" ▄█▀▀▀█▄████▀▀▀██████▀▀██▀▀█████▀▀██▀▀███████▀███▄   ▀███▀ ▄▄█▀▀▀█▄█ ▄█▀▀▀█▄█    ";
    content3[1] = L"▄██    ▀█ ██    ▀██▀   ██   ▀█▀   ██   ▀█ ██   ███▄    █ ▄██▀     ▀█▄██    ▀█    ";
    content3[2] = L"▀███▄     ██   █       ██         ██      ██   █ ███   █ ██▀       ▀▀███▄        ";
    content3[3] = L"  ▀█████▄ ██████       ██         ██      ██   █  ▀██▄ █ ██           ▀█████▄    ";
    content3[4] = L"▄     ▀██ ██   █  ▄    ██         ██      ██   █   ▀██▄█ ██▄    ▀████     ▀██    ";
    content3[5] = L"██     ██ ██     ▄█    ██         ██      ██   █     ███ ▀██▄     ████     ██▀   ";
    content3[6] = L" █▀█████▀▄██████████  ▄████▄     ▄████▄  ▄████▄███▄    ██   ▀▀████████▀█████▀    ";
    content2[7] = L"━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━   ";



    for (int i = 0; i < 8; i++) {
        printCenterCharacters(content3[i], color[2], Color::bright_white, short(45 + i), My_Windows);
    }
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
