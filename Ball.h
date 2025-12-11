#pragma once
#include <SFML/Graphics.hpp>
#include <cmath> 

class Ball {
public:
    sf::CircleShape shape;
    sf::Vector2f velocity;

    Ball(float radius = 10.f) {
        shape.setRadius(radius);
        shape.setFillColor(sf::Color::White);
        shape.setPosition(400, 300);
        velocity = { 4.f, 4.f };
    }

    void update() {
        shape.move(velocity);

        if (shape.getPosition().x < 0 ||
            shape.getPosition().x + shape.getRadius() * 2 > 800)
            velocity.x = -velocity.x;

        if (shape.getPosition().y < 0)
            velocity.y = -velocity.y;
    }

  
    void accelerate(float factor = 0.5f) {
        
        velocity.x = std::copysign(std::abs(velocity.x) + factor, velocity.x);
        velocity.y = std::copysign(std::abs(velocity.y) + factor, velocity.y);
    }
    
};