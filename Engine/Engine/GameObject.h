#pragma once

/**
 * @class GameObject
 * @brief klasa bazowa reprezentuj¹ca obiekt w grze
 */
class GameObject
{
public:
    /**
     * @brief konstruktor klasy GameObject
     */
    GameObject();

    /**
     * @brief wirtualny destruktor klasy GameObject
     */
    virtual ~GameObject();

    /**
     * @brief ustawia pozycje obiektu
     * @param x wspolrzedna X pozycji
     * @param y wspolrzedna Y pozycji
     */
    void setPosition(float x, float y);

    /**
     * @brief pobiera pozycje obiektu
     * @param x referencja do zmiennej przechowujacej wspolrzedna X pozycji
     * @param y referencja do zmiennej przechowujacej wspolrzedna Y pozycji
     */
    void getPosition(float& x, float& y) const;

    /**
     * @brief ustawia obrot obiektu
     * @param angle kat obrotu w stopniach
     */
    void setRotation(float angle);

    /**
     * @brief pobiera obrot obiektu
     * @return obrot obiektu w stopniach
     */
    float getRotation() const;

    /**
     * @brief ustawia skale obiektu
     * @param factor wspolczynnik skalowania
     */
    void setScale(float factor);

    /**
     * @brief pobiera skale obiektu
     * @return aktualna skala obiektu
     */
    float getScale() const;

    /**
     * @brief pobiera wspolrzedna X obiektu
     * @return wspolrzedna X obiektu
     */
    float getX() const;

    /**
     * @brief pobiera wspolrzedna Y obiektu
     * @return wspolrzedna Y obiektu
     */
    float getY() const;

private:
    float go_x; /**< wspolrzedna X obiektu */
    float go_y; /**< wspolrzedna Y obiektu */
    float go_rotation; /**< obrot obiektu */
    float go_scale; /**< skala obiektu */
};

