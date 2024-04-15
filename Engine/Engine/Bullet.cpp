#include "Bullet.h"



void Bullet::update() {
    point.x += direction.x * speed;
    point.y += direction.y * speed;
}
