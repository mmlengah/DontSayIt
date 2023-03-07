#pragma once
#include <iostream>
#include <string>
#include <SDL_image.h>

namespace util {
	//vector 2 struct
	struct Vector2 {
		float x, y;

		Vector2() {
			x = y = 0;
		}

		Vector2(float x, float y) {
			this->x = x;
			this->y = y;
		}

		Vector2 operator+(const Vector2& v) const {
			return Vector2(x + v.x, y + v.y);
		}

		Vector2 operator-(const Vector2& v) const {
			return Vector2(x - v.x, y - v.y);
		}

		Vector2 operator*(const Vector2& v) const {
			return Vector2(x * v.x, y * v.y);
		}

		Vector2 operator/(const Vector2& v) const {
			return Vector2(x / v.x, y / v.y);
		}
	};

	//function for loading images
	static bool loadImage(const char* filePath, SDL_Renderer* r, SDL_Texture** t) {
		SDL_Surface* image = IMG_Load(filePath);
		if (image == nullptr) {
			std::cout << "could not load image. Filepath: " << filePath << std::endl;
			return false;
		}
		*t = SDL_CreateTextureFromSurface(r, image);
		SDL_FreeSurface(image);
		return true;
	}
	
}