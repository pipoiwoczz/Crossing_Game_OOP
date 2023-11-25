#include "setup.h"
#include"Graphics.h"

SMALL_RECT My_Windows = { 0, 0, 0, 0 };

void Graphic::textSize(HANDLE hStdout, int fsize) {
  //  HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx = new CONSOLE_FONT_INFOEX();
    lpConsoleCurrentFontEx->cbSize = sizeof(CONSOLE_FONT_INFOEX);
    GetCurrentConsoleFontEx(hStdout, 0, lpConsoleCurrentFontEx);
    lpConsoleCurrentFontEx->dwFontSize.X = 1;
    lpConsoleCurrentFontEx->dwFontSize.Y = 1;
    SetCurrentConsoleFontEx(hStdout, 0, lpConsoleCurrentFontEx);
    delete lpConsoleCurrentFontEx;
}

Graphic::~Graphic()
{

}

void Graphic::disableUserSelection() {
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(hStdin, &mode);
    SetConsoleMode(hStdin, mode & (~ENABLE_QUICK_EDIT_MODE));
}

void Graphic::hideCursor(HANDLE h, bool isHideCursor) {
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = !isHideCursor;
    SetConsoleCursorInfo(h, &info);
}

void Graphic::setWindowSize(short width, short height) {
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r); //stores the console's current dimensions

    MoveWindow(console, 0, 0, width, height, TRUE);

}

void Graphic::fixConsoleWindow() {
    ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
    HWND consoleWindow = GetConsoleWindow();
    LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
    style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
    SetWindowLong(consoleWindow, GWL_STYLE, style);
  
    //CONSOLE_SCREEN_BUFFER_INFOEX csbie;
    //csbie.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
    //GetConsoleScreenBufferInfoEx(consoleHandle, &csbie);
    //csbie.dwSize.X = 432;
    //csbie.dwSize.Y = 126;
    ////csbie.srWindow = My_Windows;
    //csbie.dwMaximumWindowSize.X = 432;
    //csbie.dwMaximumWindowSize.Y = 126;
    //SetConsoleScreenBufferInfoEx(consoleHandle, &csbie);
    //SetConsoleScreenBufferSize(consoleHandle, csbie.dwSize);
    //GetConsoleScreenBufferInfo(consoleHandle, &csbi);
    //csbi.dwSize.X = 432;
    //csbi.dwSize.Y = 126;
    //
    //SetConsoleScreenBufferSize(consoleHandle, csbi.dwSize);
    //My_Windows.Bottom = csbi.srWindow.Bottom;
    //My_Windows.Right = csbi.srWindow.Right;
   // SetWindowPos(consoleWindow, 0, 0, 0, 480, 131, SWP_NOSIZE | SWP_NOZORDER);

    system("color f0");
    //432, 126
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


