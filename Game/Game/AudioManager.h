#pragma once
#include <SDL_mixer.h>

class AudioManager
{
public:
	AudioManager();
	void init();
	void playBackgroundMusic();
	void playBetterBackgroundMusic();
	void PlayDroppedItem();
	void PlayOkWord();
	void PlayPickUp();
private:
	void PlayChunk(Mix_Chunk* c);
	Mix_Music* backgroundMusic;
	Mix_Music* otherBackgroundMusic;
	Mix_Chunk* dropItem;
	Mix_Chunk* okWord;
	Mix_Chunk* pickUpItem;
	bool bakamitai;
};

