#include "Letter.h"

Letter::Letter(int x, int y, int w, int h)
{
	white.r = 255;
	white.b = 255;
	white.g = 255;
	white.a = 255;

	letterRect.x = x;
	letterRect.y = y;
	letterRect.w = w;
	letterRect.h = h;
}


void Letter::draw(SDL_Renderer* r, TTF_Font* font, const char* letter)
{
	SDL_Surface* textImage = TTF_RenderText_Solid(font, letter, white);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(r, textImage);
	SDL_RenderCopy(r, textTexture, NULL, &letterRect);

	SDL_DestroyTexture(textTexture);
	SDL_FreeSurface(textImage);
}
