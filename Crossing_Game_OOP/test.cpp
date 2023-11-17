#include "setup.h"
#include "Map.h"
#include "Graphics.h"
#include "Tank.h"
#include "cPeople.h"
#include "cGame.h"
#include "cAsset.h"

int main() {
	Graphic gr;
	

	cGame game;
	game.MainGame();

	return 1;
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
