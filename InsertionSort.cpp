#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <thread>

// Función para dibujar el gráfico
void drawGraph(sf::RenderWindow& window, const std::vector<int>& vec) {
    float barWidth = (window.getSize().x * 0.6f) / static_cast<float>(vec.size()); // Ajustar para ocupar el 60% del ancho de la ventana
    float offsetX = (window.getSize().x - barWidth * vec.size()) / 2; // Calcular desplazamiento para centrar la gráfica

    for (size_t i = 0; i < vec.size(); ++i) {
        sf::RectangleShape bar(sf::Vector2f(barWidth - 2, static_cast<float>(vec[i] * 3))); // Escalar altura
        bar.setPosition(offsetX + i * barWidth, window.getSize().y - bar.getSize().y - 50); // Centrar y ajustar altura desde el fondo
        bar.setFillColor(sf::Color::Cyan);
        window.draw(bar);
    }
}

// Función para el algoritmo de ordenamiento Insertion Sort
void insertionSort(std::vector<int>& vec, sf::RenderWindow& window, sf::Text& complexityText, sf::Text& promptText, sf::Text& inputText, sf::Text& resultText) {
    size_t n = vec.size();
    complexityText.setString("Complejidad de Insertion Sort: O(n^2)");

    for (size_t i = 1; i < n; ++i) {
        int key = vec[i];
        int j = i - 1;

        // Dibujar inicial antes de empezar comparaciones
        window.clear();

        float barWidth = (window.getSize().x * 0.6f) / static_cast<float>(vec.size());
        float offsetX = (window.getSize().x - barWidth * vec.size()) / 2;

        for (size_t k = 0; k < vec.size(); ++k) {
            sf::RectangleShape bar(sf::Vector2f(barWidth - 2, static_cast<float>(vec[k] * 3)));
            bar.setPosition(offsetX + k * barWidth, window.getSize().y - bar.getSize().y - 50);

            if (k == i) {
                bar.setFillColor(sf::Color::Yellow); // Clave actual
            } else {
                bar.setFillColor(sf::Color::Magenta); // Color estándar
            }
            window.draw(bar);
        }

        // Dibujar textos
        window.draw(promptText);
        window.draw(inputText);
        window.draw(resultText);
        window.draw(complexityText);
        window.display();

        sf::sleep(sf::milliseconds(500));

        // Comparaciones y movimientos
        while (j >= 0 && vec[j] > key) {
            vec[j + 1] = vec[j];

            // Dibujar estado actual
            window.clear();

            for (size_t k = 0; k < vec.size(); ++k) {
                sf::RectangleShape bar(sf::Vector2f(barWidth - 2, static_cast<float>(vec[k] * 3)));
                bar.setPosition(offsetX + k * barWidth, window.getSize().y - bar.getSize().y - 50);

                if (k == j) {
                    bar.setFillColor(sf::Color::Cyan); // Comparación actual
                } else if (k == j + 1) {
                    bar.setFillColor(sf::Color::Red); // Movimiento actual
                } else if (k == i) {
                    bar.setFillColor(sf::Color::Yellow); // Clave actual
                } else {
                    bar.setFillColor(sf::Color::Magenta); // Color estándar
                }
                window.draw(bar);
            }

            // Dibujar textos
            window.draw(promptText);
            window.draw(inputText);
            window.draw(resultText);
            window.draw(complexityText);
            window.display();

            sf::sleep(sf::milliseconds(300));
            --j;
        }
        vec[j + 1] = key;

        // Actualizar texto con el estado actual de los números
        std::string resultTextStr = "Numeros en proceso: ";
        for (const auto& num : vec) {
            resultTextStr += std::to_string(num) + " ";
        }
        resultText.setString(resultTextStr);

        // Dibujar estado después de insertar la clave
        window.clear();

        for (size_t k = 0; k < vec.size(); ++k) {
            sf::RectangleShape bar(sf::Vector2f(barWidth - 2, static_cast<float>(vec[k] * 3)));
            bar.setPosition(offsetX + k * barWidth, window.getSize().y - bar.getSize().y - 50);

            if (k == j + 1) {
                bar.setFillColor(sf::Color::Green); // Clave insertada
            } else {
                bar.setFillColor(sf::Color::Magenta); // Color estándar
            }
            window.draw(bar);
        }

        // Dibujar textos
        window.draw(promptText);
        window.draw(inputText);
        window.draw(resultText);
        window.draw(complexityText);
        window.display();

        sf::sleep(sf::milliseconds(500));
    }

    // Actualizar texto con el resultado final de los números ordenados
    std::string resultTextStr = "Numeros ordenados: ";
    for (const auto& num : vec) {
        resultTextStr += std::to_string(num) + " ";
    }
    resultText.setString(resultTextStr);

    // Dibujar el último estado de la ventana para mostrar el resultado final
    window.clear();
    window.draw(promptText);
    window.draw(inputText);
    window.draw(resultText);
    window.draw(complexityText);
    drawGraph(window, vec);
    window.display();
}

// Función principal para abrir la ventana de entrada y ordenamiento
void openSortingWindow(sf::RenderWindow& mainWindow) {
    sf::RenderWindow sortWindow(sf::VideoMode(800, 500), "Ordenar Numeros");

    sf::Font font;
    if (!font.loadFromFile("PlaywriteGBS-VariableFont_wght.ttf")) {
        std::cerr << "Error al cargar la fuente" << std::endl;
        return;
    }

    sf::Text promptText("Ingrese numeros separados por comas:", font, 20);
    promptText.setFillColor(sf::Color::White);
    promptText.setPosition(10, 20);

    sf::Text inputText("", font, 20);
    inputText.setFillColor(sf::Color::White);
    inputText.setPosition(10, 60);

    sf::Text resultText("", font, 20);
    resultText.setFillColor(sf::Color::White);
    resultText.setPosition(10, 100);

    sf::Text complexityText("", font, 20);
    complexityText.setFillColor(sf::Color::Yellow);
    complexityText.setPosition(10, 150);

    sf::String input;
    std::vector<int> numeros;

    while (sortWindow.isOpen()) {
        sf::Event event;
        while (sortWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                sortWindow.close();
            }
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == 8 && !input.isEmpty()) { // Manejo de backspace
                    input.erase(input.getSize() - 1);
                } else if (event.text.unicode < 128) { // Agregar carácter si es válido
                    input += static_cast<char>(event.text.unicode);
                }
                inputText.setString(input);
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                std::stringstream ss(input.toAnsiString());
                std::string number;
                numeros.clear();
                while (std::getline(ss, number, ',')) {
                    try {
                        numeros.push_back(std::stoi(number));
                    } catch (...) {
                        resultText.setString("Error: Numero no valido");
                        sortWindow.clear();
                        sortWindow.draw(promptText);
                        sortWindow.draw(inputText);
                        sortWindow.draw(resultText);
                        sortWindow.display();
                        sf::sleep(sf::seconds(2));
                        resultText.setString("");
                        break;
                    }
                }

                // Ejecutar el algoritmo de ordenamiento y mostrar el gráfico dinámico
                insertionSort(numeros, sortWindow, complexityText, promptText, inputText, resultText);
            }
        }

        // Redibujar la ventana
        sortWindow.clear();
        sortWindow.draw(promptText);   // Instrucción visible todo el tiempo
        sortWindow.draw(inputText);    // Entrada visible todo el tiempo
        sortWindow.draw(resultText);   // Resultado visible todo el tiempo
        sortWindow.draw(complexityText); // Complejidad visible todo el tiempo
        drawGraph(sortWindow, numeros);
        sortWindow.display();
    }
}

int main() {
    sf::RenderWindow mainWindow(sf::VideoMode(800, 600), "Visualización de Ordenamiento");

    // Crear el texto inicial de bienvenida
    sf::Font font;
    if (!font.loadFromFile("PlaywriteGBS-VariableFont_wght.ttf")) {
        std::cerr << "Error al cargar la fuente" << std::endl;
        return -1;
    }
    while (mainWindow.isOpen()) {
        sf::Event event;
        while (mainWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                mainWindow.close();
            }
            mainWindow.close();
            openSortingWindow(mainWindow);
            
        }

        // Dibujar la pantalla de bienvenida
        mainWindow.clear();
        mainWindow.display();
    }

    return 0;
} 
