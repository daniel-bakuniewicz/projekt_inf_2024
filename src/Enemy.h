#pragma once
#include <SFML/Graphics.hpp>

class Enemy
{
private:
    sf::RectangleShape shape;
    float speed;
    int health;

public:
    Enemy(float x, float y, float width, float height, float speed, int initialHealth = 2);

    void update(float deltaTime);
    void render(sf::RenderWindow& window);

    sf::FloatRect getBounds() const;

    void takeDamage();
    bool isDead() const;
};
