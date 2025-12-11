#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class HighscoreInput {
public:
    HighscoreInput(float width, float height);
    void handleInput(sf::Event event);
    void draw(sf::RenderWindow& window);

    
    std::string getNickname() const { return currentNickname; }

    
    void reset() { currentNickname = ""; }

private:
    sf::Font font;
    sf::Text promptText;
    sf::Text inputField;
    std::string currentNickname;
};
