#include "PauseMenu.h"

PauseMenu::PauseMenu(sf::RenderWindow& window) : window(window), resumePressed(false), mainMenuPressed(false), exitPressed(false)
{
    if (!font.loadFromFile("assets/arial.ttf"))
    {
        throw std::runtime_error("Failed to load font: assets/arial.ttf");
    }

    background.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
    background.setFillColor(sf::Color(0, 0, 0, 150)); // Półprzezroczyste tło

    resumeText.setFont(font);
    resumeText.setString("Resume Game (ESC)");
    resumeText.setCharacterSize(30);
    resumeText.setFillColor(sf::Color::White);
    resumeText.setPosition(window.getSize().x / 2.0f - resumeText.getGlobalBounds().width / 2.0f, 200.0f);

    mainMenuText.setFont(font);
    mainMenuText.setString("Main Menu (M)");
    mainMenuText.setCharacterSize(30);
    mainMenuText.setFillColor(sf::Color::White);
    mainMenuText.setPosition(window.getSize().x / 2.0f - mainMenuText.getGlobalBounds().width / 2.0f, 300.0f);

    exitText.setFont(font);
    exitText.setString("Exit Game (X)");
    exitText.setCharacterSize(30);
    exitText.setFillColor(sf::Color::White);
    exitText.setPosition(window.getSize().x / 2.0f - exitText.getGlobalBounds().width / 2.0f, 400.0f);
}




void PauseMenu::handleInput()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }

        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
                resumePressed = true;
            }
            else if (event.key.code == sf::Keyboard::M)
            {
                mainMenuPressed = true;
            }
            else if (event.key.code == sf::Keyboard::X)
            {
                exitPressed = true;
            }
        }
    }
}

void PauseMenu::update()
{
    
}

void PauseMenu::render()
{
    window.draw(background);
    window.draw(resumeText);
    window.draw(mainMenuText);
    window.draw(exitText);
    window.display();
}


bool PauseMenu::isResumePressed()
{
    bool wasPressed = resumePressed;
    resumePressed = false;
    return wasPressed;
}


bool PauseMenu::isMainMenuPressed()
{
    bool wasPressed = mainMenuPressed;
    mainMenuPressed = false;
    return wasPressed;
}

bool PauseMenu::isExitPressed()
{
    bool wasPressed = exitPressed;
    exitPressed = false;
    return wasPressed;
}
