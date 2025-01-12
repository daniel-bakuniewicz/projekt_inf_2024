#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Platform.h"
#include "Enemy.h"
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

    int waveCounter;
    bool isNextWaveReady;

    void generateEnemies();
    void checkWaveProgress();
    void initBackground();
    void generateMap();

public:
    Game();
    void run();
};
