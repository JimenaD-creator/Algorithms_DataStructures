#include "Prácticas.h"
#include <cstdlib>
#include <vector>
#include <thread>
#include <chrono>
#include <iostream>

using namespace std;
using namespace sf;

void linearSearchVisual(sf::RenderWindow &window, const std::vector<int> &vec, int target) {
    bool found = false;
    sf::Font font;
    if (!font.loadFromFile("PlaywriteGBS-VariableFont_wght.ttf")) {
        std::cerr << "Error al cargar la fuente\n";
        return;
    }

    std::vector<sf::Text> elements(vec.size());
    for (size_t i = 0; i < vec.size(); ++i) {
        elements[i].setFont(font);
        elements[i].setString(std::to_string(vec[i]));
        elements[i].setCharacterSize(30);
        elements[i].setFillColor(sf::Color::White);
        elements[i].setPosition(50 + i * 80, 100); // Ajustar posición vertical
    }

    std::vector<sf::RectangleShape> bars(vec.size());
    for (size_t i = 0; i < vec.size(); ++i) {
        bars[i].setSize(sf::Vector2f(40, vec[i] * 5));
        bars[i].setFillColor(sf::Color::White);
        bars[i].setPosition(50 + i * 50, window.getSize().y - bars[i].getSize().y - 50); // Ajustar posición vertical
    }

    sf::Text complexity("Complejidad: O(n)", font, 20);
    complexity.setFillColor(sf::Color::Yellow);
    complexity.setPosition(50, 20);

    for (size_t i = 0; i < vec.size() && window.isOpen(); ++i) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }
        }
        for (auto &el : elements) el.setFillColor(sf::Color::White);
        elements[i].setFillColor(sf::Color::Green);

        for (auto &bar : bars) bar.setFillColor(sf::Color::White);
        bars[i].setFillColor(sf::Color::Green);

        window.clear();
        for (const auto &el : elements) window.draw(el);
        for (const auto &bar : bars) window.draw(bar);
        window.draw(complexity);
        window.display();

        sf::sleep(sf::seconds(1));
        if (vec[i] == target) {
            elements[i].setFillColor(sf::Color::Yellow);
            bars[i].setFillColor(sf::Color::Yellow);
            found = true;
            break;
        }
    }

    sf::Text result(found ? "Elemento encontrado" : "Elemento no encontrado", font, 30);
    result.setFillColor(found ? sf::Color::Green : sf::Color::Red);
    result.setPosition(50, 300); // Ajustar posición vertical

    window.clear();
    for (const auto &el : elements) window.draw(el);
    for (const auto &bar : bars) window.draw(bar);
    window.draw(result);
    window.draw(complexity);
    window.display();

    sf::sleep(sf::seconds(3));
}
int main(){  
    sf::RenderWindow window(sf::VideoMode(1000, 600), "Linear Search");
    linearSearchVisual(window, {2, 5, 8, 12, 16, 23, 38, 45, 56, 67, 78}, 23);
}