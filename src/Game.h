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
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    Player player;
    std::vector<Platform> platforms;
    std::vector<Enemy> enemies;
    std::vector<Bullet> bullets;

    int waveCounter;
    bool isNextWaveReady;

    void generateEnemies();
    void spawnNextWave();
    void initBackground();
    void generateMap();
    void handleShooting();

public:
    Game();
    void run();
};
