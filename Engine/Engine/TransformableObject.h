#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>

class TransformableObject :
    public GameObject
{
public:
    TransformableObject();
    virtual ~TransformableObject();

    virtual void translate(float x, float y) = 0;
    virtual void rotate(float angle) = 0;
    virtual void scale(float factor) = 0;
};

