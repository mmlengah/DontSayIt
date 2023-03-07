#pragma once
#include <SDL.h>
#include <unordered_map>
#include <vector>
#include <string>
#include "Letter.h"
#include "AudioManager.h"
class BadWords
{
public:
	BadWords();
	~BadWords();
	bool Init(const int* width);
	void Update(const int* width, const int* height, double* dt, SDL_Rect r, AudioManager* am);
	void Draw(SDL_Renderer* r);
	void SetUpWord(const int* width);
	void RemoveWord();
	void LetterCollidedWithPlayer(int i);
	void LetterCollidedWithHolder(int i, int j);
	void SendLetterBack(int i);
	bool CanPlaceWords();
	bool IsLetterPlaced(int i);
	bool GetIsSomeOneOnme(int i);
	bool StartNextLevel(const int* width);
	std::vector<SDL_Rect> GetLetterRects();
	std::vector<SDL_Rect> GetLetterHolderRects();	
private:
	void ReadFile(const char* filepath, std::unordered_map<std::string, std::string>* words);
	void startNextWord(AudioManager* am);
	std::string FormatWord();
	std::unordered_map<std::string, std::string> safeWords;
	std::unordered_map<std::string, std::string> ourSwearWords;
	std::unordered_map<std::string, std::string> otherSwearWords;
	std::vector<std::string>  ourSwearWordsVector;

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
	Uint32 changeWordTimer;
	bool fall = false;
	bool playedSafe = false;
};

