#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "Player.h"
#include "Enemy.h"
#include "Platform.h"
#include "Bullet.h"
#include "MainMenu.h"
#include "PauseMenu.h"

class Game
{
private:
    enum class Difficulty { Easy, Medium, Hard };
    Difficulty difficultyLevel = Difficulty::Medium; // Standardowy tryb: Medium
    
    sf::RenderWindow window;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Texture enemyTexture;

    sf::Font font;
    sf::Text timeText;
    sf::Text killsText;
    sf::Text livesText;
    sf::Text helpText;
    sf::Text statusMessage;

    sf::Clock gameClock;
    sf::Clock statusMessageClock;

    Player player;
    std::vector<Enemy> enemies;
    std::vector<Platform> platforms;
    std::vector<Bullet> bullets;

    int killCount;
    int lives;
    int waveCounter;

    void initBackground();
    void initUI();

    void handleInput(bool& isPaused);
    void runPauseMenu(sf::Clock& clock, bool& isPaused);
    void updateGame(float deltaTime);
    void renderGame();

    void generateMap();
    void generateEnemies();
    void spawnNextWave();

    void updateEnemies(float deltaTime);
    void updateBullets(float deltaTime);

    void renderPlatforms();
    void renderEnemies();
    void renderBullets();
    void renderUI();

    void updateUI();
    void updateLivesText();

    void handleShooting();

    void saveGame(const std::string& filename);
    void loadGame(const std::string& filename);

    void showStatus(const std::string& message);

    bool showStatusMessage = false;



public:
    Game();
    void run();
    void setDifficulty(Difficulty level);
};
