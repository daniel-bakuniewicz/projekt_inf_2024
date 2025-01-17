#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class Enemy
{
private:
    sf::RectangleShape shape;
    sf::Texture texture;
    sf::Sprite sprite;

    int currentFrame;
    int totalFrames;
    int health;
    
    float frameDuration;
    float frameTimer;
    float speed;

public:
    Enemy(float x, float y, float width, float height, float speed, int initialHealth = 2);

    void update(float deltaTime);
    void render(sf::RenderWindow& window);
    void initAnimation(const sf::Texture& sharedTexture, int frames, float duration);
    void updateAnimation(float deltaTime);

    sf::FloatRect getBounds() const;

    void takeDamage();
    bool isDead() const;
};