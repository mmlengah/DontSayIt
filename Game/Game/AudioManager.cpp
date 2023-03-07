#include "AudioManager.h"

AudioManager::AudioManager()
{
	bakamitai = false;
}

void AudioManager::playBackgroundMusic()
{
	bakamitai = false;
	//Play the music
	if (Mix_PlayMusic(backgroundMusic, -1) == -1)
	{
		return;
	}		
}

void AudioManager::playBetterBackgroundMusic()
{
	if (bakamitai) { return; }
	bakamitai = true;
	//Play the music
	if (Mix_PlayMusic(otherBackgroundMusic, -1) == -1)
	{
		return;
	}
}

void AudioManager::PlayDroppedItem()
{
	PlayChunk(dropItem);
}

void AudioManager::PlayOkWord()
{
	PlayChunk(okWord);
}

void AudioManager::PlayPickUp()
{
	PlayChunk(pickUpItem);
}

void AudioManager::PlayChunk(Mix_Chunk* c)
{
	if (Mix_PlayChannel(-1, c, 0) == -1) {
		return;
	}
}

void AudioManager::init()
{
	otherBackgroundMusic = Mix_LoadMUS("Assets/Music/Bakamitai.mp3");
	backgroundMusic = Mix_LoadMUS("Assets/Music/JUDGEMENT.mp3");
	dropItem = Mix_LoadWAV("Assets/Music/DropItem.mp3");
	okWord = Mix_LoadWAV("Assets/Music/Ok word.mp3");
	pickUpItem = Mix_LoadWAV("Assets/Music/PickUpItem.mp3");
	Mix_VolumeMusic(25);
	Mix_VolumeChunk(dropItem, 30);
	Mix_VolumeChunk(okWord, 30);
	Mix_VolumeChunk(pickUpItem, 30);
}
