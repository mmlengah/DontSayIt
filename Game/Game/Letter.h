#pragma once
#include <SDL.h>
#include <SDL_ttf.h>

class Letter
{
public:
	Letter(int x, int y);
	void draw(SDL_Renderer* r, TTF_Font* font, const char* letter);
private:
	
	SDL_Color white;
	SDL_Rect letterRect;
};

