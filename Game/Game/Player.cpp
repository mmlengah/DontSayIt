#include "Player.h"
#include <iostream>



Player::Player(int width, int height)
{
	speed = 1;
	position = util::Vector2(0, (float) height);
	
	playerRect.x = (int) position.x;
	playerRect.y = (int) position.y;
	playerRect.w = (int) (width * 0.1);
	playerRect.h = (int) (height * 0.15);

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

void Player::PlayerKeyDown(SDL_Event* e)
{
	switch (e->key.keysym.scancode) {
	case SDL_SCANCODE_UP:
	case SDL_SCANCODE_W:
		keyStates[0] = true;
		break;
	case SDL_SCANCODE_DOWN:
	case SDL_SCANCODE_S:
		keyStates[1] = true;
		break;
	case SDL_SCANCODE_LEFT:
	case SDL_SCANCODE_A:
		keyStates[2] = true;
		break;
	case SDL_SCANCODE_RIGHT:
	case SDL_SCANCODE_D:
		keyStates[3] = true;
		break;
	}

	
	
}

void Player::PlayerKeyUp(SDL_Event* e)
{
	switch (e->key.keysym.scancode) {
	case SDL_SCANCODE_UP:
	case SDL_SCANCODE_W:
		keyStates[0] = false;
		break;
	case SDL_SCANCODE_DOWN:
	case SDL_SCANCODE_S:
		keyStates[1] = false;
		break;
	case SDL_SCANCODE_LEFT:
	case SDL_SCANCODE_A:
		keyStates[2] = false;
		break;
	case SDL_SCANCODE_RIGHT:
	case SDL_SCANCODE_D:
		keyStates[3] = false;
		break;
	}
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

void Player::Movement(int width, int height)
{
	//move player
	if (keyStates[0]) {
		position.y -= speed;
	}
	if (keyStates[1]) {
		position.y += speed;
	}
	if (keyStates[2]) {
		position.x -= speed;
	}
	if (keyStates[3]) {
		position.x += speed;
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
