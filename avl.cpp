#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <string>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    int height;

    Node(int value) : data(value), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
public:
    Node* root;

    AVLTree() : root(nullptr) {}
    Node* insert(Node* node, int value);
    Node* search(Node* node, int value);
    Node* removeNode(Node* node, int value);
    Node* findMin(Node* node);
    int getHeight(Node* node);
    int getBalanceFactor(Node* node);
    Node* rotateRight(Node* y);
    Node* rotateLeft(Node* x);
    Node* balance(Node* node);
    void drawTree(Node* node, sf::RenderWindow& window, sf::Font& font, float x, float y, float xOffset, int targetValue);
};

int AVLTree::getHeight(Node* node) {
    if (!node) return 0;
    return node->height;
}

int AVLTree::getBalanceFactor(Node* node) {
    if (!node) return 0;
    return getHeight(node->left) - getHeight(node->right);
}

Node* AVLTree::rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

Node* AVLTree::rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

Node* AVLTree::balance(Node* node) {
    int balance = getBalanceFactor(node);

    // Left heavy subtree
    if (balance > 1) {
        if (getBalanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left);
        }
        return rotateRight(node);
    }

    // Right heavy subtree
    if (balance < -1) {
        if (getBalanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);
        }
        return rotateLeft(node);
    }

    return node;
}

Node* AVLTree::insert(Node* node, int value) {
    if (!node) return new Node(value);

    if (value < node->data) {
        node->left = insert(node->left, value);
    } else if (value > node->data) {
        node->right = insert(node->right, value);
    } else {
        return node; // Duplicates are not allowed
    }

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    return balance(node);
}

Node* AVLTree::search(Node* node, int value) {
    if (!node || node->data == value) return node;
    return (value < node->data) ? search(node->left, value) : search(node->right, value);
}

Node* AVLTree::findMin(Node* node) {
    while (node && node->left) node = node->left;
    return node;
}

Node* AVLTree::removeNode(Node* node, int value) {
    if (!node) return node;

    if (value < node->data) {
        node->left = removeNode(node->left, value);
    } else if (value > node->data) {
        node->right = removeNode(node->right, value);
    } else {
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

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    return balance(node);
}

void AVLTree::drawTree(Node* node, sf::RenderWindow& window, sf::Font& font, float x, float y, float xOffset, int targetValue) {
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
    sf::CircleShape circle(30);  // Changed the radius to 30 to make the circle bigger
    if (node->data == targetValue) {
        circle.setFillColor(sf::Color::Red); // Mark found node
    } else {
        circle.setFillColor(sf::Color::Cyan);
    }
    circle.setPosition(x - 30, y - 30);  // Adjusted to center the circle
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
    AVLTree tree;
    sf::RenderWindow window(sf::VideoMode(800, 600), "AVL Tree Visualization");
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
                    input.pop_back();  // Delete the last character from the input
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

        window.clear();

        // Draw the AVL tree and other components
        tree.drawTree(tree.root, window, font, 400, 100, 150, targetValue);

        // Display input message and current input
        sf::Text textMessage;
        textMessage.setFont(font);
        textMessage.setString(message);
        textMessage.setCharacterSize(18);
        textMessage.setFillColor(sf::Color::Magenta);
        textMessage.setPosition(10, 10);
        window.draw(textMessage);

        if (capturingInput) {
            sf::Text inputText;
            inputText.setFont(font);
            inputText.setString(input);
            inputText.setCharacterSize(18);
            inputText.setFillColor(sf::Color::Yellow);
            inputText.setPosition(10, 40);
            window.draw(inputText);
        }

        // Display complexity information
        sf::Text timeText;
        timeText.setFont(font);
        timeText.setString(timeComplexity);
        timeText.setCharacterSize(18);
        timeText.setFillColor(sf::Color::Green);
        timeText.setPosition(10, 520);
        window.draw(timeText);

        sf::Text spaceText;
        spaceText.setFont(font);
        spaceText.setString(spaceComplexity);
        spaceText.setCharacterSize(18);
        spaceText.setFillColor(sf::Color::Green);
        spaceText.setPosition(10, 500);
        window.draw(spaceText);

        window.display();
    }

    return 0;
}
