#pragma once
#include "Tile.h"
#include <SFML\Graphics.hpp>

class Lava : public Tile {
public:
	void init();

	Lava(float x, float y, float w, float h, int id) : Tile(x, y, w, h, "lava", id) { init(); };
};