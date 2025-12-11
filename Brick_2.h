#pragma once
#include <SFML/Graphics.hpp>

class Brick {
public:
    sf::RectangleShape shape;
    int lives = 3;
    bool destroyed = false;

    Brick(float x, float y, float width = 60.f, float height = 25.f) {
        shape.setSize({ width, height });
        shape.setPosition(x, y);

       
        shape.setOutlineThickness(2.f);
        shape.setOutlineColor(sf::Color::White);
       

        updateColor();
    }

    void hit() {
        if (destroyed) return;

        lives--;
        if (lives <= 0) {
            destroyed = true;
        }
        else {
            updateColor();
        }
    }

    void updateColor() {
        if (lives == 3)      shape.setFillColor(sf::Color::Red);
        else if (lives == 2) shape.setFillColor(sf::Color::Yellow);
        else if (lives == 1) shape.setFillColor(sf::Color::Green);
    }

    int getHP() const { return lives; }
};