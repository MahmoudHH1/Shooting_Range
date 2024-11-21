#include "Bullet.h"
#include <glut.h>

// Parameterized constructor
Bullet::Bullet(float x, float y, float z, float dx, float dy, float dz, float speed)
    : x(x), y(y), z(z), dx(dx), dy(dy), dz(dz), speed(speed) , active(false) {}

// Default constructor
Bullet::Bullet()
    : x(0), y(0), z(0), dx(0), dy(0), dz(0), speed(0) , active(false) {} // Initialize all to zero