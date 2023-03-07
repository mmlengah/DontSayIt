#include "BadWords.h"
#include <string>
#include <fstream>
#include <iostream>
#include <iterator>

BadWords::BadWords()
{
	ReadFile("Assets/SwearWords/SafeWords.txt", &safeWords);
	ReadFile("Assets/SwearWords/badWords.txt", &ourSwearWords);
	otherSwearWords = ourSwearWords;
	otherSwearWords["COCK"] = "COCK";
	otherSwearWords["FUCK"] = "FUCK";
	otherSwearWords["FUCKERS"] = "FUCKERS";
	otherSwearWords["FUCKER"] = "FUCKER";

	for (auto const& x : ourSwearWords)
	{
		ourSwearWordsVector.push_back(x.second);
	}
}

BadWords::~BadWords()
{
	RemoveWord();
}

void BadWords::SetUpWord(const int* width)
{	
	playedSafe = false;
	startingLocations = {};
	letterHolder = {};
	isSomeoneOnMe = {};
	startingLocations = {};
	currentWord = "";
	createdWord = "";
	currentWord = ourSwearWordsVector[rand() % ourSwearWordsVector.size()];
	int dist = (int) (*width / currentWord.size());
	for (int i = 0; i < currentWord.size(); i++) {
		createdWord += "_";
		startingLocations.push_back({ i * dist, 0 });
		isSomeoneOnMe.push_back(-1);
		letters.push_back(new Letter(i * dist, 0, 1 * dist, (int)(dist / 1.5)));
		SDL_Rect tempRect{};
		tempRect.x = i * dist + 5;
		tempRect.y = (int)(dist / 1.5);
		tempRect.w = 1 * (dist - 10);
		tempRect.h = 5;		
		letterHolder.push_back(tempRect);
	}
	now = SDL_GetTicks();
	placedTimer = SDL_GetTicks();
	timer = now + 2000; //add 2 seconds
	fall = false;
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

void BadWords::LetterCollidedWithPlayer(int i)
{
	letters[i]->CollidedWithPlayer();
}

void BadWords::LetterCollidedWithHolder(int i, int j)
{
	letters[i]->SetFollowPlayer(false);
	letters[i]->SetLocation(startingLocations[j][0], startingLocations[j][1]);
	letters[i]->SetPlaced(true);
	isSomeoneOnMe[j] = i;
	createdWord[j] = currentWord[i];
	playedSafe = false;
#if _DEBUG
	std::cout << createdWord << std::endl;
#endif 						
}

void BadWords::SendLetterBack(int i)
{	
	int j = isSomeoneOnMe[i];
	letters[j]->SetFollowPlayer(false);
	letters[j]->SetPlaced(false);
	letters[j]->SetLocation(startingLocations[j][0], 400 - letters[j]->GetRect().h);
	isSomeoneOnMe[i] = -1;
	createdWord[i] = '_';
	playedSafe = false;
#if _DEBUG
	std::cout << createdWord << std::endl;
#endif 		
}

bool BadWords::CanPlaceWords()
{
	return (SDL_GetTicks() > timer + 500 && fall);
}

bool BadWords::IsLetterPlaced(int i)
{
	return letters[i]->GetPlaced();
}

bool BadWords::GetIsSomeOneOnme(int i)
{
	if (isSomeoneOnMe[i] >= 0) { return true; }
	return false;
}

bool BadWords::StartNextLevel(const int* width)
{
	if (playedSafe && changeWordTimer < SDL_GetTicks()) {		
		RemoveWord();
		SetUpWord(width);
	}
	return (playedSafe && changeWordTimer < SDL_GetTicks());
}

std::vector<SDL_Rect> BadWords::GetLetterRects()
{
	std::vector<SDL_Rect> n;
	for (int i = 0; i < letters.size(); i++) {
		n.push_back(letters[i]->GetRect());
	}
	return n;
}

std::vector<SDL_Rect> BadWords::GetLetterHolderRects()
{
	return letterHolder;
}

void BadWords::startNextWord(AudioManager* am)
{
	if (ourSwearWords.contains(FormatWord()) || otherSwearWords.contains(FormatWord())) {
		am->playBetterBackgroundMusic();
	}
	else if (safeWords.contains(FormatWord()) && !playedSafe) {		
		am->PlayOkWord();
		playedSafe = true;
		changeWordTimer = SDL_GetTicks() + 5000;//5 second timer
	}
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

void BadWords::Update(const int* width, const int* height, double* dt, SDL_Rect r, AudioManager* am)
{
	if (SDL_GetTicks() > timer && !fall) {
		fall = true;
		for (int i = 0; i < letters.size(); i++) {
			letters[i]->SetFalling(fall);
		}
	}

	for(int i = 0; i < letters.size(); i++){
		letters[i]->update(width, height, dt, r);
	}

	startNextWord(am);
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
			(*words)[line] = line;
		}

		file.close();
	}
}

std::string BadWords::FormatWord()
{
	std::string o;
	bool started = false;
	for (int i = 0; i < createdWord.size(); i++) {
		if (createdWord[i] != '_' && !started) {
			started = true;
			o += createdWord[i];
		}
		else if (createdWord[i] != '_') {
			o += createdWord[i];
		}
		else if (createdWord[i] == '_' && started) {
			break;
		}
	}
	return o;
}
