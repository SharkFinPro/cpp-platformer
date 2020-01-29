#pragma once
#include "Tile.h"
#include <SFML\Graphics.hpp>

class Water : public Tile {
public:
	void init();

	Water(float x, float y, float w, float h, sf::Vector2f scale) : Tile(x, y, w, h, scale, "water") { init(); };
};