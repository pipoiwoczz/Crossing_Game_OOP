#ifndef SOUNDENGINE_H
#define SOUNDENGINE_H
#include "setup.h"

#pragma comment(lib, "winmm.lib")



enum class SoundEffect {
	menuMove = 0,
	coinEarn = 1,
	lionFx = 2,
	rhinoFx = 3,
	crocoFx = 4,
	sharkFx = 5,
	surferFx = 6,
	vehicleFx = 7
 };
enum class SoundTrack {
	background = 0
};
class Sound {
private:

	static vector<wstring> SoundEffectList;
	static vector<wstring> TrackList;

	static wstring currentSound;
	static int BGSoundVolume; // sound volume: 0 250 500 750 1000 (a sound has volume from 0 - 1000)
	static int EffectSoundVolume;	// sound volume: 0 250 500 750 1000 (a sound has volume from 0 - 1000)
	


	static void setTrackVolume();
	static void setFxVolume();

public:
	
	Sound();
	~Sound();

	static int getCurrentMusicVolume();
	static int getCurrentEffectVolume();

	static void setBGVolume(int value);
	static void setEffectVolume(int value);

	static void startAudioEngine();
	static void cleanAudioEngine();

	static void resumeCurrentTrack();
	static void pauseCurrentTrack();

	static void playTrack(SoundTrack track, bool repeat = false);

	static void playSoundEffect(SoundEffect soundEffect);
	static void pauseSoundEffect(SoundEffect soundEffect);

	static void reduceSoundBackground();
	static void increaseSoundBackground();

	static void reduceEffectSound();
	static void increaseEffectSound();
	
	
};

#endif // !SOUNDENGINE_H
