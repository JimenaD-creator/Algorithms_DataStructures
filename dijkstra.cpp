#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <sstream>

using namespace std;

// Función para encontrar la ruta más corta con Dijkstra
vector<int> dijkstra(const vector<vector<pair<int, float>>>& grafo, int inicio, int destino, float& distancia_minima) {
    int n = grafo.size();
    vector<float> distancias(n, numeric_limits<float>::max());
    vector<int> previo(n, -1); // Para reconstruir la ruta
    priority_queue<pair<float, int>, vector<pair<float, int>>, greater<>> pq;

    distancias[inicio] = 0;
    pq.push({0, inicio});

    while (!pq.empty()) {
        float d = pq.top().first;
        int nodo = pq.top().second;
        pq.pop();

        if (d > distancias[nodo]) continue;

        for (const auto& vecino : grafo[nodo]) {
            int vecinoNodo = vecino.first;
            float peso = vecino.second;

            if (distancias[nodo] + peso < distancias[vecinoNodo]) {
                distancias[vecinoNodo] = distancias[nodo] + peso;
                previo[vecinoNodo] = nodo;
                pq.push({distancias[vecinoNodo], vecinoNodo});
            }
        }
    }

    // Reconstruir la ruta desde el destino
    vector<int> ruta;
    for (int at = destino; at != -1; at = previo[at]) {
        ruta.push_back(at);
    }
    reverse(ruta.begin(), ruta.end());

    distancia_minima = distancias[destino];
    return ruta;
}

int main() {
    // Grafo como lista de adyacencias
    vector<vector<pair<int, float>>> grafo(13); // 12 nodos, índices del 1 al 12

    // Añadir las conexiones con pesos (nodos están indexados desde 1 para facilidad)
    grafo[1].push_back({2, 59.4}); grafo[2].push_back({1, 59.4});
    grafo[2].push_back({3, 36.06}); grafo[3].push_back({2, 36.06});
    grafo[3].push_back({4, 195.52}); grafo[4].push_back({3, 195.52});
    grafo[2].push_back({10, 58.85}); grafo[10].push_back({2, 58.85});
    grafo[4].push_back({5, 23.35}); grafo[5].push_back({4, 23.35});
    grafo[5].push_back({6, 80.12}); grafo[6].push_back({5, 80.12});
    grafo[6].push_back({7, 40}); grafo[7].push_back({6, 40});
    grafo[7].push_back({8, 120}); grafo[8].push_back({7, 120});
    grafo[8].push_back({9, 100}); grafo[9].push_back({8, 100});
    grafo[9].push_back({10, 189.06}); grafo[10].push_back({9, 189.06});
    grafo[9].push_back({11, 215.35}); grafo[11].push_back({9, 215.35});
    grafo[11].push_back({12, 183.99}); grafo[12].push_back({11, 183.99});
    grafo[12].push_back({6, 106.65}); grafo[6].push_back({12, 106.65});

    // Crear ventana gráfica
    sf::RenderWindow window(sf::VideoMode(800, 600), "Grafo con Pesos");

    // Variables de entrada para los nodos
    int nodo_inicio = 1, nodo_destino = 1;
    bool seleccionando_inicio = true;
    bool calculo_realizado = false;
    float distancia_minima;
    vector<int> ruta;

    vector<sf::CircleShape> nodos(13);
    vector<sf::Text> etiquetas_nodos(13);
    vector<sf::Vector2f> posiciones = {
        {}, {100, 100}, {250, 100}, {400, 100}, {560, 100}, {700, 100},
        {750, 300}, {550, 300}, {400, 300}, {250, 250}, {100, 300}, {250, 400}, {550, 450}
    };

    sf::Font font;
    if (!font.loadFromFile("PlaywriteGBS-VariableFont_wght.ttf")) {
        cerr << "No se pudo cargar la fuente." << endl;
        return 1;
    }

    for (int i = 1; i <= 12; i++) {
        nodos[i].setRadius(20);
        nodos[i].setFillColor(sf::Color::Cyan);
        nodos[i].setPosition(posiciones[i]);
        nodos[i].setOrigin(20, 20);

        etiquetas_nodos[i].setFont(font);
        etiquetas_nodos[i].setString(to_string(i));
        etiquetas_nodos[i].setCharacterSize(16);
        etiquetas_nodos[i].setFillColor(sf::Color::Black);
        etiquetas_nodos[i].setPosition(posiciones[i].x - 10, posiciones[i].y - 10);
    }

    sf::Text texto;
    texto.setFont(font);
    texto.setCharacterSize(18);
    texto.setFillColor(sf::Color::White);
    texto.setPosition(10, 10);

    // Texto para las aristas
    vector<sf::Text> textos_aristas;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed && !calculo_realizado) {
                sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);

                for (int i = 1; i <= 12; i++) {
                    if (nodos[i].getGlobalBounds().contains(mouse_pos.x, mouse_pos.y)) {
                        if (seleccionando_inicio) {
                            nodo_inicio = i;
                            nodos[i].setFillColor(sf::Color::Green);
                            seleccionando_inicio = false;
                        } else {
                            nodo_destino = i;
                            nodos[i].setFillColor(sf::Color::Red);
                            seleccionando_inicio = true;
                            calculo_realizado = true;
                            ruta = dijkstra(grafo, nodo_inicio, nodo_destino, distancia_minima);
                        }
                    }
                }
            }
        }

        window.clear();

        // Dibujar aristas
        for (int i = 1; i <= 12; i++) {
            for (auto& vecino : grafo[i]) {
                int destino = vecino.first;
                sf::Vertex line[] = {
                    sf::Vertex(posiciones[i], sf::Color::Yellow),
                    sf::Vertex(posiciones[destino], sf::Color::Yellow)
                };
                window.draw(line, 2, sf::Lines);

                // Añadir el texto de la distancia
                sf::Text texto_arista;
                texto_arista.setFont(font);
                texto_arista.setCharacterSize(12);
                texto_arista.setFillColor(sf::Color::White);
                float distancia = vecino.second;
                stringstream ss;
                ss << distancia;
                texto_arista.setString(ss.str());
                sf::Vector2f pos_texto = (posiciones[i] + posiciones[destino]) / 2.0f;
                texto_arista.setPosition(pos_texto);
                window.draw(texto_arista);
            }
        }

        // Dibujar la ruta más corta si está calculada
        if (calculo_realizado) {
            for (size_t i = 1; i < ruta.size(); i++) {
                int u = ruta[i - 1], v = ruta[i];
                sf::Vertex line[] = {
                    sf::Vertex(posiciones[u], sf::Color::Red),
                    sf::Vertex(posiciones[v], sf::Color::Red)
                };
                window.draw(line, 2, sf::Lines);
            }

            // Mostrar distancia y ruta
            stringstream ss;
            ss << "Distancia minima: " << distancia_minima << " metros" << "\nRuta: ";
            for (int nodo : ruta) {
                ss << nodo << " -> ";
            }
            texto.setString(ss.str());
        } else {
            texto.setString("Selecciona el nodo de inicio (verde) y destino (rojo).");
        }

        window.draw(texto);

        // Dibujar nodos con etiquetas
        for (int i = 1; i <= 12; i++) {
            window.draw(nodos[i]);
            window.draw(etiquetas_nodos[i]);
        }

        window.display();
    }

    return 0;
}