#pragma once
#include "Tile.h"
#include <SFML\Graphics.hpp>

class Player : public Tile {
private:
	int health = 100;

	float startX = 0.0f;
	float startY = 0.0f;

	float speed = 4.0f;
	float maxSpeed = 20.0f;

	float gravity = 0.8f;
	float xvel = 0.0f;
	float yvel = 0.0f;
	
	float jumpHeight = 19.0f;
	float maxFallSpeed = 24.0f;

	bool falling = true;

	sf::Vector2u window;

	std::string state = "";

	std::vector<Tile> *tiles;
	
	int *shadow;

public:
	void init(std::vector<Tile> *items, int *shadow, sf::Vector2u window);

	Player(float x, float y, float w, float h, std::vector<Tile> *items, int *shadow, sf::Vector2u window, sf::Vector2f scale) : Tile(x, y, w, h, scale, "player") { init(items, shadow, window); };

	void reset();

	void setPosition(float x, float y);

	bool collideWith(float xv, float yv, Tile *tile);
	
	void update();

	void jump();

	void moveLeft();

	void moveRight();

	int getHealth();
};