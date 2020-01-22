#include "Tile.h"

Tile::Tile(float x, float y, float w, float h, std::string type_) {
    type = type_;

    position.x = x;
    position.y = y;
    
    tileShape.setSize(sf::Vector2f(w, h));
    tileShape.setPosition(position);
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