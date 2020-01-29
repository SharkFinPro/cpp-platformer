#include "Tile.h"

Tile::Tile(float x, float y, float w, float h, sf::Vector2f scale, std::string type_) {
    type = type_;

    position.x = x;
    position.y = y;
    
    tileShape.setSize(sf::Vector2f(w * scale.x, h * scale.y));
    tileShape.setPosition(sf::Vector2f(position.x * scale.x, position.y * scale.y));
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