#include "Tile.h"
#include <cstdlib>

Tile::Tile(float x, float y, float w, float h) {
    position.x = x;
    position.y = y;
    
    tileShape.setSize(sf::Vector2f(w, h));
    tileShape.setPosition(position);
    tileShape.setFillColor(sf::Color(std::rand() % 255 + 1, std::rand() % 255 + 1, std::rand() % 255 + 1));
}

sf::FloatRect Tile::getPosition() {
    return tileShape.getGlobalBounds();
}

sf::RectangleShape Tile::getShape() {
    return tileShape;
}
