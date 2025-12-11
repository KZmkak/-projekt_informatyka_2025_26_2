#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Game.h"
#include "PauseMenu.h"
#include "Ranking.h"       
#include "HighscoreInput.h" 
#include <iostream>


enum class GameState {
    Menu,
    Playing,
    Paused,
    HighscoreInput, 
    Ranking,        
    Exiting
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Arkanoid with Menu and Ranking");
    window.setFramerateLimit(60);

    Menu menu(window.getSize().x, window.getSize().y);
    PauseMenu pauseMenu(window.getSize().x, window.getSize().y);
    Ranking ranking(window.getSize().x, window.getSize().y);
    HighscoreInput highscoreInput(window.getSize().x, window.getSize().y);

    Game game;
    GameState currentState = GameState::Menu;
    int finalScore = 0; 

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Time dt = clock.restart();
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                currentState = GameState::Exiting;
                window.close();
            }

           
            else if (currentState == GameState::Menu) {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Up) menu.MoveUp();
                    else if (event.key.code == sf::Keyboard::Down) menu.MoveDown();
                    else if (event.key.code == sf::Keyboard::Enter) {
                        if (menu.getSelectedItem() == 0) {
                            game.reset();
                            currentState = GameState::Playing;
                        }
                        else if (menu.getSelectedItem() == 1) {
                            ranking.loadScores(); 
                            currentState = GameState::Ranking;
                        }
                        else if (menu.getSelectedItem() == 2) {
                            currentState = GameState::Exiting;
                            window.close();
                        }
                    }
                }
            }

            
            else if (currentState == GameState::Paused) {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Space)
                        currentState = GameState::Playing; 
                    else if (event.key.code == sf::Keyboard::Escape)
                        currentState = GameState::Menu; 
                }
            }

            
            else if (currentState == GameState::Ranking) {
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                    currentState = GameState::Menu;
                }
            }

          
            else if (currentState == GameState::HighscoreInput) {
                highscoreInput.handleInput(event);
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                    std::string nick = highscoreInput.getNickname();
                    if (nick.empty()) nick = "Anonim";

                    ranking.addScore(nick, finalScore);
                    highscoreInput.reset();
                    currentState = GameState::Ranking; 
                }
            }

            
            else if (currentState == GameState::Playing) {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Space) {
                        currentState = GameState::Paused;
                    }
                    else if (event.key.code == sf::Keyboard::Escape) {
                        currentState = GameState::Menu;
                    }
                    
                }
            }
        } 


        

        if (currentState == GameState::Playing) {
            game.update(dt);

           
            if (game.getBall().velocity.y == -999.f) {
                finalScore = game.getScore();
                currentState = GameState::HighscoreInput;
            }
        }


       
        window.clear(sf::Color::Black);

        if (currentState == GameState::Menu) {
            menu.draw(window);
        }
        else if (currentState == GameState::Playing || currentState == GameState::Paused) {
            game.render(window);
            if (currentState == GameState::Paused) {
                pauseMenu.draw(window);
            }
        }
        else if (currentState == GameState::HighscoreInput) {
            
            game.render(window);
            highscoreInput.draw(window);
        }
        else if (currentState == GameState::Ranking) {
            ranking.draw(window);
        }

        window.display();
    }

    return 0;
}
