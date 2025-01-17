#include "Enemy.h"
#include <iostream>

Enemy::Enemy(float x, float y, float width, float height, float speed, int initialHealth) : speed(speed), health(initialHealth)
{
    shape.setSize({width, height});
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(x, y);
}


void Enemy::update(float deltaTime)
{
    shape.move(-speed * deltaTime, 0);
    sprite.setPosition(shape.getPosition());
}

void Enemy::render(sf::RenderWindow& window)
{
    sprite.setPosition(shape.getPosition());
    window.draw(sprite);
}



sf::FloatRect Enemy::getBounds() const
{
    return shape.getGlobalBounds();
}

void Enemy::takeDamage()
{
    if (health > 0)
    {
        health--;
    }
}

bool Enemy::isDead() const
{
    return health <= 0;
}

void Enemy::initAnimation(const sf::Texture& sharedTexture, int frames, float duration)
{
    sprite.setTexture(sharedTexture);

    int frameWidth = sharedTexture.getSize().x / frames;
    int frameHeight = sharedTexture.getSize().y;

    sprite.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));
    sprite.setOrigin(frameWidth / 2.0f, frameHeight / 2.0f);

    float scaleFactor = 3.0f;
    sprite.setScale(scaleFactor, scaleFactor);

    currentFrame = 0;
    totalFrames = frames;
    frameDuration = duration;
    frameTimer = 0.0f;
}

void Enemy::updateAnimation(float deltaTime)
{
    frameTimer += deltaTime;

    if (frameTimer >= frameDuration)
    {
        frameTimer -= frameDuration;
        currentFrame = (currentFrame + 1) % totalFrames;

        int frameWidth = sprite.getTexture()->getSize().x / totalFrames;
        sprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth, sprite.getTexture()->getSize().y));
    }
}




