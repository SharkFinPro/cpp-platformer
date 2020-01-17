#include "Player.h"
#include <vector>
#include <string>

void Player::init(float change) {
    tileShape.setFillColor(sf::Color(42, 139, 200));

    speed *= change;
    maxSpeed *= change;

    gravity *= change;

    jumpHeight *= change;
    maxFallSpeed *= change;
}

void Player::reset() {
    setPosition(startX, startY);
}

void Player::setPosition(float x, float y) {
    position.x = x;
    position.y = y;

    startX = x;
    startY = y;

    tileShape.setPosition(position);
}

void Player::collideWith(float xv, float yv, Tile tile) {
    float tx = tile.getPosition().left;
    float ty = tile.getPosition().top;
    float tw = tile.getShape().getSize().x;
    float th = tile.getShape().getSize().y;

    float x = position.x;
    float y = position.y;
    float w = getShape().getSize().x;
    float h = getShape().getSize().y;

    if (y + h > ty && y < ty + th && x + w > tx && x < tx + tw) { // Check if tiles collide
        if (tile.getType().compare("lava") == 0) {
            reset();
        } else if (yv > 0) { // Bottom
            yvel = 0;
            falling = false;
            position.y = ty - h;
        } else if (yv < 0) { // Top
            yvel = 0;
            falling = true;
            position.y = ty + th;
        } else if (xv > 0) { // Right
            xvel = 0;
            position.x = tx - w;
        } else if (xv < 0) { // Left
            xvel = 0;
            position.x = tx + tw;
        }
    }
}

void Player::update(float windowWidth, float windowHeight, std::vector<Tile> tiles) {
    // Apply x updates & collisions
    xvel /= 1.55f;
    if (xvel > maxSpeed) {
        xvel = maxSpeed;
    } else if (xvel < -maxSpeed) {
        xvel = -maxSpeed;
    }
    position.x += xvel;
    for (int i = 0; i < (int)tiles.size(); i++) {
        collideWith(xvel, 0, tiles[i]);
    }
    
    // Apply y updates & collisions
    yvel += gravity;
    position.y += yvel;
    for (int i = 0; i < (int)tiles.size(); i++) {
        collideWith(0, yvel, tiles[i]);
    }

    // Set tileshape position
    tileShape.setPosition(position);
}

void Player::jump() {
    if (!falling) {
        yvel = -jumpHeight;
        falling = true;
    }
}

void Player::moveLeft() {
    xvel -= speed;
}

void Player::moveRight() {
    xvel += speed;
}
