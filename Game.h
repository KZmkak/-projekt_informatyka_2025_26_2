#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Ball.h"
#include "Paddle.h"
#include "Brick_2.h" 

class Game {
public:
    Game();
    void update(sf::Time dt);
    void render(sf::RenderTarget& target);
    void reset();
    int getScore() const { return m_score; }
    
    const Paddle& getPaddle() const { return m_paletka; }
    const Ball& getBall() const { return m_pilka; }
    const std::vector<Brick>& getBlocks() const { return m_bloki; }

private:
    Paddle m_paletka;
    Ball m_pilka;
    std::vector<Brick> m_bloki;

   
    int m_score = 0;
    int m_speedThreshold = 100; 
    sf::Font m_font;
    sf::Text m_scoreText;


    void createLevel();
    void setupScoreText(); 
    void accelerateBall(); 
};