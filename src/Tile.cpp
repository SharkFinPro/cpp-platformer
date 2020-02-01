#include "Tile.h"

std::vector<Tile> *Tile::tiles;

void Tile::setTiles(std::vector<Tile> *_tiles) {
    tiles = _tiles;
}

Tile::Tile(float x, float y, float w, float h, std::string type_, int _id) {
    type = type_;
    id = _id;

    position.x = x;
    position.y = y;
    
    tileShape.setSize(sf::Vector2f(w, h));
    tileShape.setPosition(sf::Vector2f(position.x, position.y));
    tileShape.setFillColor(sf::Color::White);
}

sf::FloatRect Tile::getPosition() {
    return tileShape.getGlobalBounds();
}

sf::RectangleShape Tile::getShape() {
    return tileShape;
}

std::string Tile::getType() {
    return type;
}

int Tile::getDamage() {
    return damage;
}

int Tile::getId() {
    return id;
}

bool Tile::tryToFall() {
	for (int i = 0; i < 24 * 24; i++) {
		Tile t = tiles->at(i);
		if (t.getId() == id) {
			Tile n = tiles->at(i + 24);
			if (n.getType().compare("Air") == 0) {
                position.y = n.getPosition().top;
                tileShape.setPosition(sf::Vector2f(position.x, position.y));
                tiles->at(i + 24) = tiles->at(i);
                tiles->at(i) = n;
                return true;
			}
		}
	}
    return false;
}