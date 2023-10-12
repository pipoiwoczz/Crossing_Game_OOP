#include "setup.h"

void textColor(int color) {
    HANDLE mau;
    mau = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(mau, color);
}

void gotoXY(int x, int y) {
    static HANDLE h = NULL;
    if (!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = { x, y };
    SetConsoleCursorPosition(h, c);
}

void fixConsoleWindow() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(consoleHandle, &csbi);
    SetConsoleScreenBufferSize(consoleHandle, csbi.dwMaximumWindowSize);

    system("color f0");

    ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
    HWND consoleWindow = GetConsoleWindow();
    LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
    style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
    SetWindowLong(consoleWindow, GWL_STYLE, style);

}

void showScrollBar(BOOL Show) {
    HWND hWnd = GetConsoleWindow();
    ShowScrollBar(hWnd, SB_BOTH, Show);
}

void DisableCtrButton(bool Close, bool Min, bool Max) {
    HWND hWnd = GetConsoleWindow();
    HMENU hMenu = GetSystemMenu(hWnd, false);

    if (Close == 1)
    {
        DeleteMenu(hMenu, SC_CLOSE, MF_BYCOMMAND);
    }
    if (Min == 1)
    {
        DeleteMenu(hMenu, SC_MINIMIZE, MF_BYCOMMAND);
    }
    if (Max == 1)
    {
        DeleteMenu(hMenu, SC_MAXIMIZE, MF_BYCOMMAND);
    }
}

void hideCursor(bool isHideCursor) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = !isHideCursor;
	SetConsoleCursorInfo(consoleHandle, &info);
}

void setWindowSize(short width, short height) {
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r); //stores the console's current dimensions

    MoveWindow(console, r.left, r.top, width, height, TRUE); 

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

void textSize(int size) {
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx = new CONSOLE_FONT_INFOEX();
	lpConsoleCurrentFontEx->cbSize = sizeof(CONSOLE_FONT_INFOEX);
	GetCurrentConsoleFontEx(hStdout, 0, lpConsoleCurrentFontEx);
	lpConsoleCurrentFontEx->dwFontSize.X = size;
	lpConsoleCurrentFontEx->dwFontSize.Y = size;
	SetCurrentConsoleFontEx(hStdout, 0, lpConsoleCurrentFontEx);
    delete lpConsoleCurrentFontEx;
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

void drawMainMenu(){

}

void drawGame() {

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
    content[0] = L"▄████████    ▄████████  ▄██████▄     ▄████████    ▄████████  ▄█  ███▄▄▄▄      ▄██████▄          ▄████████  ▄██████▄     ▄████████  ████████▄";
    content[1] = L"███    ███   ███    ███ ███    ███   ███    ███   ███    ███ ███  ███▀▀▀██▄   ███    ███        ███    ███ ███    ███   ███    ███ ███   ▀███";
    content[2] = L"███    █▀    ███    ███ ██s    ███   ███    █▀    ███    █▀  ███▌ ███   ███   ███    █▀         ███    ███ ███    ███   ███    ███ ███    ███"; 
    content[3] = L"███         ▄███▄▄▄▄██▀ ███    ███   ███          ███        ███▌ ███   ███  ▄███              ▄███▄▄▄▄██▀ ███    ███   ███    ███ ███    ███";
    content[4] = L"███        ▀▀███▀▀▀▀▀   ███    ███ ▀███████████ ▀███████████ ███▌ ███   ███ ▀▀███ ████▄       ▀▀███▀▀▀▀▀   ███    ███ ▀███████████ ███    ███";
    content[5] = L"███    █▄  ▀███████████ ███    ███          ███          ███ ███  ███   ███   ███    ███      ▀███████████ ███    ███   ███    ███ ███    ███";
    content[6] = L"███    ███   ███    ███ ███    ███    ▄█    ███    ▄█    ███ ███  ███   ███   ███    ███        ███    ███ ███    ███   ███    ███ ███   ▄███"; 
    content[7] = L"████████▀    ███    ███  ▀██████▀   ▄████████▀   ▄████████▀  █▀    ▀█   █▀    ████████▀         ███    ███  ▀██████▀    ███    █▀  ████████▀ ";  
    content[8] = L"             ███    ███                                                                         ███    ███                                   ";

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