#pragma once
#include "Tile.h"
#include <SFML\Graphics.hpp>

class Player : public Tile {
private:
	float speed = 2.0f;
	float maxSpeed = 10.0f;

	float gravity = 0.4f;
	float xvel = 0.0f;
	float yvel = 0.0f;
	
	float jumpHeight = 9.5f;
	float maxFallSpeed = 12.0f;

	bool falling = true;

public:
	Player(float x, float y, float w, float h) : Tile(x, y, w, h) {};

	void setPosition(float x, float y);

	void modify(float change);

	void collideWith(float xv, float yv, Tile tile);
	
	void update(float delta, float windowWidth, float windowHeight, std::vector<Tile> tiles);

	void jump();

	void moveLeft(float delta);

	void moveRight(float delta);
};