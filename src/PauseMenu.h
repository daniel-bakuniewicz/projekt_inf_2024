#pragma once
#include <SFML/Graphics.hpp>

class PauseMenu
{
public:
    PauseMenu(sf::RenderWindow& window);

    void handleInput();
    void update();
    void render();

    bool isResumePressed();
    bool isMainMenuPressed();
    bool isExitPressed();

private:
    sf::RenderWindow& window;
    sf::Font font;
    sf::Text resumeText;
    sf::Text mainMenuText;
    sf::Text exitText;
    sf::RectangleShape background;


    bool resumePressed;
    bool mainMenuPressed;
    bool exitPressed;
};
