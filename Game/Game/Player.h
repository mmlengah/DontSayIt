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
	void Update(int width, int height, float* dt, std::vector<SDL_Rect> letterRects);
	void PlayerKeyDown(SDL_Event* e);
	void PlayerKeyUp(SDL_Event* e);
	SDL_Rect GetRect();
	bool* GetHolding();
private:
	//functions
	void Animation();
	void Movement(int width, int height, float* dt);
	void HoldLetter();
	void Collision(std::vector<SDL_Rect> letterRects);
	//variables
	bool holding = false;
	bool keyStates[4] = { false, false, false, false };
	SDL_Rect playerRect;
	std::vector<SDL_Texture*> textures;
	int animationFrame;
	float speed;
	util::Vector2 position;
};

