#pragma once
#include "Tile.h"
#include <SFML\Graphics.hpp>

class Player : public Tile {
private:
	float speed = 8.0f;
	float maxSpeed = 30.0f;

	float gravity = 0.5f;
	float xvel = 0.0f;
	float yvel = 0.0f;
	
	float jumpHeight = 20.0f;
	float maxFallSpeed = 15.0f;

	bool falling = true;

public:
	Player(float x, float y, float w, float h) : Tile(x, y, w, h) {};

	void collideWith(float xv, float yv, Tile tile);
	
	void update(float delta, float windowWidth, float windowHeight, std::vector<Tile> tiles);

	void jump();

	void moveLeft(float delta);

	void moveRight(float delta);
};