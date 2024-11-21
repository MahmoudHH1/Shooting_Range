#ifndef BULLET_H
#define BULLET_H

//#include <glut.h>

class Bullet {
public:
    float x, y, z;     // Position
    float dx, dy, dz;  // Direction
    float speed;       // Speed
    bool active;

    // Parameterized constructor
    Bullet(float x, float y, float z, float dx, float dy, float dz, float speed);

    // Default constructor
    Bullet();
};

#endif
