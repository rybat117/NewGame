#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>

#include "../header/globals.h"
#include "../header/tile.h"
#include "../header/rectangle.h"

class Graphics;
struct SDL_Texture;
struct SDL_Rect;
struct Tileset;

class Level {
public:
	Level();
	Level(std::string mapName, Vector2 spawnPoint, Graphics &graphics);
	~Level();
	void update(int elapsedTime);
	void draw(Graphics &graphics);

	std::vector<Rectangle> checkTileCollisions(const Rectangle& other);

	const Vector2 getPlayerSpawnPoint() const;

private:
	std::string _mapName;
	Vector2 _spawnPoint;

	Vector2 _size;
	Vector2 _tileSize;

	SDL_Texture* _backgroundTexture;

	std::vector<Tile> _tileList;
	std::vector<Tileset> _tilesets;
	std::vector<Rectangle> _collisionRects;

	//std::vector<SDL_Rect>

	/* void loadMap
	* loads a map
	*/
	void loadMap(std::string mapName, Graphics& graphics);
};

//Tileset structure
struct Tileset {
	SDL_Texture* Texture;
	int firstGid;

	Tileset() {
		this->firstGid = -1;
	}

	Tileset(SDL_Texture* texture, int firstGid) {
		this->Texture = texture;
		this->firstGid = firstGid;
	}
};

#endif