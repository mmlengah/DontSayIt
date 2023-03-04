#pragma once
#include <iostream>
#include <string>

namespace util {
	

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

		Vector2 operator*(const Vector2& v) const {
			return Vector2(x / v.x, y / v.y);
		}
	};
	
}