#include "Menu.h"

Menu::Menu(float width, float height) {
    font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    selectedItemIndex = 0;

    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::Blue);
    menu[0].setString("Nowa gra");
    menu[0].setCharacterSize(60);
    menu[0].setPosition(width / 2.f - 100.f, height / 2.f - 50.f);

   
    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::White);
    menu[1].setString("Ranking");
    menu[1].setCharacterSize(60);
    menu[1].setPosition(width / 2.f - 100.f, height / 2.f + 10.f); 

    
    menu[2].setFont(font);
    menu[2].setFillColor(sf::Color::White);
    menu[2].setString("Wyjscie");
    menu[2].setCharacterSize(60);
    menu[2].setPosition(width / 2.f - 100.f, height / 2.f + 70.f);
}

void Menu::draw(sf::RenderWindow& window) {
    for (const auto& item : menu)
        window.draw(item);
}

void Menu::MoveUp() {
    if (selectedItemIndex > 0) {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        menu[selectedItemIndex].setFillColor(sf::Color::Blue);
    }
}

void Menu::MoveDown() {
    if (selectedItemIndex < MAX_ITEMS - 1) {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menu[selectedItemIndex].setFillColor(sf::Color::Blue);
    }
}

