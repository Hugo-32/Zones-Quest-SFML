#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>

#define ENEMY_COUNT 3
#define ENEMY_SIZE 20

using namespace std;
using namespace sf;

class Enemy {
private:
    Sprite sprite;
    bool isActive;
    Texture texture;
    IntRect textureRect;
    int currentSpriteIndex;
    Clock animationClock;
    float animationDelay;
    int direction;

public:
    Enemy();

    void setScale(float scaleX, float scaleY);

    Sprite& getSprite();

    Vector2f getPosition() const;

    void setPosition(float x, float y);

    void draw(RenderWindow& window);

    int getDirection();

    void setDirection(int d);

    void updateAnimation();

    bool getActive();

    void setActive(bool isActive);

    void handleEnemyMovement(Vector2f playerPosition);
};

#endif ENEMY_H