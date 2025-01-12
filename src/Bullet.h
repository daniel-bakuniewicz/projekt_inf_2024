#pragma once
#include <SFML/Graphics.hpp>

class Bullet
{
private:
    sf::RectangleShape shape;
    float speed;

public:
    Bullet(float x, float y, float width, float height, float speed);

    void update(float deltaTime);
    void render(sf::RenderWindow& window);

    sf::FloatRect getBounds() const;
};
