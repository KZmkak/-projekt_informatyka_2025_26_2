#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Paddle.h"
#include "Ball.h"
#include "Brick_2.h"
#include "BlockData.h"

class GameState {
public:
    
    sf::Vector2f paddlePosition;
    sf::Vector2f ballPosition;
    sf::Vector2f ballVelocity;
    std::vector<BlockData> blocks;

    GameState() = default;

    
    void capture(const Paddle& paddle, const Ball& ball, const std::vector<Brick>& bricks) {
        paddlePosition = paddle.shape.getPosition();
        ballPosition = ball.shape.getPosition();
        ballVelocity = ball.velocity;

        blocks.clear();
        blocks.reserve(bricks.size());

        for (const auto& b : bricks) {
            if (!b.destroyed) {
                BlockData data;
                data.x = b.shape.getPosition().x;
                data.y = b.shape.getPosition().y;
                data.hp = b.getHP();

                blocks.push_back(data);
            }
        }
    }
};
