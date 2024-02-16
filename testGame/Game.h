#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <chrono>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <random>
#include "Zone.h"
#include "Player.h"
#include "Coin.h"
#include "Enemy.h"
#include "Audio.h"

using namespace std;
using namespace sf;

class Game {
private:
    RenderWindow window;
    Zone* zones[4];
    Player player;
    vector<Coin> coins;
    int points = 0;
    Texture coinTexture;
    Texture enemyTexture;
    Color playerColors[4];
    Clock gameClock;
    Font timerFont;
    Font timerFontOutline;
    Text timerText;
    Text timerTextOutline;
    Text scoreText;
    Text livesText;
    Text livesTextOutline;
    Text scoreTextOutline;
    Enemy enemies[ENEMY_COUNT];
    Audio gameAudio;
    bool allEnemiesDefeated = false;
    bool gameOver;
    bool showGameOverScreen;
    bool gameWin;
    bool showGameWinScreen;

public:
    Game();
    void run();

private:
    bool checkCollision(Sprite s1, Sprite s2);
    bool checkCollision(FloatRect first, FloatRect second);
    float findDistance(Sprite s1, Sprite s2);
    void handlePlayerMovement(const Event& event, Player& player, const RenderWindow& window);
    void updateDirection(const Event& event, Player& player);
    void moveVec(const Event& event, Player& player, const RenderWindow& window);
    void updatePlayerZoneAndColor();
};

#endif // GAME_H
