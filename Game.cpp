#include "Game.h"
#include <algorithm>
#include <cmath>
#include <iostream>


void resolveCollision(Ball& ball, Brick& brick) {
    sf::FloatRect ballBounds = ball.shape.getGlobalBounds();
    sf::FloatRect brickBounds = brick.shape.getGlobalBounds();

    float dx = (ballBounds.left + ballBounds.width / 2.f) - (brickBounds.left + brickBounds.width / 2.f);
    float dy = (ballBounds.top + ballBounds.height / 2.f) - (brickBounds.top + brickBounds.height / 2.f);

    float overlapX = (ballBounds.width / 2.f + brickBounds.width / 2.f) - std::abs(dx);
    float overlapY = (ballBounds.height / 2.f + brickBounds.height / 2.f) - std::abs(dy);

    if (overlapX < overlapY) {
        ball.velocity.x = -ball.velocity.x;
        if (dx > 0) {
            ball.shape.setPosition(brickBounds.left + brickBounds.width + 1.f, ball.shape.getPosition().y);
        }
        else {
            ball.shape.setPosition(brickBounds.left - ballBounds.width - 1.f, ball.shape.getPosition().y);
        }

    }
    else {
        ball.velocity.y = -ball.velocity.y;
        if (dy > 0) {
            ball.shape.setPosition(ball.shape.getPosition().x, brickBounds.top + brickBounds.height + 1.f);
        }
        else {
            ball.shape.setPosition(ball.shape.getPosition().x, brickBounds.top - ballBounds.height - 1.f);
        }
    }
}


void Game::setupScoreText() {
    if (!m_font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
    }
    m_scoreText.setFont(m_font);
    m_scoreText.setCharacterSize(24);
    m_scoreText.setFillColor(sf::Color::White);
    m_scoreText.setPosition(10.f, 10.f); 
}

void Game::accelerateBall() {
    m_pilka.accelerate(0.5f);
    m_speedThreshold += 100;
}

Game::Game() {
    setupScoreText();
    createLevel();
}

void Game::reset() {
    m_paletka = Paddle();
    m_pilka = Ball();
    m_score = 0;              
    m_speedThreshold = 100;   
    createLevel();
}

void Game::createLevel() {
    m_bloki.clear();
    const float brickWidth = 70.f;
    const float brickHeight = 30.f;
    const float screenWidth = 800.f;
    const int maxCols = 10;
    const float startY = 50.f;

    for (int row = 0; row < 5; ++row) {
        int numCols = maxCols - (row * 2);
        if (numCols <= 0) break;

        float totalRowWidth = numCols * brickWidth;
        float startX = (screenWidth - totalRowWidth) / 2.f;

        for (int col = 0; col < numCols; ++col) {
            m_bloki.emplace_back(
                startX + col * brickWidth,
                startY + row * brickHeight,
                brickWidth,
                brickHeight
            );
        }
    }
}

void Game::update(sf::Time dt) {
    m_paletka.update();
    m_pilka.update();

    if (m_pilka.shape.getPosition().y + m_pilka.shape.getRadius() * 2 >= 600) {
        m_pilka.velocity = { 0.f, -999.f }; 
        return; 
    }
    if (m_pilka.shape.getGlobalBounds().intersects(m_paletka.shape.getGlobalBounds())) {
        m_pilka.velocity.y = -std::abs(m_pilka.velocity.y);
        m_pilka.shape.setPosition(
            m_pilka.shape.getPosition().x,
            m_paletka.shape.getPosition().y - m_pilka.shape.getRadius() * 2
        );
    }

    for (auto& blok : m_bloki) {
        if (!blok.destroyed) {
            if (m_pilka.shape.getGlobalBounds().intersects(blok.shape.getGlobalBounds())) {

                int initialHP = blok.getHP();

                blok.hit();
                resolveCollision(m_pilka, blok);

                if (blok.destroyed) {
                    m_score += 20; 
                }
                else if (initialHP > blok.getHP()) {
                    m_score += 10; 
                }

                break; 
            }
        }
    }

    if (m_score >= m_speedThreshold) {
        accelerateBall();
        std::cout << "Pilka przyspieszona! Nowy prog: " << m_speedThreshold << " Nowa predkosc: "
            << m_pilka.velocity.x << ", " << m_pilka.velocity.y << std::endl;
    }

    m_bloki.erase(
        std::remove_if(m_bloki.begin(), m_bloki.end(),
            [](const Brick& b) { return b.destroyed; }),
        m_bloki.end()
    );
}

void Game::render(sf::RenderTarget& target) {
    target.draw(m_pilka.shape);
    target.draw(m_paletka.shape);

    for (auto& blok : m_bloki)
        if (!blok.destroyed)
            target.draw(blok.shape);

    m_scoreText.setString("Punkty: " + std::to_string(m_score));
    target.draw(m_scoreText);
}