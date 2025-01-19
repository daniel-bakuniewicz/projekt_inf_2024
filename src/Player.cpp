#include "Player.h"
#include <iostream>

Player::Player() : speed(200.0f), jumpVelocity(-500.0f), gravity(500.0f), verticalVelocity(0.0f), onGround(false), canFallThrough(false)
{
    shape.setSize({50, 50});
    shape.setFillColor(sf::Color::Blue);
    shape.setOrigin(shape.getSize().x / 2.0f, shape.getSize().y / 2.0f);
}

void Player::init(const sf::RenderWindow& window, float startX, float startY)
{
    shape.setPosition(startX, startY);
    onGround = true;
}

void Player::update(float deltaTime, const sf::RenderWindow& window)
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

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        canFallThrough = true;
    }

    else
    {
        canFallThrough = false;
    }

    if (!onGround)
    {
        float enhancedGravity = gravity * 2.0f;
        verticalVelocity += enhancedGravity * deltaTime;
    }

    else
    {
        verticalVelocity += gravity * deltaTime;
    }

    shape.move(0, verticalVelocity * deltaTime);

    if (shape.getPosition().y >= 550)
    {
        shape.setPosition(shape.getPosition().x, 550);
        verticalVelocity = 0;
        onGround = true;
    }

    sf::Vector2f position = shape.getPosition();
    
    float halfWidth = shape.getSize().x / 2.0f;

    if (position.x - halfWidth < 0)
    {
        shape.setPosition(halfWidth, position.y);
    }

    else if (position.x + halfWidth > window.getSize().x)
    {
        shape.setPosition(window.getSize().x - halfWidth, position.y);
    }
}


void Player::checkCollision(const sf::FloatRect& platformBounds)
{
    sf::FloatRect playerBounds = getBounds();

    if (canFallThrough)
    {
        return;
    }

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
    sprite.setPosition(shape.getPosition());
    window.draw(sprite);
}

void Player::initAnimation(const std::string& textureFile, int frames, float duration)
{
    if (!texture.loadFromFile(textureFile))
    {
        throw std::runtime_error("Failed to load texture: " + textureFile);
    }

    float scaleFactor = 3.0f;
    sprite.setTexture(texture);
    sprite.setScale(scaleFactor, scaleFactor);

    int frameWidth = texture.getSize().x / frames;
    int frameHeight = texture.getSize().y;

    sprite.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));

    sprite.setOrigin(frameWidth / 2.0f, frameHeight / 2.0f - 10.0f);

    sprite.setScale(-scaleFactor, scaleFactor);

    currentFrame = 0;
    totalFrames = frames;
    frameDuration = duration;
    frameTimer = 0.0f;
}



void Player::updateAnimation(float deltaTime)
{
    frameTimer += deltaTime;

    if (frameTimer >= frameDuration)
    {
        frameTimer -= frameDuration;
        currentFrame = (currentFrame + 1) % totalFrames;

        int frameWidth = texture.getSize().x / totalFrames;
        sprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth, texture.getSize().y));
    }
}



