#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Platform.h"
#include "Enemy.h"
#include "Bullet.h"
#include <vector>

class Game
{
private:
    sf::RenderWindow window;
    sf::Texture enemyTexture;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Font font;                
    sf::Text timeText;            
    sf::Text killsText;                        
    sf::Clock gameClock;
    sf::Text livesText;

    Player player;
    
    std::vector<Platform> platforms;
    std::vector<Enemy> enemies;
    std::vector<Bullet> bullets;


    int killCount;  
    int waveCounter;
    int lives;

    bool isNextWaveReady;

    void generateEnemies();
    void spawnNextWave();
    void initBackground();
    void generateMap();
    void handleShooting();
    void updateUI();
    void updateLivesText();

public:
    Game();
    void run();
};
