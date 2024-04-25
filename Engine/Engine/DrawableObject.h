#pragma once
#include "GameObject.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Color.hpp>

/**
 * @class DrawableObject
 * @brief Klasa bazowa reprezentujaca obiekt ktory bedziemy rysowac
 */
class DrawableObject :
    public GameObject
{
public:
    /**
     * @brief konstruktor klasy DrawableObject
     */
    DrawableObject();

    /**
     * @brief wirtualny destruktor klasy DrawableObject
     */
    virtual ~DrawableObject();

    /**
     * @brief metoda rysujaca obiekt w oknie renderowania
     * @param window Referencja do okna renderowania
     * @param color kolor w jakim ma zostac narysowany obiekt
     */
    virtual void draw(sf::RenderWindow& window, sf::Color color) = 0;
};

