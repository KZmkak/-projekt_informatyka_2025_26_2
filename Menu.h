#pragma once
#include <SFML/Graphics.hpp>
#include <array>

#define MAX_ITEMS 3

class Menu {
public:
    Menu(float width, float height);

    void draw(sf::RenderWindow& window);
    void MoveUp();
    void MoveDown();
    int getSelectedItem() const { return selectedItemIndex; }

private:
    int selectedItemIndex;
    std::array<sf::Text, MAX_ITEMS> menu;
    sf::Font font;
};


