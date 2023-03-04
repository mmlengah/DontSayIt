#pragma once
#include <SDL.h>
#include <unordered_map>
#include <vector>
#include <string>
#include "Letter.h"

class BadWords
{
public:
	BadWords();
	bool Init();
	void Draw(SDL_Renderer* r);
private:
	void ReadFile(const char* filepath);
	std::unordered_map<std::string, std::string> words;
	TTF_Font* font = nullptr;

	std::vector<Letter*> letters;
};

