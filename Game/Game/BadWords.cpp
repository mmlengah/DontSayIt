#include "BadWords.h"
#include <string>
#include <fstream>
#include <iostream>

BadWords::BadWords()
{
	ReadFile("Assets/SwearWords/Motherfucker.txt");
	std::string m = "MOTHERFUCKER";
	for (int i = 0; i < m.size(); i++) {
		letters.push_back(new Letter(i * 50, 0));
	}
}

bool BadWords::Init()
{
	font = TTF_OpenFont("Assets/Fonts/vcr_osd_mono/VCR_OSD_MONO_1.001.ttf", 21);
	if (font == NULL) {
		return false;
	}

	return true;
}

void BadWords::Draw(SDL_Renderer* r)
{
	std::string m = "MOTHERFUCKER";
	for (int i = 0; i < m.size(); i++) {
		std::string s(1, m[i]);
		letters[i]->draw(r, font, s.c_str());
	}
}

void BadWords::ReadFile(const char* filepath)
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
			words[line] = line;
		}

		file.close();
	}
}
