#include "Game.h"
#include <cstdlib>
#include <ctime>

Game::Game() : window(sf::VideoMode(800, 600), "Penguin Defense"), waveCounter(1), killCount(0), lives(10)
{
    window.setFramerateLimit(60);
    initBackground();
    generateMap();
    player.initAnimation("assets/player_walk_animation.png", 6, 0.15f);


    if (!platforms.empty())
    {
        const auto& middlePlatform = platforms[platforms.size() / 2];
        sf::FloatRect platformBounds = middlePlatform.getBounds();
        player.init(window, platformBounds.left + platformBounds.width / 2, platformBounds.top - 25.0f);
    }

    if (!font.loadFromFile("assets/arial.ttf"))
    {
        throw std::runtime_error("Failed to load font: assets/arial.ttf");
    }

    if (!enemyTexture.loadFromFile("assets/enemy_animation.png"))
    {
        throw std::runtime_error("Failed to load enemy texture");
    }


    timeText.setFont(font);
    timeText.setCharacterSize(20);
    timeText.setFillColor(sf::Color::White);
    timeText.setPosition(600.0f, 10.0f);

    killsText.setFont(font);
    killsText.setCharacterSize(20);
    killsText.setFillColor(sf::Color::White);
    killsText.setPosition(600.0f, 40.0f);

    livesText.setFont(font);
    livesText.setCharacterSize(20);
    livesText.setFillColor(sf::Color::White);
    livesText.setPosition(600.0f, 70.0f);

    updateLivesText();
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
        player.updateAnimation(deltaTime);

        for (auto& platform : platforms)
        {
            player.checkCollision(platform.getBounds());
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

        for (auto bulletIt = bullets.begin(); bulletIt != bullets.end();)
        {
            bool bulletRemoved = false;

            for (auto enemyIt = enemies.begin(); enemyIt != enemies.end();)
            {
                if (bulletIt->getBounds().intersects(enemyIt->getBounds()))
                {
                    enemyIt->takeDamage();
                    bulletIt = bullets.erase(bulletIt);
                    bulletRemoved = true;

                    if (enemyIt->isDead())
                    {
                        enemyIt = enemies.erase(enemyIt);
                        killCount++;
                    }

                    else
                    {
                        ++enemyIt;
                    }

                    break;
                }

                else
                {
                    ++enemyIt;
                }
            }

            if (!bulletRemoved)
            {
                ++bulletIt;
            }
        }

        for (auto enemyIt = enemies.begin(); enemyIt != enemies.end();)
        {
            if (enemyIt->getBounds().intersects(player.getBounds()))
            {
                lives -= 2;
                updateLivesText();
                enemyIt = enemies.erase(enemyIt);
            }

            else if (enemyIt->getBounds().left <= 0)
            {
                lives--;
                updateLivesText();
                enemyIt = enemies.erase(enemyIt);
            }

            else
            {
                ++enemyIt;
            }
        }

        if (lives <= 0)
        {
            window.close();
        }

        spawnNextWave();
    
        updateUI();

        window.clear();
        window.draw(backgroundSprite);

        for (auto& platform : platforms)
        {
            platform.render(window);
        }

        for (auto& enemy : enemies)
        {
            enemy.render(window);
            enemy.update(deltaTime);
            enemy.updateAnimation(deltaTime);  
        }

        for (auto& bullet : bullets)
        {
            bullet.render(window);
        }

        player.render(window);

        window.draw(timeText);
        window.draw(killsText);
        window.draw(livesText);

        window.display();
    }
}


void Game::generateMap()
{
    float windowWidth = window.getSize().x;
    float windowHeight = window.getSize().y;

    float platformWidth = 200.0f;
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
    float enemyWidth = 40.0f;
    float enemyHeight = 40.0f;
    float enemyStartX = window.getSize().x - enemyWidth;
    float enemySpeed = 100.0f + waveCounter * 10.0f;

    enemies.clear();

    for (const auto& platform : platforms)
    {
        if (std::rand() % 2 == 0)
        {
            sf::FloatRect platformBounds = platform.getBounds();
            float enemyY = platformBounds.top - 40.0f;

            Enemy enemy(800.0f, enemyY, 40.0f, 40.0f, 100.0f, 2);
            enemy.initAnimation(enemyTexture, 8, 0.2f);
            enemies.push_back(enemy);
        }
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

void Game::updateUI()
{
    float elapsedTime = gameClock.getElapsedTime().asSeconds();

    timeText.setString("Czas: " + std::to_string(static_cast<int>(elapsedTime)));
    killsText.setString("Punkty: " + std::to_string(killCount));
}

void Game::updateLivesText()
{
    livesText.setString("Zycia: " + std::to_string(lives));
}






