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

    generateEnemies();
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

        player.update(deltaTime, window);

        for (auto& platform : platforms)
        {
            player.checkCollision(platform.getBounds());
        }

        for (auto& enemy : enemies)
        {
            enemy.update(deltaTime);
        }

        handleShooting();

        for (auto it = bullets.begin(); it != bullets.end();)
        {
            it->update(deltaTime);
            if (it->getBounds().left > window.getSize().x)
            {
                it = bullets.erase(it);
            }
            else
            {
                ++it;
            }
        }

        spawnNextWave();

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

        for (auto& bullet : bullets)
        {
            bullet.render(window);
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
    float enemySpeed = 100.0f;
    for (const auto& platform : platforms)
    {
        sf::FloatRect platformBounds = platform.getBounds();
        float enemyY = platformBounds.top - 40.0f;
        enemies.emplace_back(800.0f, enemyY, 40.0f, 40.0f, enemySpeed);
    }
}


void Game::spawnNextWave()
{
    bool allEnemiesGone = true;

    for (const auto& enemy : enemies)
    {
        if (enemy.getBounds().left + enemy.getBounds().width > 0)
        {
            allEnemiesGone = false;
            break;
        }
    }

    if (allEnemiesGone)
    {
        ++waveCounter;
        generateEnemies();
    }
}

void Game::handleShooting()
{
    static sf::Clock shootClock; 
    float shootDelay = 0.3f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && shootClock.getElapsedTime().asSeconds() > shootDelay)
    {
        sf::Vector2f playerPosition = player.getBounds().getPosition();
        float bulletX = playerPosition.x + player.getBounds().width / 2.0f;
        float bulletY = playerPosition.y + player.getBounds().height / 2.0f;

        bullets.emplace_back(bulletX, bulletY, 10.0f, 5.0f, 500.0f);
        shootClock.restart();
    }
}




