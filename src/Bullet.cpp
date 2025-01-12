#include "Bullet.h"

Bullet::Bullet(float x, float y, float width, float height, float speed) : speed(speed)
{
    shape.setSize({width, height});
    shape.setFillColor(sf::Color::Cyan);
    shape.setPosition(x, y);
}

void Bullet::update(float deltaTime)
{
    shape.move(speed * deltaTime, 0);
}

void Bullet::render(sf::RenderWindow& window)
{
    window.draw(shape);
}

sf::FloatRect Bullet::getBounds() const
{
    return shape.getGlobalBounds();
}
