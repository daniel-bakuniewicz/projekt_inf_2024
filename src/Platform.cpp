#include "Platform.h"

Platform::Platform(float x, float y, float width, float height)
{
    shape.setSize({width, height});
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(x, y);
}

void Platform::render(sf::RenderWindow& window)
{
    window.draw(shape);
}

sf::FloatRect Platform::getBounds() const
{
    return shape.getGlobalBounds();
}
