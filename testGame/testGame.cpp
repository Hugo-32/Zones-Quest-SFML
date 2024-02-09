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
};

class BlackZone : public Zone {
public:
    BlackZone(float width, float height) {
        color = Color::Black;
        shape.setFillColor(color);
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

class Game {
private:
    RenderWindow window;
    Zone* zones[4];

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
            }

            window.clear();
            for (int i = 0; i < 4; ++i) {
                zones[i]->draw(window);
            }
            window.display();
        }
    }

    ~Game() {
        for (int i = 0; i < 4; ++i) {
            delete zones[i];
        }
    }
};

int main() {
    Game game;
    game.run();

    return 0;
}