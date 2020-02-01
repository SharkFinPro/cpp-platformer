#include "Player.h"
#include "Air.h"
#include "Wall.h"
#include "Lava.h"
#include "Water.h"
#include "JumpPad.h"
#include "Faller.h"
#include <vector>
#include <SFML/Graphics.hpp>

int tileMap[24][24] = {
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 3, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 3, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 3, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 3, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 5, 5, 5, 1, 0, 0, 1},
    {1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
    {1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
    {2, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 2},
    {2, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 4, 4, 4, 0, 9, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

int id = 0;

int nextId() {
    return id++;
}

int main() {
    // Window
    float scale = sf::VideoMode().getDesktopMode().width / 1920.0f;
    if (scale < 0.5f) {
        scale = 0.5;
    }
    sf::RenderWindow window(sf::VideoMode((int)(800 * scale), (int)(800 * scale)), "Platformer", sf::Style::Close);
    window.setFramerateLimit(60);

    // Overlay
    int shadow = 0;
    sf::RectangleShape overlay;
    overlay.setSize(sf::Vector2f((float)window.getSize().x, (float)window.getSize().y));
    overlay.setPosition(sf::Vector2f(0, 0));
    overlay.setFillColor(sf::Color(0, 0, 0, 255 - shadow));

    // Create Player and set tile size
    std::vector<Tile> tiles;
    Tile::setTiles(&tiles);
    float tileSize = 400 / 24.0f;
    Player player(100.0f, 100.0f, tileSize, tileSize, &shadow, window.getSize(), nextId());

    // Generate Tiles
    for (int i = 0; i < 24; i++) {
        for (int j = 0; j < 24; j++) {
            switch (tileMap[i][j]) {
            case 0:
                tiles.push_back(Air(j * tileSize, i * tileSize, tileSize, tileSize, nextId()));
                break;
            case 1:
                tiles.push_back(Wall(j * tileSize, i * tileSize, tileSize, tileSize, nextId()));
                break;
            case 2:
                tiles.push_back(Lava(j * tileSize, i * tileSize, tileSize, tileSize, nextId()));
                break;
            case 3:
                tiles.push_back(Water(j * tileSize, i * tileSize, tileSize, tileSize, nextId()));
                break;
            case 4:
                tiles.push_back(JumpPad(j * tileSize, i * tileSize, tileSize, tileSize, nextId()));
                break;
            case 5:
                tiles.push_back(Faller(j * tileSize, i * tileSize, tileSize, tileSize, nextId()));
                break;
            case 9:
                tiles.push_back(Air(j * tileSize, i * tileSize, tileSize, tileSize, nextId()));
                player.setPosition(j * tileSize, i * tileSize);
                break;
            }
        }
    }
    
    // Player health overlay
    sf::Font healthFont;
    healthFont.loadFromFile("square.ttf");
    sf::Text playerHealth = sf::Text();
    playerHealth.setFont(healthFont);
    playerHealth.setPosition(sf::Vector2f(25.0f, 0.0f));
    playerHealth.setFillColor(sf::Color::Red);
    playerHealth.setCharacterSize((unsigned int)(25));

    while (window.isOpen()) {
        // Events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Input
        if (window.hasFocus()) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
            if (shadow >= 255) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                    player.jump();
                }
                if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))) {
                    player.moveLeft();
                }
                if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))) {
                    player.moveRight();
                }
            }

            // Update the Player
            player.update();

            // Draw stuff
            window.clear(sf::Color(200, 200, 200));

            window.draw(player.getShape());
            for (size_t i = 0; i < tiles.size(); i++) {
                window.draw(tiles[i].getShape());
            }

            playerHealth.setString("Health: " + std::to_string(player.getHealth()));
            window.draw(playerHealth);

            if (shadow < 255) {
                overlay.setFillColor(sf::Color(0, 0, 0, 255 - shadow));
                window.draw(overlay);
                shadow += 4;
            }

            // Scale to window size
            sf::View view = window.getDefaultView();
            view.zoom(0.5f / scale);
            view.setCenter(200.0f, 200.0f);
            window.setView(view);

            window.display();
        }
    }

    return 0;
}