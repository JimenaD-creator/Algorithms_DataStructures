#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev; // Añadido para soporte de doble enlace
};

class LinkedList {
private:
    Node* head;
    Node* tail; // Puntero al último nodo

public:
    LinkedList() : head(nullptr), tail(nullptr) {}

    void addNode(int value) {
        Node* newNode = new Node();
        newNode->data = value;
        newNode->next = nullptr;
        newNode->prev = nullptr;

        if (head == nullptr) {
            head = tail = newNode; // Si la lista está vacía, el nuevo nodo es tanto la cabeza como la cola
        } else {
            tail->next = newNode; // Agregar después del último nodo
            newNode->prev = tail; // El nuevo nodo apunta hacia el nodo anterior
            tail = newNode; // El nuevo nodo se convierte en la cola
        }
    }

    void removeNode(int value, string& resultMessage) {
        if (head == nullptr) {
            resultMessage = "La lista está vacía.";
            return;
        }

        Node* temp = head;

        while (temp != nullptr && temp->data != value) {
            temp = temp->next;
        }

        if (temp == nullptr) {
            resultMessage = "Nodo con valor " + to_string(value) + " no encontrado.";
            return;
        }

        if (temp->prev != nullptr) {
            temp->prev->next = temp->next;
        } else {
            head = temp->next; // Si el nodo a eliminar es el primero
        }

        if (temp->next != nullptr) {
            temp->next->prev = temp->prev;
        } else {
            tail = temp->prev; // Si el nodo a eliminar es el último
        }

        delete temp;
        resultMessage = "Nodo con valor " + to_string(value) + " eliminado.";
    }

    Node* searchNode(int value) {
        Node* temp = head;
        while (temp != nullptr) {
            if (temp->data == value) {
                return temp;
            }
            temp = temp->next;
        }
        return nullptr;
    }

    void showList(sf::RenderWindow& window, sf::Font& font) {
        Node* temp = head;
        int x = 50, y = 250;

        while (temp != nullptr) {
            // Dibujar nodo
            sf::CircleShape node(30);
            node.setFillColor(sf::Color::Cyan); // Color de los nodos
            node.setPosition(x, y);
            window.draw(node);

            // Mostrar valor del nodo
            sf::Text text;
            text.setFont(font);
            text.setString(to_string(temp->data));
            text.setCharacterSize(24);
            text.setFillColor(sf::Color::Black); // Texto blanco

            // Centrar texto en el nodo
            sf::FloatRect textRect = text.getLocalBounds();
            text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
            text.setPosition(x + 30, y + 30);
            window.draw(text);

            // Dibujar flechas para los enlaces dobles (prev y next)
            if (temp->next != nullptr) {
                sf::Vertex line[] = {
                    sf::Vertex(sf::Vector2f(x + 60, y + 30), sf::Color::White),
                    sf::Vertex(sf::Vector2f(x + 130, y + 30), sf::Color::White)
                };
                window.draw(line, 2, sf::Lines);

                sf::ConvexShape arrow1;
                arrow1.setPointCount(3);
                arrow1.setFillColor(sf::Color::White);
                arrow1.setPoint(0, sf::Vector2f(x + 130, y + 25));
                arrow1.setPoint(1, sf::Vector2f(x + 120, y + 30));
                arrow1.setPoint(2, sf::Vector2f(x + 130, y + 35));
                window.draw(arrow1);
            }

            if (temp->prev != nullptr) {
                sf::Vertex line[] = {
                    sf::Vertex(sf::Vector2f(x + 0, y + 30), sf::Color::White),
                    sf::Vertex(sf::Vector2f(x - 70, y + 30), sf::Color::White)
                };
                window.draw(line, 2, sf::Lines);

                sf::ConvexShape arrow2;
                arrow2.setPointCount(3);
                arrow2.setFillColor(sf::Color::White);
                arrow2.setPoint(0, sf::Vector2f(x - 70, y + 25));
                arrow2.setPoint(1, sf::Vector2f(x - 60, y + 30));
                arrow2.setPoint(2, sf::Vector2f(x - 70, y + 35));
                window.draw(arrow2);
            }

            temp = temp->next;
            x += 170; // Desplazar los nodos a la derecha
        }
    }

    string getComplexities() {
        return "Complejidad de los metodos:\n"
               "Agregar nodo: O(1)\n"
               "Eliminar nodo: O(n)\n"
               "Buscar nodo: O(n)";
    }
};

void displayUserInput(sf::RenderWindow& window, sf::Font& font, const string& userInput, const string& operationMessage) {
    sf::Text inputText;
    inputText.setFont(font);
    inputText.setString(operationMessage + " " + userInput);
    inputText.setCharacterSize(24);
    inputText.setFillColor(sf::Color::Yellow);
    inputText.setPosition(50, 50);
    window.draw(inputText);
}

void displayComplexities(sf::RenderWindow& window, sf::Font& font, const string& complexities) {
    sf::Text complexityText;
    complexityText.setFont(font);
    complexityText.setString(complexities);
    complexityText.setCharacterSize(18);
    complexityText.setFillColor(sf::Color::White);
    complexityText.setPosition(50, 400); 
    window.draw(complexityText);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 600), "Lista Enlazada Doble");
    sf::Font font;
    if (!font.loadFromFile("PlaywriteGBS-VariableFont_wght.ttf")) {
        cout << "No se pudo cargar la fuente." << endl;
        return -1;
    }

    LinkedList linkedlist;
    string userInput = "";
    string operationMessage = "Presione A para agregar, D para eliminar, S para buscar: ";
    string resultMessage = "";
    bool isAdding = false, isDeleting = false, isSearching = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode < 128) {
                    char enteredChar = static_cast<char>(event.text.unicode);
                    if (isdigit(enteredChar)) {
                        userInput += enteredChar;
                    } else if (enteredChar == '\b' && !userInput.empty()) {
                        userInput.pop_back();
                    }
                }
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter && !userInput.empty()) {
                    int value = stoi(userInput);
                    if (isAdding) {
                        linkedlist.addNode(value);
                        resultMessage = "Nodo con valor " + userInput + " agregado.";
                    } else if (isDeleting) {
                        linkedlist.removeNode(value, resultMessage);
                    } else if (isSearching) {
                        Node* foundNode = linkedlist.searchNode(value);
                        resultMessage = foundNode ? "Nodo con valor " + userInput + " encontrado."
                                                  : "Nodo con valor " + userInput + " no encontrado.";
                    }
                    isAdding = isDeleting = isSearching = false;
                    operationMessage = "Presione A para agregar, D para eliminar, S para buscar: ";
                    userInput.clear();
                }

                if (event.key.code == sf::Keyboard::A) {
                    isAdding = true;
                    isDeleting = isSearching = false;
                    operationMessage = "Ingrese un numero para agregar: ";
                } else if (event.key.code == sf::Keyboard::D) {
                    isDeleting = true;
                    isAdding = isSearching = false;
                    operationMessage = "Ingrese un numero para eliminar: ";
                } else if (event.key.code == sf::Keyboard::S) {
                    isSearching = true;
                    isAdding = isDeleting = false;
                    operationMessage = "Ingrese un numero para buscar: ";
                }
            }
        }

        window.clear();

        sf::Text resultText;
        resultText.setFont(font);
        resultText.setString(resultMessage);
        resultText.setCharacterSize(24);
        resultText.setFillColor(sf::Color::Green);
        resultText.setPosition(50, 150);
        window.draw(resultText);

        linkedlist.showList(window, font);
        displayUserInput(window, font, userInput, operationMessage);
        displayComplexities(window, font, linkedlist.getComplexities());

        window.display();
    }

    return 0;
}
