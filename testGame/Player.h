#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Zone.h"

using namespace std;
using namespace sf;

class Player {
private:
    Zone* currentZone;
    int direction;
    int hp;
    Sprite sprite;
    Texture texture;
    IntRect textureRect;
    int currentSpriteIndex;
    Clock animationClock;
    float animationDelay;
    bool isPlayerAlive;

public:
    Player();
    void setScale(float scaleX, float scaleY);
    void setHP(int hp);
    int getHP();
    int getAliveStatus();
    void setAliveStatus();
    Sprite& getSprite();
    Vector2f getPosition() const;
    void setPosition(float x, float y);
    Zone* getZone() const;
    void setZone(Zone* zone);
    void draw(RenderWindow& window);
    int getDirection();
    void setDirection(int d);
    void updateAnimation();
};

#endif PLAYER_H