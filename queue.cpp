#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <queue>

using namespace std;

class Queue {
private:
    queue<int> queueData; 
    int capacity;

public:
    Queue(int maxCapacity) : capacity(maxCapacity) {}

    bool isFull() {
        return queueData.size() >= capacity;
    }

    bool isEmpty() {
        return queueData.empty();
    }

    string enqueue(int value) {
        if (isFull()) {
            return "La cola esta llena. No se puede agregar el turno: " + to_string(value);
        }
        queueData.push(value);
        return "Turno " + to_string(value) + " agregado a la cola.";
    }

    string dequeue() {
        if (isEmpty()) {
            return "La cola esta vacia. No hay turnos por atender.";
        }
        int frontTurn = queueData.front();
        queueData.pop();
        return "Atendiendo turno " + to_string(frontTurn);
    }

    vector<int> getQueueElements() {
        vector<int> elements;
        queue<int> tempQueue = queueData;

        while (!tempQueue.empty()) {
            elements.push_back(tempQueue.front());
            tempQueue.pop();
        }

        return elements;
    }
};

void displayQueue(sf::RenderWindow& window, sf::Font& font, vector<int> elements) {
    int x = 50, y = 250;
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

        x += width + 20; // Separación entre los elementos
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Sistema de Turnos con Colas");
    sf::Font font;
    if (!font.loadFromFile("PlaywriteGBS-VariableFont_wght.ttf")) {
        cout << "No se pudo cargar la fuente." << endl;
        return -1;
    }

    Queue queue(10); // Cola con capacidad para 5 turnos
    int turno = 1;

    string message = "Presiona 'A' para agregar turno, 'S' para atender.";

    // Complejidad de los métodos
    string complexities = "Complejidad:\nEnqueue: O(1)\nDequeue: O(1)\nGetQueueElements: O(n)";

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Agregar turno al presionar "A"
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A) {
                message = queue.enqueue(turno++);
            }

            // Atender turno al presionar "S"
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S) {
                message = queue.dequeue();
            }
        }

        window.clear();

        // Mostrar el estado de la cola
        vector<int> elements = queue.getQueueElements();
        displayQueue(window, font, elements);

        // Mostrar mensaje
        sf::Text text;
        text.setFont(font);
        text.setString(message);
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::White);
        text.setPosition(50, 50);
        window.draw(text);

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
