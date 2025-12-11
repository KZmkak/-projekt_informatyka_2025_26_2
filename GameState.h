#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "BlockData.h"
#include "Paddle.h"
#include "Ball.h"
#include "Brick_2.h"

class GameSnapshot {
public:
    sf::Vector2f paddlePosition;
    sf::Vector2f ballPosition;
    sf::Vector2f ballVelocity;
    std::vector<BlockData> blocks;

    GameSnapshot() = default;

    void capture(const Paddle& paddle, const Ball& ball, const std::vector<Brick>& bricks) {
        paddlePosition = paddle.shape.getPosition();
        ballPosition = ball.shape.getPosition();
        ballVelocity = ball.velocity;

        blocks.clear();
        blocks.reserve(bricks.size());

        for (const auto& b : bricks) {
            if (!b.destroyed) {
                BlockData d;
                d.x = b.shape.getPosition().x;
                d.y = b.shape.getPosition().y;
                d.hp = b.getHP();
                blocks.push_back(d);
            }
        }
    }
};

