#define ENEMY_SIZE 20
#define ENEMY_COUNT 3


#include <chrono>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
#include <algorithm>
#include "Coin.h"

using namespace sf;
using namespace std;


class Enemy {
    Sprite sprite;
    bool isActive;
    Texture texture;
    IntRect textureRect;
    int currentSpriteIndex;
    Clock animationClock;
    float animationDelay;
    int direction;
public:
    Enemy() : currentSpriteIndex(0), animationDelay(0.1f), direction(0){
        texture.loadFromFile("/Evil.png");
        sprite.setTexture(texture);
        textureRect = IntRect(0, 0, 48, 72);
        sprite.setTextureRect(textureRect);
        isActive = true;
    }
    void setScale(float scaleX, float scaleY)
    {
        sprite.setScale(scaleX, scaleY);
    }
        
    Sprite& getSprite() {
        return sprite;
    }
    Vector2f getPosition() const {
        return sprite.getPosition();
    }
    void setPosition(float x, float y) {
        sprite.setPosition(x, y);
    }
    void draw(RenderWindow& window) {
        window.draw(sprite);
    }

    int getDirection() {
        return direction;
    }
    void setDirection(int d) {
        direction = d;
        int row = d - 1;
        textureRect.left = currentSpriteIndex * 48;
        textureRect.top = row * 72;
        sprite.setTextureRect(textureRect);
    }
    void updateAnimation() {
        if (animationClock.getElapsedTime().asSeconds() >= animationDelay) {
            currentSpriteIndex = (currentSpriteIndex + 1) % 3;
            setDirection(direction);
            animationClock.restart();
        }
    }

    bool getActive() {
        return isActive;
    }
    void setActive(bool isActive){
        this->isActive = isActive;
    }
    
};


class Zone {
protected:
    Color color;
    RectangleShape shape;
    Texture texture;
    int type;

public:
    virtual void draw(RenderWindow& window) = 0;

    void setPosition(float x, float y) {
        shape.setPosition(x, y);
    }
    RectangleShape& getShape()
    {
        return shape;
    }
    int getType() {
        return type;
    }
};

class BlackZone : public Zone {
public:
    BlackZone(float width, float height) {
        texture.loadFromFile("bg1.png");
        shape.setTexture(&texture);
        shape.setSize(Vector2f(width, height));
        type = 1;
    }

    void draw(RenderWindow& window) override {
        window.draw(shape);
    }
};

class GreenZone : public Zone {
    Enemy enemies[ENEMY_COUNT];
public:
    GreenZone(float width, float height) {
        texture.loadFromFile("bg2.png");
        shape.setTexture(&texture);
        shape.setSize(Vector2f(width, height));
        type = 2;
    }


    void draw(RenderWindow& window) override {
        window.draw(shape);
    }
    
    
};

class BlueZone : public Zone {
public:
    BlueZone(float width, float height) {
        texture.loadFromFile("bg3.png");
        shape.setTexture(&texture);
        shape.setSize(Vector2f(width, height));
        type = 3;
    }

    void draw(RenderWindow& window) override {
        window.draw(shape);
    }
    void initializeEnemeies() {
        return;
    }
};

class YellowZone : public Zone {
public:
    YellowZone(float width, float height) {
        texture.loadFromFile("bg4.png");
        shape.setTexture(&texture);
        shape.setSize(Vector2f(width, height));
        type = 4;
    }


    void draw(RenderWindow& window) override {
        window.draw(shape);
    }
};



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
public:
    Player() : currentSpriteIndex(0), direction(0), hp(3), animationDelay(0.1f){
        texture.loadFromFile("Evil.png");
        sprite.setTexture(texture);
        textureRect = IntRect(0, 0, 48, 72);
        sprite.setTextureRect(textureRect);
        currentZone = nullptr;
    }
    void setScale(float scaleX, float scaleY)
    {
        sprite.setScale(scaleX, scaleY);
    }
    void setHP(int hp) {
        this->hp = hp;
    }
    int getHP(){
        return this->hp;
    }
    Sprite& getSprite() {
        return sprite;
    }
    Vector2f getPosition() const {
        return sprite.getPosition();
    }
    void setPosition(float x, float y) {
        sprite.setPosition(x, y);
    }
    Zone* getZone() const {
        return currentZone;
    }
    void setZone(Zone* zone) {
        currentZone = zone;
    }

    void draw(RenderWindow& window) {
        window.draw(sprite);
    }

    int getDirection() {
        return direction;
    }
    void setDirection(int d) {
        direction = d;
        int row = d - 1;
        textureRect.left = currentSpriteIndex * 48;
        textureRect.top = row * 72;
        sprite.setTextureRect(textureRect);
    }
    void updateAnimation() {
        if (animationClock.getElapsedTime().asSeconds() >= animationDelay) {
            currentSpriteIndex = (currentSpriteIndex + 1) % 3;
            setDirection(direction);
            animationClock.restart();
        }
    }
};


class Game {
private:
    RenderWindow window;
    Zone* zones[4];
    Player player;
    vector<Coin> coins;
    //Coin coins[Coin::COIN_AMOUNT];
    int points=0;
    Texture coinTexture;
    Texture enemyTexture;
    Color playerColors[4];
    Clock gameClock;
    Font timerFont;
    Text timerText;
    Text scoreText;
    Text livesText;
    Enemy enemies[ENEMY_SIZE];
    bool gameOver;
    bool showGameOverScreen;

public:
    Game() : showGameOverScreen(false) {
        gameOver = false;
        VideoMode desktop = VideoMode::getDesktopMode();

        window.create(VideoMode(desktop.width, desktop.height), "SFML Game", Style::Fullscreen);


        float zoneWidth = desktop.width / 2.0f;
        float zoneHeight = desktop.height / 2.0f;
        
        
        
        srand(static_cast<unsigned int>(time(nullptr)));
        
        Zone * greenZone = nullptr;
        

        zones[0] = new BlackZone(zoneWidth, zoneHeight);
        zones[1] = new GreenZone(zoneWidth, zoneHeight);
        zones[2] = new BlueZone(zoneWidth, zoneHeight);
        zones[3] = new YellowZone(zoneWidth, zoneHeight);
        
        
        

        playerColors[0] = Color::Red;
        playerColors[1] = Color::Green;
        playerColors[2] = Color::Blue;
        playerColors[3] = Color::Yellow;
        
        std::random_device rd;
        std::mt19937 g(rd());
        shuffle(begin(zones), end(zones), g);
        
        
        //rundom_shuffle(begin(zones), end(zones));
        for (int i = 0; i < 4; ++i) {
            std::cout<<zones[i]->getType();
            float x = (i % 2) * zoneWidth;
            float y = (i / 2) * zoneHeight;
            zones[i]->setPosition(x, y);
            if (zones[i]->getType() == 2) {
                greenZone = zones[i];
            }
        }
        
        for (int i=0;i<ENEMY_COUNT;i++) {
            bool col = true;
            while (col) {
                int posX = rand()%int(greenZone->getShape().getSize().x-ENEMY_SIZE) + greenZone->getShape().getPosition().x;
                int posY = rand()%int(greenZone->getShape().getSize().y - ENEMY_SIZE) + greenZone->getShape().getPosition().y;
                enemies[i].setPosition(posX, posY);
                col = false;
                for(int j=0;j<i;j++) {
                    if (checkCollision(enemies[i].getSprite(), enemies[j].getSprite())) {
                        col = true;
                        break;
                    }
                }
            }
        }

        coinTexture.loadFromFile("coin1_16x16.png");
        sf::IntRect coinZone = sf::IntRect(0,0, desktop.width - Coin::DEFAULT_COIN_RECT_WIDTH, desktop.height - Coin::DEFAULT_COIN_RECT_HEIGHT);
        for (int i=0; i<Coin::GENERAL_COIN_AMOUNT; i++)
        {
            Coin tmpcoin(coinTexture);
            tmpcoin.getSprite().setPosition(rand() % coinZone.width+coinZone.left, rand() % coinZone.height+coinZone.top);
            tmpcoin.getSprite().setScale(Coin::DEFAULT_COIN_SCALE, Coin::DEFAULT_COIN_SCALE);
            coins.push_back(tmpcoin);
        }

        int blackZoneIndex=0;
        for (int i = 0; i < 4; i++)
        {
            if (zones[i]->getType() == 4)
            {
                blackZoneIndex = i;
                break;
            }
        }

        coinZone = sf::IntRect(zones[blackZoneIndex]->getShape().getPosition().x, zones[blackZoneIndex]->getShape().getPosition().y,int(zones[blackZoneIndex]->getShape().getSize().x) - Coin::DEFAULT_COIN_RECT_WIDTH, int(zones[blackZoneIndex]->getShape().getSize().y) - Coin::DEFAULT_COIN_RECT_HEIGHT);

        for (int i = 0; i < Coin::INVISIBILITY_COIN_AMOUNT; i++)
        {
            Coin tmpcoin(coinTexture);
            tmpcoin.getSprite().setPosition(rand() % coinZone.width + coinZone.left, rand() % coinZone.height + coinZone.top);
            tmpcoin.getSprite().setScale(Coin::DEFAULT_COIN_SCALE, Coin::DEFAULT_COIN_SCALE);
            coins.push_back(tmpcoin);
        }

        timerFont.loadFromFile("timerFont.otf");
        timerText.setFont(timerFont);
        timerText.setCharacterSize(27);
        timerText.setFillColor(Color::White);


        scoreText.setFont(timerFont);
        scoreText.setCharacterSize(27);
        scoreText.setFillColor(Color::White);
        scoreText.setPosition(10, 10);
        scoreText.setString("Score: 0");

        livesText.setFont(timerFont);
        livesText.setCharacterSize(27);
        livesText.setFillColor(Color::White);
        livesText.setString("Lives: 3");
        livesText.setPosition(window.getSize().x - livesText.getLocalBounds().width - 10, 10);
    }
    
    bool checkCollision(Sprite s1, Sprite s2) {
        Vector2f l1 = {s1.getPosition().x, s1.getPosition().y};
        Vector2f r1 = {s1.getPosition().x + s1.getGlobalBounds().width, s1.getPosition().y+s1.getGlobalBounds().height};
        Vector2f l2 = {s2.getPosition().x, s2.getPosition().y};
        Vector2f r2 = {s2.getPosition().x + s2.getGlobalBounds().width, s2.getPosition().y+s2.getGlobalBounds().height};
        
        if (l1.x > r2.x || l2.x > r1.x)
            return false;
         
        if (r1.y < l2.y || r2.y < l1.y)
            return false;
         
        
        return true;
    }

    /// <summary>
    /// Overload the checkCollision using the default SFML method
    /// </summary>
    bool checkCollision(sf::FloatRect first, sf::FloatRect second)
    {
        return first.intersects(second);
    }

    float findDistance(Sprite s1, Sprite s2) {
        float x1 = s1.getPosition().x + s1.getGlobalBounds().width/2;
        float x2 = s2.getPosition().x + s2.getGlobalBounds().width/2;
        float y1 = s1.getPosition().y + s1.getGlobalBounds().height/2;
        float y2 = s2.getPosition().y + s2.getGlobalBounds().height/2;
        return sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
    }
    
    

    void handlePlayerMovement(const Event& event, Player& player, const RenderWindow& window) {
        const float speed = 10.0f;
        const Vector2f& playerPosition = player.getPosition();
        const FloatRect& playerBounds = player.getSprite().getGlobalBounds();

        if (event.key.code == Keyboard::Right && playerBounds.left + playerBounds.width < window.getSize().x) {
            player.setDirection(3);
            player.updateAnimation();
            player.setPosition(playerPosition.x + speed, playerPosition.y);
        }
        else if (event.key.code == Keyboard::Left && playerBounds.left > 0.0f) {
            player.setDirection(2);
            player.updateAnimation();
            player.setPosition(playerPosition.x - speed, playerPosition.y);
        }
        else if (event.key.code == Keyboard::Down && playerBounds.top + playerBounds.height < window.getSize().y) {
            player.setDirection(1);
            player.updateAnimation();
            player.setPosition(playerPosition.x, playerPosition.y + speed);
        }
        else if (event.key.code == Keyboard::Up && playerBounds.top > 0.0f) {
            player.setDirection(4);
            player.updateAnimation();
            player.setPosition(playerPosition.x, playerPosition.y - speed);
        }
    }
    void updateDirection(const Event& event, Player& player) {
        if (event.key.code == Keyboard::Right) {
            player.setDirection(3);
        }
        else if (event.key.code == Keyboard::Left) {
            player.setDirection(2);
        }
        else if (event.key.code == Keyboard::Down) {
            player.setDirection(1);
        }
        else if (event.key.code == Keyboard::Up) {
            player.setDirection(4);
        }


    }
    
    void moveVec(const Event& event, Player& player, const RenderWindow& window) {
        const float speed = 0.1f;
        const Vector2f& playerPosition = player.getPosition();
        const FloatRect& playerBounds = player.getSprite().getGlobalBounds();

        switch (player.getDirection()) {
        case 1:
            if (playerBounds.top + playerBounds.height < window.getSize().y) {
                player.setPosition(playerPosition.x, playerPosition.y + speed);
                player.updateAnimation();
            }
            else {
                gameOver = true;
            }
            break;
        case 2:
            if (playerBounds.left > 0.0f) {
                player.setPosition(playerPosition.x - speed, playerPosition.y);
                player.updateAnimation();
            }
            else {
                gameOver = true;
            }
            break;
        case 3:
            if (playerBounds.left + playerBounds.width < window.getSize().x) {
                player.setPosition(playerPosition.x + speed, playerPosition.y);
                player.updateAnimation();
            }
            else {
                gameOver = true;
            }
            break;
        case 4:
            if (playerBounds.top > 0.0f) {
                player.setPosition(playerPosition.x, playerPosition.y - speed);
                player.updateAnimation();
            }
            else {
                gameOver = true;
            }
            break;
        }
    }

    void updatePlayerZoneAndColor() {
        for (int i = 0; i < 4; ++i) {
            if (zones[i]->getShape().getGlobalBounds().contains(player.getPosition())) {
                if (player.getZone() != zones[i]) {
                    player.setZone(zones[i]);
                    //player.setColorBasedOnZone();
                }

                break;
            }
        }
    }

    void run() {
        player.setScale(2.0f, 2.0f);
        int isLoaded = 0;
        auto lastHitted = chrono::high_resolution_clock::now();
        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed)
                    window.close();

                if (event.type == Event::KeyPressed) {
                    if (player.getZone()->getType() == 3) {
                        updateDirection(event, player);
                    } else {
                        handlePlayerMovement(event, player, window);
                    }
                    if (event.key.code == Keyboard::Space && player.getZone()->getType() == 2) {
                        for (int i=0; i<ENEMY_COUNT; i++) {
                            if (findDistance(player.getSprite(), enemies[i].getSprite()) <= 200) {
                                enemies[i].setActive(false);
                            }
                        }
                    }
                    if (event.key.code == Keyboard::R && gameOver == true)
                    {
                        window.close();
                        Game game;
                        game.run();
                    }
                    if (event.key.code == Keyboard::Escape && gameOver == true)
                    {
                        window.close();
                    }
                }
            

            }
            
            Time elapsedTime = gameClock.getElapsedTime();
            int timeLeft = max(120 - static_cast<int>(elapsedTime.asSeconds()), 0);
            FloatRect textRect = timerText.getLocalBounds();
            timerText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
            timerText.setPosition(Vector2f(window.getSize().x / 2.0f, 10 + textRect.height / 2.0f));

            if (timeLeft <= 0 || player.getHP() <= 0) {
                gameOver = true;
               
            }

            string timerString = "Time: " + to_string(timeLeft);
            timerText.setString(timerString);
            
            if (isLoaded && player.getZone()->getType() == 3) {
                moveVec(event, player, window);
            }
            if (isLoaded && player.getZone()->getType() == 2) {
                for (int i=0; i<ENEMY_COUNT; i++) {
                    if (enemies[i].getActive() && checkCollision(player.getSprite(), enemies[i].getSprite()) && std::chrono::duration<double, std::milli>(chrono::high_resolution_clock::now()-lastHitted).count() > 3000) {
                        player.setHP(player.getHP()-1);
                        livesText.setString("Lives: " + to_string(player.getHP()));
                        std::cout<<"damage";
                        lastHitted = chrono::high_resolution_clock::now();
                    }
                }
                
            }
            
            //Picking up the coins check
            for (auto i = coins.begin(); i != coins.end();)
            {
                //Check for collision with any coin
                if (checkCollision(player.getSprite().getGlobalBounds(), (*i).getSprite().getGlobalBounds()))
                {
                    //Add points for picking up the coin
                    points += (*i).getValue();
                    //Update the Score string
                    scoreText.setString("Score: " + to_string(points));
                    //Remove the coin from vector and set iterator to the next coin
                    i=coins.erase(i);
                }
                //otherwise advance the iterator
                else ++i;
            }
            
            if (!gameOver)
            {
                updatePlayerZoneAndColor();
                window.clear();
                for (int i = 0; i < 4; ++i) {
                    zones[i]->draw(window);
                    isLoaded = 1;
                }

                for (int i = 0;i < ENEMY_COUNT;i++) {
                    if (enemies[i].getActive()) {
                        enemies[i].draw(window);
                    }
                }
                //update the sprite frames for the coins
                for (auto i = coins.begin(); i != coins.end(); i++)
                {
                    (*i).tickSprite();
                    window.draw((*i).getSprite());
                }

                player.draw(window);
                window.draw(timerText);
                window.draw(scoreText);
                window.draw(livesText);
            }
            else
            {
                if (!showGameOverScreen)
                {
                    RectangleShape darkScreen(Vector2f(window.getSize().x, window.getSize().y));
                    darkScreen.setFillColor(Color(0, 0, 0, 150));
                    window.draw(darkScreen);

                    Font gameOverFont;
                    gameOverFont.loadFromFile("timerFont.otf");

                    Text gameOverText("Game Over", gameOverFont, 50);
                    gameOverText.setFillColor(Color::White);
                    FloatRect textRect = gameOverText.getLocalBounds();
                    gameOverText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
                    gameOverText.setPosition(Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f));
                    window.draw(gameOverText);

                    scoreText.setFont(timerFont);
                    scoreText.setCharacterSize(30);
                    scoreText.setString("Total Score: " + to_string(points));
                    FloatRect scoreTextRect = scoreText.getLocalBounds();
                    scoreText.setOrigin(scoreTextRect.left + scoreTextRect.width / 2.0f, scoreTextRect.top + scoreTextRect.height / 2.0f);
                    scoreText.setPosition(Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f + 50.0f));
                    window.draw(scoreText);

                    Text restartButton("Restart (Press 'R')", gameOverFont, 30);
                    restartButton.setFillColor(Color::White);
                    FloatRect restartButtonRect = restartButton.getLocalBounds();
                    restartButton.setOrigin(restartButtonRect.left + restartButtonRect.width / 2.0f, restartButtonRect.top + restartButtonRect.height / 2.0f);
                    restartButton.setPosition(Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f + 100.0f));
                    window.draw(restartButton);

                    Text exitButton("Exit (Press 'Esc')", gameOverFont, 30);
                    exitButton.setFillColor(Color::White);
                    FloatRect exitButtonRect = exitButton.getLocalBounds();
                    exitButton.setOrigin(exitButtonRect.left + exitButtonRect.width / 2.0f, exitButtonRect.top + exitButtonRect.height / 2.0f);
                    exitButton.setPosition(Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f + 150.0f));
                    window.draw(exitButton);
                }
                
            }

            window.display();
        }
    }
};

int main()
{
    Game game;
    game.run();
    return 0;
}
