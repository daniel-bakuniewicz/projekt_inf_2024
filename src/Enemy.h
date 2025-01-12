#pragma once
#include <SFML/Graphics.hpp>

class Enemy
{
private:
    sf::RectangleShape shape;
    float speed;

public:
    Enemy(float x, float y, float width, float height, float speed);

    void update(float deltaTime);
    void render(sf::RenderWindow& window);

    sf::FloatRect getBounds() const;
};
