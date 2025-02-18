#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <string>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

class BinaryTree {
public:
    Node* root;

    BinaryTree() : root(nullptr) {}
    Node* insert(Node* node, int value);
    Node* search(Node* node, int value);
    Node* removeNode(Node* node, int value);
    Node* findMin(Node* node);
    void drawTree(Node* node, sf::RenderWindow& window, sf::Font& font, float x, float y, float xOffset, int targetValue);
};

Node* BinaryTree::insert(Node* node, int value) {
    if (!node) return new Node(value);
    if (value < node->data) node->left = insert(node->left, value);
    else node->right = insert(node->right, value);
    return node;
}

Node* BinaryTree::search(Node* node, int value) {
    if (!node || node->data == value) return node;
    return (value < node->data) ? search(node->left, value) : search(node->right, value);
}

Node* BinaryTree::findMin(Node* node) {
    while (node && node->left) node = node->left;
    return node;
}

Node* BinaryTree::removeNode(Node* node, int value) {
    if (!node) return node;
    if (value < node->data) node->left = removeNode(node->left, value);
    else if (value > node->data) node->right = removeNode(node->right, value);
    else {
        if (!node->left) {
            Node* temp = node->right;
            delete node;
            return temp;
        } else if (!node->right) {
            Node* temp = node->left;
            delete node;
            return temp;
        }
        Node* successor = findMin(node->right);
        node->data = successor->data;
        node->right = removeNode(node->right, successor->data);
    }
    return node;
}

void BinaryTree::drawTree(Node* node, sf::RenderWindow& window, sf::Font& font, float x, float y, float xOffset, int targetValue) {
    if (!node) return;

    // Draw left subtree
    if (node->left) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(x, y), sf::Color::White),
            sf::Vertex(sf::Vector2f(x - xOffset, y + 100), sf::Color::White)
        };
        window.draw(line, 2, sf::Lines);
        drawTree(node->left, window, font, x - xOffset, y + 100, xOffset / 2, targetValue);
    }

    // Draw right subtree
    if (node->right) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(x, y), sf::Color::White),
            sf::Vertex(sf::Vector2f(x + xOffset, y + 100), sf::Color::White)
        };
        window.draw(line, 2, sf::Lines);
        drawTree(node->right, window, font, x + xOffset, y + 100, xOffset / 2, targetValue);
    }

    // Highlight the target node
    sf::CircleShape circle(30);  // Cambié el radio a 30 para hacer el círculo más grande
    if (node->data == targetValue) {
        circle.setFillColor(sf::Color::Red); // Mark found node
    } else {
        circle.setFillColor(sf::Color::Cyan);
    }
    circle.setPosition(x - 30, y - 30);  // Ajuste para centrar el círculo
    window.draw(circle);

    // Display node value
    sf::Text text;
    text.setFont(font);
    text.setString(to_string(node->data));
    text.setCharacterSize(18);
    text.setFillColor(sf::Color::Black);
    text.setPosition(x - 10, y - 15);
    window.draw(text);
}

int main() {
    BinaryTree tree;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Binary Tree Visualization");
    sf::Font font;
    if (!font.loadFromFile("PlaywriteGBS-VariableFont_wght.ttf")) {
        cout << "No se pudo cargar la fuente." << endl;
        return -1;
    }

    string input = "";
    string message = "Presiona I para ingresar, S para buscar, R para eliminar un nodo.";
    bool capturingInput = false;
    char action = '\0';
    int targetValue = -1;
    string timeComplexity = "Complejidad Temporal: O(log n) (Promedio), O(n) (Peor caso)";
    string spaceComplexity = "Complejidad Espacial: O(n)";

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (capturingInput && event.key.code == sf::Keyboard::Enter) {
                    int value = stoi(input);
                    if (action == 'I') {
                        tree.root = tree.insert(tree.root, value);
                        message = "Nodo " + input + " insertado.";
                    } else if (action == 'S') {
                        Node* found = tree.search(tree.root, value);
                        if (found) {
                            message = "Nodo " + input + " encontrado.";
                            targetValue = value; // Mark the found node
                        } else {
                            message = "Nodo " + input + " no encontrado.";
                            targetValue = -1;
                        }
                    } else if (action == 'R') {
                        tree.root = tree.removeNode(tree.root, value);
                        message = "Nodo " + input + " eliminado";
                    }
                    input = "";
                    capturingInput = false;
                } else if (capturingInput && event.key.code >= sf::Keyboard::Num0 && event.key.code <= sf::Keyboard::Num9) {
                    input += static_cast<char>('0' + event.key.code - sf::Keyboard::Num0);
                } else if (capturingInput && event.key.code == sf::Keyboard::Backspace && !input.empty()) {
                    input.pop_back();  // Borrar el último carácter del input
                } else if (!capturingInput) {
                    if (event.key.code == sf::Keyboard::I) {
                        message = "Ingrese el nodo a insertar:";
                        capturingInput = true;
                        action = 'I';
                    } else if (event.key.code == sf::Keyboard::S) {
                        message = "Ingrese el nodo a buscar:";
                        capturingInput = true;
                        action = 'S';
                    } else if (event.key.code == sf::Keyboard::R) {
                        message = "Ingrese el nodo a eliminar:";
                        capturingInput = true;
                        action = 'R';
                    }
                }
            }
        }

        window.clear(sf::Color::Black);

        // Instrucciones
        sf::Text instructions(message, font, 18);
        instructions.setFillColor(sf::Color::Yellow); // Color de texto para las instrucciones
        instructions.setPosition(10, 10);
        window.draw(instructions);

        // Input del usuario
        if (capturingInput) {
            sf::Text userInput("Input: " + input, font, 18);
            userInput.setFillColor(sf::Color::Magenta); // Color de texto para el input
            userInput.setPosition(10, 50);
            window.draw(userInput);
        }

        // Dibujar el árbol
        tree.drawTree(tree.root, window, font, 400, 50, 200, targetValue);

        // Complejidad Temporal y Espacial en la parte inferior
        sf::Text complexity(timeComplexity + "\n" + spaceComplexity, font, 18);
        complexity.setFillColor(sf::Color::Green); // Color de texto para las complejidades
        complexity.setPosition(10, 500);
        window.draw(complexity);

        window.display();
    }

    return 0;
}
