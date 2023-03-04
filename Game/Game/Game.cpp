#include "game.h"
#include <stdio.h>
#include <iostream>


const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 400;

Game::Game()
{
	p = new Player(SCREEN_WIDTH, SCREEN_HEIGHT);
}

bool Game::Init()
{
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

	
	return true;
}

bool Game::KeepAlive()
{
	if (!EventHandler()) { return false; }
	return true;
}

void Game::Update()
{
	
}

void Game::Draw()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	p->Draw(renderer);

	SDL_RenderPresent(renderer);
}

void Game::Clean()
{
	delete p;

	SDL_DestroyWindow(window);
	SDL_Quit();
}

bool Game::EventHandler()
{
	SDL_Event ev;
	while (SDL_PollEvent(&ev)) {
		if (ev.type == SDL_QUIT) {
			return false;
		}
		else if (ev.type == SDL_KEYDOWN) {
			p->PlayerInput(&ev);
			return QuitButton(&ev);
			
		}
		else if (ev.type == SDL_KEYUP) {

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
