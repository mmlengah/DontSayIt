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
	~BadWords();
	bool Init(const int* width);
	void Draw(SDL_Renderer* r);
	void SetUpWord(const int* width);
	void RemoveWord();
private:
	void ReadFile(const char* filepath, std::unordered_map<std::string, std::string>* words);
	std::unordered_map<std::string, std::string> safeWords;
	std::unordered_map<std::string, std::string> swearWords;
	TTF_Font* font = nullptr;

	std::vector<Letter*> letters;
	std::vector<SDL_Rect> letterHolder;

	std::string currentWord;
};

