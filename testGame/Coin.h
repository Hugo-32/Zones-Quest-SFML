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

	/// <summary>
	/// Delay in seconds between frames of the animation.
	/// </summary>
	float animationDelay;

	sf::Clock animationClock;
public:
	/// <summary>
	/// The default point value of a coin.
	/// </summary>
	static const int DEFAULT_COIN_VALUE = 1;

	/// <summary>
	/// Default X coin rect position in the texture
	/// </summary>
	static const int DEFAULT_COIN_RECT_X = 0;
	/// <summary>
	/// Default Y coin rect position in the texture
	/// </summary>
	static const int DEFAULT_COIN_RECT_Y = 0;
	/// <summary>
	/// Default Width of the coin on the spritesheet
	/// </summary>
	static const int DEFAULT_COIN_RECT_WIDTH = 16;
	/// <summary>
	/// Default Height of the coin on the spritesheet
	/// </summary>
	static const int DEFAULT_COIN_RECT_HEIGHT = 16;
	/// <summary>
	/// Amount of images on the coin spritesheet
	/// </summary>
	static const int COIN_SPRITE_COUNT = 15;

	/// <summary>
	/// Amount of coins spread across all areas.
	/// </summary>
	static const int GENERAL_COIN_AMOUNT = 5;

	/// <summary>
	/// Amount of coins spread in the invisibility zone.
	/// </summary>
	static const int INVISIBILITY_COIN_AMOUNT = 50;

	/// <summary>
	/// Default delay on the coin animation/sprite change in seconds.
	/// </summary>
	static const float DEFAULT_COIN_ANIMATION_DELAY;
	/// <summary>
	/// Default increase in size of the coins.
	/// </summary>
	static const float DEFAULT_COIN_SCALE;

	/// <summary>
	/// Default constructor of the coin.
	/// </summary>
	Coin();
	/// <summary>
	/// Construct the coin with the needed texture
	/// </summary>
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

	/// <summary>
	/// Set new texture to the Coin.
	/// </summary>
	void setTexture(const sf::Texture& texture);

	/// <summary>
	/// Advance the sprite to the next frame.
	/// </summary>
	void tickSprite();

	/// <summary>
	/// Get the sprite of the coin.
	/// </summary>
	sf::Sprite& getSprite();
	
	/// <summary>
	/// Get the position of the sprite of the coin.
	/// </summary>
	sf::Vector2f getSpritePosition();
};