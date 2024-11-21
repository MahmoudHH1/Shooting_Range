#include "Player.h"
#include <glut.h>

float movementSpeed = 0.3f; // Speed of the player's movement

Player::Player(float x, float y, float z, float length, float width, float height)
    : x(x), y(y), z(z), length(length), width(width), height(height) {}

void drawCube(float length, float width, float height) {
    glPushMatrix();
    glScalef(length, height, width);
    glutSolidCube(1.0f);
    glPopMatrix();
}

void drawSphere(float radius) {
    glutSolidSphere(radius, 16, 16);
}

void Player::drawPlayer() const {
    float bodyHeight = height * 0.4f; // Reduced body height (40% of total height)
    float headRadius = height * 0.15f; // Head radius (15% of total height)
    float armWidth = width * 0.2f;     // Arm width
    float legWidth = width * 0.4f;     // Leg width
    float limbLength = height * 0.5f;  // Arm/leg length
    float gunLength = limbLength * 1.2f; // Gun length increased (120% of arm length)
    float gunWidth = gunLength * 0.2f;  // Gun width (relative to gun length)

    // Draw Body (smaller body)
    glPushMatrix();
    glTranslatef(x, y + bodyHeight / 2, z);
    glColor3f(0.0f, 0.0f, 1.0f); // Blue color for the body
    drawCube(length, width, bodyHeight); // Draw smaller body
    glPopMatrix();

    // Draw Head
    glPushMatrix();
    glTranslatef(x, y + bodyHeight + headRadius, z);
    glColor3f(1.0f, 0.8f, 0.6f); // Skin color for the head
    drawSphere(headRadius); // Draw a more realistic spherical head
    glPopMatrix();

    // Draw Eyes (proper positioning)
    float eyeOffsetX = headRadius * 0.5f; // Horizontal distance from center
    float eyeOffsetY = headRadius * 0.2f; // Vertical distance from center

    // Left Eye
    glPushMatrix();
    glTranslatef(x - eyeOffsetX, y + bodyHeight + headRadius + eyeOffsetY, z + headRadius / 1.5f);
    glColor3f(0.0f, 0.0f, 0.0f); // Black color for eyes
    drawSphere(headRadius * 0.3f); // Left eye
    glPopMatrix();

    // Right Eye
    glPushMatrix();
    glTranslatef(x + eyeOffsetX, y + bodyHeight + headRadius + eyeOffsetY, z + headRadius / 1.5f);
    glColor3f(0.0f, 0.0f, 0.0f); // Black color for eyes
    drawSphere(headRadius * 0.3f); // Right eye
    glPopMatrix();

    // Draw Left Arm (holding the bigger gun)
    glPushMatrix();
    glTranslatef(x - length / 2 - armWidth / 2, y + bodyHeight / 2, z + armWidth / 2);  // Slightly forward for gun visibility
    glColor3f(0.0f, 0.0f, 1.0f); // Same color as body
    drawCube(armWidth, armWidth, limbLength); // Draw upper arm
    glPopMatrix();

    // Draw Left Hand holding the bigger gun
    glPushMatrix();
    glTranslatef(x - length / 2 - armWidth / 2, y + bodyHeight / 2 - limbLength / 2, z);  // Hand holding gun
    glColor3f(0.5f, 0.5f, 0.5f); // Gun color (metallic)
    drawCube(gunLength, gunWidth, 0.1f); // Bigger gun barrel
    glPopMatrix();

    glPushMatrix();
    glTranslatef(x - length / 2 - armWidth / 2, y + bodyHeight / 2 - limbLength / 2, z - gunWidth / 3);  // Gun handle
    glColor3f(0.5f, 0.5f, 0.5f); // Gun color (metallic)
    drawCube(0.1f, armWidth, 0.1f); // Gun handle
    glPopMatrix();

    // Draw Right Arm (more natural position)
    glPushMatrix();
    glTranslatef(x + length / 2 + armWidth / 2, y + bodyHeight / 2, z);
    glColor3f(0.0f, 0.0f, 1.0f); // Same color as body
    drawCube(armWidth, armWidth, limbLength); // Draw upper arm
    glPopMatrix();

    // Draw Left Leg
    glPushMatrix();
    glTranslatef(x - length / 4, y - limbLength / 2, z);
    glColor3f(0.0f, 0.0f, 1.0f); // Same color as body
    drawCube(legWidth, legWidth, limbLength); // Draw left leg
    glPopMatrix();

    // Draw Right Leg
    glPushMatrix();
    glTranslatef(x + length / 4, y - limbLength / 2, z);
    glColor3f(0.0f, 0.0f, 1.0f); // Same color as body
    drawCube(legWidth, legWidth, limbLength); // Draw right leg
    glPopMatrix();
}




void Player::moveBackward() {
    if (z - movementSpeed >= -5.0f) { // Check if moving forward doesn't exceed the front wall
        z -= movementSpeed;
    }
}

void Player::moveForward() {
    if (z + movementSpeed <= 5.0f) { // Check if moving backward doesn't exceed the back wall
        z += movementSpeed;
    }
}

void Player::moveLeft() {
    if (x + movementSpeed <= 5.0f) { // Check if moving right doesn't exceed the right wall
        x += movementSpeed;
    }
}

void Player::moveRight() {
    if (x - movementSpeed >= -5.0f) { // Check if moving left doesn't exceed the left wall
        x -= movementSpeed;
    }
}




