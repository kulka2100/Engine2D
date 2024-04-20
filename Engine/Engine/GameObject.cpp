#include "GameObject.h"

GameObject::GameObject()
    : go_x(0.0f), go_y(0.0f), go_rotation(0.0f), go_scale(1.0f) {}

GameObject::~GameObject() {}

void GameObject::setPosition(float x, float y) {
    go_x = x;
    go_y = y;
}

void GameObject::getPosition(float& x, float& y) const {
    x = go_x;
    y = go_y;
}

void GameObject::setRotation(float angle) {
    go_rotation = angle;
}

float GameObject::getRotation() const {
    return go_rotation;
}

void GameObject::setScale(float factor) {
    go_scale = factor;
}

float GameObject::getScale() const {
    return go_scale;
}