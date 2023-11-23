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
	static int BGSoundVolume; // sound volume: 0 250 500 750 1000 (a sound has volume from 0 - 1000)
	static int EffectSoundVolume;	// sound volume: 0 250 500 750 1000 (a sound has volume from 0 - 1000)
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
	static void reduceSoundBackground() {
		Sound::BGSoundVolume -= 250;
		Sound::BGSoundVolume = max(Sound::BGSoundVolume, 0);
		wstring volume = L"setaudio test volume to " + to_wstring(Sound::BGSoundVolume);
		mciSendString(volume.c_str(), 0, 0, 0);
	}
	static void increaseSoundBackground() {
		Sound::BGSoundVolume -= 250;
		Sound::BGSoundVolume = min(Sound::BGSoundVolume, 1000);
		wstring volume = L"setaudio test volume to " + to_wstring(Sound::BGSoundVolume);
		mciSendString(volume.c_str(), 0, 0, 0);
	}
	static void reduceEffectSound() {
		wstring effect[5] = { L"hitsound", L"bombhitsound", L"finishgamesound", L"finishlevelsound", L"diesound" };
		Sound::EffectSoundVolume -= 250;
		Sound::EffectSoundVolume = max(Sound::EffectSoundVolume, 0);
		wstring effectVolume = L"setaudio hitsound volume to " + to_wstring(Sound::EffectSoundVolume);
		for (int i = 0; i < 5; i++) {
			wstring effectVolume = L"setaudio " + effect[0] + L" volume to " + to_wstring(Sound::EffectSoundVolume);
			mciSendString(effectVolume.c_str(), 0, 0, 0);
		}
	}
	static void increaseEffectSound() {
		wstring effect[5] = { L"hitsound", L"bombhitsound", L"finishgamesound", L"finishlevelsound", L"diesound" };
		Sound::EffectSoundVolume += 250;
		Sound::EffectSoundVolume = min(Sound::EffectSoundVolume, 1000);
		wstring effectVolume = L"setaudio hitsound volume to " + to_wstring(Sound::EffectSoundVolume);
		for (int i = 0; i < 5; i++) {
			wstring effectVolume = L"setaudio " + effect[0] + L" volume to " + to_wstring(Sound::EffectSoundVolume);
			mciSendString(effectVolume.c_str(), 0, 0, 0);
		}
	}
	static void playBackGroundSound() {
		mciSendString(TEXT("pause test"), 0, 0, 0);
		mciSendString(TEXT("play test repeat"), 0, 0, 0);
	}
	static void playVihecleSound();
	static void musicThread() {
		//auto music = async(launch::async, &Sound::playIntroSound);
	}
};
