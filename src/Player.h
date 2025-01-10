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

public:
    Player();

    void init(const sf::RenderWindow& window);
    void update(float deltaTime);
    void checkCollision(const sf::FloatRect& platformBounds);
    void render(sf::RenderWindow& window);

    sf::FloatRect getBounds() const;
};
