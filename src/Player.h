#pragma once
#include <SFML/Graphics.hpp>

class Player
{
private:
    sf::RectangleShape shape;
    float speed;
    float jumpVelocity;
    float gravity;
    float verticalVelocity;
    bool onGround;
    bool canFallThrough;

public:
    Player();

    void init(const sf::RenderWindow& window, float startX, float startY);
    void update(float deltaTime, const sf::RenderWindow& window);
    void checkCollision(const sf::FloatRect& platformBounds);
    void render(sf::RenderWindow& window);

    sf::FloatRect getBounds() const;
};
