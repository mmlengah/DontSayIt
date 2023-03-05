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
	p->Update(SCREEN_WIDTH, SCREEN_HEIGHT, &deltaTime, bw->GetLetterRects(), bw->GetIsFollowingPlayer(), bw->GetIsFalling());
	bw->Update(&SCREEN_WIDTH, &SCREEN_HEIGHT, &deltaTime, p->GetRect(), p->GetHolding());
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

float Game::SetDeltaTime()
{
	LAST = NOW;
	NOW = SDL_GetPerformanceCounter();
	return (float)((NOW - LAST) * 1000 / (float)SDL_GetPerformanceFrequency());
}

bool Game::EventHandler()
{
	SDL_Event ev;
	while (SDL_PollEvent(&ev)) {
		if (ev.type == SDL_QUIT) {
			return false;
		}
		else if (ev.type == SDL_KEYDOWN) {
			p->PlayerKeyDown(&ev);
			return QuitButton(&ev);
			
		}
		else if (ev.type == SDL_KEYUP) {
			p->PlayerKeyUp(&ev);
		}
	}

	return true;
}

bool Game::QuitButton(SDL_Event* e)
{
	switch (e->key.keysym.scancode) {
	case SDL_SCANCODE_ESCAPE:
		return false;
	}
	return true;
}

