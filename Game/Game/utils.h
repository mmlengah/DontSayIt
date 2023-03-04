#pragma once
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

		Vector2(Vector2& v) {
			x = v.x;
			y = v.y;
		}
	};
}