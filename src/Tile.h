#pragma once
#include <SFML\Graphics.hpp>
#include <string>

class Tile {
protected:
	sf::Vector2f position;
	sf::RectangleShape tileShape;

	std::string type = "";

public:
	Tile();
	Tile(float x, float y, float w, float h, std::string type_);

	sf::FloatRect getPosition();

	sf::RectangleShape getShape();

	std::string getType();
};