#include "Sound.h"

void Sound::setTrackVolume()
{
	for (wstring track : TrackList)
	{
		mciSendString(wstring(L"setaudio " + track + L" volume to " + to_wstring(BGSoundVolume)).c_str(), 0, 0, 0);
	}
}

void Sound::setFxVolume()
{
	for (wstring FxEffect : SoundEffectList)
	{
		mciSendString(wstring(L"setaudio " + FxEffect + L" volume to " + to_wstring(EffectSoundVolume)).c_str(), 0, 0, 0);
	}
}
Sound::Sound() {};
Sound::~Sound() {};

int Sound::getCurrentMusicVolume()
{
	return BGSoundVolume;
}
int Sound::getCurrentEffectVolume()
{
	return EffectSoundVolume;
}

void Sound::setBGVolume(int value)
{
	BGSoundVolume = value;
}

void Sound::setEffectVolume(int value)
{
	EffectSoundVolume = value;
}

void Sound::startAudioEngine()
{
	for (wstring track : TrackList)
	{
		mciSendString(wstring(L"open \"Sound/" + track + L".mp3\" type mpegvideo alias " + track).c_str(), 0, 0, 0);
		mciSendString(wstring(L"setaudio " + track + L" volume to " + to_wstring(BGSoundVolume)).c_str(), 0, 0, 0);
	}

	for (wstring FxEffect : SoundEffectList)
	{
		mciSendString(wstring(L"open \"Sound/" + FxEffect + L".mp3\" type mpegvideo alias " + FxEffect).c_str(), 0, 0, 0);
		mciSendString(wstring(L"setaudio " + FxEffect + L" volume to " + to_wstring(EffectSoundVolume)).c_str(), 0, 0, 0);
	}
}

void Sound::cleanAudioEngine()
{
	for (wstring track : TrackList)
	{
		mciSendString(wstring(L"close " + track).c_str(), NULL, 0, NULL);
	}

	for (wstring FxEffect : SoundEffectList)
	{
		mciSendString(wstring(L"close " + FxEffect).c_str(), NULL, 0, NULL);
	}
}

void Sound::resumeCurrentTrack()
{
	wstring pauseL = L"resume " + currentSound;
	mciSendString(pauseL.c_str(), 0, 0, 0);
}
void Sound::pauseCurrentTrack()
{
	wstring pauseL = L"pause " + currentSound;
	mciSendString(pauseL.c_str(), 0, 0, 0);
}

void Sound::playTrack(SoundTrack track, bool repeat)
{
	currentSound = TrackList[int(track)];
	wstring playL = L"play " + currentSound;
	if (repeat)
		playL += L" repeat";
	else
		playL += L" from 0";
	mciSendString(playL.c_str(), 0, 0, 0);
}
void Sound::playSoundEffect(SoundEffect soundEffect)
{
	mciSendString(wstring(L"play " + SoundEffectList[int(soundEffect)] + L" from 0").c_str(), 0, 0, 0);
}

void Sound::pauseSoundEffect(SoundEffect soundEffect)
{
	mciSendString(wstring(L"pause " + SoundEffectList[int(soundEffect)]).c_str(), 0, 0, 0);
}

void Sound::reduceSoundBackground() {
	BGSoundVolume -= 250;
	BGSoundVolume = max(BGSoundVolume, 0);

	setTrackVolume();
}
void Sound::increaseSoundBackground() {
	BGSoundVolume += 250;
	BGSoundVolume = min(BGSoundVolume, 1000);

	setTrackVolume();
}
void Sound::reduceEffectSound() {
	EffectSoundVolume -= 250;
	EffectSoundVolume = max(EffectSoundVolume, 0);

	setFxVolume();
}
void Sound::increaseEffectSound() {
	EffectSoundVolume += 250;
	EffectSoundVolume = min(EffectSoundVolume, 1000);

	setFxVolume();
}
