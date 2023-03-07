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
	void Update(int width, int height, double* dt);
	void PlayerMoveLeft(bool b);
	void PlayerMoveRight(bool b);
	void PlayerMoveUp(bool b);
	void PlayerMoveDown(bool b);	
	SDL_Rect GetRect();
	float* GetPosY();
	bool GetHolding();
	void StopHolding();
	void collidedWithLetter();
	void Reset();
	bool GetKeyStates(int i);
private:
	//functions
	void Animation();
	void Movement(int width, int height, double* dt);

	//variables
	bool holding = false;
	bool keyStates[4] = { false, false, false, false };
	SDL_Rect playerRect;
	std::vector<SDL_Texture*> textures;
	int animationFrame;
	float speed;
	util::Vector2 position;
};

