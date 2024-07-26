#ifndef GLOBALS_H
#define GLOBALS_H

// TODO: Implement scalable resolution

namespace globals {
	const int SCREEN_WIDTH = 1920;
	const int SCREEN_HEIGHT = 1080;

	const float SPRITE_SCALE = 4.0f;
}

enum Direction {
	LEFT,
	RIGHT,
	UP,
	DOWN
};

struct Vector2 {
	int x, y;
	Vector2() :
		x(0), y(0)
	{}
	Vector2(int x, int y) :
		x(x), y(y)
	{}
	Vector2 zero() {
		return Vector2(0, 0);
	}
};

#endif