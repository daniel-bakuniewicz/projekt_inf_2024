#include "DeathScreen.h"

DeathScreen::DeathScreen(sf::RenderWindow& window) : window(window)
{
    if (!font.loadFromFile("assets/arial.ttf"))
    {
        throw std::runtime_error("Failed to load font");
    }

    overlay.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
    overlay.setFillColor(sf::Color(0, 0, 0, 150));

    gameOverText.setFont(font);
    gameOverText.setString("GAME OVER");
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(window.getSize().x / 2.0f - gameOverText.getGlobalBounds().width / 2.0f, window.getSize().y / 3.0f);

    exitText.setFont(font);
    exitText.setString("Press ESC to Exit");
    exitText.setCharacterSize(25);
    exitText.setFillColor(sf::Color::White);
    exitText.setPosition(window.getSize().x / 2.0f - exitText.getGlobalBounds().width / 2.0f, window.getSize().y / 2.0f);
}

void DeathScreen::render()
{
    window.draw(overlay);
    window.draw(gameOverText);
    window.draw(exitText);
}

void DeathScreen::handleInput(bool& shouldExit)
{
    sf::Event event;
    
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            shouldExit = true;
            
            window.close();
        }

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        {
            shouldExit = true;
        }
    }
}
