#pragma once
#include "Tile.h"
#include <SFML\Graphics.hpp>

class JumpPad : public Tile {
public:
	void init();

	JumpPad(float x, float y, float w, float h) : Tile(x, y, w, h, "JumpPad") { init(); };
};