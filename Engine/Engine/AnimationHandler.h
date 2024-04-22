#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class AnimationHandler {
private:
    struct Animation {
        std::vector<sf::Texture> frames;
        unsigned int currentFrame;
        sf::Clock clock;
        sf::Time frameTime;
        bool isPlaying;
        bool wasUpdated;
    };

    std::vector<Animation> animations;

public:
    AnimationHandler();
    // Funkcja zwracaj¹ca liczbê animacji przechowywanych w obiekcie AnimationHandler
    size_t getNumAnimations() const {
        return animations.size();
    }
    void addAnimation(const std::vector<sf::Texture>& frames);
    void play(unsigned int animationIndex, sf::Time frameTime = sf::seconds(0.1));
    void pause(unsigned int animationIndex);
    void stop(unsigned int animationIndex);
    void update(unsigned int animationIndex);
    void draw(sf::RenderWindow& window, unsigned int animationIndex, float x, float y);
    bool getWasUpdated(unsigned int animationIndex);
};