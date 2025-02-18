#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace std;

struct Node {
    int data;
    Node* next;
};

class Stack {
private:
    Node* topNode;

public:
    Stack() : topNode(nullptr) {}

    void push(int value) { // Complejidad O(1)
        Node* newNode = new Node();
        newNode->data = value;
        newNode->next = topNode;
        topNode = newNode;
    }

    string pop() { // Complejidad O(1)
        if (isEmpty()) {
            return "El stack esta vacio. No se puede realizar pop.";
        }
        Node* temp = topNode;
        topNode = topNode->next;
        delete temp;
        return "Elemento removido del stack.";
    }

    int top() { // Complejidad O(1)
        if (isEmpty()) {
            return -1; // Indicador de stack vacío
        }
        return topNode->data;
    }

    bool isEmpty() { // Complejidad O(1)
        return topNode == nullptr;
    }

    vector<int> getStackElements() { // Complejidad O(n)
        vector<int> elements;
        Node* current = topNode;
        while (current != nullptr) {
            elements.push_back(current->data);
            current = current->next;
        }
        return elements;
    }
};

void displayStack(sf::RenderWindow& window, sf::Font& font, vector<int> elements) {
    int x = 350, y = 450; // Posición inicial de los elementos
    int width = 100, height = 50;

    for (size_t i = 0; i < elements.size(); ++i) {
        sf::RectangleShape rect(sf::Vector2f(width, height));
        rect.setFillColor(sf::Color::Cyan);
        rect.setPosition(x, y);
        window.draw(rect);

        sf::Text text;
        text.setFont(font);
        text.setString(to_string(elements[i]));
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::Black);

        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        text.setPosition(x + width / 2.0f, y + height / 2.0f);
        window.draw(text);

        y -= height + 10; // Mover hacia arriba para el siguiente elemento
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Visualizacion del Stack");
    sf::Font font;
    if (!font.loadFromFile("PlaywriteGBS-VariableFont_wght.ttf")) {
        cout << "No se pudo cargar la fuente." << endl;
        return -1;
    }

    Stack stack;
    string message = "Presiona 'P' para push (agregar), 'O' para pop (remover).";

    // Complejidad de los métodos
    string complexities = "Complejidad:\nPush: O(1)\nPop: O(1)\nGetStackElements: O(n)\nTop: O(1)";
    int nextValue = 10;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Agregar elemento al presionar "P"
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P) {
                stack.push(nextValue);
                message = "Push: " + to_string(nextValue) + " agregado al stack.";
                nextValue += 10; // Incrementar valor para la próxima inserción
            }

            // Remover elemento al presionar "O"
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::O) {
                message = stack.pop();
            }
        }

        window.clear();

        // Mostrar el stack
        vector<int> elements = stack.getStackElements();
        displayStack(window, font, elements);

        // Mostrar mensaje dinámico
        sf::Text textMessage;
        textMessage.setFont(font);
        textMessage.setString(message);
        textMessage.setCharacterSize(20);
        textMessage.setFillColor(sf::Color::White);
        textMessage.setPosition(50, 50);
        window.draw(textMessage);

        // Mostrar complejidad
        sf::Text textComplexity;
        textComplexity.setFont(font);
        textComplexity.setString(complexities);
        textComplexity.setCharacterSize(18);
        textComplexity.setFillColor(sf::Color::Green);
        textComplexity.setPosition(50, 100);
        window.draw(textComplexity);

        window.display();
    }

    return 0;
}
