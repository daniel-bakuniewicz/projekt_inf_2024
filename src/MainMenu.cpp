#include "MainMenu.h"

MainMenu::MainMenu(sf::RenderWindow& window) : window(window), startPressed(false)
{
    if (!font.loadFromFile("assets/arial.ttf"))
    {
        throw std::runtime_error("Failed to load font: assets/arial.ttf");
    }

    titleText.setFont(font);
    titleText.setString("Penguin Defense");
    titleText.setCharacterSize(60);
    titleText.setFillColor(sf::Color::Cyan);
    titleText.setPosition(window.getSize().x / 2.0f - titleText.getGlobalBounds().width / 2.0f, 100.0f);

    startText.setFont(font);
    startText.setString("Press ENTER to Start");
    startText.setCharacterSize(30);
    startText.setFillColor(sf::Color::White);
    startText.setPosition(window.getSize().x / 2.0f - startText.getGlobalBounds().width / 2.0f, 200.0f);

    exitText.setFont(font);
    exitText.setString("Press ESC to Exit");
    exitText.setCharacterSize(30);
    exitText.setFillColor(sf::Color::White);
    exitText.setPosition(window.getSize().x / 2.0f - exitText.getGlobalBounds().width / 2.0f, 250.0f);

    easyText.setFont(font);
    easyText.setString("Easy (1)");
    easyText.setCharacterSize(30);
    easyText.setFillColor(sf::Color::Green);
    easyText.setPosition(window.getSize().x / 2.0f - easyText.getGlobalBounds().width / 2.0f, 350.0f);

    mediumText.setFont(font);
    mediumText.setString("Medium (2)");
    mediumText.setCharacterSize(30);
    mediumText.setFillColor(sf::Color::Yellow);
    mediumText.setPosition(window.getSize().x / 2.0f - mediumText.getGlobalBounds().width / 2.0f, 400.0f);

    hardText.setFont(font);
    hardText.setString("Hard (3)");
    hardText.setCharacterSize(30);
    hardText.setFillColor(sf::Color::Red);
    hardText.setPosition(window.getSize().x / 2.0f - hardText.getGlobalBounds().width / 2.0f, 450.0f);

    if (!playerTexture.loadFromFile("assets/player_walk_animation.png"))
    {
        throw std::runtime_error("Failed to load player animation texture");
    }

    if (!enemyTexture.loadFromFile("assets/enemy_animation.png"))
    {
        throw std::runtime_error("Failed to load enemy animation texture");
    }

    playerSprite.setTexture(playerTexture);
    playerSprite.setScale(2.0f, 2.0f);
    playerSprite.setTextureRect(sf::IntRect(0, 0, playerTexture.getSize().x / playerFrames, playerTexture.getSize().y));

    enemySprite.setTexture(enemyTexture);
    enemySprite.setScale(2.0f, 2.0f);
    enemySprite.setTextureRect(sf::IntRect(0, 0, enemyTexture.getSize().x / enemyFrames, enemyTexture.getSize().y));
}

void MainMenu::handleInput()
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
            if (event.key.code == sf::Keyboard::Enter)
            {
                startPressed = true; // Rozpocznij gre
            }
            else if (event.key.code == sf::Keyboard::Escape)
            {
                window.close(); // Wyjscie z gry
            }
            else if (event.key.code == sf::Keyboard::Num1)
            {
                selectedDifficulty = 0; // Latwy
            }
            else if (event.key.code == sf::Keyboard::Num2)
            {
                selectedDifficulty = 1; // Sredni
            }
            else if (event.key.code == sf::Keyboard::Num3)
            {
                selectedDifficulty = 2; // Trudny
            }
        }
    }
}

void MainMenu::update(float deltaTime)
{
    animationTimer += deltaTime;

    if (animationTimer >= 0.15f)
    {
        currentPlayerFrame = (currentPlayerFrame + 1) % playerFrames;
        currentEnemyFrame = (currentEnemyFrame + 1) % enemyFrames;

        playerSprite.setTextureRect(sf::IntRect(
            currentPlayerFrame * (playerTexture.getSize().x / playerFrames), 0,
            playerTexture.getSize().x / playerFrames,
            playerTexture.getSize().y));

        enemySprite.setTextureRect(sf::IntRect(
            currentEnemyFrame * (enemyTexture.getSize().x / enemyFrames), 0,
            enemyTexture.getSize().x / enemyFrames,
            enemyTexture.getSize().y));

        animationTimer = 0.f;
    }

    playerSprite.setPosition(window.getSize().x - 110.f, window.getSize().y - 100.f);
    enemySprite.setPosition(20.f, window.getSize().y - 80.f);
}

void MainMenu::render()
{
    window.clear();
    window.draw(titleText);
    window.draw(startText);
    window.draw(exitText);
    window.draw(easyText);
    window.draw(mediumText);
    window.draw(hardText);
    window.draw(playerSprite);
    window.draw(enemySprite);
    window.display();
}
