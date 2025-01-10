#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Platform.h"
#include <vector>

class Game
{
private:
    sf::RenderWindow window;
    Player player;
    std::vector<Platform> platforms;

    void initPlatforms();

public:
    Game();
    void run();
};
