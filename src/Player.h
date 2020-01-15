#pragma once
#include "Tile.h"
#include <SFML\Graphics.hpp>

class Player : public Tile {
private:
	float speed = 4.0f;
	float maxSpeed = 15.0f;

	float gravity = 0.25f;
	float xvel = 0.0f;
	float yvel = 0.0f;
	
	float jumpHeight = 10.0f;
	float maxFallSpeed = 7.5f;

	bool falling = true;

public:
	Player(float x, float y, float w, float h) : Tile(x, y, w, h) {};

	void updateSpeeds(int change);

	void collideWith(float xv, float yv, Tile tile);
	
	void update(float delta, float windowWidth, float windowHeight, std::vector<Tile> tiles);

	void jump();

	void moveLeft(float delta);

	void moveRight(float delta);
};