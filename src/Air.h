#pragma once
#include "Tile.h"
#include <SFML\Graphics.hpp>

class Air : public Tile {
public:
	void init();

	Air(float x, float y, float w, float h, int id) : Tile(x, y, w, h, "Air", id) { init(); };
};