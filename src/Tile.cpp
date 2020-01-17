#include "Tile.h"

Tile::Tile() {

}

Tile::Tile(float x, float y, float w, float h, std::string type_) {
    position.x = x;
    position.y = y;

    type = type_;
    
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

std::string Tile::getType() {
    return type;
}