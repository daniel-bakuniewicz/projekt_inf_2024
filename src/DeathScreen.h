#pragma once
#include <SFML/Graphics.hpp>

class DeathScreen
{
private:
    sf::RenderWindow& window;
    sf::Font font;
    sf::Text gameOverText;
    sf::Text exitText;
    sf::RectangleShape overlay;

public:
    DeathScreen(sf::RenderWindow& window);
    void render();
    void handleInput(bool& shouldExit);
};
