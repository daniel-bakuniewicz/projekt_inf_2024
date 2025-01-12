#include "Enemy.h"

Enemy::Enemy(float x, float y, float width, float height, float speed) : speed(speed)
{
    shape.setSize({width, height});
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(x, y);
}


void Enemy::update(float deltaTime)
{
    shape.move(-speed * deltaTime, 0);
}

void Enemy::render(sf::RenderWindow& window)
{
    window.draw(shape);
}

sf::FloatRect Enemy::getBounds() const
{
    return shape.getGlobalBounds();
}
