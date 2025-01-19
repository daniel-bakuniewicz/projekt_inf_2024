#pragma once
#include <SFML/Graphics.hpp>

class HelpMenu
{
private:
    sf::RenderWindow& window;
    sf::RectangleShape overlay;

    sf::Font font;
    sf::Text titleText;
    sf::Text instructionsText;

public:
    HelpMenu(sf::RenderWindow& window);
    
    void handleInput(bool& shouldExit);
    void render();
};
