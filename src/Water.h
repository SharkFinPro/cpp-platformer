#pragma once
#include "Tile.h"
#include <SFML\Graphics.hpp>

class Water : public Tile {
public:
	void init();

	Water(float x, float y, float w, float h) : Tile(x, y, w, h, "water") { init(); };
};