#include "Tile.h"
#include "Player.h"
#include <SFML/Graphics.hpp>

int xMult = sf::VideoMode().getDesktopMode().width / 1920;
int yMult = sf::VideoMode().getDesktopMode().height / 1080;

int main() {
    // Window
    sf::RenderWindow window(sf::VideoMode(1000 * xMult, 800 * yMult), "Platformer", sf::Style::Titlebar);
    window.setFramerateLimit(60);

    float windowWidth = (float)window.getSize().x;
    float windowHeight = (float)window.getSize().y;

    // Tiles
    float tileSize = 50.0f * xMult;
    Player player(100.0f, 300.0f, tileSize, tileSize);
    player.updateSpeeds(xMult);
    int tileMap[16][20] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };
    std::vector<Tile> tiles;
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 20; j++) {
            if (tileMap[i][j] == 1) {
                tiles.push_back(Tile(j * tileSize, i * tileSize, tileSize, tileSize));
            }
        }
    }
    
    // Timing
    sf::Clock clock;
    float delta;

    while (window.isOpen()) {
        // Get delta
        delta = (float)clock.getElapsedTime().asMilliseconds();
        clock.restart();

        // Events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Input
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            player.jump();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && player.getPosition().left > 0) {
            player.moveLeft(delta);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && player.getPosition().left + player.getShape().getSize().x < windowWidth) {
            player.moveRight(delta);
        }

        // Updates
        player.update(delta, windowWidth, windowHeight, tiles);

        // Drawing
        window.clear(sf::Color::Black);
        
        for (int i = 0; i < (int)tiles.size(); i++) {
            window.draw(tiles[i].getShape());
        }

        window.draw(player.getShape());

        window.display();
    }

    return 0;
}