#include "JumpPad.h"

void JumpPad::init() {
	tileShape.setSize(sf::Vector2f(tileShape.getSize().x, tileShape.getSize().y / 5));
	tileShape.setPosition(tileShape.getPosition().x, tileShape.getPosition().y + tileShape.getSize().y * 4);
	tileShape.setFillColor(sf::Color(150, 150, 150));
}