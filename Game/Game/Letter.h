#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "utils.h"

class Letter
{
public:
	Letter(int x, int y, int w, int h);
	~Letter();
	void update(const int* width, const int* height, double* dt, SDL_Rect r);
	void draw(SDL_Renderer* r, TTF_Font* font, const char* letter);
	void SetFalling(bool f);
	SDL_Rect GetRect();
	void SetFollowPlayer(bool b);
	void CollidedWithPlayer();
	void SetLocation(int x, int y);
	void SetPlaced(bool b);
	bool GetPlaced();
private:	
	void Falling(const int* width, const int* height, double* dt);
	void FollowPlayer(SDL_Rect r);
	
	SDL_Color white;
	SDL_Rect letterRect;
	float speed;
	bool isFollowPlayer = false;
	bool isFalling;
	bool placed = false;
	util::Vector2 pos;
};

