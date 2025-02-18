#pragma once
#include "SFML/Graphics.hpp"
#include <cstdlib>
#define MAX_NUMBER_OF_ITEMS 21
class Prácticas{
    public:

    Prácticas(float width, float height);
    ~Prácticas();

    void draws(sf::RenderWindow &window);
    void MoveUp();
    void MoveDown();
    int GetPressedItem(){return selectedItemIndex;}
    void binarySearchVisual(sf::RenderWindow &window, const std::vector<int> &vec, int target);
    void linearSearchVisual(sf::RenderWindow &window, const std::vector<int> &vec, int target);
    void openNewWindow(const std::string &message);


    private:
    int selectedItemIndex;
    sf::Font font;
    sf::Text menu[MAX_NUMBER_OF_ITEMS];

};