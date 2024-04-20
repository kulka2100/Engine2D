#pragma once
#include "GameObject.h"
class UpdatableObject :
    public GameObject
{
public:
    UpdatableObject();
    virtual ~UpdatableObject();

    virtual void update() = 0;
};

