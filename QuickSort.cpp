#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>

// Función para dibujar el gráfico
void drawGraph(sf::RenderWindow& window, const std::vector<int>& vec, sf::Text& promptText, sf::Text& inputText, sf::Text& sortedText, sf::Text& complexityText) {
    window.clear();
    window.draw(promptText);
    window.draw(inputText);
    window.draw(sortedText);
    window.draw(complexityText);

    float barWidth = (window.getSize().x * 0.6f) / static_cast<float>(vec.size());
    float offsetX = (window.getSize().x - barWidth * vec.size()) / 2;

    for (size_t i = 0; i < vec.size(); ++i) {
        sf::RectangleShape bar(sf::Vector2f(barWidth - 2, static_cast<float>(vec[i] * 3)));
        bar.setPosition(offsetX + i * barWidth, window.getSize().y - bar.getSize().y - 50);
        bar.setFillColor(sf::Color::Cyan);
        window.draw(bar);
    }
    window.display();
}

// Algoritmo QuickSort con animación
int partition(std::vector<int>& array, int min, int max, sf::RenderWindow& window, sf::Text& promptText, sf::Text& inputText, sf::Text& sortedText, sf::Text& complexityText) {
    int pivot = array[min];
    int i = min + 1;

    // Dibujar la gráfica inicial, resaltar el pivote
    window.clear();
    float barWidth = (window.getSize().x * 0.6f) / static_cast<float>(array.size());
    float offsetX = (window.getSize().x - barWidth * array.size()) / 2;

    for (size_t k = 0; k < array.size(); ++k) {
        sf::RectangleShape bar(sf::Vector2f(barWidth - 2, static_cast<float>(array[k] * 3)));
        bar.setPosition(offsetX + k * barWidth, window.getSize().y - bar.getSize().y - 50);

        if (k == min) {
            bar.setFillColor(sf::Color::Yellow); // Resaltar el pivote
        } else {
            bar.setFillColor(sf::Color::Magenta); // Color estándar
        }
        window.draw(bar);
    }

    // Dibujar textos
    window.draw(promptText);
    window.draw(inputText);
    window.draw(sortedText);
    window.draw(complexityText);
    window.display();
    sf::sleep(sf::milliseconds(500));

    // Proceso de partición
    for (int j = i; j <= max; ++j) {
        if (array[j] < pivot) {
            std::swap(array[i], array[j]);
            i++;

            // Actualización visual después del intercambio
            window.clear();

            for (size_t k = 0; k < array.size(); ++k) {
                sf::RectangleShape bar(sf::Vector2f(barWidth - 2, static_cast<float>(array[k] * 3)));
                bar.setPosition(offsetX + k * barWidth, window.getSize().y - bar.getSize().y - 50);

                if (k == min) {
                    bar.setFillColor(sf::Color::Yellow); // Resaltar el pivote
                } else if (k == i - 1) {
                    bar.setFillColor(sf::Color::Red); // Intercambio realizado
                } else {
                    bar.setFillColor(sf::Color::Magenta); // Color estándar
                }
                window.draw(bar);
            }

            window.draw(promptText);
            window.draw(inputText);
            window.draw(sortedText);
            window.draw(complexityText);
            window.display();
            sf::sleep(sf::milliseconds(300));
        }
    }

    // Intercambio final para colocar el pivote en su posición
    std::swap(array[min], array[i - 1]);

    // Dibujar la gráfica después del intercambio final
    window.clear();
    for (size_t k = 0; k < array.size(); ++k) {
        sf::RectangleShape bar(sf::Vector2f(barWidth - 2, static_cast<float>(array[k] * 3)));
        bar.setPosition(offsetX + k * barWidth, window.getSize().y - bar.getSize().y - 50);

        if (k == i - 1) {
            bar.setFillColor(sf::Color::Yellow); // Resaltar el pivote en su posición final
        } else {
            bar.setFillColor(sf::Color::Magenta); // Color estándar
        }
        window.draw(bar);
    }

    window.draw(promptText);
    window.draw(inputText);
    window.draw(sortedText);
    window.draw(complexityText);
    window.display();
    sf::sleep(sf::milliseconds(500));

    return i - 1;
}

void quickSort(std::vector<int>& vec, int min, int max, sf::RenderWindow& window, sf::Text& promptText, sf::Text& inputText, sf::Text& sortedText, sf::Text& complexityText) {
    if (min < max) {
        int pivot = partition(vec, min, max, window, promptText, inputText, sortedText, complexityText);

        // Recursividad visual
        quickSort(vec, min, pivot - 1, window, promptText, inputText, sortedText, complexityText);
        quickSort(vec, pivot + 1, max, window, promptText, inputText, sortedText, complexityText);
    }
}

// Función principal para manejar la ventana gráfica
void openSortingWindow() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "QuickSort Visualizado");

    sf::Font font;
    if (!font.loadFromFile("PlaywriteGBS-VariableFont_wght.ttf")) {
        std::cerr << "Error al cargar la fuente" << std::endl;
        return;
    }

    sf::Text promptText("Ingrese numeros separados por comas y presione Enter:", font, 20);
    promptText.setFillColor(sf::Color::White);
    promptText.setPosition(10, 20);

    sf::Text inputText("", font, 20);
    inputText.setFillColor(sf::Color::White);
    inputText.setPosition(10, 60);

    sf::Text sortedText("", font, 20);
    sortedText.setFillColor(sf::Color::Green);
    sortedText.setPosition(10, 100);

    sf::Text complexityText("", font, 20);
    complexityText.setFillColor(sf::Color::Yellow);
    complexityText.setPosition(10, 140);

    sf::String input;
    std::vector<int> numbers;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == 8 && !input.isEmpty()) { // Backspace
                    input.erase(input.getSize() - 1);
                } else if (event.text.unicode < 128) { // Solo caracteres válidos
                    input += static_cast<char>(event.text.unicode);
                }
                inputText.setString(input);
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                // Procesar la entrada
                std::stringstream ss(input.toAnsiString());
                std::string number;
                numbers.clear();
                while (std::getline(ss, number, ',')) {
                    try {
                        numbers.push_back(std::stoi(number));
                    } catch (...) {
                        sortedText.setString("Error: Entrada no valida.");
                        drawGraph(window, numbers, promptText, inputText, sortedText, complexityText);
                        sf::sleep(sf::seconds(2));
                        sortedText.setString("");
                        break;
                    }
                }

                // Ejecutar QuickSort con visualización
                quickSort(numbers, 0, numbers.size() - 1, window, promptText, inputText, sortedText, complexityText);

                // Mostrar números ordenados
                std::ostringstream oss;
                for (size_t i = 0; i < numbers.size(); ++i) {
                    oss << numbers[i] << (i < numbers.size() - 1 ? ", " : "");
                }
                sortedText.setString("Ordenados: " + oss.str());
                complexityText.setString("Complejidad: O(n log n)");
                drawGraph(window, numbers, promptText, inputText, sortedText, complexityText);
            }
        }

        // Dibujar la ventana
        drawGraph(window, numbers, promptText, inputText, sortedText, complexityText);
    }
}

int main() {
    openSortingWindow();
    return 0;
}
