#pragma once
#include <SFML/Graphics.hpp>
#include <array>

class Brick : public sf::RectangleShape {
	private:
		int hp;
		bool isDestroy;
		static const std::array<sf::Color, 4> colorLUT;
		
	public:
		Brick(sf::Vector2f startPo, sf::Vector2f rozmiar, int L);
		void nColor();
		void hit();
		void draw(sf::RenderTarget& window);
		
};


Brick::Brick(sf::Vector2f startPo, sf::Vector2f rozmiar, int L) {
	hp = L;
	isDestroy = false;
	this->setFillColor(sf::Color::Yellow);
	this->setOutlineColor(sf::Color::White);


}

const std::array<sf::Color, 4> Brick::colorLUT = {
	sf::Color::Transparent,
	sf::Color::Yellow,
	sf::Color::Magenta,
	sf::Color::Red,
};

void Brick::hit() {
	if (isDestroy == true)
		return;
	hp--;
	nColor();
	if (hp <= 0)
		isDestroy = true;
}

void Brick::nColor() {
	if(hp>=0 && hp<=3)
	this->setFillColor(colorLUT[hp]);
}

void Brick::draw(sf::RenderTarget& window) {
	window.draw(*this);
}