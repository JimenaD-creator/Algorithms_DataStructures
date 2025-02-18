#include <SFML/Graphics.hpp>
#include <vector>
#include <queue>
#include <random>
#include <chrono>
#include <thread>

class Maze {
public:
    Maze(int width, int height, int cellSize);
    void generateMaze();
    bool solveMaze(sf::RenderWindow& window);  // Declaración del método solveMaze
    bool solveMazeBFS(sf::RenderWindow& window);  // Método para resolver con BFS
    void draw(sf::RenderWindow& window);

private:
    enum Cell { WALL, PATH, VISITED, START, END, SOLUTION };

    struct Position {
        int x, y;
        Position(int x, int y) : x(x), y(y) {}
    };

    int width, height, cellSize;
    std::vector<std::vector<Cell>> grid;
    Position start, end;

    void generateDFS(Position pos);
    bool solveDFS(Position pos, sf::RenderWindow& window);  // Declaración de la función solveDFS
    std::vector<Position> getNeighbors(const Position& pos);
};


Maze::Maze(int width, int height, int cellSize)
    : width(width), height(height), cellSize(cellSize), start(1, 1), end(width - 2, height - 2) {
    grid.resize(width, std::vector<Cell>(height, WALL));
    generateMaze();
    grid[start.x][start.y] = START;
    grid[end.x][end.y] = END;
}

void Maze::generateMaze() {
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            grid[x][y] = WALL;
        }
    }
    generateDFS(start);
    grid[start.x][start.y] = START;
    grid[end.x][end.y] = END;
}

void Maze::generateDFS(Position pos) {
    grid[pos.x][pos.y] = PATH;
    std::vector<Position> directions = { {0, -2}, {0, 2}, {-2, 0}, {2, 0} };
    std::shuffle(directions.begin(), directions.end(), std::mt19937(std::random_device()()));

    for (const Position& direction : directions) {
        int nx = pos.x + direction.x;
        int ny = pos.y + direction.y;

        if (nx > 0 && ny > 0 && nx < width - 1 && ny < height - 1 && grid[nx][ny] == WALL) {
            grid[nx][ny] = PATH;
            grid[pos.x + direction.x / 2][pos.y + direction.y / 2] = PATH;
            generateDFS({ nx, ny });
        }
    }
}

bool Maze::solveMaze(sf::RenderWindow& window) {
    return solveDFS(start, window);
}
bool Maze::solveMazeBFS(sf::RenderWindow& window) {
    std::queue<Position> q;
    q.push(start);
    grid[start.x][start.y] = VISITED;

    while (!q.empty()) {
        Position pos = q.front();
        q.pop();

        if (pos.x == end.x && pos.y == end.y) {
            // Llegamos al final, marcamos el camino de la solución
            grid[pos.x][pos.y] = SOLUTION;
            return true;
        }

        // Visualizamos cada paso
        draw(window);
        window.display();
        sf::sleep(sf::milliseconds(200));  // Pausa para ver el progreso

        std::vector<Position> neighbors = { {0, -1}, {0, 1}, {-1, 0}, {1, 0} };
        for (const Position& dir : neighbors) {
            int nx = pos.x + dir.x;
            int ny = pos.y + dir.y;

            if (nx >= 0 && ny >= 0 && nx < width && ny < height && (grid[nx][ny] == PATH || grid[nx][ny] == END)) {
                q.push({nx, ny});
                grid[nx][ny] = VISITED;  // Marcamos como visitado
            }
        }
    }
    return false;
}

bool Maze::solveDFS(Position pos, sf::RenderWindow& window) {
    if (pos.x == end.x && pos.y == end.y) {
        grid[pos.x][pos.y] = SOLUTION;
        return true;
    }

    grid[pos.x][pos.y] = VISITED;
    draw(window);
    window.display();
    sf::sleep(sf::milliseconds(200));

    std::vector<Position> neighbors = { {0, -1}, {0, 1}, {-1, 0}, {1, 0} };
    for (const Position& dir : neighbors) {
        int nx = pos.x + dir.x;
        int ny = pos.y + dir.y;

        if (grid[nx][ny] == PATH || grid[nx][ny] == END) {
            if (solveDFS({ nx, ny }, window)) {
                grid[pos.x][pos.y] = SOLUTION;
                draw(window);
                window.display();
                sf::sleep(sf::milliseconds(50));
                return true;
            }
        }
    }

    grid[pos.x][pos.y] = PATH;
    return false;
}

void Maze::draw(sf::RenderWindow& window) {
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
            cell.setPosition(x * cellSize, y * cellSize);

            switch (grid[x][y]) {
                case WALL: cell.setFillColor(sf::Color::Black); break;
                case PATH: cell.setFillColor(sf::Color::White); break;
                case VISITED: cell.setFillColor(sf::Color::Blue); break;
                case START: cell.setFillColor(sf::Color::Green); break;
                case END: cell.setFillColor(sf::Color::Red); break;
                case SOLUTION: cell.setFillColor(sf::Color::Yellow); break;
            }

            window.draw(cell);
        }
    }
}

int main() {
    int width = 21;
    int height = 21;
    int cellSize = 20;

    sf::RenderWindow window(sf::VideoMode(width * cellSize, height * cellSize), "Maze Solver");

    Maze maze(width, height, cellSize);
    maze.generateMaze();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        maze.draw(window);
        window.display();

      

        if(maze.solveMazeBFS(window)){
             sf::sleep(sf::seconds(2));
             break;
        }
    }

    return 0;
}