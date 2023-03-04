#include "Player.h"
#include <iostream>



Player::Player(int width, int height)
{
	speed = 5;
	position = util::Vector2();
	
	playerRect.x = (int) position.x;
	playerRect.y = (int) position.y;
	playerRect.w = (int) (width * 0.1);
	playerRect.h = (int) (height * 0.1);
}

void Player::Draw(SDL_Renderer* r)
{
	//make the rect white
	SDL_SetRenderDrawColor(r, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(r, &playerRect);
	//render it to the screen
	SDL_RenderCopy(r, NULL, NULL, &playerRect);
}

void Player::Update()
{
}

void Player::PlayerInput(SDL_Event* e)
{
	switch (e->key.keysym.scancode) {
	case SDL_SCANCODE_W:
		position.y -= speed;
		break;
	case SDL_SCANCODE_S:
		position.y += speed;
		break;
	case SDL_SCANCODE_A:
		position.x -= speed;
		break;
	case SDL_SCANCODE_D:
		position.x += speed;
		break;
	}

	playerRect.x = (int)position.x;
	playerRect.y = (int)position.y;
	


}
