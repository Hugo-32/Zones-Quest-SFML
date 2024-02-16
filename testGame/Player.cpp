#include "Player.h"

Player::Player() : currentSpriteIndex(0), direction(0), hp(3), animationDelay(0.1f), isPlayerAlive(true) {
    texture.loadFromFile("Evil.png");
    sprite.setTexture(texture);
    textureRect = IntRect(0, 0, 48, 72);
    sprite.setTextureRect(textureRect);
    currentZone = nullptr;
}

void Player::setScale(float scaleX, float scaleY) {
    sprite.setScale(scaleX, scaleY);
}

void Player::setHP(int hp) {
    this->hp = hp;
}

int Player::getHP() {
    return this->hp;
}

int Player::getAliveStatus() {
    return this->isPlayerAlive;
}

void Player::setAliveStatus() {
    this->isPlayerAlive = !isPlayerAlive;
}

Sprite& Player::getSprite() {
    return sprite;
}

Vector2f Player::getPosition() const {
    return sprite.getPosition();
}

void Player::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

Zone* Player::getZone() const {
    return currentZone;
}

void Player::setZone(Zone* zone) {
    currentZone = zone;
}

void Player::draw(RenderWindow& window) {
    if (currentZone && currentZone->getType() != 4) {
        window.draw(sprite);
    }
}

int Player::getDirection() {
    return direction;
}

void Player::setDirection(int d) {
    direction = d;
    int row = d - 1;
    textureRect.left = currentSpriteIndex * 48;
    textureRect.top = row * 72;
    sprite.setTextureRect(textureRect);
}

void Player::updateAnimation() {
    if (animationClock.getElapsedTime().asSeconds() >= animationDelay) {
        currentSpriteIndex = (currentSpriteIndex + 1) % 3;
        setDirection(direction);
        animationClock.restart();
    }
}
