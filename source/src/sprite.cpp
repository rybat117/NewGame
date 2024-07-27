#include "../header/sprite.h"
#include "../header/graphics.h"
#include "../header/globals.h"

Sprite::Sprite() {}

Sprite::Sprite(Graphics &graphics, const std::string& filePath, int sourceX, int sourceY, int width, int height,
		float posX, float posY) :
			_x(posX),
			_y(posY)

{
	this->_sourceRect.x = sourceX;
	this->_sourceRect.y = sourceY;
	this->_sourceRect.w = width;
	this->_sourceRect.h = height;

	this->_spriteSheet = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(filePath));
	if (this->_spriteSheet == NULL) {
		printf("\nERROR: Unable to load image\n");
	}

	this->_boundingBox = Rectangle(this->_x, this->_y, width * globals::SPRITE_SCALE, height * globals::SPRITE_SCALE);
}

Sprite::~Sprite() {}

void Sprite::draw(Graphics& graphics, int x, int y) {
	SDL_Rect destinationRectangle = { x, y, this->_sourceRect.w * globals::SPRITE_SCALE, this->_sourceRect.h * globals::SPRITE_SCALE };
	graphics.blitSurface(this->_spriteSheet, &this->_sourceRect, &destinationRectangle);
}

void Sprite::update() {
	this->_boundingBox = Rectangle(this->_x, this->_y, this->_sourceRect.w * globals::SPRITE_SCALE, this->_sourceRect.h * globals::SPRITE_SCALE);
}

const Rectangle Sprite::getBoundingBox() const {
	return this->_boundingBox;
}

//Side getCollisionSide
//Determine which side the collision occurred on
const sides::Side Sprite::getCollisionSide(Rectangle& other) const {
	int amtRight, amtLeft, amtTop, amtBottom;
	amtRight = this->getBoundingBox().getRight() - other.getLeft();
	amtLeft =  other.getRight() - this->getBoundingBox().getLeft();
	amtTop = other.getBottom() - this->getBoundingBox().getTop();
	amtBottom = this->getBoundingBox().getBottom() - other.getTop();

	int vals[4] = { abs(amtRight), abs(amtLeft), abs(amtTop), abs(amtBottom) };
	int min = vals[0];
	for (int i = 0; i < 4; i++) {
		if (vals[i] < min) {
			min = vals[i];
		}
	}

	return
		min == abs(amtRight) ? sides::RIGHT :
		min == abs(amtLeft) ? sides::LEFT :
		min == abs(amtTop) ? sides::TOP :
		min == abs(amtBottom) ? sides::BOTTOM : 
		sides::NONE;
}