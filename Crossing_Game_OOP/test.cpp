//#include "Map.h"
//#include "Graphics.h"
#include "cGame.h"
#include <iostream>
int main() {
	Graphic gr;
	cGameEngine::startEngine();
	
	cGame a;
	a.MainGame();
	

	//cout << "---------" << endl;

	//CONSOLE_SCREEN_BUFFER_INFO csbi1, csbi2;
	//GetConsoleScreenBufferInfo(cGameEngine::Hbuffer1, &csbi1);
	//GetConsoleScreenBufferInfo(cGameEngine::Hbuffer2, &csbi2);

	//cout << csbi1.dwSize.X << endl;
	//cout << csbi2.dwSize.X << endl;

}

//#include <iostream>
//#include <windows.h>
//#include <mmsystem.h>
//
//#pragma comment(lib, "winmm.lib")
//
//class Sound {
//public:
//    Sound(const char* filename) {
//        m_filename = filename;
//    }
//
//    void play() {
//        PlaySound(LPCWSTR(m_filename), NULL, SND_FILENAME | SND_ASYNC);
//    }
//
//private:
//    const char* m_filename;
//};

//int main() {
//        mciSendString(TEXT("open mywavsound.mp3 type mpegvideo alias mp3"), NULL, 0, NULL);
//        mciSendString(TEXT("play mp3 repeat"), NULL, 0, NULL);
//    
//   
//    system("pause");
//    return 0;
//}
