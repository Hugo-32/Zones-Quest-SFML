
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resources, use the helper
// function `resourcePath()` from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace sf;
using namespace std;

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
    int getType(){
        return type;
    }
};

class BlackZone : public Zone {
public:
    BlackZone(float width, float height) {
        //color = Color::Black;
        //shape.setFillColor(color);
        texture.loadFromFile("background1.png");
        shape.setTexture(&texture);
        shape.setSize(Vector2f(width, height));
        type = 1;
    }

    void draw(RenderWindow& window) override {
        window.draw(shape);
    }
};

class GreenZone : public Zone {
public:
    GreenZone(float width, float height) {
        texture.loadFromFile("background2.png");
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
        texture.loadFromFile("background3.png");
        shape.setTexture(&texture);
        shape.setSize(Vector2f(width, height));
        type = 3;
    }

    void draw(RenderWindow& window) override {
        window.draw(shape);
    }
};

class YellowZone : public Zone {
public:
    YellowZone(float width, float height) {
        texture.loadFromFile("background4.png");
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
    RectangleShape shape;
    Zone* currentZone;
    Color playerColor;
    int direction;
    

public:
    Player() {
        shape.setSize(Vector2f(40, 60));
        currentZone = nullptr;
        shape.setFillColor(playerColor);
        direction = 0;
    }
    RectangleShape& getShape() {
        return shape;
    }
    Vector2f getPosition() const {
        return shape.getPosition();
    }
    void setPosition(float x, float y) {
        shape.setPosition(x, y);
    }
    Zone* getZone() const {
        return currentZone;
    }
    void setZone(Zone* zone) {
        currentZone = zone;
    }

    void draw(RenderWindow& window) {
        window.draw(shape);
    }
    void setColor(Color color) {
        playerColor = color;
        shape.setFillColor(playerColor);
    }
    void setColorBasedOnZone() {
        if (currentZone != nullptr) {
            if (dynamic_cast<BlackZone*>(currentZone) != nullptr) {
                playerColor = Color::White;
            }
            else if (dynamic_cast<BlueZone*>(currentZone) != nullptr) {
                playerColor = Color::Red;
            }
            else if (dynamic_cast<YellowZone*>(currentZone) != nullptr) {
                playerColor = Color::Transparent;
            }
            else if (dynamic_cast<GreenZone*>(currentZone) != nullptr) {
                playerColor = Color::Yellow;
            }
        }

        shape.setFillColor(playerColor);
    }
    
    int getDirection(){
        return direction;
    }
    void setDirection(int d){
        this->direction = d;
    }
};


class Game {
private:
    RenderWindow window;
    Zone* zones[4];
    Player player;
    Color playerColors[4];

public:
    Game() {
        VideoMode desktop = VideoMode::getDesktopMode();


        /*window.create(VideoMode(800,600), "SFML Game");//, Style::Fullscreen);
        float zoneWidth = 800 / 2.0f;
        float zoneHeight = 600 / 2.0f;*/
        
        window.create(VideoMode(desktop.width, desktop.height), "SFML Game", Style::Fullscreen);


        float zoneWidth = desktop.width / 2.0f;
        float zoneHeight = desktop.height / 2.0f;
        
        
        srand(static_cast<unsigned int>(time(nullptr)));


        zones[0] = new BlackZone(zoneWidth, zoneHeight);
        zones[1] = new GreenZone(zoneWidth, zoneHeight);
        zones[2] = new BlueZone(zoneWidth, zoneHeight);
        zones[3] = new YellowZone(zoneWidth, zoneHeight);

        playerColors[0] = Color::Red;
        playerColors[1] = Color::Green;
        playerColors[2] = Color::Blue;
        playerColors[3] = Color::Yellow;

        random_shuffle(begin(zones), end(zones));
        for (int i = 0; i < 4; ++i) {
            float x = (i % 2) * zoneWidth;
            float y = (i / 2) * zoneHeight;
            zones[i]->setPosition(x, y);
        }
    }

    void handlePlayerMovement(const Event& event, Player& player, const RenderWindow& window) {
        const float speed = 20.0f;
        const Vector2f& playerPosition = player.getPosition();
        const Vector2f& playerSize = player.getShape().getSize();

        if (event.key.code == Keyboard::Right && playerPosition.x + playerSize.x < window.getSize().x) {
            player.setPosition(playerPosition.x + speed, playerPosition.y);
            player.setDirection(1);
        }
        else if (event.key.code == Keyboard::Left && playerPosition.x > 0.0f) {
            player.setPosition(playerPosition.x - speed, playerPosition.y);
            player.setDirection(2);
        }
        else if (event.key.code == Keyboard::Down && playerPosition.y + playerSize.y < window.getSize().y) {
            player.setPosition(playerPosition.x, playerPosition.y + speed);
            player.setDirection(3);
        }
        else if (event.key.code == Keyboard::Up && playerPosition.y > 0.0f) {
            player.setPosition(playerPosition.x, playerPosition.y - speed);
            player.setDirection(4);
        }
    }
    void updateDirection(const Event& event, Player& player) {
        if (event.key.code == Keyboard::Right) {
            player.setDirection(1);
        }
        else if (event.key.code == Keyboard::Left) {
            player.setDirection(2);
        }
        else if (event.key.code == Keyboard::Down) {
            player.setDirection(3);
        }
        else if (event.key.code == Keyboard::Up) {
            player.setDirection(4);
        }
        
        
    }
    
    void moveVec(const Event& event, Player& player, const RenderWindow& window) {
        const float speed = 0.1f;
        const Vector2f& playerPosition = player.getPosition();
        const Vector2f& playerSize = player.getShape().getSize();
        switch (player.getDirection()) {
            case 1:
                if (playerPosition.x + playerSize.x < window.getSize().x) {
                    player.setPosition(playerPosition.x + speed, playerPosition.y);
                }
                else {
                    std::cout<<"game over";
                }
                break;
            case 2:
                if ( playerPosition.x > 0.0f) {
                    player.setPosition(playerPosition.x - speed, playerPosition.y);
                } else {
                    std::cout<<"game over";
                }
                break;
            case 3:
                if (playerPosition.y + playerSize.y <window.getSize().y){
                    player.setPosition(playerPosition.x, playerPosition.y + speed);
                }else {
                    std::cout<<"game over";
                }
                break;
            case 4:
                if (playerPosition.y > 0.0f) {
                    player.setPosition(playerPosition.x, playerPosition.y - speed);
                } else {
                    std::cout<<"game over";
                }
                break;
        }
    }

    void updatePlayerZoneAndColor() {
        for (int i = 0; i < 4; ++i) {
            if (zones[i]->getShape().getGlobalBounds().contains(player.getPosition())) {
                if (player.getZone() != zones[i]) {
                    player.setZone(zones[i]);
                    player.setColorBasedOnZone();
                }

                break;
            }
        }
    }

    void run() {
        int isLoaded = 0;
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
                }

            }
            
            
            if (isLoaded and player.getZone()->getType() == 3) {
                moveVec(event, player, window);
            }
            updatePlayerZoneAndColor();
            window.clear();
            for (int i = 0; i < 4; ++i) {
                zones[i]->draw(window);
                isLoaded = 1;
            }



            player.draw(window);

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
