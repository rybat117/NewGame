#include "../header/player.h"
#include "../header/graphics.h"

namespace player_constants {
	const float WALK_SPEED = 0.1f * globals::SPRITE_SCALE;
	const float JUMP_HEIGHT = -0.2f * globals::SPRITE_SCALE;
	const float GRAVITY = 0.0005f * globals::SPRITE_SCALE;
}

Player::Player() {}

Player::Player(Graphics &graphics, float x, float y) :
	AnimatedSprite(graphics, "assets/sprites/MyChar.png", 0, 0, 16, 16, x, y, 100)
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
	this->addAnimation(1, 0, 0, "JumpLeft", 16, 16, Vector2(0, 0));
	this->addAnimation(1, 0, 16, "JumpRight", 16, 16, Vector2(0, 0));
}

void Player::animationDone(std::string currentAnimation) {}

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
	if (this->_dy == 0) {
		this->_dy = player_constants::JUMP_HEIGHT;
	}
	this->playAnimation(this->_facing == RIGHT ? "JumpRight" : "JumpLeft");
}

void Player::stopMoving() {
	this->_dx = 0;
	this->playAnimation(this->_facing == RIGHT ? "IdleRight" : "IdleLeft");
}

void Player::update(float elapsedTime) {
	// Move by dx and dy
	this->_x += this->_dx * elapsedTime;
	this->_y += this->_dy * elapsedTime;
	if (this->_y < globals::SCREEN_HEIGHT * 0.6) {
			this->_dy += player_constants::GRAVITY * elapsedTime;	
	}
	else {
		this->_dy = 0;
	}

	AnimatedSprite::update(elapsedTime);
}

void Player::draw(Graphics &graphics) {
	AnimatedSprite::draw(graphics, this->_x, this->_y);
}