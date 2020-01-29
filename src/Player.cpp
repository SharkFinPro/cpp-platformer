#include "Player.h"
#include <string>
#include <vector>
#include <iostream>

void Player::init(float change, std::vector<Tile>* items, int* _shadow) {
    tileShape.setFillColor(sf::Color(42, 139, 200));

    // Link overlay shadow
    shadow = _shadow;

    // Set the tiles to the items array
    tiles = items;

    // Apply changes to speeds based off screen size
    speed *= change;
    maxSpeed *= change;
    gravity *= change;
    jumpHeight *= change;
    maxFallSpeed *= change;
}

void Player::reset() {
    setPosition(startX, startY);
    *shadow = 0;
}

void Player::setPosition(float x, float y) {
    position.x = x;
    position.y = y;

    startX = x;
    startY = y;

    tileShape.setPosition(position);
}

bool Player::collideWith(float xv, float yv, Tile *tile) {
    float tx = tile->getPosition().left;
    float ty = tile->getPosition().top;
    float tw = tile->getShape().getSize().x;
    float th = tile->getShape().getSize().y;

    float x = position.x;
    float y = position.y;
    float w = getShape().getSize().x;
    float h = getShape().getSize().y;

    if (y + h > ty&& y < ty + th && x + w > tx&& x < tx + tw) { // Check if tiles collide
        if (tile->getType().compare("lava") == 0) {
            reset();
        } else if (tile->getType().compare("water") == 0) {

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
        return true;
    }
    return false;
}

void Player::update() {
    // Apply x updates & collisions
    xvel /= 1.55f;
    if (state.compare("water") == 0) {
        xvel /= 1.25;
    }
    if (xvel > maxSpeed) {
        xvel = maxSpeed;
    }
    else if (xvel < -maxSpeed) {
        xvel = -maxSpeed;
    }
    position.x += xvel;
    for (size_t i = 0; i < tiles->size(); i++) {
        collideWith(xvel, 0, &tiles->at(i));
    }
    
    
    // Apply y updates & collisions & check state change
    falling = true;
    yvel += gravity;
    if (state.compare("water") == 0) {
        yvel /= 1.25;
    }
    position.y += yvel;
    bool stateChange = true;
    bool checked = false;
    std::string nextState = "";
    for (size_t i = 0; i < tiles->size(); i++) {
        if (collideWith(0, yvel, &tiles->at(i))) {
            checked = true;
            if (tiles->at(i).getType().compare(state) == 0) {
                stateChange = false;
            } else {
                nextState = tiles->at(i).getType();
            }
        }
    }
    if (stateChange || !checked) {
        state = nextState;
    }

    // Set tileshape position
    tileShape.setPosition(position);
}

void Player::jump() {
    if (state.compare("water") == 0) {
        yvel = -jumpHeight;
        yvel /= 1.5;
    } else if (state.compare("JumpPad") == 0) {
        yvel = -jumpHeight * 1.25f;
    } else if (!falling) {
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
