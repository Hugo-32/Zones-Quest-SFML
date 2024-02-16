#include "Coin.h"
const float Coin::DEFAULT_COIN_ANIMATION_DELAY = 0.1f;
const float Coin::DEFAULT_COIN_SCALE = 2.5f;

using namespace std;
using namespace sf;

Coin::Coin() :
	value(DEFAULT_COIN_VALUE),
	coinRect(DEFAULT_COIN_RECT_X, DEFAULT_COIN_RECT_Y, DEFAULT_COIN_RECT_WIDTH, DEFAULT_COIN_RECT_HEIGHT),
	currentSpriteIndex(0),
	animationDelay(DEFAULT_COIN_ANIMATION_DELAY)
{
	sprite.setTextureRect(coinRect);
}

Coin::Coin(const Texture& texture) :
	value(DEFAULT_COIN_VALUE),
	coinRect(DEFAULT_COIN_RECT_X, DEFAULT_COIN_RECT_Y, DEFAULT_COIN_RECT_WIDTH, DEFAULT_COIN_RECT_HEIGHT),
	currentSpriteIndex(0),
	animationDelay(DEFAULT_COIN_ANIMATION_DELAY)
{
	sprite.setTexture(texture);
	sprite.setTextureRect(coinRect);
}

int Coin::getValue()
{
	return this->value;
}

void Coin::setValue(const int value)
{
	this->value = value;
}

void Coin::setTexture(const Texture& texture)
{
	this->sprite.setTexture(texture);
}

void Coin::tickSprite()
{
	if (animationClock.getElapsedTime().asSeconds() >= animationDelay) {
		currentSpriteIndex = (currentSpriteIndex + 1) % COIN_SPRITE_COUNT;
		coinRect.left = currentSpriteIndex * 16;
		sprite.setTextureRect(coinRect);
		animationClock.restart();
	}
}

Sprite& Coin::getSprite()
{
	return this->sprite;
}

Vector2f Coin::getSpritePosition()
{
	return this->sprite.getPosition();
}