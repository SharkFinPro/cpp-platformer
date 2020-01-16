#include "Player.h"
#include "Tile.h"
#include <vector>

void Player::setPosition(float x, float y) {
    position.x = x;
    position.y = y;

    tileShape.setPosition(position);
}

Player::Player(float x, float y, float w, float h, float change) {
    //Player::Tile(x, y, w, h);
    //Tile(x, y, w, h);
    
    position.x = x;
    position.y = y;

    tileShape.setSize(sf::Vector2f(w, h));
    tileShape.setPosition(position);

    speed *= change;
    maxSpeed *= change;

    gravity *= change;

    jumpHeight *= change;
    maxFallSpeed *= change;

    tileShape.setFillColor(sf::Color(42, 139, 200));
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
        if (yv > 0) { // Bottom
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
    // Cap the x axis speed
    if (xvel > maxSpeed) {
        xvel = maxSpeed;
    } else if (xvel < -maxSpeed) {
        xvel = -maxSpeed;
    }

    // Apply vel updates
    xvel /= 1.55f;
    yvel += gravity;
    
    // Apply x updates & collisions
    position.x += xvel;
    for (int i = 0; i < (int)tiles.size(); i++) {
        collideWith(xvel, 0, tiles[i]);
    }
    
    // Apply y updates & collisions
    falling = true;
    position.y += yvel;
    for (int i = 0; i < (int)tiles.size(); i++) {
        collideWith(0, yvel, tiles[i]);
    }

    // Keep player in window frame
    if (position.y >= windowHeight - tileShape.getSize().y && yvel > 0) {
        position.y = windowHeight - tileShape.getSize().y;
        yvel = 0.0f;
        falling = false;
    }
    if (position.x < 0) {
        position.x = 0;
        xvel = 0.0f;
    } else if (position.x > windowWidth - tileShape.getSize().x) {
        position.x = windowWidth - tileShape.getSize().x;
        xvel = 0.0f;
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
