#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

/**
 * @class AnimationHandler
 * @brief Klasa obslugujaca animacje
 */
class AnimationHandler {
private:
    /**
     * @struct Animation
     * @brief Struktura reprezentujaca animacje
     */
    struct Animation {
        std::vector<sf::Texture> frames; /**< Wektor klatek animacji */
        unsigned int currentFrame; /**< Numer aktualnej klatki */
        sf::Clock clock; /**< Zegar animacji */
        sf::Time frameTime; /**< Czas trwania jednej klatki */
        bool isPlaying; /**< Flaga wskazujaca, czy animacja jest odtwarzana */
        bool wasUpdated; /**< Flaga wskazujaca, czy animacja zostala zaktualizowana */
    };

    std::vector<Animation> animations; /**< Wektor przechowujacy animacje */

public:
    /**
     * @brief Konstruktor klasy AnimationHandler
     */
    AnimationHandler();

    /**
     * @brief Funkcja zwracajaca liczbe animacji przechowywanych w obiekcie AnimationHandler
     * @return Liczba animacji
     */
    size_t getNumAnimations() const {
        return animations.size();
    }

    /**
     * @brief Metoda dodajaca nowa animacje
     * @param frames Wektor tekstur reprezentujacych klatki animacji
     */
    void addAnimation(const std::vector<sf::Texture>& frames);

    /**
     * @brief Metoda rozpoczynajaca odtwarzanie animacji
     * @param animationIndex Indeks animacji do odtworzenia
     * @param frameTime Czas trwania jednej klatki animacji
     */
    void play(unsigned int animationIndex, sf::Time frameTime = sf::seconds(0.1));

    /**
     * @brief Metoda pauzujaca odtwarzanie animacji
     * @param animationIndex Indeks animacji do zatrzymania
     */
    void pause(unsigned int animationIndex);

    /**
     * @brief Metoda zatrzymujaca odtwarzanie animacji
     * @param animationIndex Indeks animacji do zatrzymania
     */
    void stop(unsigned int animationIndex);

    /**
     * @brief Metoda aktualizujaca stan animacji
     * @param animationIndex Indeks animacji do zaktualizowania
     */
    void update(unsigned int animationIndex);

    /**
     * @brief Metoda rysujaca animacje na oknie renderowania
     * @param window Referencja do okna renderowania
     * @param animationIndex Indeks animacji do narysowania
     * @param x Wspolrzedna X pozycji animacji
     * @param y Wspolrzedna Y pozycji animacji
     */
    void draw(sf::RenderWindow& window, unsigned int animationIndex, float x, float y);

    /**
     * @brief Metoda zwracajaca informacje o aktualizacji animacji
     * @param animationIndex Indeks animacji
     * @return Wartosc logiczna wskazujaca, czy animacja zostala zaktualizowana
     */
    bool getWasUpdated(unsigned int animationIndex);
};