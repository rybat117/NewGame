#ifndef PLAYER_H
#define PLAYER_H

#include "../header/animatedsprite.h"
#include "../header/globals.h"

class Graphics;

class Player : public AnimatedSprite {
public:
	Player();
	Player(Graphics &graphics, Vector2 spawnPoint);
	void draw(Graphics &graphics);
	void update(float elapsedTime);

	/* void moveLeft
	* Moves the player left by -dx
	*/
	void moveLeft();

	/* void moveRight
	* Moves the player right by dx
	*/
	void moveRight();

	///* void jump
	//* Makes the player jump
	//*/
	void jump();

	/* void stopMoving
	* Stops moving the player
	*/
	void stopMoving();

	virtual void animationDone(std::string currentAnimation);
	virtual void setupAnimation();

	void handleTileCollisions(std::vector<Rectangle>& other);

	const float getX() const;
	const float getY() const;
private:
	float _dx, _dy;

	Direction _facing;

	bool _grounded;
};

#endif
