#include "../header/player.h"
#include "../header/graphics.h"

namespace player_constants {
	const float WALK_SPEED = 0.1f * globals::SPRITE_SCALE;
	const float JUMP_HEIGHT = -0.20f * globals::SPRITE_SCALE;
	const float GRAVITY = 0.00075f * globals::SPRITE_SCALE;
	const float GRAVITY_CAP = 0.3f * globals::SPRITE_SCALE;
}

Player::Player() {}

Player::Player(Graphics &graphics, Vector2 spawnPoint) :
	AnimatedSprite(graphics, "assets/sprites/MyChar.png", 0, 0, 16, 16, spawnPoint.x, spawnPoint.y, 100),
	_dx(0),
	_dy(0),
	_facing(RIGHT),
	_grounded(false),
	_jumpCount(0)
{
	graphics.loadImage("assets/sprites/MyChar.png");

	this->setupAnimation();
	this->playAnimation("RunRight");
}

void Player::setupAnimation() {
	this->addAnimation(1, 0, 0, "IdleLeft", 16, 16, Vector2(0, 0));
	this->addAnimation(1, 0, 16, "IdleRight", 16, 16, Vector2(0, 0));
	this->addAnimation(3, 0, 0, "RunLeft", 16, 16, Vector2(0,0));
	this->addAnimation(3, 0, 16, "RunRight", 16, 16, Vector2(0,0));
	this->addAnimation(1, 8, 0, "JumpLeft", 16, 16, Vector2(0, 0));
	this->addAnimation(1, 8, 16, "JumpRight", 16, 16, Vector2(0, 0));
}

void Player::animationDone(std::string currentAnimation) {}

const float Player::getX() const {
	return this->_x;
}

const float Player::getY() const {
	return this->_y;
}

void Player::moveLeft() {
	this->_dx = -player_constants::WALK_SPEED;
	this->playAnimation("RunLeft");
	this->_facing = LEFT;
}

void Player::moveRight() {
	this->_dx = player_constants::WALK_SPEED;
	this->playAnimation("RunRight");
	this->_facing = RIGHT;
}

void Player::jump() {
	if (this->_jumpCount < 2) {
		this->_dy = 0;
		this->_dy += player_constants::JUMP_HEIGHT;
		this->_grounded = false;
		this->playAnimation(this->_facing == RIGHT ? "JumpRight" : "JumpLeft");
		this->_jumpCount++;
	}
}

void Player::stopMoving() {
	if (this->_grounded) {
		this->_dx = 0;
		this->playAnimation(this->_facing == RIGHT ? "IdleRight" : "IdleLeft");
	}
}

//void handleTileCollision
//Handles collisions with all tiles the player is colliding with
void Player::handleTileCollisions(std::vector<Rectangle>& other) {
	//Figure out what side the collision happened on and move the player accordingly
	for (int i = 0; i < other.size(); i++) {
		sides::Side collisionSide = Sprite::getCollisionSide(other.at(i));
		if (collisionSide != sides::NONE) {
			switch (collisionSide) {
			case sides::TOP:
				this->_dy = 0;
				this->_y = other.at(i).getBottom() + 1;
				if (this->_grounded) {
					this->_dx = 0;
					this->_x -= this->_facing == RIGHT ? 1.0f : -1.0f;
				}
				break;
			case sides::BOTTOM:
				this->_y = other.at(i).getTop() - this->_boundingBox.getHeight() - 1;
				this->_dy = 0;
				this->_grounded = true;
				this->_jumpCount = 0;
				break;
			case sides::LEFT:
				this->_x = other.at(i).getRight() + 1;
				break;
			case sides::RIGHT:
				this->_x = other.at(i).getLeft() - this->_boundingBox.getWidth() - 1;
				break;
			}
		}
	}
}
//void handleSlopeCollisions
//Handles collisions with all slopes the player collides with
void Player::handleSlopeCollisions(std::vector<Slope>& others) {
	for (int i = 0; i < others.size(); i++) {
		int b = (others.at(i).getP1().y - (others.at(i).getSlope() * fabs(others.at(i).getP1().x)));

		int centerX = this->_boundingBox.getCenterX();
		int newY = (others.at(i).getSlope() * centerX) + b - 8;

		if (this->_grounded) {
			this->_y = newY - this->_boundingBox.getHeight();
			this->_grounded = true;
			this->_jumpCount = 0;
		}

	}

}

void Player::update(float elapsedTime) {
	// Apply gravity
	if (this->_dy <= player_constants::GRAVITY_CAP) {
		this->_dy += player_constants::GRAVITY * elapsedTime;
	}

	// Move by dx
	this->_x += this->_dx * elapsedTime;
	// Move by dy
	this->_y += this->_dy * elapsedTime;

	AnimatedSprite::update(elapsedTime);
}

void Player::draw(Graphics &graphics) {
	AnimatedSprite::draw(graphics, this->_x, this->_y);
}