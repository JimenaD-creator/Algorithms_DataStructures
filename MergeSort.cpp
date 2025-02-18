#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

// Función para dibujar el gráfico
void drawGraph(sf::RenderWindow& window, const vector<int>& array, sf::Text& promptText, sf::Text& inputText, sf::Text& sortedText, sf::Text& complexityText) {
    window.clear();
    window.draw(promptText);
    window.draw(inputText);
    window.draw(sortedText);
    window.draw(complexityText);

    float barWidth = (window.getSize().x * 0.6f) / static_cast<float>(array.size());
    float offsetX = (window.getSize().x - barWidth * array.size()) / 2;

    for (size_t i = 0; i < array.size(); ++i) {
        sf::RectangleShape bar(sf::Vector2f(barWidth - 2, static_cast<float>(array[i] * 3)));
        bar.setPosition(offsetX + i * barWidth, window.getSize().y - bar.getSize().y - 50);
        bar.setFillColor(sf::Color::Cyan);
        window.draw(bar);
    }
    window.display();
}

// Función para combinar arreglos en Merge Sort
void merge(vector<int>& leftArray, vector<int>& rightArray, vector<int>& array, sf::RenderWindow& window, sf::Text& promptText, sf::Text& inputText, sf::Text& sortedText, sf::Text& complexityText) {
    int lefsize = leftArray.size();
    int rightSize = rightArray.size();
    int i = 0, l = 0, r = 0;

    while (l < lefsize && r < rightSize) {
        if (leftArray[l] < rightArray[r]) {
            array[i] = leftArray[l];
            i++;
            l++;
        } else {
            array[i] = rightArray[r];
            i++;
            r++;
        }

        // Dibujar la gráfica después de cada cambio
        drawGraph(window, array, promptText, inputText, sortedText, complexityText);
        sf::sleep(sf::milliseconds(300));
    }

    while (l < lefsize) {
        array[i] = leftArray[l];
        i++;
        l++;
        drawGraph(window, array, promptText, inputText, sortedText, complexityText);
        sf::sleep(sf::milliseconds(300));
    }

    while (r < rightSize) {
        array[i] = rightArray[r];
        i++;
        r++;
        drawGraph(window, array, promptText, inputText, sortedText, complexityText);
        sf::sleep(sf::milliseconds(300));
    }
}

// Merge Sort con visualización
void mergeSort(vector<int>& array, sf::RenderWindow& window, sf::Text& promptText, sf::Text& inputText, sf::Text& sortedText, sf::Text& complexityText) {
    int n = array.size();
    if (n <= 1) return;

    int center = n / 2;
    vector<int> leftArray(center);
    vector<int> rightArray(n - center);

    for (int i = 0; i < n; i++) {
        if (i < center) leftArray[i] = array[i];
        else rightArray[i - center] = array[i];
    }

    mergeSort(leftArray, window, promptText, inputText, sortedText, complexityText);
    mergeSort(rightArray, window, promptText, inputText, sortedText, complexityText);

    merge(leftArray, rightArray, array, window, promptText, inputText, sortedText, complexityText);
}

// Función principal para la interfaz gráfica
void openSortingWindow() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Merge Sort Visualizado");

    sf::Font font;
    if (!font.loadFromFile("PlaywriteGBS-VariableFont_wght.ttf")) {
        cerr << "Error al cargar la fuente" << endl;
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
    vector<int> numbers;

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
                stringstream ss(input.toAnsiString());
                string number;
                numbers.clear();
                while (getline(ss, number, ',')) {
                    try {
                        numbers.push_back(stoi(number));
                    } catch (...) {
                        sortedText.setString("Error: Entrada no valida.");
                        drawGraph(window, numbers, promptText, inputText, sortedText, complexityText);
                        sf::sleep(sf::seconds(2));
                        sortedText.setString("");
                        break;
                    }
                }

                // Ejecutar Merge Sort con visualización
                mergeSort(numbers, window, promptText, inputText, sortedText, complexityText);

                // Mostrar números ordenados
                ostringstream oss;
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
