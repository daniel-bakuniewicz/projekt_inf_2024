#include "Player.h"

Player::Player()
    : speed(200.0f), jumpVelocity(-300.0f), gravity(500.0f), verticalVelocity(0.0f), onGround(false)
{
    shape.setSize({50, 50});
    shape.setFillColor(sf::Color::Blue);
    shape.setOrigin(shape.getSize().x / 2.0f, shape.getSize().y / 2.0f);
}

void Player::init(const sf::RenderWindow& window)
{
    shape.setPosition(window.getSize().x / 2.0f, window.getSize().y - 60);
    onGround = true;
}

void Player::update(float deltaTime)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        shape.move(-speed * deltaTime, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        shape.move(speed * deltaTime, 0);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && onGround)
    {
        verticalVelocity = jumpVelocity;
        onGround = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && onGround)
    {
        verticalVelocity = jumpVelocity;
        onGround = false;
    }

    verticalVelocity += gravity * deltaTime;
    shape.move(0, verticalVelocity * deltaTime);

    if (shape.getPosition().y >= 550)
    {
        shape.setPosition(shape.getPosition().x, 550);
        verticalVelocity = 0;
        onGround = true;
    }
}

void Player::checkCollision(const sf::FloatRect& platformBounds)
{
    sf::FloatRect playerBounds = getBounds();

    if (playerBounds.intersects(platformBounds) && verticalVelocity > 0)
    {
        float playerBottom = playerBounds.top + playerBounds.height;
        if (playerBottom <= platformBounds.top + 5.0f)
        {
            shape.setPosition(shape.getPosition().x, platformBounds.top - (playerBounds.height / 2.0f));
            verticalVelocity = 0;
            onGround = true;
        }
    }
}

sf::FloatRect Player::getBounds() const
{
    return shape.getGlobalBounds();
}

void Player::render(sf::RenderWindow& window)
{
    window.draw(shape);
}
