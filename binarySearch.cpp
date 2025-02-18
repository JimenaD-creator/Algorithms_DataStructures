#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <thread>
#include <chrono>
using namespace std;

void binarySearchVisual(sf::RenderWindow &window, const std::vector<int> &vec, int target) {
    int low = 0, high = vec.size() - 1;
    bool found = false;
    sf::Font font;

    if (!font.loadFromFile("PlaywriteGBS-VariableFont_wght.ttf")) {
        std::cerr << "Error al cargar la fuente\n";
        return;
    }

    // **Calcular el espaciado dinámico** basado en el tamaño de la ventana y del vector
    float elementWidth = window.getSize().x / (vec.size() + 1); // Espaciado horizontal
    float barMaxHeight = 300;  // Altura máxima de las barras

    std::vector<sf::Text> elements(vec.size());
    std::vector<sf::RectangleShape> bars(vec.size());

    // Posicionar los elementos de forma dinámica
    for (size_t i = 0; i < vec.size(); ++i) {
        // Configurar cada número
        elements[i].setFont(font);
        elements[i].setString(std::to_string(vec[i]));
        elements[i].setCharacterSize(20);  // Tamaño de la fuente reducido
        elements[i].setFillColor(sf::Color::White);
        elements[i].setPosition(elementWidth * i + 10, 70); // Ajusta la posición horizontal y vertical

        // Configurar cada barra
        bars[i].setSize(sf::Vector2f(30, vec[i] * barMaxHeight / 163));  // Normalizar altura
        bars[i].setFillColor(sf::Color::White);
        bars[i].setPosition(elementWidth * i + 10, window.getSize().y - bars[i].getSize().y - 50);
    }

    sf::Text complexity("Complejidad: O(log n)", font, 20);
    complexity.setFillColor(sf::Color::Yellow);
    complexity.setPosition(50, 10);  // Posición del texto de complejidad

    while (low <= high && window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }
        }

        int mid = low + (high - low) / 2;

        // Restablecer colores
        for (auto &el : elements) el.setFillColor(sf::Color::White);
        for (auto &bar : bars) bar.setFillColor(sf::Color::White);

        // Colorear los elementos importantes
        elements[low].setFillColor(sf::Color::Blue);
        elements[mid].setFillColor(sf::Color::Green);
        elements[high].setFillColor(sf::Color::Red);

        bars[low].setFillColor(sf::Color::Blue);
        bars[mid].setFillColor(sf::Color::Green);
        bars[high].setFillColor(sf::Color::Red);

        // Dibujar todo en la ventana
        window.clear();
        for (const auto &el : elements) window.draw(el);
        for (const auto &bar : bars) window.draw(bar);
        window.draw(complexity);
        window.display();

        sf::sleep(sf::seconds(1));

        // Búsqueda binaria
        if (vec[mid] == target) {
            elements[mid].setFillColor(sf::Color::Yellow);
            bars[mid].setFillColor(sf::Color::Yellow);
            found = true;
            break;
        } else if (vec[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    // Mensaje de resultado
    sf::Text result(found ? "Elemento encontrado" : "Elemento no encontrado", font, 30);
    result.setFillColor(found ? sf::Color::Green : sf::Color::Red);
    result.setPosition(50, 300);

    // Dibujar el resultado final
    window.clear();
    for (const auto &el : elements) window.draw(el);
    for (const auto &bar : bars) window.draw(bar);
    window.draw(result);
    window.draw(complexity);
    window.display();

    // Esperar para que el usuario vea el resultado final
    sf::sleep(sf::seconds(3));
}
int main(){
    sf::RenderWindow window(sf::VideoMode(800, 600), "Binary Search");
    std::vector<int> data = {2, 5, 8, 12, 16, 23, 38, 45, 56, 67, 78, 87, 90, 110, 145, 150, 163};
    binarySearchVisual(window, data, 78);

}