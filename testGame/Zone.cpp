#include "Zone.h"

BlackZone::BlackZone(float width, float height) {
    texture.loadFromFile("bg1.png");
    shape.setTexture(&texture);
    shape.setSize(Vector2f(width, height));
    type = 1;
}

void BlackZone::draw(RenderWindow& window) {
    window.draw(shape);
}

GreenZone::GreenZone(float width, float height) {
    texture.loadFromFile("bg4.png");
    shape.setTexture(&texture);
    shape.setSize(Vector2f(width, height));
    type = 2;
}

void GreenZone::draw(RenderWindow& window) {
    window.draw(shape);
}

BlueZone::BlueZone(float width, float height) {
    texture.loadFromFile("bg2.png");
    shape.setTexture(&texture);
    shape.setSize(Vector2f(width, height));
    type = 3;
}

void BlueZone::draw(RenderWindow& window) {
    window.draw(shape);
}

void BlueZone::initializeEnemeies() {
    return;
}

YellowZone::YellowZone(float width, float height) {
    texture.loadFromFile("bg3.png");
    shape.setTexture(&texture);
    shape.setSize(Vector2f(width, height));
    type = 4;
}

void YellowZone::draw(RenderWindow& window) {
    window.draw(shape);
}
