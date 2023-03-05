#include "Letter.h"
#include <cstdlib>
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

	isFalling = false;

	speed = (float) (rand() % 6 + 10) / 25;
}

void Letter::draw(SDL_Renderer* r, TTF_Font* font, const char* letter)
{
	SDL_Surface* textImage = TTF_RenderText_Solid(font, letter, white);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(r, textImage);
	SDL_RenderCopy(r, textTexture, NULL, &letterRect);

	SDL_DestroyTexture(textTexture);
	SDL_FreeSurface(textImage);
}

void Letter::update(const int* width, const int* height, float* dt, SDL_Rect r)
{
	Falling(width, height, dt);
	FollowPlayer(r);
}

void Letter::SetFalling(bool f)
{
	isFalling = f;
}

SDL_Rect Letter::GetRect()
{
	return letterRect;
}

SDL_Rect* Letter::GetRectP()
{
	return &letterRect;
}

void Letter::SetFollowPlayer(bool b)
{
	isFollowPlayer = b;
}

void Letter::Falling(const int* width, const int* height, float* dt)
{
	if (!isFalling) { return; }
	letterRect.y += (int) (speed * *dt);

	//left
	if (letterRect.x <= 0) {
		letterRect.x = 0;
	}
	//top
	if (letterRect.y <= 0) {
		letterRect.y = 0;
	}
	//right
	if (letterRect.x >= *width - letterRect.w) {
		letterRect.x = (int)(*width - letterRect.w);		
	}
	//bottom
	if (letterRect.y >= *height - letterRect.h) {
		letterRect.y = (int)(*height - letterRect.h);
		isFalling = false;
	}
}

void Letter::FollowPlayer(SDL_Rect r)
{
	if (!isFollowPlayer) { return; }
	letterRect.x = r.x + 5;
	letterRect.y = r.y - 30;
}

void Letter::Collision(SDL_Rect r)
{
	if (isFollowPlayer) { return; }
	if (SDL_HasIntersection(&letterRect, &r)) {
		isFollowPlayer = true;
	}
}
