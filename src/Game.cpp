#include "Game.h"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include "MainMenu.h"
#include "PauseMenu.h"
#include "DeathScreen.h"
#include "HelpMenu.h"

Game::Game() : window(sf::VideoMode(800, 600), "Penguin Defense"), waveCounter(1), killCount(0), lives(10)
{
    window.setFramerateLimit(60);

    if (!backgroundTexture.loadFromFile("assets/background.png"))
    {
        throw std::runtime_error("Failed to load background.png");
    }

    if (!font.loadFromFile("assets/arial.ttf"))
    {
        throw std::runtime_error("Failed to load font: assets/arial.ttf");
    }

    if (!enemyTexture.loadFromFile("assets/enemy_animation.png"))
    {
        throw std::runtime_error("Failed to load enemy texture");
    }

    backgroundSprite.setTexture(backgroundTexture);

    initUI();

    generateMap();

    player.initAnimation("assets/player_walk_animation.png", 6, 0.15f);

    if (!platforms.empty()) // Inicjalizacja pozycji gracza na srodkowej platformie
    {
        const auto& middlePlatform = platforms[platforms.size() / 2];
        sf::FloatRect platformBounds = middlePlatform.getBounds();
        player.init(window, platformBounds.left + platformBounds.width / 2, platformBounds.top - 25.0f);
    }

    generateEnemies();
}

void Game::run()
{
    MainMenu mainMenu(window);

    sf::Clock gameClock;

    while (window.isOpen() && !mainMenu.isStartPressed())
    {
        mainMenu.handleInput();

        float deltaTime = gameClock.restart().asSeconds();

        mainMenu.update(deltaTime);
        mainMenu.render();
    }

    switch (mainMenu.getSelectedDifficulty())
    {
        case 0:
            setDifficulty(Difficulty::Easy);
            break;
        case 1:
            setDifficulty(Difficulty::Medium);
            break;
        case 2:
            setDifficulty(Difficulty::Hard);
            break;
        default:
            setDifficulty(Difficulty::Medium); // Domyslnie sredni poziom trudności
            break;
    }

    generateEnemies();

    sf::Clock clock;
    bool isPaused = false;

    while (window.isOpen())
    {
        handleInput(isPaused);

        if (lives <= 0)
        {
            DeathScreen deathScreen(window);

            bool shouldExit = false;

            while (!shouldExit)
            {
                deathScreen.handleInput(shouldExit);

                window.clear();

                renderGame();
                deathScreen.render();

                window.display();
            }

            return;
        }
    
        if (isPaused)
        {
            runPauseMenu(clock, isPaused);
        }

        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
        {
            HelpMenu helpMenu(window);

            bool shouldExit = false;

            while (!shouldExit)
            {
                helpMenu.handleInput(shouldExit);

                window.clear();

                renderGame();
                helpMenu.render();

                window.display();
            }

            clock.restart();
        }

        else
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
            {
                saveGame("savegame.txt");
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
            {
                loadGame("savegame.txt");
                clock.restart();
            }

            float deltaTime = clock.restart().asSeconds();

            updateGame(deltaTime);

            renderGame();

            window.display();
        }
    }
}

void Game::handleInput(bool& isPaused)
{
    sf::Event event;

    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        {
            isPaused = !isPaused;
        }
    }
}

void Game::runPauseMenu(sf::Clock& clock, bool& isPaused)
{
    PauseMenu pauseMenu(window);

    while (isPaused)
    {
        pauseMenu.handleInput();

        if (pauseMenu.isResumePressed())
        {
            isPaused = false;
            break;
        }
        
        else if (pauseMenu.isMainMenuPressed())
        {
            MainMenu mainMenu(window);
            while (window.isOpen() && !mainMenu.isStartPressed())
            {
                mainMenu.handleInput();
                float deltaTime = clock.restart().asSeconds();
                mainMenu.update(deltaTime);
                mainMenu.render();
            }
            return;
        }

        else if (pauseMenu.isExitPressed())
        {
            window.close();
            return;
        }

        renderGame();

        sf::RectangleShape overlay(sf::Vector2f(window.getSize().x, window.getSize().y));
        overlay.setFillColor(sf::Color(0, 0, 0, 150));
        window.draw(overlay);

        pauseMenu.render();
    }
    
    if (!isPaused)
    {
        clock.restart();
    }
}

void Game::updateGame(float deltaTime)
{
    player.update(deltaTime, window);
    player.updateAnimation(deltaTime);

    updateEnemies(deltaTime);
    updateBullets(deltaTime);

    for (auto& platform : platforms)
    {
        player.checkCollision(platform.getBounds());
    }

    handleShooting();
    spawnNextWave();
    updateUI();
}

void Game::renderGame()
{
    window.clear();
    window.draw(backgroundSprite);

    renderPlatforms();
    renderEnemies();
    renderBullets();
    player.render(window);
    renderUI();

    if (showStatusMessage && statusMessageClock.getElapsedTime().asSeconds() < 2.0f)
    {
        window.draw(statusMessage);
    }

    else
    {
        showStatusMessage = false;
    }
}

void Game::updateEnemies(float deltaTime)
{
    for (auto& enemy : enemies)
    {
        enemy.update(deltaTime);
        enemy.updateAnimation(deltaTime);
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
}


void Game::updateBullets(float deltaTime)
{
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
}

void Game::renderPlatforms()
{
    for (auto& platform : platforms)
    {
        platform.render(window);
    }
}

void Game::renderEnemies()
{
    for (auto& enemy : enemies)
    {
        enemy.render(window);
    }
}

void Game::renderBullets()
{
    for (auto& bullet : bullets)
    {
        bullet.render(window);
    }
}

void Game::renderUI()
{
    window.draw(timeText);
    window.draw(killsText);
    window.draw(livesText);
    window.draw(helpText);
}

void Game::initUI()
{
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

    helpText.setFont(font);
    helpText.setCharacterSize(20);
    helpText.setFillColor(sf::Color::White);
    helpText.setPosition(60.f, 20.f);

    updateLivesText();

    statusMessage.setFont(font);
    statusMessage.setCharacterSize(30);
    statusMessage.setFillColor(sf::Color::Yellow);
    statusMessage.setPosition(window.getSize().x / 2.0f - 100.0f, window.getSize().y / 2.0f - 50.0f);
}

void Game::generateMap()
{
    platforms.clear();

    float windowWidth = window.getSize().x;
    float windowHeight = window.getSize().y;

    float platformWidth = 200.0f;
    float platformHeight = 10.0f;

    float leftX = 0.0f;
    float startY = windowHeight - 100.0f;
    float gap = 100.0f;

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

    int enemyHp = 2;
    switch (difficultyLevel)
    {
    case Difficulty::Easy:
        enemyHp = 1;
        break;
    case Difficulty::Medium:
        enemyHp = 2;
        break;
    case Difficulty::Hard:
        enemyHp = 3;
        break;
    }

    enemies.clear();
    for (const auto& platform : platforms)
    {
        if (std::rand() % 2 == 0)
        {
            sf::FloatRect platformBounds = platform.getBounds();
            float enemyY = platformBounds.top - enemyHeight;

            Enemy enemy(enemyStartX, enemyY, enemyWidth, enemyHeight, enemySpeed, enemyHp);
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
    timeText.setString("Time: " + std::to_string(static_cast<int>(elapsedTime)));
    killsText.setString("Score: " + std::to_string(killCount));
    helpText.setString("Help (H)");
}

void Game::updateLivesText()
{
    livesText.setString("Lives: " + std::to_string(lives));
}

void Game::setDifficulty(Difficulty level)
{
    difficultyLevel = level;
}

void Game::saveGame(const std::string& filename)
{
    std::ofstream saveFile(filename);

    if (!saveFile.is_open())
    {
        throw std::runtime_error("Failed to open save file: " + filename);
    }

    saveFile << "lives " << lives << "\n";
    saveFile << "kills " << killCount << "\n";
    saveFile << "player " << player.getBounds().left << " " << player.getBounds().top << "\n";

    for (const auto& enemy : enemies)
    {
        saveFile << "enemy " << enemy.getBounds().left << " " << enemy.getBounds().top << " " << enemy.getHealth() << "\n";
    }

    for (const auto& bullet : bullets)
    {
        saveFile << "bullet " << bullet.getBounds().left << " " << bullet.getBounds().top << "\n";
    }

    saveFile.close();

    showStatus("Game Saved");
}

void Game::loadGame(const std::string& filename)
{
    std::ifstream saveFile(filename);

    if (!saveFile.is_open())
    {
        throw std::runtime_error("Failed to open save file: " + filename);
    }

    enemies.clear();
    bullets.clear();

    std::string type;
    while (saveFile >> type)
    {
        if (type == "lives")
        {
            saveFile >> lives;
        }

        else if (type == "kills")
        {
            saveFile >> killCount;
        }

        else if (type == "player")
        {
            float x, y;
            saveFile >> x >> y;
            player.init(window, x, y);
        }

        else if (type == "enemy")
        {
            float x, y;
            int health;
            saveFile >> x >> y >> health;
            Enemy enemy(x, y, 40.f, 40.f, 100.f, health);
            enemy.initAnimation(enemyTexture, 8, 0.2f);
            enemies.push_back(enemy);
        }

        else if (type == "bullet")
        {
            float x, y;
            saveFile >> x >> y;
            bullets.emplace_back(x, y, 10.f, 5.f, 500.f);
        }
    }

    saveFile.close();

    showStatus("Game Loaded");
}

void Game::showStatus(const std::string& message)
{
    statusMessage.setString(message);
    statusMessage.setPosition(window.getSize().x / 2.0f - statusMessage.getGlobalBounds().width / 2.0f, window.getSize().y / 2.0f - statusMessage.getGlobalBounds().height / 2.0f);
    showStatusMessage = true;
    statusMessageClock.restart();
}



