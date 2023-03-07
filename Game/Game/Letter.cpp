#include "Letter.h"
#include <cstdlib>
#include <iostream>

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

	speed = 0.05f;
	pos = util::Vector2((float)x, (float)y);
}

Letter::~Letter()
{
	isFollowPlayer = false;
	letterRect.x = 1000;
	letterRect.y = 1000;
}

void Letter::draw(SDL_Renderer* r, TTF_Font* font, const char* letter)
{
	SDL_Surface* textImage = TTF_RenderText_Solid(font, letter, white);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(r, textImage);
	SDL_RenderCopy(r, textTexture, NULL, &letterRect);

	SDL_DestroyTexture(textTexture);
	SDL_FreeSurface(textImage);
}

void Letter::update(const int* width, const int* height, double* dt, SDL_Rect r)
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

void Letter::SetFollowPlayer(bool b)
{
	isFollowPlayer = b;
}

void Letter::Falling(const int* width, const int* height, double* dt)
{
	if (!isFalling) { return; }
	pos.y += (float)(speed * *dt);
	letterRect.y += (int) pos.y;

	//left
	if (letterRect.x < 0) {
		pos.x = 0;
		letterRect.x = (int) pos.x;
	}
	//top
	if (letterRect.y < 0) {
		pos.y = 0;
		letterRect.y = (int) pos.y;
	}
	//right
	if (letterRect.x > *width - letterRect.w) {
		pos.x = (float)(*width - letterRect.w);
		letterRect.x = (int) pos.x;
	}
	//bottom
	if (letterRect.y > *height - letterRect.h) {
		pos.y = (float)(*height - letterRect.h);
		letterRect.y = (int) pos.y;
		isFalling = false;
	}
}

void Letter::FollowPlayer(SDL_Rect r)
{
	if (!isFollowPlayer) { return; }
	letterRect.x = r.x + 5;
	letterRect.y = r.y - 30;
}

void Letter::CollidedWithPlayer()
{
	isFollowPlayer = true;
	isFalling = false;
}

void Letter::SetLocation(int x, int y)
{
	letterRect.x = x;
	letterRect.y = y;
}

void Letter::SetPlaced(bool b)
{
	placed = b;
}

bool Letter::GetPlaced()
{
	return placed;
}
