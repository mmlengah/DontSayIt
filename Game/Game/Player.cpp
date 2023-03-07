#include "Player.h"
#include <iostream>



Player::Player(int width, int height)
{
	speed = 0.3f;
	position = util::Vector2(0, (float) height);

	
	playerRect.x = (int) position.x;
	playerRect.y = (int) position.y;
	playerRect.w = (int) (width * 0.1);
	playerRect.h = (int) (height * 0.15);

	if (position.y >= height - playerRect.h) {
		position.y = (float)(height - playerRect.h);
		playerRect.y = (int)position.y;
	}

	for (int i = 0; i < 8; i++) {
		textures.push_back(nullptr);
	}

	animationFrame = 0;
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
	//load other images in
	for (int i = 4; i < 8; i++) {
		if (!util::loadImage(("Assets/Player/HandsUp/Moving_sprite_arms_up_" + std::to_string(i - 3) + ".png").c_str(),
			r, &(textures[i]))) {
			return false;
		}
	}
	
	return true;
}

void Player::Draw(SDL_Renderer* r)
{	
	SDL_RenderCopy(r, textures[animationFrame], NULL, &playerRect);
}

void Player::Update(int width, int height, double* dt)
{
	Movement(width, height, dt);
}

void Player::PlayerMoveLeft(bool b)
{
	if (keyStates[2] == b) { return; }
	keyStates[2] = b;
}

void Player::PlayerMoveRight(bool b)
{
	if (keyStates[3] == b) { return; }
	keyStates[3] = b;
}

void Player::PlayerMoveUp(bool b)
{
	if (keyStates[0] == b) { return; }
	keyStates[0] = b;
}

void Player::PlayerMoveDown(bool b)
{
	if (keyStates[1] == b) { return; }
	keyStates[1] = b;
}

bool Player::GetKeyStates(int i)
{
	return keyStates[i];
}

SDL_Rect Player::GetRect()
{
	return playerRect;
}

float* Player::GetPosY()
{
	return &position.y;
}

bool Player::GetHolding()
{
	return holding;
}

void Player::StopHolding()
{
	holding = false;
	animationFrame = 0;
}

void Player::collidedWithLetter()
{
	if (holding) { return; }
	holding = true;
	animationFrame = 4;
}

void Player::Reset()
{
	position.y = 400;
	if (position.y >= 400 - playerRect.h) {
		position.y = (float)(400 - playerRect.h);
		playerRect.y = (int)position.y;
	}
	animationFrame = 0;
	holding = false;
}

void Player::Animation()
{
	//arms down = 0, 1, 2, 3;
	//arms up 4, 5, 6, 7;
	int limit = 3;
	if (holding) { limit += 4; }
	if (playerRect.x != (int)position.x || playerRect.y != (int)position.y) {
		animationFrame += 1;
		if (animationFrame > limit) {
			if (holding) { animationFrame = 4; }
			else { animationFrame = 0; }
			
		}
	}
}

void Player::Movement(int width, int height, double* dt)
{
	//move player
	if (keyStates[0]) {
		position.y -= (float) (speed * *dt);
	}
	if (keyStates[1]) {
		position.y += (float)(speed * *dt);
	}
	if (keyStates[2]) {
		position.x -= (float)(speed * *dt);
	}
	if (keyStates[3]) {
		position.x += (float)(speed * *dt);
	}

	if (keyStates[3] || keyStates[2] || keyStates[1] || keyStates[0]) {
		//animate when moving
		Animation();
	}

	playerRect.x = (int)position.x;
	playerRect.y = (int)position.y;


	//keep player in bounds
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

