#pragma once
#include "Point2D.h"

/**
 * @class Bullet
 * @brief Klasa reprezentujaca pocisk
 */
class Bullet : public Point2D
{
private:
	sf::Vector2f direction; /**< wektor kierunku w ktorym porusza sie pocisk */
	float speed; /**< szybkosc poruszania sie pocisku */

public:
    /**
     * @brief konstruktor klasy Bullet
     * @param x wspolrzedna X poczatkowa pozycja pocisku
     * @param y wspolrzedna Y poczatkowa pozycja pocisku
     * @param dir wektor kierunku w ktorym porusza sie pocisk
     * @param spd szybkosc poruszania sie pocisku
     */
	Bullet(float x, float y, sf::Vector2f dir, float spd) : Point2D(x, y), direction(dir), speed(spd) {};

    /**
     * @brief metoda aktualizujaca pozycje pocisku na podstawie jego predkosci i kierunku
     */
	void update();
};
