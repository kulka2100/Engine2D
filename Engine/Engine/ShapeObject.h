#pragma once
#include "DrawableObject.h"
#include "TransformableObject.h"
#include <SFML/Graphics.hpp>

class ShapeObject : public DrawableObject, public TransformableObject {
protected:
    sf::Vector2f position;

public:
    ShapeObject() : DrawableObject(), TransformableObject(), position(0.0f, 0.0f) {}
    ShapeObject(float x, float y) : DrawableObject(), TransformableObject(), position(x, y) {}
    virtual ~ShapeObject() {};

    virtual void draw(sf::RenderWindow& window, sf::Color color) = 0;
    virtual void translate(float x, float y) override;
    virtual void rotate(float angle) override;
    virtual void scale(float factor) override;
};

