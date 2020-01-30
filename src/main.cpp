#include "Player.h"
#include "Wall.h"
#include "Lava.h"
#include "Water.h"
#include "JumpPad.h"
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
    {1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 1, 0, 0, 1},
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

int main() {
    // Window
    int scale = sf::VideoMode().getDesktopMode().width / 1920;
    sf::RenderWindow window(sf::VideoMode(800 * scale, 800 * scale), "Platformer", sf::Style::Close);
    window.setFramerateLimit(60);

    // Overlay
    int shadow = 0;
    sf::RectangleShape overlay;
    overlay.setSize(sf::Vector2f(800, 800));
    overlay.setPosition(sf::Vector2f(0, 0));
    overlay.setFillColor(sf::Color(0, 0, 0, 255 - shadow));

    // Create Player and set tile size
    std::vector<Tile> tiles;
    float tileSize = 800.0f / 24.0f;
    Player player(100.0f, 100.0f, tileSize, tileSize, &tiles, &shadow, window.getSize());

    // Generate Tiles
    for (int i = 0; i < 24; i++) {
        for (int j = 0; j < 24; j++) {
            switch (tileMap[i][j]) {
            case 1:
                tiles.push_back(Wall(j * tileSize, i * tileSize, tileSize, tileSize));
                break;
            case 2:
                tiles.push_back(Lava(j * tileSize, i * tileSize, tileSize, tileSize));
                break;
            case 3:
                tiles.push_back(Water(j * tileSize, i * tileSize, tileSize, tileSize));
                break;
            case 4:
                tiles.push_back(JumpPad(j * tileSize, i * tileSize, tileSize, tileSize));
                break;
            case 9:
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
    playerHealth.setPosition(sf::Vector2f(0.0f, 0.0f));
    playerHealth.setFillColor(sf::Color::Red);
    playerHealth.setCharacterSize(50);

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

            // create a view half the size of the default view
            sf::View view = window.getDefaultView();
            view.setCenter(400, 400);
            view.zoom(1.0f / (float)scale);

            // Display the window
            window.setView(view);
            window.display();
        }
    }

    return 0;
}