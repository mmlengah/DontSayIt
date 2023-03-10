#include "game.h"
#include <stdio.h>
#include <iostream>
#include <ctime>

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 400;

Game::Game()
{
	srand((unsigned int)time(NULL));
	p = new Player(SCREEN_WIDTH, SCREEN_HEIGHT);
	bw = new BadWords();
	am = new AudioManager();
}

bool Game::Init()
{
	//sdl2
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "could not initialize SDL2!" << std::endl;
		std::cout << SDL_GetError() << std::endl;
		return false;
	}

	window = SDL_CreateWindow(
		"Don't say it",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN
	);

	if (window == NULL) {
		std::cout << "could not initialise window!" << std::endl;
		std::cout << SDL_GetError() << std::endl;
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		std::cout << "could not initialise renderer" << std::endl;
		std::cout << SDL_GetError() << std::endl;
		return false;
	}

	screenSurface = SDL_GetWindowSurface(window);
	SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0, 0, 0));
	SDL_UpdateWindowSurface(window);

	//init ttf
	if (TTF_Init() != 0) {
		std::cout << SDL_GetError() << std::endl;
	}

	//init mixer
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		std::cout << SDL_GetError() << std::endl;
	}

	//init the player
	p->init(renderer);
	bw->Init(&SCREEN_WIDTH);
	am->init();
	am->playBackgroundMusic();

	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;
	float deltaTime = 0;

	return true;
}

bool Game::KeepAlive()
{
	if (!EventHandler()) { return false; }
	return true;
}

void Game::Update()
{
	deltaTime = SetDeltaTime();
	p->Update(SCREEN_WIDTH, SCREEN_HEIGHT, &deltaTime);
	bw->Update(&SCREEN_WIDTH, &SCREEN_HEIGHT, &deltaTime, p->GetRect(), am);
	Collisions();

	if (bw->StartNextLevel(&SCREEN_WIDTH)) {
		p->Reset();
	}
}

void Game::Draw()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	p->Draw(renderer);
	bw->Draw(renderer);

	SDL_RenderPresent(renderer);
}

void Game::Clean()
{
	delete p;

	bw->RemoveWord();
	delete bw;

	SDL_DestroyWindow(window);
	SDL_Quit();
}

double Game::SetDeltaTime()
{
	LAST = NOW;
	NOW = SDL_GetPerformanceCounter();
	return (double)((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());
}

bool Game::EventHandler()
{
	SDL_Event ev;
	while (SDL_PollEvent(&ev)) {
		if (ev.type == SDL_QUIT) {
			return false;
		}
		else if (ev.type == SDL_KEYDOWN) {
			switch (ev.key.keysym.scancode) {
				case SDL_SCANCODE_ESCAPE:
					return false;
					break;
				case SDL_SCANCODE_UP:
				case SDL_SCANCODE_W:
#if _DEBUG
					if (!p->GetKeyStates(0)) {
						std::cout << "up arrow / W pressed" << std::endl;
					}
				
#endif // DEBUG
					p->PlayerMoveUp(true);
					
					break;
				case SDL_SCANCODE_DOWN:
				case SDL_SCANCODE_S:

#if _DEBUG
					if (!p->GetKeyStates(1)) {
						std::cout << "down arrow / S pressed" << std::endl;
					}
				
#endif // DEBUG
					p->PlayerMoveDown(true);
					break;
				case SDL_SCANCODE_LEFT:
				case SDL_SCANCODE_A:

#if _DEBUG
					if (!p->GetKeyStates(2)) {
						std::cout << "left arrow / A pressed" << std::endl;
					}
				
#endif // DEBUG
					p->PlayerMoveLeft(true);
					break;
				case SDL_SCANCODE_RIGHT:
				case SDL_SCANCODE_D:
#if _DEBUG
					if (!p->GetKeyStates(3)) {
						std::cout << "right arrow / D pressed" << std::endl;
					}				
#endif // DEBUG
					p->PlayerMoveRight(true);
					break;
			}
			return true;
			
		}
		else if (ev.type == SDL_KEYUP) {
			switch (ev.key.keysym.scancode) {
				case SDL_SCANCODE_UP:
				case SDL_SCANCODE_W:
#if _DEBUG
				std::cout << "up arrow / W released" << std::endl;
#endif // DEBUG
					p->PlayerMoveUp(false);
					break;
				case SDL_SCANCODE_DOWN:
				case SDL_SCANCODE_S:

#if _DEBUG
				std::cout << "down arrow / S released" << std::endl;
#endif // DEBUG
					p->PlayerMoveDown(false);
					break;
				case SDL_SCANCODE_LEFT:
				case SDL_SCANCODE_A:

#if _DEBUG
				std::cout << "left arrow / A released" << std::endl;
#endif // DEBUG
					p->PlayerMoveLeft(false);
					break;
				case SDL_SCANCODE_RIGHT:
				case SDL_SCANCODE_D:
#if _DEBUG
				std::cout << "right arrow / D released" << std::endl;
#endif // DEBUG
					p->PlayerMoveRight(false);
					break;
			}
		}
	}

	return true;
}

void Game::Collisions()
{
	//if player touches a letter
	std::vector<SDL_Rect> letterRects = bw->GetLetterRects();
	for (int i = 0; i < letterRects.size(); i++) {
		if (p->GetHolding()) {	break; }
		if (bw->IsLetterPlaced(i)) { continue; }
		SDL_Rect playerRect = p->GetRect();
		if (SDL_HasIntersection(&letterRects[i], &playerRect)) {
			am->PlayPickUp();
			p->collidedWithLetter();
			bw->LetterCollidedWithPlayer(i);
		}
	}

	//if letter touches letter holder
	std::vector<SDL_Rect> letterHolderRects = bw->GetLetterHolderRects();
	for (int i = 0; i < letterRects.size(); i++) {
		for (int j = 0; j < letterHolderRects.size(); j++) {
			//if you can place words and there are colliding
			if (!bw->GetIsSomeOneOnme(j) && !bw->IsLetterPlaced(i) && bw->CanPlaceWords() && SDL_HasIntersection(&letterRects[i], &letterHolderRects[j])) {
				bw->LetterCollidedWithHolder(i, j);
				p->StopHolding();
			}			
		}		
	}

	//player collides with rect
	for (int i = 0; i < letterHolderRects.size(); i++) {
		//if player touches rect 
		SDL_Rect playerRect = p->GetRect();
		if (bw->GetIsSomeOneOnme(i) && SDL_HasIntersection(&letterHolderRects[i], &playerRect)) {
			am->PlayDroppedItem();
			bw->SendLetterBack(i);			
		}
	}
}

