#pragma once
#include <SFML\Graphics.hpp>

class Tile {
protected:
	sf::Vector2f position;
	sf::RectangleShape tileShape;

	std::string type = "";

	int damage = 0;

public:
	Tile(float x, float y, float w, float h, std::string type_);

	sf::FloatRect getPosition();

	sf::RectangleShape getShape();

	std::string getType();

	int getDamage();
};