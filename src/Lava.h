#pragma once
#include "Tile.h"
#include <SFML\Graphics.hpp>

class Lava : public Tile {
private:
	float damage = 1;

public:
	void init();

	Lava(float x, float y, float w, float h, sf::Vector2f scale) : Tile(x, y, w, h, scale, "lava") { init(); };
};