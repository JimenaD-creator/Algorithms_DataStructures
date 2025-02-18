#include "Prácticas.h"
#include <cstdlib>
#include <vector>
#include <thread>
#include <chrono>
#include <iostream>

using namespace std;
using namespace sf;

Prácticas::Prácticas(float width, float height){
    if(!font.loadFromFile("PlaywriteGBS-VariableFont_wght.ttf")){
       std::cerr<< "Error loading font\n";
    }else{
        std::cout << "Font loaded successfully\n";
    }

    // Título "Algoritmos de búsqueda"
    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::Cyan);
    menu[0].setString("Algoritmos de busqueda");
    menu[0].setCharacterSize(40);  // Aumenta el tamaño de la fuente
    menu[0].setPosition(sf::Vector2f(width / 2 - 250, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));

    // Elementos de búsqueda
    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::White);
    menu[1].setString("Binary Search");
    menu[1].setPosition(sf::Vector2f(width / 2 - 100, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));

    menu[2].setFont(font);
    menu[2].setFillColor(sf::Color::Blue);
    menu[2].setString("Funcionamiento");
    menu[2].setPosition(sf::Vector2f(width / 2 - 50, height / (MAX_NUMBER_OF_ITEMS + 1) * 3));

    menu[3].setFont(font);
    menu[3].setFillColor(sf::Color::White);
    menu[3].setString("Linear Search");
    menu[3].setPosition(sf::Vector2f(width / 2 - 100, height / (MAX_NUMBER_OF_ITEMS + 1) * 4));

    // Título "Algoritmos de Ordenamiento"
    menu[4].setFont(font);
    menu[4].setFillColor(sf::Color::Cyan);
    menu[4].setString("Algoritmos de Ordenamiento");
    menu[4].setCharacterSize(40);  // Aumenta el tamaño de la fuente
    menu[4].setPosition(sf::Vector2f(width / 2 - 250, height / (MAX_NUMBER_OF_ITEMS + 1) * 5));

    // Elementos de ordenamiento
    menu[5].setFont(font);
    menu[5].setFillColor(sf::Color::White);
    menu[5].setString("Bubble Sort");
    menu[5].setPosition(sf::Vector2f(width / 2 - 100, height / (MAX_NUMBER_OF_ITEMS + 1) * 6));

    menu[6].setFont(font);
    menu[6].setFillColor(sf::Color::White);
    menu[6].setString("Selection Sort");
    menu[6].setPosition(sf::Vector2f(width / 2 - 100, height / (MAX_NUMBER_OF_ITEMS + 1) * 7));

    menu[7].setFont(font);
    menu[7].setFillColor(sf::Color::White);
    menu[7].setString("Insertion Sort");
    menu[7].setPosition(sf::Vector2f(width / 2 - 100, height / (MAX_NUMBER_OF_ITEMS + 1) * 8));

    menu[8].setFont(font);
    menu[8].setFillColor(sf::Color::White);
    menu[8].setString("Quick Sort");
    menu[8].setPosition(sf::Vector2f(width / 2 - 100, height / (MAX_NUMBER_OF_ITEMS + 1) * 9));

    menu[9].setFont(font);
    menu[9].setFillColor(sf::Color::White);
    menu[9].setString("Merge Sort");
    menu[9].setPosition(sf::Vector2f(width / 2 - 100, height / (MAX_NUMBER_OF_ITEMS + 1) * 10));

    menu[10].setFont(font);
    menu[10].setFillColor(sf::Color::Cyan);
    menu[10].setString("Estructuras de datos lineales");
    menu[10].setCharacterSize(40);
    menu[10].setPosition(sf::Vector2f(width / 2 - 250, height / (MAX_NUMBER_OF_ITEMS + 1) * 11));

    menu[11].setFont(font);
    menu[11].setFillColor(sf::Color::White);
    menu[11].setString("Linked List");
    menu[11].setPosition(sf::Vector2f(width / 2 - 100, height / (MAX_NUMBER_OF_ITEMS + 1) * 12));

    menu[12].setFont(font);
    menu[12].setFillColor(sf::Color::White);
    menu[12].setString("Double Linked List");
    menu[12].setPosition(sf::Vector2f(width / 2 - 100, height / (MAX_NUMBER_OF_ITEMS + 1) * 13));

    menu[13].setFont(font);
    menu[13].setFillColor(sf::Color::White);
    menu[13].setString("Queue");
    menu[13].setPosition(sf::Vector2f(width / 2 - 100, height / (MAX_NUMBER_OF_ITEMS + 1) * 14));

    menu[14].setFont(font);
    menu[14].setFillColor(sf::Color::White);
    menu[14].setString("Stack");
    menu[14].setPosition(sf::Vector2f(width / 2 - 100, height / (MAX_NUMBER_OF_ITEMS + 1) * 15));

    menu[15].setFont(font);
    menu[15].setFillColor(sf::Color::Cyan);
    menu[15].setString("Estructuras de datos no lineales");
    menu[15].setCharacterSize(40);
    menu[15].setPosition(sf::Vector2f(width / 2 - 250, height / (MAX_NUMBER_OF_ITEMS + 1) * 16));

    menu[16].setFont(font);
    menu[16].setFillColor(sf::Color::White);
    menu[16].setString("BST - Binary Search Tree");
    menu[16].setPosition(sf::Vector2f(width / 2 - 100, height / (MAX_NUMBER_OF_ITEMS + 1) * 17));

    menu[17].setFont(font);
    menu[17].setFillColor(sf::Color::White);
    menu[17].setString("AVL");
    menu[17].setPosition(sf::Vector2f(width / 2 - 100, height / (MAX_NUMBER_OF_ITEMS + 1) * 18));

    menu[18].setFont(font);
    menu[18].setFillColor(sf::Color::Cyan);
    menu[18].setString("Grafos");
    menu[18].setCharacterSize(40);
    menu[18].setPosition(sf::Vector2f(width / 2 - 150, height / (MAX_NUMBER_OF_ITEMS + 1) * 19));

    menu[19].setFont(font);
    menu[19].setFillColor(sf::Color::White);
    menu[19].setString("BFS/DFS");
    menu[19].setPosition(sf::Vector2f(width / 2 - 100, height / (MAX_NUMBER_OF_ITEMS + 1) * 20));

    menu[20].setFont(font);
    menu[20].setFillColor(sf::Color::White);
    menu[20].setString("Dijkstra");
    menu[20].setPosition(sf::Vector2f(width / 2 - 100, height / (MAX_NUMBER_OF_ITEMS + 1) * 21));



    selectedItemIndex = 0; 
}

Prácticas::~Prácticas() {}


void Prácticas::MoveUp() {
    if(selectedItemIndex - 1 >= 0) {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        menu[selectedItemIndex].setFillColor(sf::Color::Magenta);
    }
}

void Prácticas::MoveDown() {
    if(selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS) {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menu[selectedItemIndex].setFillColor(sf::Color::Magenta);
    }
}
// Función para realizar búsqueda binaria y visualización

// Búsqueda lineal visual con SFML

void Prácticas::openNewWindow(const std::string &message) {
    sf::RenderWindow newWindow(sf::VideoMode(400, 300), "Nueva Ventana");

    sf::Font font;
    if (!font.loadFromFile("PlaywriteGBS-VariableFont_wght.ttf")) {
        std::cerr << "Error al cargar la fuente" << std::endl;
        return;
    }

    sf::Text text(message, font, 24);
    text.setFillColor(sf::Color::White);
    text.setPosition(50, 100);

    while (newWindow.isOpen()) {
        sf::Event event;
        while (newWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                newWindow.close();
            }
        }

        newWindow.clear(sf::Color::Black);
        newWindow.draw(text);
        newWindow.display();
    }
}
void Prácticas::draws(sf::RenderWindow &window) {
    for(int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
        window.draw(menu[i]);
    }
}

