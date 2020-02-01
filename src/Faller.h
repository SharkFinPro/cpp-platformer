#pragma once
#include "Tile.h"
#include <SFML\Graphics.hpp>

class Faller : public Tile {
public:
	void init();

	Faller(float x, float y, float w, float h, int id) : Tile(x, y, w, h, "Faller", id) { init(); };
};