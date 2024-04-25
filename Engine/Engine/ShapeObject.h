#pragma once
#include "DrawableObject.h"
#include "TransformableObject.h"
#include <SFML/Graphics.hpp>

/**
 * @brief klasa reprezentujaca obiekt ksztaltu, dziedziczaca po DrawableObject i TransformableObject
 */
class ShapeObject : public DrawableObject, public TransformableObject {
protected:
    sf::Vector2f position; /**< Pozycja obiektu */

public:
    /**
      * @brief konstruktor domyslny
      */
    ShapeObject() : DrawableObject(), TransformableObject(), position(0.0f, 0.0f) {}

    /**
     * @brief konstruktor z ustawieniem pozycji
     * @param x wspolrzedna X pozycji obiektu
     * @param y wspolrzedna Y pozycji obiektu
     */
    ShapeObject(float x, float y) : DrawableObject(), TransformableObject(), position(x, y) {}

    /**
     * @brief destruktor wirtualny
     */
    virtual ~ShapeObject() {};

    /**
     * @brief metoda abstrakcyjna do rysowania obiektu
     * @param window okno renderowania
     * @param color kolor rysowanego obiektu
     */
    virtual void draw(sf::RenderWindow& window, sf::Color color) = 0;
    
    /**
     * @brief metoda do przesuniecia obiektu
     * @param x przesuniecie wzgledem osi X
     * @param y przesuniecie wzgledem osi Y
     */
    virtual void translate(float x, float y) override;

    /**
     * @brief metoda do obrotu obiektu wzgledem srodka ekranu
     * @param angle kat obrotu w stopniach
     */
    virtual void rotate(float angle) override;

    /**
     * @brief metoda do skalowania obiektu wzgledem srodka ekranu
     * @param factor wspolczynnik skalowania
     */
    virtual void scale(float factor) override;
};

