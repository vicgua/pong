#ifndef PILOTA_HPP
#define PILOTA_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>

#include <chrono>
#include <random>
#include "Random.hpp"

#include "Pala.hpp"
#include "Marcador.hpp"

#include "common.hpp"

class Pilota {
public:
    Pilota(Marcador* marcador);
    ~Pilota();
    void render(sf::RenderWindow& window, const Pala& jugador);
private:
    /// Possibles col·lisions

    enum Col {
        NO,
        /// Superior
        SUP,
        /// Inferior (mateix efecte que SUP)
        INF = SUP,
        /// Lateral
        LAT
    };

    static constexpr double toRad(double deg) {
        return deg * M_PI / 180;
    }

    static constexpr double toDeg(double rad) {
        return rad * 180 / M_PI;
    }

    static double normRad(double a);

    void reset();
    void move(const Pala& jugador);
    Col colisio(const Pala& jugador, double vx, double vy);
    constexpr static double V_0 = 0.05;
    constexpr static double A = 5e-6;
    constexpr static double V_MAX = 0.15;
    constexpr static float RADI = 10;
    double vx;
    double vy;
    sf::CircleShape* shape;
    Marcador* marcador;
    Col ultima_col;
    sf::SoundBuffer s_buffer;
    sf::Sound sound;
};

#endif /* PILOTA_HPP */

