#pragma once
#include <SFML\Graphics.hpp>

class Tile {
protected:
	sf::Vector2f position;
	sf::RectangleShape tileShape;

public:
	Tile(float x, float y, float w, float h);

	sf::FloatRect getPosition();

	sf::RectangleShape getShape();
};