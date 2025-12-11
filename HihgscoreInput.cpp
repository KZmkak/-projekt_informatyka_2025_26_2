#include "HighscoreInput.h"
#include <iostream>

HighscoreInput::HighscoreInput(float width, float height) {
    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
       
    }

    promptText.setFont(font);
    promptText.setString("NOWY REKORD!\nWprowadz swoj nick (ENTER, aby potwierdzic):");
    promptText.setCharacterSize(30);
    promptText.setFillColor(sf::Color::White);
    promptText.setOrigin(promptText.getLocalBounds().width / 2.0f, promptText.getLocalBounds().height / 2.0f);
    promptText.setPosition(width / 2.0f, height / 2.0f - 50.f);

    inputField.setFont(font);
    inputField.setCharacterSize(40);
    inputField.setFillColor(sf::Color::Yellow);
    inputField.setPosition(width / 2.0f - 50.f, height / 2.0f + 50.f);
}

void HighscoreInput::handleInput(sf::Event event) {
    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode < 128) { 
            char enteredChar = static_cast<char>(event.text.unicode);
            if (enteredChar == 8) { 
                if (!currentNickname.empty()) {
                    currentNickname.pop_back();
                }
            }
            else if (enteredChar >= 32 && currentNickname.length() < 10) { 
                currentNickname += enteredChar;
            }
        }
    }
}

void HighscoreInput::draw(sf::RenderWindow& window) {
    inputField.setString(currentNickname + "_"); 
    window.draw(promptText);
    window.draw(inputField);
}