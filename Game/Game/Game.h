#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "Player.h"
#include "Letter.h"
#include "BadWords.h"

class Game
{
public:
	Game();
	bool Init();
	bool KeepAlive();
	void Update();
	void Draw();	
	void Clean();
private:
	float SetDeltaTime();
	bool EventHandler();
	bool QuitButton(SDL_Event* e);

	SDL_Window* window = nullptr;
	SDL_Surface* screenSurface = nullptr;
	SDL_Renderer* renderer = nullptr;
	
	Uint64 NOW = 0;
	Uint64 LAST = 0;
	float deltaTime = 0;

	Player* p;
	BadWords* bw;

};

