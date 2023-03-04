#pragma once
#include <SDL.h>
#include "utils.h"
class Player
{
public:
	Player(int width, int height);
	void Draw(SDL_Renderer* r);
	void Update();
	void PlayerInput(SDL_Event* e);
private:
	SDL_Rect playerRect;
	int speed;
	util::Vector2 position;
};

