#include "Title.hpp"

Title::Title() {
    assert(texture.loadFromFile("assets/images/Title.png"));
    sprite.setTexture(texture);
    assert(font.loadFromFile("assets/fonts/AnonymousPro-Regular.ttf"));
    punt_max_text.setFont(font);
    punt_max_text.setPosition(Marcador::POS_X, Marcador::POS_Y);
    punt_max_text.setFillColor(sf::Color::Black);
    punt_max_text.setCharacterSize(Marcador::FONT_SIZE);
    punt_max_text.setString(L"Puntuació més alta:"); // L és necessari per a
    // crear un wchar_t* en lloc d'un char* (pels accents)
    punt_max.setFont(font);
    punt_max.setFillColor(sf::Color::Black);
    punt_max.setCharacterSize(Marcador::FONT_SIZE);
}

void Title::render(sf::RenderWindow& window) {
    window.clear(sf::Color::White);
    window.draw(sprite);
    if (puntuacio_mes_alta != -1) {
        window.draw(punt_max_text);
        std::string punt_str = std::to_string(puntuacio_mes_alta);
        punt_max.setPosition(WIDTH - Marcador::POS_X - punt_str.length() *
                Marcador::FONT_SIZE, Marcador::POS_Y);
        punt_max.setString(punt_str);
        window.draw(punt_max);
    }
    window.display();
}


