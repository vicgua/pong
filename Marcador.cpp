#include "Marcador.hpp"

Marcador::Marcador(bool videsInf) {
    this->vides_inf = videsInf;
    vides = VIDES_INICIALS;
    punts = 0;
	if (!font.loadFromFile("assets/fonts/AnonymousPro-Regular.ttf"))
		throw std::runtime_error(no_asset);
	if (!font_bold.loadFromFile("assets/fonts/AnonymousPro-Bold.ttf"))
		throw std::runtime_error(no_asset);
    t_punts.setFont(font);
    t_punts.setPosition(POS_X, POS_Y);
    t_punts.setFillColor(sf::Color::Black);
    t_punts.setCharacterSize(FONT_SIZE);
    t_punts.setString(std::to_string(punts));
    t_vides.setFont(font);
    std::string videsStr = videsInf ? "Inf" : std::to_string(vides);
    t_vides.setPosition(WIDTH - POS_X - videsStr.length() * FONT_SIZE, POS_Y);
    t_vides.setFillColor(sf::Color::Red);
    t_vides.setCharacterSize(FONT_SIZE);
    t_vides.setString(videsStr);
}

void Marcador::addPunts(int num) {
    punts += num;
    t_punts.setString(std::to_string(punts));
}

void Marcador::subsVides(int num) {
    if (vides_inf) return;
    vides -= num;
    if (vides < 0) {
        puntuacio_mes_alta = std::max(puntuacio_mes_alta, punts);
        show_title = true;
        paused = true;
        vides = VIDES_INICIALS;
    }
    std::string videsStr = std::to_string(vides);
    t_vides.setString(videsStr);
    t_vides.setPosition(WIDTH - POS_X - videsStr.length() * FONT_SIZE, POS_Y);
}

void Marcador::render(sf::RenderWindow& window) {
    if (paused) {
        sf::Text pausa;
        std::string pausaStr = "Pausa";
        pausa.setString(pausaStr);
        //pausa.setStyle(sf::Text::Bold);
        pausa.setFillColor(sf::Color::Black);
        pausa.setFont(font_bold);
        pausa.setCharacterSize(2 * FONT_SIZE);
        pausa.setPosition(WIDTH / 2 - pausaStr.length() / 2 * PAUSA_SIZE,
                HEIGHT / 2 - PAUSA_SIZE / 2);
        window.draw(pausa);
    }
    window.draw(t_punts);
    window.draw(t_vides);
}
