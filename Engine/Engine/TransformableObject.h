#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>

/**
 * @brief klasa reprezentujaca transormowalny obiekt ksztaltu, dziedziczaca po GameObject
 */
class TransformableObject :
    public GameObject
{
public:
    /**
      * @brief konstruktor domyslny
      */
    TransformableObject();

    /**
     * @brief destruktor wirtualny
     */
    virtual ~TransformableObject();

    /**
     * @brief metoda do przesuniecia obiektu
     * @param x przesuniecie wzgledem osi X
     * @param y przesuniecie wzgledem osi Y
     */
    virtual void translate(float x, float y) = 0;

    /**
     * @brief metoda do obrotu obiektu wzgledem srodka ekranu
     * @param angle kat obrotu w stopniach
     */
    virtual void rotate(float angle) = 0;

    /**
     * @brief metoda do skalowania obiektu wzgledem srodka ekranu
     * @param factor wspolczynnik skalowania
     */
    virtual void scale(float factor) = 0;
};

