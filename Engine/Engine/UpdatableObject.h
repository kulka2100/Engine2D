#pragma once
#include "GameObject.h"

/**
 * @brief klasa reprezentujaca aktualizujacy sie obiekt ksztaltu, dziedziczaca po GameObject
 */
class UpdatableObject :
    public GameObject
{
public:
    /**
     * @brief konstruktor domyœlny
     */
    UpdatableObject();
    /**
     * @brief destruktor wirtualny
     */
    virtual ~UpdatableObject();

    /**
     * @brief metoda do aktualizacji obiektu
     */
    virtual void update() = 0;
};

