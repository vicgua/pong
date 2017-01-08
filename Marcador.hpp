#ifndef MARCADOR_HPP
#define MARCADOR_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <stdexcept>
#include <string>

#include "common.hpp"

class Marcador {
public:
    Marcador(bool videsInf = false);
    void addPunts(int num = 1);
    void subsVides(int num = 1);
    void render(sf::RenderWindow& window);
    static constexpr int VIDES_INICIALS = 3;
    static constexpr int FONT_SIZE = 18; // En píxels
    static constexpr int PAUSA_SIZE = 2 * FONT_SIZE;
    static constexpr float POS_X = 10;
    static constexpr float POS_Y = 10;
private:
    int punts;
    int vides;
    bool vides_inf;
    sf::Text t_punts;
    sf::Text t_vides;
    sf::Font font;
    sf::Font font_bold;
};

#endif /* MARCADOR_HPP */