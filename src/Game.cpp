#include "Game.h"

Game::Game() : window(sf::VideoMode(800, 600), "Penguin Defense")
{
    window.setFramerateLimit(60);
    initBackground();
    generateMap();

    if (!platforms.empty())
    {
        const auto& middlePlatform = platforms[platforms.size() / 2];
        sf::FloatRect platformBounds = middlePlatform.getBounds();
        player.init(window, platformBounds.left + platformBounds.width / 2, platformBounds.top - 25.0f);
    }
}

void Game::initBackground()
{
    if (!backgroundTexture.loadFromFile("assets/background.png"))
    {
        throw std::runtime_error("Failed to load background.png");
    }
    backgroundSprite.setTexture(backgroundTexture);
}

void Game::run()
{
    sf::Clock clock;

    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        player.update(deltaTime);

        for (auto& platform : platforms)
        {
            player.checkCollision(platform.getBounds());
        }

        for (auto& enemy : enemies)
        {
            enemy.update(deltaTime);
        }

        window.clear();

        window.draw(backgroundSprite);

        for (auto& platform : platforms)
        {
            platform.render(window);
        }

        for (auto& enemy : enemies)
        {
            enemy.render(window);
        }

        player.render(window);

        window.display();
    }
}


void Game::generateMap()
{
    float windowWidth = window.getSize().x;
    float windowHeight = window.getSize().y;

    float platformWidth = 100.0f;
    float platformHeight = 10.0f;

    float leftX = 0.0f;

    float startY = windowHeight - 100.0f;
    float gap = 100.0f;

    platforms.clear();
    for (int i = 0; i < 5; ++i)
    {
        platforms.emplace_back(leftX, startY - i * gap, platformWidth, platformHeight);
    }

    generateEnemies();
}

void Game::generateEnemies()
{
    float windowWidth = window.getSize().x;
    float enemyWidth = 40.0f;
    float enemyHeight = 40.0f;
    float enemyStartX = windowWidth - enemyWidth;
    float enemySpeed = 100.0f;

    enemies.clear();
    for (const auto& platform : platforms)
    {
        sf::FloatRect platformBounds = platform.getBounds();
        float enemyY = platformBounds.top - enemyHeight;
        enemies.emplace_back(enemyStartX, enemyY, enemyWidth, enemyHeight, enemySpeed);
    }
}

