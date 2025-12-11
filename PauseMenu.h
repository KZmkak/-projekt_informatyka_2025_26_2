#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class PauseMenu {
public:
    PauseMenu(float width, float height);
    void draw(sf::RenderWindow& window);

private:
    sf::Font font;
    sf::Text pausedText;
};