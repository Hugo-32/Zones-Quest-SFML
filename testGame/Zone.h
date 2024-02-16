#ifndef ZONE_H
#define ZONE_H

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

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

    RectangleShape& getShape() {
        return shape;
    }

    int getType() {
        return type;
    }
};

class BlackZone : public Zone {
public:
    BlackZone(float width, float height);
    void draw(RenderWindow& window) override;
};

class GreenZone : public Zone {
public:
    GreenZone(float width, float height);
    void draw(RenderWindow& window) override;
};

class BlueZone : public Zone {
public:
    BlueZone(float width, float height);
    void draw(RenderWindow& window) override;
    void initializeEnemeies();
};

class YellowZone : public Zone {
public:
    YellowZone(float width, float height);
    void draw(RenderWindow& window) override;
};

#endif // ZONE_H
