#include <cmath>
#include "Target.h"
#include <glut.h>

// Static variables for animation
static float xPos = 0.0f;  // X position of the target
static float speed = 0.001f; // Speed of the movement (adjust as needed)
static float amplitude = 1.0f; // Maximum distance to move to the left and right

// Constructors
Target::Target(float x, float y, float z, float raduis)
    : x(x), y(y), z(z), raduis(raduis) {}

Target::Target() : x(8.0f), y(0.0f), z(4.0f), raduis(0.9f) {}

// Function to draw a circle centered at (cx, cy, cz)
void Target::drawCircle(float radius, int segments) {
    glBegin(GL_POLYGON);
    float cx = x;
    float cy = y;
    float cz = z; 
    for (int i = 0; i < segments; ++i) {
        float angle = 2.0f * 3.14f * i / segments;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex3f(cx + x, cy + y, cz); // Add the center coordinates (cx, cy, cz)
    }
    glEnd();
}

// Function to draw the target
void Target::drawTarget() {
    int segments = 360; // High value for smooth circles
    glPushMatrix();

    // Move the entire target to its position
    glTranslatef(x+6, y, z-0.1); // Translate the target to its (x, y, z)

    glDisable(GL_LIGHTING); // Disable lighting for consistent color rendering

    // Draw concentric circles, centered at (0, 0, 0) after translation
    // Largest ring (red)
    glColor3f(1.0f, 0.0f, 0.0f);
    drawCircle(0.9f, segments);
    glTranslatef(0.0f, 0.0f, -0.01f);

    // Second ring (yellow)
    glColor3f(1.0f, 1.0f, 0.0f);
    drawCircle(0.6f, segments);
    glTranslatef(0.0f, 0.0f , -0.01f);

    // Third ring (black)
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle(0.4f, segments);
    glTranslatef(0.0f, 0.0f, -0.01f);

    // Fourth ring (white)
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle( 0.3f, segments);
    glTranslatef(0.0f, 0.0f, -0.01f);


    // Center dot (black)
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle(0.05f, segments);
    glTranslatef(0.0f, 0.0f, -0.01f);

    glEnable(GL_LIGHTING); // Re-enable lighting
    glPopMatrix();
}

float Target::getDistanceFromCenter(float bulletX, float bulletY, float bulletZ) {
    // Account for target's position and animation offset
    float targetX = x+4.3 ; // Include the translation from drawTarget
    float targetY = y;
    float targetZ = z;

    // Calculate 3D distance using Euclidean distance formula
    return sqrt(pow(targetX - bulletX, 2) +
        pow(targetY - bulletY, 2) +
        pow(targetZ - bulletZ, 2));
}

bool Target::checkCollision(float bulletX, float bulletY, float bulletZ){
    // Calculate distance from bullet to target center
    float distance = getDistanceFromCenter(bulletX-4, bulletY, bulletZ);
    // Check if bullet is within the largest ring (radius 0.9f)
    return distance <= 0.9f;
}

// Function to animate target movement
void Target::animateTargetMovement() {
    x = amplitude * sin(glutGet(GLUT_ELAPSED_TIME) * speed); // Smooth oscillation
}

// Function to update the target
void Target::update() {
    animateTargetMovement();
}
