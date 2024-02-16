#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
#include <algorithm>
#include "Coin.h"
#include "Audio.h"
#include "Enemy.h"
#include "Player.h"
#include "Zone.h"
#include "Game.h"

int main()
{
    Game game;
    game.run();
    return 0;
}