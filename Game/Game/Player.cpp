#include "Player.h"
#include <iostream>



Player::Player(int width, int height)
{
	speed = 5;
	position = util::Vector2();
	
	playerRect.x = (int) position.x;
	playerRect.y = (int) position.y;
	playerRect.w = (int) (width * 0.1);
	playerRect.h = (int) (height * 0.15);

	for (int i = 0; i < 8; i++) {
		textures.push_back(nullptr);
	}
}

Player::~Player()
{
	for (int i = 0; i < textures.size(); i++) {
		SDL_DestroyTexture(textures[i]);
	}	
}

bool Player::init(SDL_Renderer* r)
{
	//load image in
	for (int i = 0; i < 4; i++) {
		if (!util::loadImage(("Assets/Player/HandsDown/Moving_sprite_" + std::to_string(i+1) + ".png").c_str(), 
			r, &(textures[i]))) {
			return false;
		}
	}
	
	return true;
}

void Player::Draw(SDL_Renderer* r)
{
	//make the rect white
	//SDL_SetRenderDrawColor(r, 255, 255, 255, SDL_ALPHA_OPAQUE);
	//SDL_RenderFillRect(r, &playerRect);
	//render it to the screen
	SDL_RenderCopy(r, textures[animationFrame], NULL, &playerRect);
}

void Player::Update(int width, int height)
{
	Movement(width, height);
	
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

	//animate when moving
	Animation();
	
}

void Player::Animation()
{
	if (playerRect.x != (int)position.x || playerRect.y != (int)position.y) {
		animationFrame += 1;
		if (animationFrame > 3) {
			animationFrame = 0;
		}
	}
}

void Player::Movement(int width, int height)
{
	playerRect.x = (int)position.x;
	playerRect.y = (int)position.y;

	if (playerRect.x <= 0) {
		playerRect.x = 0;
		position.x = 0;		
	}
	if (playerRect.y <= 0) {
		playerRect.y = 0;
		position.y = 0;		
	}
	if (playerRect.x >= width - playerRect.w) {
		playerRect.x = (int) (width - playerRect.w);
		position.x = (float) (width - playerRect.w);
	}
	if (playerRect.y >= height - playerRect.h) {
		playerRect.y = (int)(height - playerRect.h);
		position.y = (float)(height - playerRect.h);
	}
	
}
