#include "ShapeObject.h"


// Implementacja przesuniêcia kszta³tu
void ShapeObject::translate(float x, float y) {
    position.x += x;
    position.y += y;
}

// Implementacja rotacji
void ShapeObject::rotate(float angle) { 
    float s = sin(angle);
    float c = cos(angle);
    float x = position.x;
    float y = position.y;
    position.x = x * c - y * s;
    position.y = x * s + y * c;
}

//Implementacja skalowania
void ShapeObject::scale(float factor) {
    position.x *= factor;
    position.y *= factor;
}