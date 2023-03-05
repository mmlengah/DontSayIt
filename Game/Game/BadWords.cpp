#include "BadWords.h"
#include <string>
#include <fstream>
#include <iostream>

BadWords::BadWords()
{
	ReadFile("Assets/SwearWords/SafeWords.txt", &safeWords);
	ReadFile("Assets/SwearWords/swearWords.txt", &swearWords);
}

BadWords::~BadWords()
{
	RemoveWord();
}

void BadWords::SetUpWord(const int* width)
{	
	currentWord = swearWords.begin()->first;
	int dist = (int) (*width / currentWord.size());
	for (int i = 0; i < currentWord.size(); i++) {
		letters.push_back(new Letter(i * dist, 0, 1 * dist, (int)(dist / 1.5)));
		SDL_Rect tempRect{};
		tempRect.x = i * dist + 5;
		tempRect.y = (int)(dist / 1.5);
		tempRect.w = 1 * (dist - 10);
		tempRect.h = 5;
		letterHolder.push_back(tempRect);
	}
	now = SDL_GetTicks();
	timer = now + 2000; //add 2 seconds
}

void BadWords::RemoveWord()
{
	for (int i = 0; i < letters.size(); i++) {
		delete letters[i];
	}
	letters.resize(0);
	fall = false;
	timer = SDL_GetTicks();
}

bool BadWords::Init(const int* width)
{
	font = TTF_OpenFont("Assets/Fonts/vcr_osd_mono/VCR_OSD_MONO_1.001.ttf", 21);
	if (font == NULL) {
		return false;
	}

	SetUpWord(width);

	return true;
}

void BadWords::Update(float* dt)
{
	if (SDL_GetTicks() > timer && !fall) {
		fall = true;
		for (int i = 0; i < letters.size(); i++) {
			letters[i]->SetFalling(fall);
		}
	}

	for(int i = 0; i < letters.size(); i++){
		letters[i]->update(dt);
	}
}

void BadWords::Draw(SDL_Renderer* r)
{
	for (int i = 0; i < currentWord.size(); i++) {
		std::string s(1, currentWord[i]);
		letters[i]->draw(r, font, s.c_str());
	}

	for (int i = 0; i < letterHolder.size(); i++) {
		//make the rect white
		SDL_SetRenderDrawColor(r, 255, 255, 255, SDL_ALPHA_OPAQUE);
		SDL_RenderFillRect(r, &letterHolder[i]);
		//render it to the screen
		SDL_RenderCopy(r, NULL, NULL, &letterHolder[i]);
	}
}

void BadWords::ReadFile(const char* filepath, std::unordered_map<std::string, std::string>* words)
{
	//create file variable
	std::fstream file;
	//open the file in read mode
	file.open(filepath, std::ios::in);
	//check if file opened successfully
	if (file.is_open()) {
		std::string line;
		while (std::getline(file, line)) {
			for (int i = 0; i < line.size(); i++) {
				line[i] = std::toupper(line[i]);
			}
			(*words)[line] = line;
		}

		file.close();
	}
}
