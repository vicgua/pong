#include "Pilota.hpp"

Pilota::Pilota(Marcador* marcador) {
    shape = new sf::CircleShape(RADI);
    shape->setFillColor(sf::Color(51, 204, 51));
    assert(s_buffer.loadFromFile("assets/sounds/pong.wav"));
    sound.setBuffer(s_buffer);
    this->marcador = marcador;
    ultima_col = NO;
    reset();
}

Pilota::~Pilota() {
    delete shape;
}

void Pilota::render(sf::RenderWindow& window, const Pala& jugador) {
    move(jugador);
    window.draw(*shape);
}

void Pilota::reset() {
    double angle;
    do
        angle = Random::genReal<double>(toRad(225), toRad(315)); while (angle == toRad(270));
    vx = V_0 * cos(angle);
    vy = V_0 * sin(angle);
    shape->setPosition((WIDTH - RADI) / 2, HEIGHT - 2 * RADI - Pala::POS_Y);
}

double Pilota::normRad(double a) {
    while (a < 0)
        a += 2 * M_PI;
    return fmod(a, 2 * M_PI);
}

void Pilota::move(const Pala& jugador) {
    if (paused) return;
    sf::Vector2<float> pos = shape->getPosition();

    if (Random::genBool(0.01)) { // Canvia de velocitat ocasionalment
        double v = sqrt(vx * vx + vy * vy);
        double angle = normRad(atan2(vy, vx));
        double a = Random::genReal(1.2 * A, -A); // Accelera més que frena
        if (v + a <= V_MAX && v + a >= V_0) {
            v += a;
            vx = v * cos(angle);
            vy = v * sin(angle);
        }
    }

    // Si es surt, inverteix la direcció
    if (pos.x + vx + RADI <= 0) {
        vx *= -1;
        pos = shape->getPosition();
        sound.play();
    } else if (pos.x + vx + RADI >= WIDTH) {
        vx *= -1;
        pos = shape->getPosition();
        sound.play();
    }
    if (pos.y + vy + RADI <= 0) {
        vy *= -1;
        sound.play();
    } else if (pos.y + vy + RADI >= HEIGHT) {
        marcador->subsVides();
        reset();
        return;
    }
    switch (colisio(jugador, vx, vy)) {
        case NO:
            // `ultima_col` evita que es quedi "aturada", donant molts punts.
            ultima_col = NO;
            break;
        case SUP:
            if (ultima_col != NO)
                break;
            ultima_col = SUP;
            marcador->addPunts();
            vy *= -1;
            sound.play();
            break;
        case LAT:
            if (ultima_col != NO)
                break;
            ultima_col = LAT;
            vx *= -1;
            sound.play();
            break;
    };
    shape->move(vx, vy);
}

Pilota::Col Pilota::colisio(const Pala& jugador, double vx, double vy) {
    sf::Vector2<float> pos = shape->getPosition() + shape->getOrigin()
            + sf::Vector2f(vx, vy);
    sf::Vector2<float> pos_pala = jugador.shape->getPosition()
            + jugador.shape->getOrigin();
    if (pos.x - RADI <= pos_pala.x + Pala::DX && pos.x + RADI >= pos_pala.x
            && pos.y + RADI >= pos_pala.y
            && pos.y - RADI <= pos_pala.y + Pala::DY)
        return INF;
    if (pos.y - RADI >= pos_pala.y && pos.y + RADI <= pos_pala.y + Pala::DY
            && pos.x + RADI >= pos_pala.x
            && pos.x - RADI <= pos_pala.x + Pala::DX)
        return LAT;
    return NO;
}
