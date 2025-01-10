#include "Game.h"

Game::Game() : window(sf::VideoMode(800, 600), "Penguin Defense")
{
    window.setFramerateLimit(60);
    player.init(window);
    initPlatforms();
}

void Game::initPlatforms()
{
    platforms.emplace_back(100.0f, 500.0f, 200.0f, 20.0f);
    platforms.emplace_back(300.0f, 450.0f, 200.0f, 20.0f);
    platforms.emplace_back(500.0f, 400.0f, 200.0f, 20.0f);
    platforms.emplace_back(300.0f, 350.0f, 200.0f, 20.0f);
    platforms.emplace_back(100.0f, 300.0f, 200.0f, 20.0f);
    platforms.emplace_back(300.0f, 250.0f, 200.0f, 20.0f);
    platforms.emplace_back(500.0f, 200.0f, 200.0f, 20.0f);
    platforms.emplace_back(300.0f, 150.0f, 200.0f, 20.0f);
    platforms.emplace_back(100.0f, 100.0f, 200.0f, 20.0f);
    

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

        for (auto& platform : platforms)
        {
            platform.render(window);
        }

        player.render(window);

        window.display();
    }
}
