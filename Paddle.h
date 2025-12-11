
#pragma once
#include <SFML/Graphics.hpp>

class Paddle {
public:
    sf::RectangleShape shape;
    float speed = 6.f;

    Paddle() {
        shape.setSize({ 120.f, 20.f });
        shape.setFillColor(sf::Color::White);
        shape.setPosition(340.f, 550.f);
    }

    void update() {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            shape.move(-speed, 0);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            shape.move(speed, 0);

        if (shape.getPosition().x < 0)
            shape.setPosition(0, shape.getPosition().y);

        if (shape.getPosition().x + shape.getSize().x > 800)
            shape.setPosition(800 - shape.getSize().x, shape.getPosition().y);
    }
}; 
