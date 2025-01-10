#include "Game.h"

Game::Game() : window(sf::VideoMode(800, 600), "Penguin Defense")
{
    window.setFramerateLimit(60);
    initBackground();
    player.init(window);
    initPlatforms();
}

void Game::initBackground()
{
    if (!backgroundTexture.loadFromFile("assets/background.png"))
    {
        throw std::runtime_error("Failed to load background.png");
    }
    backgroundSprite.setTexture(backgroundTexture);
}

void Game::initPlatforms()
{
    platforms.emplace_back(100.0f, 500.0f, 200.0f, 20.0f);
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

        window.clear();

        window.draw(backgroundSprite); // Rysowanie tła

        for (auto& platform : platforms)
        {
            platform.render(window);
        }

        player.render(window);

        window.display();
    }
}
