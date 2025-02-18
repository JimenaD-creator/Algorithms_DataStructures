#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "Prácticas.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <thread>
#include <chrono>
using namespace std;

struct Empleado {
    string nombre;
    int edad;  
    string hobbies;
    string habilidades;
};

vector<Empleado> empleados = { {"Alice", 25, "Leer, Correr", "C++"},
    {"Bob", 30, "Programar, Musica", "Java"}, {"Charlie", 22, "Videojuegos, Pintura", "Python"}, 
    {"David", 28, "Futbol, Viajar", "JavaScript"}, {"Eve", 35, "Cocina, Jardineria", "C#"}, {"Frank", 27, "Ciclismo, Lectura", "Ruby"}, {"Grace", 32, "Natacion, Ajedrez", "Go"}, 
    {"Hank", 24, "Esqui, Fotografia", "Swift"}, {"Ivy", 29, "Yoga, Teatro", "TypeScript"}, {"Jack", 31, "Escalar, Piano", "Kotlin"}, {"Kathy", 26, "Leer, Cocina", "PHP"},
     {"Leo", 33, "Correr, Ciclismo", "Perl"}, {"Mona", 29, "Cine, Teatro", "Scala"}, {"Nina", 24, "Natacion, Viajes", "Rust"}, {"Oscar", 28, "Videojuegos, Música", "Haskell"}, {"Paul", 30, "Fotografía, Esqui", "SQL"},
      {"Quincy", 27, "Ajedrez, Jardineria", "HTML/CSS"}, {"Rachel", 31, "Escalar, Yoga", "SASS"}, {"Steve", 34, "Piano, Correr", "R"}, 
      {"Tina", 23, "Cocina, Videojuegos", "Lua"}, {"Uma", 29, "Teatro, Pintura", "Elixir"}, {"Victor", 32, "Viajar, Escalar", "MATLAB"}, {"Wendy", 25, "Ciclismo, Leer", "Dart"}, 
      {"Xander", 30, "Musica, Futbol", "VB.NET"}, {"Yara", 28, "Correr, Jardineria", "Shell Scripting"}, {"Zane", 26, "Fotografia, Cine", "Objective-C"}, {"Albert", 35, "Leer, Pintura", "Clojure"}, 
      {"Brenda", 31, "Yoga, Natacion", "Erlang"}, {"Calvin", 33, "Ajedrez, Videojuegos", "C"}, {"Diana", 29, "Escalar, Esqui", "Fortran"}, {"Eli", 24, "Teatro, Piano", "Julia"}, {"Fiona", 27, "Cocina, Viajar", "Racket"}, 
      {"George", 28, "Natacion, Musica", "Tcl"}, {"Helen", 30, "Correr, Fotografia", "F#"}, {"Isaac", 32, "Escalar, Jardineria", "Groovy"}, {"Jenny", 26, "Pintura, Leer", "PowerShell"}, {"Kevin", 31, "Ciclismo, Yoga", "Lisp"}, 
      {"Linda", 34, "Cine, Teatro", "Prolog"}, {"Mike", 28, "Ajedrez, Programar", "PostgreSQL"}, {"Nora", 27, "Esquí, Escalar", "SQLite"}, {"Owen", 29, "Leer, Piano", "Cassandra"}, {"Paula", 25, "Viajar, Correr", "MongoDB"}, 
      {"Quentin", 33, "Fotografia, Cine", "Redis"}, {"Rita", 30, "Ciclismo, Videojuegos", "Memcached"}, {"Sam", 26, "Correr, Jardineria", "MySQL"}, {"Tracy", 32, "Teatro, Leer", "MariaDB"}, {"Ulysses", 28, "Programar, Natacion", "Oracle"},
       {"Vera", 29, "Yoga, Musica", "SQL Server"}, {"Will", 31, "Esqui, Jardineria", "Firebase"}, {"Xena", 27, "Escalar, Cine", "Neo4j"}, {"Yuri", 35, "Leer, Programar", "GraphQL"}, {"Zara", 24, "Fotografia, Pintura", "Docker"}, 
       {"Arthur", 30, "Cocina, Musica", "Kubernetes"}, {"Bella", 26, "Videojuegos, Esqui", "Ansible"}, {"Cody", 28, "Piano, Yoga", "Terraform"}, {"Derek", 33, "Leer, Jardineria", "Chef"}, {"Eva", 31, "Ciclismo, Cine", "Puppet"}, 
       {"Fred", 29, "Programar, Escalar", "Jenkins"}, {"Gina", 34, "Natacion, Ajedrez", "Travis CI"}, {"Harry", 27, "Escalar, Musica", "CircleCI"}, {"Irene", 25, "Videojuegos, Fotografia", "GitLab CI"}, {"Jacob", 32, "Cocina, Leer", "GitHub Actions"}, 
       {"Kara", 29, "Yoga, Correr", "Azure DevOps"}, {"Louis", 31, "Ajedrez, Programar", "AWS"}, {"Molly", 28, "Escalar, Natacion", "GCP"}, {"Nate", 26, "Ciclismo, Teatro", "Heroku"}, {"Olivia", 30, "Fotografia, Jardineria", "Lambda"}, 
       {"Peter", 35, "Leer, Programar", "S3"}, {"Quinn", 24, "Pintura, Cine", "EC2"}, {"Rose", 27, "Cocina, Escalar", "CloudFormation"}, {"Sean", 29, "Videojuegos, Musica", "Elastic Beanstalk"}, {"Tara", 33, "Teatro, Ajedrez", "Azure Functions"}, 
       {"Uri", 31, "Natacion, Jardineria", "Cloudflare"}, {"Vince", 28, "Leer, Escalar", "Fastly"}, {"Willa", 30, "Yoga, Cine", "Kong"}, {"Ximena", 27, "Correr, Pintura", "Nginx"}, {"Yusuf", 29, "Ciclismo, Jardineria", "HAProxy"}, {"Zoe", 26, "Natacion, Fotografia", "Consul"}, 
       {"Andre", 31, "Escalar, Ajedrez", "Vault"}, {"Beth", 28, "Leer, Videojuegos", "Prometheus"}, {"Chris", 35, "Correr, Musica", "Grafana"}, {"Daisy", 24, "Natacion, Escalar", "Kibana"}, {"Ethan", 27, "Fotografia, Ciclismo", "ElasticSearch"}, 
       {"Faith", 29, "Teatro, Piano", "Logstash"}, {"Gabe", 30, "Cocina, Leer", "Fluentd"}, {"Hazel", 32, "Ajedrez, Jardineria", "Kafka"}, {"Ian", 28, "Correr, Yoga", "RabbitMQ"}, {"Judy", 26, "Videojuegos, Fotografia", "ActiveMQ"}, {"Karl", 34, "Ciclismo, Programar", "Kafka Streams"}, 
       {"Lena", 29, "Escalar, Cine", "Spark Streaming"}, {"Mick", 31, "Leer, Musica", "Flink"}, {"Nina", 27, "Pintura, Jardineria", "Samza"} };
   
void ordenarEmpleados(vector <Empleado> &empleados){
    int n = empleados.size();
    for(int i = 0; i < n-1; i++){ //Ciclo para recorrer los elementos del vector. El elemento más grande va pasando al final y ya no se considera
        for(int j = 0; j < n-1-i; j++){ //El límite disminuye con cada iteración porque los elementos finales ya están en su lugar correcto
            if(empleados[j].nombre > empleados[j+1].nombre){ //Comparar posiciones de los empleados
                swap(empleados[j], empleados[j+1]); //intercambio
            };
        };
    };

       
}
int binarySearch(const vector<Empleado>& empleados, const string& nombre) {
    int low = 0;
    int high = empleados.size() - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (empleados[mid].nombre == nombre) {
            return mid;
        }
        if (empleados[mid].nombre < nombre) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

void mostrarInformación(sf::RenderWindow &window, const Empleado& empleado) {
    sf::Font font;
    if (!font.loadFromFile("PlaywriteGBS-VariableFont_wght.ttf")) {
        std::cerr << "Error al cargar la fuente" << std::endl;
        return;
    }

    // Crear texto para mostrar la información del empleado
    std::string info = "Nombre: " + empleado.nombre + "\n"
                       "Edad: " + std::to_string(empleado.edad) + "\n"
                       "Hobbies: " + empleado.hobbies + "\n"
                       "Habilidades: " + empleado.habilidades;

    sf::Text infoText(info, font, 20);
    infoText.setFillColor(sf::Color::White);
    infoText.setPosition(10, 50);

    // Limpiar la ventana y dibujar el texto
    window.clear(sf::Color::Black);
    window.draw(infoText);
    window.display();

    // Esperar unos segundos antes de cerrar la ventana
    sf::sleep(sf::seconds(5));
}

void openBinarySearchWindow(sf::RenderWindow &mainWindow) {
    sf::RenderWindow searchWindow(sf::VideoMode(400, 300), "Buscar Empleado");

    sf::Font font;
    if (!font.loadFromFile("PlaywriteGBS-VariableFont_wght.ttf")) {
        std::cerr << "Error al cargar la fuente" << std::endl;
        return;
    }

    sf::Text promptText("Ingrese el nombre del empleado:", font, 20);
    promptText.setFillColor(sf::Color::White);
    promptText.setPosition(10, 20);

    sf::Text inputText("", font, 20);
    inputText.setFillColor(sf::Color::White);
    inputText.setPosition(10, 60);

    sf::Text resultText("", font, 20);
    resultText.setFillColor(sf::Color::White);
    resultText.setPosition(10, 100);

    sf::String input; // Almacena la entrada del usuario

    while (searchWindow.isOpen()) {
        sf::Event event;
        while (searchWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                searchWindow.close();
            }
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode < 128) { // Solo permitir caracteres ASCII
                    if (event.text.unicode == '\b') { // Manejo de retroceso
                        if (!input.isEmpty()) {
                            input.erase(input.getSize() - 1, 1);
                        }
                    } else if (event.text.unicode == '\r') { // Manejo de Enter
                        // Realiza la búsqueda y muestra el resultado
                        int index = binarySearch(empleados, input.toAnsiString());
                        if (index != -1) {
                            mostrarInformación(searchWindow, empleados[index]);
                        } else {
                            resultText.setString("Empleado no encontrado");
                        }
                    } else { // Añadir caracteres al input
                        input += event.text.unicode;
                    }
                }
            }
        }

        inputText.setString(input); // Actualiza el texto de entrada

        searchWindow.clear(sf::Color::Black);
        searchWindow.draw(promptText);
        searchWindow.draw(inputText);
        searchWindow.draw(resultText);
        searchWindow.display();
    }
}

void openNewWindow(const std::string &message) {
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
//........................ BUBBLE SORT ..................................
// Función para intercambiar dos valores
void change(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

// Algoritmo de ordenamiento por selección
void selectionSort(vector<int> &vec, sf::RenderWindow &window, vector<int> &sortedVec) {
     int n = vec.size();
    for (int i = 0; i < n - 1; i++) {
        int minVal = i;
        for (int j = i + 1; j < n; j++) {
            if (vec[j] < vec[minVal]) {
                minVal = j;
            }
        }
        if (minVal != i) {
            change(vec[i], vec[minVal]);
        }

        // Visualización
        window.clear(sf::Color::Black);
        for (size_t k = 0; k < vec.size(); ++k) {
            sf::RectangleShape rectangle(sf::Vector2f(20, vec[k] * 5)); // Escalando la altura
            rectangle.setFillColor(sf::Color::Green);
            rectangle.setPosition(k * 25, window.getSize().y - vec[k] * 5);
            window.draw(rectangle);
        }
        
        // Mostrar la lista ordenada
        std::string sortedText = "Números ordenados: ";
        for (const auto &num : vec) {
            sortedText += std::to_string(num) + " ";
        }
        sf::Text sortedDisplay(sortedText, sf::Font(), 20);
        sortedDisplay.setFillColor(sf::Color::White);
        sortedDisplay.setPosition(10, 10);
        window.draw(sortedDisplay);

        // Complejidad del algoritmo
        std::string complexityText = "Complejidad: O(n^2) (Peor y Promedio)";
        sf::Text complexityDisplay(complexityText, sf::Font(), 20);
        complexityDisplay.setFillColor(sf::Color::White);
        complexityDisplay.setPosition(10, 40);
        window.draw(complexityDisplay);

        window.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Esperar para visualización
    }

    // Copia los números ordenados para la visualización final
    sortedVec = vec;
}



// Método principal para el ingreso y ordenamiento
void bubbleSortVisual() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Bubble Sort - Calificaciones");

    sf::Font font;
    if (!font.loadFromFile("PlaywriteGBS-VariableFont_wght.ttf")) {
        std::cerr << "Error al cargar la fuente\n";
        return;
    }

    sf::Text prompt("Ingresa la calificacion 1:", font, 24);
    prompt.setFillColor(sf::Color::White);
    prompt.setPosition(50, 50);

    sf::Text inputText("", font, 24);
    inputText.setFillColor(sf::Color::Yellow);
    inputText.setPosition(50, 100);

    sf::Text statusText("", font, 24);
    statusText.setFillColor(sf::Color::Green);
    statusText.setPosition(50, 300); // Posición ajustada para evitar empalmar con la gráfica

    // Texto sobre la complejidad del algoritmo
    sf::Text complexityText("Complejidad del Bubble Sort: O(n^2)", font, 24);
    complexityText.setFillColor(sf::Color::Cyan);
    complexityText.setPosition(50, 250); // Posición ajustada

    std::vector<int> cal(7, 0);
    std::string input = "";
    int index = 0;
    bool sorted = false;

    // Ajustes para la visualización
    int barHeightFactor = 2; // Factor para reducir la altura de las barras
    int barSpacing = 10;      // Espaciado entre las barras
    int barWidth = 50;        // Ancho de cada barra
    int startX = 100;         // Posición X inicial para dibujar las barras

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (!sorted && event.type == sf::Event::TextEntered) {
                char entered = static_cast<char>(event.text.unicode);

                if (entered == '\b' && !input.empty()) { // Manejar retroceso
                    input.pop_back();
                } else if (entered == '\r' && !input.empty()) { // Manejar ingreso de calificación
                    cal[index] = std::stoi(input);
                    input.clear();
                    index++;

                    if (index < 7) {
                        prompt.setString("Ingresa la calificacion " + std::to_string(index + 1) + ":");
                    } else {
                        // Realiza el ordenamiento con visualización
                        for (int j = 0; j < cal.size() - 1; j++) {
                            for (int k = 0; k < cal.size() - j - 1; k++) {
                                if (cal[k] > cal[k + 1]) {
                                    change(cal[k], cal[k + 1]);

                                    // Visualizar el estado actual de las calificaciones
                                    window.clear();
                                    window.draw(prompt);
                                    window.draw(inputText);

                                    // Mostrar las calificaciones
                                    std::ostringstream oss;
                                    oss << "Calificaciones ordenadas: ";
                                    for (int num : cal) {
                                        oss << num << " ";
                                    }
                                    statusText.setString(oss.str());
                                    window.draw(statusText);

                                    // Dibujar las barras en el gráfico
                                    for (size_t i = 0; i < cal.size(); i++) {
                                        sf::RectangleShape bar(sf::Vector2f(barWidth, cal[i] / barHeightFactor));
                                         if ((i == k && cal[k] < cal[k + 1]) || (i == k + 1 && cal[k + 1] < cal[k])) {
                                        bar.setFillColor(sf::Color::Red); // Color rojo para los números que se están cambiando
                                         } else {
                                        bar.setFillColor(sf::Color::Magenta); // Color normal para las demás barras
                                         }



                                        bar.setPosition(startX + i * (barWidth + barSpacing), 500 - cal[i] / barHeightFactor);
                                        window.draw(bar);
                                    }
                                    window.draw(complexityText); // 
                                    window.display();
                                    sf::sleep(sf::milliseconds(300));  // Esperar para visualizar el cambio
                                }
                            }
                        }
                        sorted = true;

                        // Mostrar las calificaciones ordenadas
                        std::string result = "Calificaciones ordenadas: ";
                        for (int num : cal) {
                            result += std::to_string(num) + " ";
                        }
                        statusText.setString(result);
                    }
                } else if (std::isdigit(entered)) {
                    input += entered; // Agregar el número ingresado
                }
            }
        }

        window.clear();
        window.draw(prompt);
        inputText.setString("Input: " + input); // Mostrar el input del usuario
        window.draw(inputText); // Mostrar el texto de entrada

        if (sorted) {
            window.draw(statusText);
            window.draw(complexityText); // Mostrar la complejidad al final
            sf::sleep(sf::seconds(2));  // Espera 2 segundos
            window.close();
        }
        window.display();
    }
}

// Función para dibujar el gráfico de barras
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
// Función para el algoritmo de ordenamiento Selection Sort
void selectionSort(std::vector<int>& vec, sf::RenderWindow& window, sf::Text& complexityText, sf::Text& promptText, sf::Text& inputText, sf::Text& resultText) {
    size_t n = vec.size();
    complexityText.setString("Complejidad de Selection Sort: O(n^2)");

    for (size_t i = 0; i < n - 1; ++i) {
        int minIndex = i;

        for (size_t j = i + 1; j < n; ++j) {
            // Dimensiones para las barras
            float barWidth = (window.getSize().x * 0.6f) / static_cast<float>(vec.size());
            float offsetX = (window.getSize().x - barWidth * vec.size()) / 2;

            // Comparación actual
            window.clear();

            // Dibujar las barras con colores específicos
            for (size_t k = 0; k < vec.size(); ++k) {
                sf::RectangleShape bar(sf::Vector2f(barWidth - 2, static_cast<float>(vec[k] * 3)));
                bar.setPosition(offsetX + k * barWidth, window.getSize().y - bar.getSize().y - 50);

                if (k == j) {
                    bar.setFillColor(sf::Color::Cyan); // Comparación actual
                } else if (k == minIndex) {
                    bar.setFillColor(sf::Color::Yellow); // Mínimo actual
                } else {
                    bar.setFillColor(sf::Color::Magenta); // Color estándar
                }

                window.draw(bar);
            }

            // Dibujar texto y gráficos
            window.draw(promptText);
            window.draw(inputText);
            window.draw(resultText);
            window.draw(complexityText);
            window.display();

            sf::sleep(sf::milliseconds(300)); // Retraso para visualizar las comparaciones

            if (vec[j] < vec[minIndex]) {
                minIndex = j; // Actualizar el índice del mínimo
            }
        }

        if (minIndex != i) {
            // Intercambio de valores
            std::swap(vec[i], vec[minIndex]);

            // Mostrar el intercambio
            window.clear();

            float barWidth = (window.getSize().x * 0.6f) / static_cast<float>(vec.size());
            float offsetX = (window.getSize().x - barWidth * vec.size()) / 2;

            for (size_t k = 0; k < vec.size(); ++k) {
                sf::RectangleShape bar(sf::Vector2f(barWidth - 2, static_cast<float>(vec[k] * 3)));
                bar.setPosition(offsetX + k * barWidth, window.getSize().y - bar.getSize().y - 50);

                if (k == i || k == minIndex) {
                    bar.setFillColor(sf::Color::Red); // Resaltar intercambio
                } else {
                    bar.setFillColor(sf::Color::Magenta); // Color estándar
                }

                window.draw(bar);
            }

            // Actualizar texto
            std::string resultTextStr = "Numeros en proceso: ";
            for (const auto& num : vec) {
                resultTextStr += std::to_string(num) + " ";
            }
            resultText.setString(resultTextStr);

            window.draw(promptText);
            window.draw(inputText);
            window.draw(resultText);
            window.draw(complexityText);
            window.display();

            sf::sleep(sf::milliseconds(500)); // Retraso para visualizar el intercambio
        }
    }

    // Mostrar resultado final
    std::string resultTextStr = "Numeros ordenados: ";
    for (const auto& num : vec) {
        resultTextStr += std::to_string(num) + " ";
    }
    resultText.setString(resultTextStr);

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
                selectionSort(numeros, sortWindow, complexityText, promptText, inputText, resultText);
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


void abrirArchivo(const string& nombreArchivo){
    std::string comando; 
    #ifdef _WIN64 
    comando = "start " + nombreArchivo; 
    #elif __APPLE__ 
    comando = "open " + nombreArchivo; 
    #else 
    comando = "xdg-open " + nombreArchivo; 
    #endif
    std::system(comando.c_str());

}


// Método principal
int main() {
    ordenarEmpleados(empleados);
    sf::RenderWindow window(sf::VideoMode(1300, 1300), "SFML Works");
    Prácticas menu(window.getSize().x, window.getSize().y);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyReleased) {
                switch (event.key.code) {
                    case sf::Keyboard::Up:
                        menu.MoveUp();
                        break;
                    case sf::Keyboard::Down:
                        menu.MoveDown();
                        break;
                    case sf::Keyboard::Return:
                        std::cout << "Enter Pressed" << std::endl;
                        switch (menu.GetPressedItem()) {
                            case 0:
                                break;
                            case 1:
                                openBinarySearchWindow(window);
                                break;
                            case 2:
                                abrirArchivo("binarySearch.exe");
                                break;
                            case 3:
                                abrirArchivo("linearSearch.exe");
                                //menu.linearSearchVisual(window, {2, 5, 8, 12, 16, 23, 38, 45, 56, 67, 78}, 23);
                                break;
                            case 4:
                                break;
                            case 5:
                                bubbleSortVisual(); 
                                break;
                            case 6:
                                openSortingWindow(window);
                                break;
                            
                            case 7:
                                abrirArchivo("InsertionSort.exe");
                                
                                break;
                            case 8:
                                abrirArchivo("QuickSort.exe");

                                break;
                            case 9:
                                abrirArchivo("MergeSort.exe");
                                break;
                            case 10:
                                break;
                            case 11:
                                abrirArchivo("linkedList.exe");
                                break;
                            case 12:
                                abrirArchivo("doubleLinkedList.exe");
                                break;
                            case 13:
                                abrirArchivo("queue.exe");
                                break;
                            case 14:
                                abrirArchivo("stack.exe");
                                break;
                            case 15:
                                break;
                            case 16:
                                abrirArchivo("bst.exe");
                                break;
                            case 17:
                                abrirArchivo("avl.exe");
                                break;
                            case 18:
                                break;
                            case 19:
                                abrirArchivo("bfs.exe");
                                break;
                            case 20:
                                abrirArchivo("dijkstra.exe");
                                break;
                            default:
                                break;
                        }
                        break;
                }
            }
        }
        window.clear();
        menu.draws(window);
        window.display();
    }

    return 0;
}



