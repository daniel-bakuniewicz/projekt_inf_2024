#pragma once
#include <SFML/Graphics.hpp>

class Platform
{
private:
    sf::RectangleShape shape;

public:
    Platform(float x, float y, float width, float height);

    void render(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
};
