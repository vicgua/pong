#include "Pala.hpp"

Pala::Pala() {
    shape = new sf::RectangleShape(sf::Vector2<float>(DX, DY));
    shape->setPosition((WIDTH - DX) / 2, HEIGHT - POS_Y);
    shape->setFillColor(sf::Color(153, 102, 51));
}

Pala::~Pala() {
    delete shape;
}

void Pala::move(double a) {
    if (paused) return;
    if (shape->getPosition().x + a < 0 ||
            shape->getPosition().x + DX + a > WIDTH)
        return;
    shape->move(a, 0);
}

void Pala::render(sf::RenderWindow& window) {
    window.draw(*shape);
}