#include "setup.h"

#pragma comment(lib, "winmm.lib")

const vector<wstring> SoundEffectList = { L"menuMove", L"menuSelect" };

enum class SoundEffect {
	menuMove = 0,
	menuSelect = 1,
 };

class Sound {
private:
	static wstring currentSound;
	static LPCWSTR ps;
	static int BGSoundVolume; // sound volume: 0 250 500 750 1000 (a sound has volume from 0 - 1000)
	static int EffectSoundVolume;	// sound volume: 0 250 500 750 1000 (a sound has volume from 0 - 1000)
public:
	
	Sound() {};
	~Sound() {};
	static void setBGVolume(int value)
	{
		BGSoundVolume = value;
	}
	static void setEffectVolume(int value)
	{
		EffectSoundVolume = value;
	}
	static int getCurrentMusicVolume()
	{
		return BGSoundVolume;
	}
	static int getCurrentEffectVolume()
	{
		return EffectSoundVolume;
	}

	static void openSoundList() {
		// open bg
		mciSendString(TEXT("open \"sound/test.mp3\" type mpegvideo alias test"), 0, 0, 0);
		wstring volume = L"setaudio test volume to " + to_wstring(Sound::BGSoundVolume);
		const wchar_t* test = volume.c_str();
		mciSendString(test, 0, 0, 0);

		// open effect
		for (int i = 0; i < SoundEffectList.size(); i++) {
			wstring command = L"open \"sound/" + SoundEffectList[i] + L".mp3\" type mpegvideo alias " + SoundEffectList[i];
			const wchar_t* cmd = command.c_str();
			mciSendString(cmd, 0, 0, 0);

			volume = L"setaudio test volume to " + to_wstring(Sound::EffectSoundVolume);
			test = volume.c_str();
			mciSendString(test, 0, 0, 0);
		}

	}
	static void pauseCurrentSound()
	{
		wstring pauseL = L"pause " + currentSound;
		mciSendString(pauseL.c_str(), 0, 0, 0);
	}

	static void playSound(const wstring &soundname, bool repeat = false)
	{
		wstring playL = L"play " + soundname;
		if (repeat)
			playL += L" repeat";
		else
			playL += L" from 0";
		currentSound = soundname;
		mciSendString(playL.c_str(), 0, 0, 0);
	}
	static void playSoundEffect(SoundEffect soundEffect)
	{
		playSound(SoundEffectList[int(soundEffect)]);
	}

	static void playBGSound() {
		playSound(L"test", true);
	}

	static void playHitSound()
	{
		pauseCurrentSound();
		mciSendString(TEXT("play hitsound"), 0, 0, 0);
	}
	static void reduceSoundBackground() {
		Sound::BGSoundVolume -= 250;
		Sound::BGSoundVolume = max(Sound::BGSoundVolume, 0);
		wstring volume = L"setaudio test volume to " + to_wstring(Sound::BGSoundVolume);
		const wchar_t* test = volume.c_str();
		//mciSendString(volume.c_str(), 0, 0, 0);
		mciSendString(test, 0, 0, 0);
	}
	static void increaseSoundBackground() {
		Sound::BGSoundVolume += 250;
		Sound::BGSoundVolume = min(Sound::BGSoundVolume, 1000);
		wstring volume = L"setaudio test volume to " + to_wstring(Sound::BGSoundVolume) ;
		const wchar_t* test = volume.c_str();
		//mciSendString(volume.c_str(), 0, 0, 0);
		mciSendString(test, 0, 0, 0);

	}
	static void reduceEffectSound() {
		Sound::EffectSoundVolume -= 250;
		Sound::EffectSoundVolume = max(Sound::EffectSoundVolume, 0);
		wstring effectVolume = L"setaudio hitsound volume to " + to_wstring(Sound::EffectSoundVolume);
		for (int i = 0; i < SoundEffectList.size(); i++) {
			wstring effectVolume = L"setaudio " + SoundEffectList[i] + L" volume to " + to_wstring(Sound::EffectSoundVolume);
			mciSendString(effectVolume.c_str(), 0, 0, 0);
		}
	}
	static void increaseEffectSound() {
		Sound::EffectSoundVolume += 250;
		Sound::EffectSoundVolume = min(Sound::EffectSoundVolume, 1000);
		wstring effectVolume = L"setaudio hitsound volume to " + to_wstring(Sound::EffectSoundVolume);
		for (int i = 0; i < SoundEffectList.size(); i++) {
			wstring effectVolume = L"setaudio " + SoundEffectList[i] + L" volume to " + to_wstring(Sound::EffectSoundVolume);
			mciSendString(effectVolume.c_str(), 0, 0, 0);
		}
	}
	
	
};
