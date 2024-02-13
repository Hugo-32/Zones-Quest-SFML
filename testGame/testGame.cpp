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

public:
    virtual void draw(RenderWindow& window) = 0;

    void setPosition(float x, float y) {
        shape.setPosition(x, y);
    }
    RectangleShape& getShape()
    {
        return shape;
    }
};

class BlackZone : public Zone {
private:
    Texture texture;
public:
    BlackZone(float width, float height) {
        color = Color::Black;
        shape.setFillColor(color);
        /*texture.loadFromFile("background_black.jpg");
        shape.setTexture(&texture);*/
        shape.setSize(Vector2f(width, height));
    }

    void draw(RenderWindow& window) override {
        window.draw(shape);
    }
};

class GreenZone : public Zone {
public:
    GreenZone(float width, float height) {
        color = Color::Green;
        shape.setFillColor(color);
        shape.setSize(Vector2f(width, height));
    }


    void draw(RenderWindow& window) override {
        window.draw(shape);
    }
};

class BlueZone : public Zone {
public:
    BlueZone(float width, float height) {
        color = Color::Blue;
        shape.setFillColor(color);
        shape.setSize(Vector2f(width, height));
    }


    void draw(RenderWindow& window) override {
        window.draw(shape);
    }
};

class YellowZone : public Zone {
public:
    YellowZone(float width, float height) {
        color = Color::Yellow;
        shape.setFillColor(color);
        shape.setSize(Vector2f(width, height));
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

public:
    Player() {
        shape.setSize(Vector2f(50, 75));
        currentZone = nullptr;
        shape.setFillColor(playerColor);
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

        window.create(VideoMode(desktop.width, desktop.height), "SFML Game", Style::Fullscreen);

        srand(static_cast<unsigned int>(time(nullptr)));

        float zoneWidth = desktop.width / 2.0f;
        float zoneHeight = desktop.height / 2.0f;

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

    void run() {
        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed)
                    window.close();

                if (event.type == Event::KeyPressed) {
                    if (event.key.code == Keyboard::Right) {
                        player.setPosition(player.getPosition().x + 10.0f, player.getPosition().y);
                    }
                    else if (event.key.code == Keyboard::Left) {
                        player.setPosition(player.getPosition().x - 10.0f, player.getPosition().y);
                    }
                    else if (event.key.code == Keyboard::Down) {
                        player.setPosition(player.getPosition().x, player.getPosition().y + 10.0f);
                    }
                    else if (event.key.code == Keyboard::Up) {
                        player.setPosition(player.getPosition().x, player.getPosition().y - 10.0f);
                    }
                }
            }

            for (int i = 0; i < 4; ++i) {
                if (zones[i]->getShape().getGlobalBounds().contains(player.getPosition())) {
                    if (player.getZone() != zones[i]) {
                        player.setZone(zones[i]);
                        player.setColorBasedOnZone();
                    }
                    break;
                }
            }

            window.clear();

            for (int i = 0; i < 4; ++i) {
                zones[i]->draw(window);
            }

            player.draw(window);

            window.display();
        }
    }
};

int main() {
    Game game;
    game.run();

    return 0;
}