#pragma once
#include <SDL.h>
#include <SDL_ttf.h>

class Letter
{
public:
	Letter(int x, int y, int w, int h);
	void update(const int* width, const int* height, float* dt, SDL_Rect r);
	void draw(SDL_Renderer* r, TTF_Font* font, const char* letter);
	void SetFalling(bool f);
	SDL_Rect GetRect();
	SDL_Rect* GetRectP();
	void SetFollowPlayer(bool b);
	void Collision(SDL_Rect r);
	void SetLocation(int x, int y);
	bool* GetIsFollowingPlayer();
	bool* GetIsFalling();
private:	
	void Falling(const int* width, const int* height, float* dt);
	void FollowPlayer(SDL_Rect r);
	

	SDL_Color white;
	SDL_Rect letterRect;
	float speed;
	bool isFollowPlayer = false;
	bool isFalling;
};

