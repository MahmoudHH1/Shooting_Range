#ifndef PLAYER_H
#define PLAYER_H

#include <glut.h>

class Player {
public:
    float x, y, z;       // Player's position
    float width, length, height;  // Player's dimensions

    // Constructor
    Player(float x, float y, float z, float length, float width, float height);

    // Method to draw the player
    void drawPlayer() const;
    void moveForward();
    void moveBackward();
    void moveRight();
    void moveLeft();
};
   
#endif