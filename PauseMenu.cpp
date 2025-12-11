#include "PauseMenu.h"

PauseMenu::PauseMenu(float width, float height) {
    
    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
        
    }

    pausedText.setFont(font);
    pausedText.setString("PAUZA\n(Wcisnij SPACES, aby wznowic\nWcisnij ESCAPE, aby wrocic do menu)");
    pausedText.setCharacterSize(30);
    pausedText.setFillColor(sf::Color::White);

 
    sf::FloatRect textRect = pausedText.getLocalBounds();
    pausedText.setOrigin(textRect.left + textRect.width / 2.0f,
        textRect.top + textRect.height / 2.0f);
    pausedText.setPosition(width / 2.0f, height / 2.0f);
}

void PauseMenu::draw(sf::RenderWindow& window) {
    window.draw(pausedText);
}