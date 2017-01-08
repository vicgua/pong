#include <SFML/Graphics.hpp>
#include "common.hpp"
#include "Pala.hpp"
#include "Pilota.hpp"
#include "Marcador.hpp"
#include "Title.hpp"
#include "Random.hpp"

#ifndef DEV_BUILD
#define DEV_BUILD 0
#endif

bool paused;
bool show_title;
int puntuacio_mes_alta;

std::default_random_engine Random::gen;

using kbd = sf::Keyboard; // Alias per a sf::Keyboard

int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT),
            "PONG");
    window.setKeyRepeatEnabled(false);
    Random::init();
    Title title;
    Marcador marcador(DEV_BUILD);
    Pilota pilota(&marcador);
    Pala pala;
    paused = true;
    show_title = true;
    puntuacio_mes_alta = -1;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    switch (event.key.code) {
                        case sf::Keyboard::Space:
                            paused = !paused;
                            break;
                        case sf::Keyboard::Escape:
                            window.close();
                            break;
                        case sf::Keyboard::F4: // Alt-F4
                            if (event.key.alt)
                                window.close();
                            break;
                        default:
                            // No fer res (siencia advertències d'alguns
                            // compiladors.
                            ;
                    }
                    break;
                default:
                    ;
            }
        }
        if (show_title) {
            if (!paused) show_title = false;
            else {
                title.render(window);
                continue;
            }
        }
        if (kbd::isKeyPressed(kbd::A) &&
                !kbd::isKeyPressed(kbd::D)) {
            if (kbd::isKeyPressed(kbd::LShift) ||
                    kbd::isKeyPressed(kbd::RShift))
                pala.move(-5 * Pala::MOV);
            else
                pala.move(-Pala::MOV);
        }
        if (kbd::isKeyPressed(kbd::D) &&
                !kbd::isKeyPressed(kbd::A)) {
            if (kbd::isKeyPressed(kbd::LShift) ||
                    kbd::isKeyPressed(kbd::RShift))
                pala.move(5 * Pala::MOV);
            else
                pala.move(Pala::MOV);
        }
        window.clear(sf::Color::White);
        pilota.render(window, pala);
        pala.render(window);
        marcador.render(window);
        window.display();
    }
}
