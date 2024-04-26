#include "AnimationHandler.h"
#include <iostream>

// Konstruktor domyœlny klasy AnimationHandler
AnimationHandler::AnimationHandler() {}

// Metoda dodaj¹ca now¹ animacjê do obs³ugi
void AnimationHandler::addAnimation(const std::vector<sf::Texture>& frames) {
    // Tworzenie nowego obiektu Animation
    Animation animation;
    // Przypisanie wektorowi klatek nowej animacji
    animation.frames = frames;
    // Ustawienie bie¿¹cej klatki na 0
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

// Metoda rozpoczynaj¹ca odtwarzanie animacji o podanym indeksie
void AnimationHandler::play(unsigned int animationIndex, sf::Time frameTime) {
    // Sprawdzenie, czy indeks animacji mieœci siê w zakresie wektora animacji
    if (animationIndex >= animations.size()) return;
    // Ustawienie czasu trwania klatki animacji
    animations[animationIndex].frameTime = frameTime;
    // Ustawienie bie¿¹cej klatki na pocz¹tek
    animations[animationIndex].currentFrame = 0;
    // Ustawienie flagi odtwarzania na true
    animations[animationIndex].isPlaying = true;
    // Uruchomienie zegara dla animacji
    animations[animationIndex].clock.restart();
    // Wyœwietlenie komunikatu o rozpoczêciu odtwarzania animacji oraz czasie startu
    std::cout << "Rozpoczêto odtwarzanie animacji. Czas startu: " << animations[animationIndex].clock.getElapsedTime().asSeconds() << std::endl;
}

// Metoda pauzuj¹ca odtwarzanie animacji o podanym indeksie
void AnimationHandler::pause(unsigned int animationIndex) {
    // Sprawdzenie, czy indeks animacji mieœci siê w zakresie wektora animacji
    if (animationIndex >= animations.size()) return;
    // Ustawienie flagi odtwarzania na false
    animations[animationIndex].isPlaying = false;
}

// Metoda zatrzymuj¹ca odtwarzanie animacji o podanym indeksie
void AnimationHandler::stop(unsigned int animationIndex) {
    // Sprawdzenie, czy indeks animacji mieœci siê w zakresie wektora animacji
    if (animationIndex >= animations.size()) return;
    // Zresetowanie bie¿¹cej klatki na pocz¹tek
    animations[animationIndex].currentFrame = 0;
    // Ustawienie flagi odtwarzania na false
    animations[animationIndex].isPlaying = false;
    // Ustawienie flagi aktualizacji na true
    animations[animationIndex].wasUpdated = true;
}

// Metoda aktualizuj¹ca stan animacji o podanym indeksie
void AnimationHandler::update(unsigned int animationIndex) {
    // Sprawdzenie, czy indeks animacji mieœci siê w zakresie wektora animacji
    if (animationIndex >= animations.size()) {
        // Ustawienie flagi aktualizacji na false
        animations[animationIndex].wasUpdated = false;
        return;
    }

    // Pobranie referencji do animacji o podanym indeksie
    Animation& animation = animations[animationIndex];
    // Sprawdzenie warunków potrzebnych do aktualizacji animacji
    if (!animation.isPlaying || animation.frames.empty()) {
        // Wyœwietlenie komunikatu o braku klatek animacji
        std::cout << "Aktualizacja brak klatek" << std::endl;
        // Ustawienie flagi aktualizacji na false
        animation.wasUpdated = false;
        return;
    }

    // Sprawdzenie, czy up³yn¹³ czas trwania klatki animacji
    if (animation.clock.getElapsedTime() >= animation.frameTime) {
        // Zresetowanie zegara animacji
        animation.clock.restart();
        // Sprawdzenie, czy bie¿¹ca klatka nie jest ostatni¹ klatk¹ animacji
        if (animation.currentFrame < ((animation.frames.size()) - 1)) {
            // Przejœcie do nastêpnej klatki animacji
            animation.currentFrame = animation.currentFrame + 1;
            // Ustawienie flagi aktualizacji na false
            animation.wasUpdated = false;
        }
        else {
            // Powrót do pierwszej klatki animacji
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

// Metoda rysuj¹ca bie¿¹c¹ klatkê animacji o podanym indeksie
void AnimationHandler::draw(sf::RenderWindow& window, unsigned int animationIndex, float x, float y) {
    // Sprawdzenie, czy indeks animacji mieœci siê w zakresie wektora animacji
    if (animationIndex >= animations.size()) return;
    // Pobranie referencji do animacji o podanym indeksie
    Animation& animation = animations[animationIndex];
    // Sprawdzenie, czy wektor klatek animacji nie jest pusty
    if (animation.frames.empty()) return;

    // Utworzenie sprite'a na podstawie bie¿¹cej klatki animacji
    sf::Sprite sprite(animation.frames[animation.currentFrame]);
    // Ustawienie pozycji sprite'a na podanych wspó³rzêdnych
    sprite.setPosition(x, y);
    // Narysowanie sprite'a na oknie
    window.draw(sprite);

    // Wyœwietlenie komunikatu o rysowaniu bie¿¹cej klatki animacji
    //std::cout << "Rysowanie klatki animacji. Bie¿¹ca klatka: " << animation.currentFrame << "Ilosc wszytskich klatek:" << animation.frames.size() << std::endl;
}

// Metoda zwracaj¹ca informacjê, czy animacja o podanym indeksie zosta³a zaktualizowana
bool AnimationHandler::getWasUpdated(unsigned int animationIndex) {
    return animations[animationIndex].wasUpdated;
}