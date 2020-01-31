#include "Player.h"
#include <string>
#include <vector>

void Player::init(std::vector<Tile>* items, int* _shadow, sf::Vector2u _window) {
    tileShape.setFillColor(sf::Color(42, 139, 200));

    window = _window;
    shadow = _shadow;
    tiles = items;
}

void Player::reset() {
    xvel = 0.0f;
    yvel = 0.0f;
    health = 100;
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

    if (y + h > ty && y < ty + th && x + w > tx && x < tx + tw) { // Check if tiles collide
        if (tile->getType().compare("lava") == 0) {
            // Don't apply collisions to lava
        } else if (tile->getType().compare("water") == 0) {
            // Don't apply collisions to water
        } else if (yv > 0) { // Bottom
            // Fall Damage
            int damage = (int)(yv * 2 - 18);
            if (damage > 0) {
                health -= damage;
            }
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
        health -= tile->getDamage();
        return true;
    }
    return false;
}

void Player::update() {
    // Apply x updates & collisions
    position.x += xvel;
    xvel /= 2.0f;
    if (state.compare("water") == 0) {
        xvel /= 1.75f;
    }
    if (xvel > maxSpeed) {
        xvel = maxSpeed;
    } else if (xvel < -maxSpeed) {
        xvel = -maxSpeed;
    }
    for (size_t i = 0; i < tiles->size(); i++) {
        collideWith(xvel, 0, &tiles->at(i));
    }
    
    // Apply y updates & collisions & check state change
    falling = true;
    position.y += yvel;
    yvel += gravity;
    if (state.compare("water") == 0) {
        yvel /= 2.0f;
    }
    std::string nextState = "";
    for (size_t i = 0; i < tiles->size(); i++) {
        if (collideWith(0, yvel, &tiles->at(i))) {
            if (tiles->at(i).getType().compare(state) != 0) {
                nextState = tiles->at(i).getType();
            }
        }
    }
    state = nextState;

    // Set tileshape position
    tileShape.setPosition(position);

    // Check for Death
    if (position.y > window.y) {
        health -= 2;
    }
    if (health <= 0) {
        reset();
    }
}

void Player::jump() {
    if (state.compare("water") == 0) {
        yvel = -jumpHeight * gravity;
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

int Player::getHealth() {
    return health;
}