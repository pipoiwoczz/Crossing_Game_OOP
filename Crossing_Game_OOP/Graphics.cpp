#include "setup.h"

void Graphic::textSize(int size) {
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx = new CONSOLE_FONT_INFOEX();
    lpConsoleCurrentFontEx->cbSize = sizeof(CONSOLE_FONT_INFOEX);
    GetCurrentConsoleFontEx(hStdout, 0, lpConsoleCurrentFontEx);
    lpConsoleCurrentFontEx->dwFontSize.X = size;
    lpConsoleCurrentFontEx->dwFontSize.Y = size;
    SetCurrentConsoleFontEx(hStdout, 0, lpConsoleCurrentFontEx);
    delete lpConsoleCurrentFontEx;
}



void Graphic::disableUserSelection() {
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(hStdin, &mode);
    SetConsoleMode(hStdin, mode & (~ENABLE_QUICK_EDIT_MODE));
}

void Graphic::hideCursor(bool isHideCursor) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = !isHideCursor;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void Graphic::setWindowSize(short width, short height) {
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r); //stores the console's current dimensions

    MoveWindow(console, r.left, r.top, width, height, TRUE);

}

void Graphic::fixConsoleWindow() {
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

void Graphic::showScrollBar(BOOL Show) {
    HWND hWnd = GetConsoleWindow();
    ShowScrollBar(hWnd, SB_BOTH, Show);
}

void Graphic::DisableCtrButton(bool Close, bool Min, bool Max) {
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

void Graphic::disableCtrlHandler(){
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD prev_mode;
    GetConsoleMode(hInput, &prev_mode);
    SetConsoleMode(hInput, prev_mode & ~ENABLE_MOUSE_INPUT);
}


