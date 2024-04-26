#include "AnimationHandler.h"
#include <iostream>

// Konstruktor domy�lny klasy AnimationHandler
AnimationHandler::AnimationHandler() {}

// Metoda dodaj�ca now� animacj� do obs�ugi
void AnimationHandler::addAnimation(const std::vector<sf::Texture>& frames) {
    // Tworzenie nowego obiektu Animation
    Animation animation;
    // Przypisanie wektorowi klatek nowej animacji
    animation.frames = frames;
    // Ustawienie bie��cej klatki na 0
    animation.currentFrame = 0;
    // Ustawienie czasu trwania klatki na 0.1 sekundy
    animation.frameTime = sf::seconds(0.1);
    // Ustawienie flagi odtwarzania na false (animacja nie jest odtwarzana)
    animation.isPlaying = false;
    // Ustawienie flagi aktualizacji na true
    animation.wasUpdated = true;
    // Dodanie animacji do wektora animacji
    animations.push_back(animation);
}

// Metoda rozpoczynaj�ca odtwarzanie animacji o podanym indeksie
void AnimationHandler::play(unsigned int animationIndex, sf::Time frameTime) {
    // Sprawdzenie, czy indeks animacji mie�ci si� w zakresie wektora animacji
    if (animationIndex >= animations.size()) return;
    // Ustawienie czasu trwania klatki animacji
    animations[animationIndex].frameTime = frameTime;
    // Ustawienie bie��cej klatki na pocz�tek
    animations[animationIndex].currentFrame = 0;
    // Ustawienie flagi odtwarzania na true
    animations[animationIndex].isPlaying = true;
    // Uruchomienie zegara dla animacji
    animations[animationIndex].clock.restart();
    // Wy�wietlenie komunikatu o rozpocz�ciu odtwarzania animacji oraz czasie startu
    std::cout << "Rozpocz�to odtwarzanie animacji. Czas startu: " << animations[animationIndex].clock.getElapsedTime().asSeconds() << std::endl;
}

// Metoda pauzuj�ca odtwarzanie animacji o podanym indeksie
void AnimationHandler::pause(unsigned int animationIndex) {
    // Sprawdzenie, czy indeks animacji mie�ci si� w zakresie wektora animacji
    if (animationIndex >= animations.size()) return;
    // Ustawienie flagi odtwarzania na false
    animations[animationIndex].isPlaying = false;
}

// Metoda zatrzymuj�ca odtwarzanie animacji o podanym indeksie
void AnimationHandler::stop(unsigned int animationIndex) {
    // Sprawdzenie, czy indeks animacji mie�ci si� w zakresie wektora animacji
    if (animationIndex >= animations.size()) return;
    // Zresetowanie bie��cej klatki na pocz�tek
    animations[animationIndex].currentFrame = 0;
    // Ustawienie flagi odtwarzania na false
    animations[animationIndex].isPlaying = false;
    // Ustawienie flagi aktualizacji na true
    animations[animationIndex].wasUpdated = true;
}

// Metoda aktualizuj�ca stan animacji o podanym indeksie
void AnimationHandler::update(unsigned int animationIndex) {
    // Sprawdzenie, czy indeks animacji mie�ci si� w zakresie wektora animacji
    if (animationIndex >= animations.size()) {
        // Ustawienie flagi aktualizacji na false
        animations[animationIndex].wasUpdated = false;
        return;
    }

    // Pobranie referencji do animacji o podanym indeksie
    Animation& animation = animations[animationIndex];
    // Sprawdzenie warunk�w potrzebnych do aktualizacji animacji
    if (!animation.isPlaying || animation.frames.empty()) {
        // Wy�wietlenie komunikatu o braku klatek animacji
        std::cout << "Aktualizacja brak klatek" << std::endl;
        // Ustawienie flagi aktualizacji na false
        animation.wasUpdated = false;
        return;
    }

    // Sprawdzenie, czy up�yn�� czas trwania klatki animacji
    if (animation.clock.getElapsedTime() >= animation.frameTime) {
        // Zresetowanie zegara animacji
        animation.clock.restart();
        // Sprawdzenie, czy bie��ca klatka nie jest ostatni� klatk� animacji
        if (animation.currentFrame < ((animation.frames.size()) - 1)) {
            // Przej�cie do nast�pnej klatki animacji
            animation.currentFrame = animation.currentFrame + 1;
            // Ustawienie flagi aktualizacji na false
            animation.wasUpdated = false;
        }
        else {
            // Powr�t do pierwszej klatki animacji
            animation.currentFrame = 0;
            // Ustawienie flagi aktualizacji na true
            animation.wasUpdated = true;
        }
    }
    else {
        // Ustawienie flagi aktualizacji na false
        animation.wasUpdated = false;
    }
}

// Metoda rysuj�ca bie��c� klatk� animacji o podanym indeksie
void AnimationHandler::draw(sf::RenderWindow& window, unsigned int animationIndex, float x, float y) {
    // Sprawdzenie, czy indeks animacji mie�ci si� w zakresie wektora animacji
    if (animationIndex >= animations.size()) return;
    // Pobranie referencji do animacji o podanym indeksie
    Animation& animation = animations[animationIndex];
    // Sprawdzenie, czy wektor klatek animacji nie jest pusty
    if (animation.frames.empty()) return;

    // Utworzenie sprite'a na podstawie bie��cej klatki animacji
    sf::Sprite sprite(animation.frames[animation.currentFrame]);
    // Ustawienie pozycji sprite'a na podanych wsp�rz�dnych
    sprite.setPosition(x, y);
    // Narysowanie sprite'a na oknie
    window.draw(sprite);

    // Wy�wietlenie komunikatu o rysowaniu bie��cej klatki animacji
    //std::cout << "Rysowanie klatki animacji. Bie��ca klatka: " << animation.currentFrame << "Ilosc wszytskich klatek:" << animation.frames.size() << std::endl;
}

// Metoda zwracaj�ca informacj�, czy animacja o podanym indeksie zosta�a zaktualizowana
bool AnimationHandler::getWasUpdated(unsigned int animationIndex) {
    return animations[animationIndex].wasUpdated;
}