#pragma once
#include "GameObject.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Color.hpp>
class DrawableObject :
    public GameObject
{
public:
    DrawableObject();
    virtual ~DrawableObject();

    virtual void draw(sf::RenderWindow& window, sf::Color color) = 0;
};

