#include "ShapeObject.h"
#include <iostream>
#include <cmath>


// Implementacja przesuniêcia kszta³tu
void ShapeObject::translate(float x, float y) {
    float currentX, currentY;
    this->GameObject::getPosition(currentX, currentY);
    this->GameObject::setPosition(currentX + x, currentY + y);
}

// Implementacja rotacji
void ShapeObject::rotate(float angle) { 
    float currentX, currentY;
    this->GameObject::getPosition(currentX, currentY);
    float s = sin(angle * 3.1415926 / 180.0);
    float c = cos(angle * 3.1415926 / 180.0);
    float newX = 400 + (currentX - 400) * c - (currentY - 300) * s;
    float newY = 300 + (currentX - 400) * s + (currentY - 300) * c;
    this->GameObject::setPosition(newX, newY);
}

//Implementacja skalowania
void ShapeObject::scale(float factor) {
    float currentX, currentY;
    this->GameObject::getPosition(currentX, currentY);
    float newX = currentX * factor + (1 - factor) * 400;
    float newY = currentY * factor + (1 - factor) * 300;
    this->GameObject::setPosition(newX, newY);
}