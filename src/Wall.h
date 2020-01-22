#pragma once
#include "Tile.h"
#include <SFML\Graphics.hpp>

class Wall : public Tile {
public:
	void init();

	Wall(float x, float y, float w, float h) : Tile(x, y, w, h, "wall") { init(); };
};