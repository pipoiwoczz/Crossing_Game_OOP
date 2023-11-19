#pragma once
#include "setup.h"
#include <mmsystem.h>
#include <future>

#pragma comment(lib, "winmm.lib")

 

class Sound {
private:
	//static char* moveSound ;
	//static string chooseSound;
	//static string dieSound;
	//static string finishLevelSound;
	//static string finishGameSound;

	//static string introSound;
	//static string backGroundSound;
	//static string vihecleSound;
	//	
	//static bool isPlayingIntro;
	//static bool isPlayingBackGround;
	//static bool isPlayingVihecle;
	
public:
	Sound() {};
	~Sound() {};
	static void playSoundList() {
		mciSendString(TEXT("open \"sound/test.mp3\" type mpegvideo alias test"), 0, 0, 0);
	}
	static void playDieSound();
	static void playFinishLevelSound();
	static void playFinishGameSound();
	static void playIntroSound() {
		mciSendString(TEXT("play test"), 0, 0, 0);
	}
	static void playBackGroundSound();
	static void playVihecleSound();
	static void musicThread() {
		//auto music = async(launch::async, &Sound::playIntroSound);
	}
};
