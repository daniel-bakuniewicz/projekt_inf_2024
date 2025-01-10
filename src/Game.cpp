#include "Game.h"

Game::Game() : window(sf::VideoMode(800, 600), "Penguin Defense") 
{
    window.setFramerateLimit(60);
}

void Game::run() 
{
    while (window.isOpen()) 
    {
        sf::Event event;
        
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.display();
    }
}
