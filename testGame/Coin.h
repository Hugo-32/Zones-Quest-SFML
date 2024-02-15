#pragma once

#include <SFML/Graphics.hpp>

/// <summary>
/// A Coin/Points representation inside the game
/// </summary>
class Coin
{
private:
	/// <summary>
	/// Sprite representing the coin in the game.
	/// </summary>
	sf::Sprite sprite;

	/// <summary>
	/// Rectangle to set the Sprite positioning in the spritesheet.
	/// </summary>
	sf::IntRect coinRect;

	/// <summary>
	/// The point value of the coin.
	/// </summary>
	int value;

	/// <summary>
	/// The number of the sprite animation in use.
	/// </summary>
	int currentSpriteIndex;

	float animationDelay;

	sf::Clock animationClock;
public:
	/// <summary>
	/// The default point value of a coin.
	/// </summary>
	static const int DEFAULT_COIN_VALUE = 1;

	static const int DEFAULT_COIN_RECT_X = 0;
	static const int DEFAULT_COIN_RECT_Y = 0;
	static const int DEFAULT_COIN_RECT_WIDTH = 16;
	static const int DEFAULT_COIN_RECT_HEIGHT = 16;
	static const int COIN_SPRITE_COUNT = 15;

	static const int GENERAL_COIN_AMOUNT = 100;
	static const int INVISIBILITY_COIN_AMOUNT = 200;

	static const float DEFAULT_COIN_ANIMATION_DELAY;
	static const float DEFAULT_COIN_SCALE;

	Coin();
	Coin(const sf::Texture& texture);

	/// <summary>
	/// Gets this coin value.
	/// </summary>
	/// <returns>This coin value.</returns>
	int getValue();

	/// <summary>
	/// Sets this coin value.
	/// </summary>
	/// <param name="value">The new value of the coin.</param>
	void setValue(int value);

	void setTexture(const sf::Texture& texture);

	void tickSprite();

	sf::Sprite& getSprite();
	
	sf::Vector2f getSpritePosition();
};