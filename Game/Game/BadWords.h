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
	void Update(const int* width, const int* height, float* dt, SDL_Rect r);
	void Draw(SDL_Renderer* r);
	void SetUpWord(const int* width);
	void RemoveWord();
	void LetterCollidedWithPlayer(int i);
	void LetterCollidedWithHolder(int i, int j);
	void SendLetterBack(int i);
	bool CanPlaceWords();
	bool IsLetterPlaced(int i);
	bool GetIsSomeOneOnme(int i);
	std::vector<SDL_Rect> GetLetterRects();
	std::vector<SDL_Rect> GetLetterHolderRects();
	void startNextWord();
private:
	void ReadFile(const char* filepath, std::unordered_map<std::string, std::string>* words);
	std::string FormatWord();
	std::unordered_map<std::string, std::string> safeWords;
	std::unordered_map<std::string, std::string> swearWords;

	TTF_Font* font = nullptr;

	std::vector<Letter*> letters;
	std::vector<SDL_Rect> letterHolder;
	std::vector<int> isSomeoneOnMe;
	std::vector<std::vector<int>> startingLocations;
	std::string currentWord;
	std::string createdWord;

	Uint32 now;
	Uint32 timer;
	Uint32 placedTimer;
	bool fall = false;
	bool stopHolding = false;
};

