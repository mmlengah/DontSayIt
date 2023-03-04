#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "Player.h"

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
	bool EventHandler();
	bool QuitButton(SDL_Event* e);

	SDL_Window* window = nullptr;
	SDL_Surface* screenSurface = nullptr;
	SDL_Renderer* renderer = nullptr;

	Player* p;
};

