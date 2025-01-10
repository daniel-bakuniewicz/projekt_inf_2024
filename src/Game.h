#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Platform.h"
#include <vector>

class Game
{
private:
    sf::RenderWindow window;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    Player player;
    std::vector<Platform> platforms;

    void initPlatforms();
    void initBackground();

public:
    Game();
    void run();
};
