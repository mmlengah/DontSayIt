#pragma once
#include <SDL.h>
#include <SDL_ttf.h>

class Letter
{
public:
	Letter(int x, int y, int w, int h);
	void update(float* dt);
	void draw(SDL_Renderer* r, TTF_Font* font, const char* letter);
	void SetFalling(bool f);
private:
	bool isFalling;
	void falling(float* dt);
	SDL_Color white;
	SDL_Rect letterRect;
};

