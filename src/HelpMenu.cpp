#include "HelpMenu.h"

HelpMenu::HelpMenu(sf::RenderWindow& window) : window(window)
{
    if (!font.loadFromFile("assets/arial.ttf"))
    {
        throw std::runtime_error("Failed to load font: assets/arial.ttf");
    }

    overlay.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
    overlay.setFillColor(sf::Color(0, 0, 0, 150));

    titleText.setFont(font);
    titleText.setString("Help Menu");
    titleText.setCharacterSize(50);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(window.getSize().x / 2.0f - titleText.getGlobalBounds().width / 2.0f, 50.0f);

    instructionsText.setFont(font);
    instructionsText.setString(
        "Controls:\n"
        "W - Jump\n"
        "A - Move Left\n"
        "D - Move Right\n"
        "S - Drop through platform\n"
        "Space - Shoot\n"
        "ESC - Pause Game\n"
        "H - Help Menu\n"
        "K - Save Game\n"
        "L - Load Game\n"
        "\nPress ESC to return to the game"
    );
    instructionsText.setCharacterSize(20);
    instructionsText.setFillColor(sf::Color::White);
    instructionsText.setPosition(window.getSize().x / 2.0f - instructionsText.getGlobalBounds().width / 2.0f, 150.0f);
}

void HelpMenu::handleInput(bool& shouldExit)
{
    sf::Event event;
    
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
            shouldExit = true;
        }

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        {
            shouldExit = true;
        }
    }
}

void HelpMenu::render()
{
    window.draw(overlay);
    window.draw(titleText);
    window.draw(instructionsText);
}
