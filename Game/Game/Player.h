#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "utils.h"

class Player
{
public:
	Player(int width, int height);
	~Player();
	bool init(SDL_Renderer* r);
	void Draw(SDL_Renderer* r);
	void Update(int width, int height);
	void PlayerInput(SDL_Event* e);
private:
	//functions
	void Animation();
	void Movement(int width, int height);

	//variables
	bool holding = false;
	SDL_Rect playerRect;
	std::vector<SDL_Texture*> textures;
	int animationFrame;
	int speed;
	util::Vector2 position;
};

