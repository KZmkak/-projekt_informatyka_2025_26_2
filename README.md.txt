 Opis Działania Gry 

1. Struktura i Klasy 
Głównemain.cpp: Główny plik programu. 
Zawiera pętlę gry, obsługę zdarzeń i zarządzanie stanami gry (GameState).
Game.h / Game.cpp: Klasa zarządzająca logiką samej rozgrywki. 
Zawiera obiekty paletki (Paddle), piłki (Ball) i wektor bloków (Brick). 
Odpowiada za aktualizację ruchu, kolizji oraz renderowanie obiektów gry.
Menu.h / Menu.cpp: Klasa odpowiedzialna za wyświetlanie i nawigację po menu głównym.
Paddle.h: Klasa reprezentująca paletkę sterowaną przez gracza.Ball.h: Klasa reprezentująca piłkę.
Brick_2.h (klasa Brick): Klasa reprezentująca pojedynczy blok, w który gracz musi uderzyć piłką.
Posiada system żyć (lives) i zmienia kolor po uderzeniu.

2. Stany Gry (Game States)
Gra operuje na kilku stanach zarządzanych przez enum class GameState w main.cpp:StanOpisObsługa Zdarzeń/LogikaMenuStan menu głównego.
Umożliwia wybór "Nowa gra" (przejście do Playing) lub "Wyjście" (zamknięcie okna).
Nawigacja klawiszami strzałek (Up, Down), akceptacja (Enter).
PlayingAktywna rozgrywka.Umożliwia ruch paletki, aktualizację piłki i kolizji z blokami.
Możliwość pauzy (Space) lub powrotu do menu (Escape).
PausedGra jest wstrzymana.Wyświetla napis "PAUZA". 
Czeka na naciśnięcie spacji, aby wznowić (Playing).
ExitingStan zamknięcia gry.Zamyka okno gry.

3. Logika Gry 
(Game.cpp)Inicjalizacja: W konstruktorze Game::Game() tworzone są bloki (8 kolumn x 4 rzędy).
Aktualizacja (update):Aktualizuje pozycję paletki i piłki.
Koniec gry (tymczasowy): Jeśli piłka spadnie poniżej dolnej krawędzi (y >= 600), jej prędkość zostaje wyzerowana (zatrzymanie).
Kolizja z paletką: Jeśli piłka uderzy w paletkę, wektor pionowy prędkości jest odwracany (velocity.y = -velocity.y).
Piłka jest natychmiastowo przesuwana na krawędź paletki, aby zapobiec ugrzęźnięciu.Kolizja z blokami: Sprawdzane są kolizje piłki z każdym niezniszczonym blokiem.
Po kolizji:Wywoływana jest metoda blok.hit() (zmniejszenie żyć, zmiana koloru lub zniszczenie bloku).
Wektor pionowy prędkości piłki jest odwracany.Usuwanie zniszczonych bloków: Bloki oznaczone jako destroyed są usuwane z wektora za pomocą std::remove_if i erase.

4. Piłka (Ball.h)
Piłka startuje ze środka ekranu.
Ruch: shape.move(velocity).Kolizje ze ścianami:Odbicie od bocznych ścian: Jeśli piłka uderzy w lewą (x < 0) lub prawą (x + 2*radius > 800) krawędź,
wektor $x$ prędkości jest odwracany (velocity.x = -velocity.x).
Odbicie od górnej ściany: Jeśli piłka uderzy w górną krawędź (y < 0), wektor $y$ prędkości jest odwracany.

5. Bloki (Brick_2.h)
Każdy blok ma 3 życia (lives).
Kolory: Kolor bloku odzwierciedla jego pozostałe życia:3 życia: Czerwony (sf::Color::Red)2 życia: Żółty (sf::Color::Yellow)1 życie: Zielony (sf::Color::Green)
Metoda hit() zmniejsza liczbę żyć i aktualizuje kolor.
Jeśli życia spadną do 0, flaga destroyed jest ustawiana na true.

6. Zapis Stanu Gry (Snapshot)
Klasa GameSnapshot służy do przechwytywania bieżącego stanu gry.
Metoda capture() zapisuje:Pozycję paletki (paddlePosition).
Pozycję i prędkość piłki (ballPosition, ballVelocity).
Pozycję i pozostałe życia (hp) niezniszczonych bloków.
W main.cpp, naciśnięcie klawisza P w stanie Playing tworzy i zapisuje ten stan (wypisując komunikat do konsoli),
wykorzystując klasę GameSnapshot.

7. Renderowanie
W pętli gry, rysowanie obiektów zależy od stanu:Menu: Rysuje tylko menu.
Playing: Rysuje paletkę, piłkę i wszystkie niezniszczone bloki.
Paused: Rysuje obiekty gry (jak w Playing), a następnie nakłada na to napis "PAUZA".
