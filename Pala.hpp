#ifndef PALA_HPP
#define PALA_HPP

#include <SFML/Graphics.hpp>

#include "common.hpp"

class Pala {
    // La classe Pilota necessita accedir a `shape` per detectar col·lisions.
    friend class Pilota;
public:
    Pala();
    ~Pala();
    void move(double a);
    void render(sf::RenderWindow& window);
    constexpr static float MOV = 0.25;
    constexpr static float POS_Y = 30;
private:
    sf::RectangleShape* shape;
    constexpr static float DX = 90;
    constexpr static float DY = 15;
};

#endif /* PALA_HPP */

