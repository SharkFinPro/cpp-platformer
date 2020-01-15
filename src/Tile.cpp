#include "Tile.h"

Tile::Tile(float x, float y, float w, float h) {
    position.x = x;
    position.y = y;
    
    tileShape.setSize(sf::Vector2f(w, h));
    tileShape.setPosition(position);
    tileShape.setFillColor(sf::Color(125, 125, 125));
}

sf::FloatRect Tile::getPosition() {
    return tileShape.getGlobalBounds();
}

sf::RectangleShape Tile::getShape() {
    return tileShape;
}
