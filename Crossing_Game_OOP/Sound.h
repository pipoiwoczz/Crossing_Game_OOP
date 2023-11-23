#include "setup.h"



 

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
	static wstring currentSound;
	static LPCWSTR ps;
public:
	Sound() {};
	~Sound() {};
	static void playSoundList() {

		mciSendString(TEXT("open \"sound/test.mp3\" type mpegvideo alias test"), 0, 0, 0);
		mciSendString(TEXT("open \"sound/bombhitsound.mp3\" type mpegvideo alias hitsound"), 0, 0, 0);

	}
	static void pauseCurrentSound()
	{
		wstring pauseL = L"pause " + currentSound;
		mciSendString(pauseL.c_str(), 0, 0, 0);
	}
	static void playSound(const wstring &soundname)
	{
		wstring playL = L"play " + soundname;
		currentSound = soundname;
		mciSendString(playL.c_str(), 0, 0, 0);
	}
	static void playDieSound();
	static void playFinishLevelSound();
	static void playFinishGameSound();
	static void playIntroSound() {
		playSound(L"test");
	}
	static void playHitSound()
	{
		mciSendString(TEXT("pause test"), 0, 0, 0);
		mciSendString(TEXT("play hitsound"), 0, 0, 0);
	}
	static void playBackGroundSound();
	static void playVihecleSound();
	static void musicThread() {
		//auto music = async(launch::async, &Sound::playIntroSound);
	}
};
