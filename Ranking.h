#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include "ScoreEntry.h"

class Ranking {
public:
    Ranking(float width, float height);
    void draw(sf::RenderWindow& window);
    void loadScores();
    void saveScores();
    void addScore(const std::string& name, int score);

private:
    std::vector<ScoreEntry> scores;
    sf::Font font;
    sf::Text titleText;
    sf::Text instructionsText;
    std::vector<sf::Text> scoreTexts;
    const std::string filename = "ranking.dat";
    const int maxScores = 10;

    void updateDisplay(float width, float height);
};
