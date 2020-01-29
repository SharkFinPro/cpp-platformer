#pragma once
#include "Tile.h"
#include <SFML\Graphics.hpp>

class Player : public Tile {
private:
	float startX = 0.0f;
	float startY = 0.0f;

	float speed = 2.0f;
	float maxSpeed = 10.0f;

	float gravity = 0.4f;
	float xvel = 0.0f;
	float yvel = 0.0f;
	
	float jumpHeight = 9.5f;
	float maxFallSpeed = 12.0f;

	bool falling = true;

	std::string state = "";

	std::vector<Tile> *tiles;
	
	int *shadow;

public:
	void init(float change, std::vector<Tile> *items, int *shadow);

	Player(float x, float y, float w, float h, float change, std::vector<Tile> *items, int *shadow) : Tile(x, y, w, h, "player") { init(change, items, shadow); };

	void reset();

	void setPosition(float x, float y);

	bool collideWith(float xv, float yv, Tile *tile);
	
	void update();

	void jump();

	void moveLeft();

	void moveRight();
};