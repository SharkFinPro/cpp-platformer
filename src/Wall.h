#pragma once
#include "Tile.h"
#include <SFML\Graphics.hpp>

class Wall : public Tile {
public:
	void init();

	Wall(float x, float y, float w, float h, sf::Vector2f scale) : Tile(x, y, w, h, scale, "wall") { init(); };
};