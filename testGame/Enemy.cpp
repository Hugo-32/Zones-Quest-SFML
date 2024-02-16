#include "Enemy.h"
#include <cmath>

Enemy::Enemy() : currentSpriteIndex(0), animationDelay(0.1f), direction(0) {
    texture.loadFromFile("monster.png");
    sprite.setTexture(texture);
    textureRect = IntRect(0, 0, 48, 72);
    sprite.setTextureRect(textureRect);
    isActive = true;
}

void Enemy::setScale(float scaleX, float scaleY) {
    sprite.setScale(scaleX, scaleY);
}

Sprite& Enemy::getSprite() {
    return sprite;
}

Vector2f Enemy::getPosition() const {
    return sprite.getPosition();
}

void Enemy::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

void Enemy::draw(RenderWindow& window) {
    window.draw(sprite);
}

int Enemy::getDirection() {
    return direction;
}

void Enemy::setDirection(int d) {
    direction = d;
    int row = d - 1;
    textureRect.left = currentSpriteIndex * 48;
    textureRect.top = row * 72;
    sprite.setTextureRect(textureRect);
}

void Enemy::updateAnimation() {
    if (animationClock.getElapsedTime().asSeconds() >= animationDelay) {
        currentSpriteIndex = (currentSpriteIndex + 1) % 3;
        setDirection(direction);
        animationClock.restart();
    }
}

bool Enemy::getActive() {
    return isActive;
}

void Enemy::setActive(bool isActive) {
    this->isActive = isActive;
}

void Enemy::handleEnemyMovement(Vector2f playerPosition) {
    const float speed = 0.01f;
    const Vector2f& enemyPosition = getPosition();
    const FloatRect& enemyBounds = getSprite().getGlobalBounds();

    if (fabs(playerPosition.x - enemyPosition.x) > fabs(playerPosition.y - enemyPosition.y)) {
        if (playerPosition.x > enemyPosition.x) {
            setDirection(3);
            setPosition(enemyPosition.x + speed, enemyPosition.y);
        }
        else if (playerPosition.x < enemyPosition.x) {
            setDirection(2);
            setPosition(enemyPosition.x - speed, enemyPosition.y);
        }
    }
    else {
        if (playerPosition.y > enemyPosition.y) {
            setDirection(1);
            setPosition(enemyPosition.x, enemyPosition.y + speed);
        }
        else if (playerPosition.y < enemyPosition.y) {
            setDirection(4);
            setPosition(enemyPosition.x, enemyPosition.y - speed);
        }
    }
}