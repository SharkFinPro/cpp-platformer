#pragma once
#include <SFML\Graphics.hpp>

class Tile {
protected:
	static std::vector<Tile>* tiles;

	int id;

	sf::Vector2f position;
	sf::RectangleShape tileShape;

	std::string type = "";

	int damage = 0;

public:
	static void setTiles(std::vector<Tile> *tiles);

	Tile(float x, float y, float w, float h, std::string type_, int id);

	sf::FloatRect getPosition();

	sf::RectangleShape getShape();

	std::string getType();

	int getDamage();

	int getId();

	bool tryToFall();
};