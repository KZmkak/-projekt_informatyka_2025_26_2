#include "Ranking.h"
#include <iostream>

Ranking::Ranking(float width, float height) {
    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
       
    }

    titleText.setFont(font);
    titleText.setString("TOP 10 NAJLEPSZYCH WYNIKOW");
    titleText.setCharacterSize(40);
    titleText.setFillColor(sf::Color::Blue);
    titleText.setOrigin(titleText.getLocalBounds().width / 2.0f, 0);
    titleText.setPosition(width / 2.0f, 20.f);

    instructionsText.setFont(font);
    instructionsText.setString("(Wcisnij ESCAPE, aby wrocic do menu)");
    instructionsText.setCharacterSize(20);
    instructionsText.setFillColor(sf::Color::White);
    instructionsText.setOrigin(instructionsText.getLocalBounds().width / 2.0f, 0);
    instructionsText.setPosition(width / 2.0f, height - 40.f);

    loadScores();
    updateDisplay(width, height);
}

void Ranking::loadScores() {
    scores.clear();
    std::ifstream file(filename);
    std::string name;
    int score;

    while (file >> name >> score) {
        scores.emplace_back(name, score);
    }

    
    std::sort(scores.begin(), scores.end(), [](const ScoreEntry& a, const ScoreEntry& b) {
        return a.score > b.score;
        });

    if (scores.size() > maxScores) {
        scores.resize(maxScores);
    }
}

void Ranking::saveScores() {
    std::ofstream file(filename);
    for (const auto& entry : scores) {
        file << entry.name << " " << entry.score << "\n";
    }
}

void Ranking::addScore(const std::string& name, int score) {
    scores.emplace_back(name, score);

    std::sort(scores.begin(), scores.end(), [](const ScoreEntry& a, const ScoreEntry& b) {
        return a.score > b.score;
        });

    if (scores.size() > maxScores) {
        scores.resize(maxScores);
    }

    saveScores();
    updateDisplay(800, 600); 
}

void Ranking::updateDisplay(float width, float height) {
    scoreTexts.clear();

    for (size_t i = 0; i < scores.size(); ++i) {
        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(30);

        std::string scoreStr = std::to_string(scores[i].score);
        std::string rankStr = std::to_string(i + 1) + ".";

       
        std::string line = rankStr + "\t\t" + scores[i].name + "\t\t" + scoreStr;
        text.setString(line);

        text.setFillColor(i == 0 ? sf::Color::Yellow : sf::Color::White); 
        text.setPosition(width / 2.0f - 150.f, 100.f + i * 40.f);
        scoreTexts.push_back(text);
    }
}

void Ranking::draw(sf::RenderWindow& window) {
    window.draw(titleText);
    for (const auto& text : scoreTexts) {
        window.draw(text);
    }
    window.draw(instructionsText);
}