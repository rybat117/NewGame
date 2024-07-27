#ifndef SPRITE_H
#define SPRITE_H

#include <SDL.h>
#include <string>

#include "../header/rectangle.h"
#include "../header/globals.h"

class Graphics;

/* Sprite class
* Holds all information for sprite classes
*/

class Sprite {
public:
	Sprite();
	Sprite(Graphics &graphics, const std::string& filePath, int SourceX, int sourceY, int width, int height,
		float posX, float posY);
	virtual ~Sprite();
	virtual void update();
	void draw(Graphics &graphics, int x, int y);

	const Rectangle getBoundingBox() const;
	const sides::Side getCollisionSide(Rectangle &other) const;

protected:
	SDL_Rect _sourceRect;
	SDL_Texture* _spriteSheet;

	Rectangle _boundingBox;

	float _x, _y;
private:
};

#endif