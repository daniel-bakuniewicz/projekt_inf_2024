#pragma once
#include <SFML/Graphics.hpp>

class Player
{
private:
    sf::RectangleShape shape;
    sf::Texture texture;
    sf::Sprite sprite;
    int currentFrame;
    int totalFrames;
    float frameDuration;
    float frameTimer;
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
    void initAnimation(const std::string& textureFile, int frames, float duration);
    void updateAnimation(float deltaTime);

    sf::FloatRect getBounds() const;
};
