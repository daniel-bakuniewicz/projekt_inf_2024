#pragma once
#include <SFML/Graphics.hpp>

class MainMenu
{
private:
    sf::RenderWindow& window;
    sf::Font font;

    sf::Text titleText;
    sf::Text startText;
    sf::Text easyText;
    sf::Text exitText;
    sf::Text mediumText;
    sf::Text hardText;

    sf::Texture playerTexture;
    sf::Texture enemyTexture;

    sf::Sprite playerSprite;
    sf::Sprite enemySprite;

    int playerFrames = 6;
    int enemyFrames = 8;
    float animationTimer = 0.f;
    int currentPlayerFrame = 0;
    int currentEnemyFrame = 0;

    bool startPressed = false;
    int selectedDifficulty = 1;

public:
    MainMenu(sf::RenderWindow& window);

    void handleInput();
    void update(float deltaTime);
    void render();

    bool isStartPressed() const { return startPressed; }

    int getSelectedDifficulty() const { return selectedDifficulty; }
};
