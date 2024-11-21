#ifndef CAMERA_H
#define CAMERA_H 

#include <glut.h>

class Camera {
public:
    Camera();
    void setFirstView();
    void setSecondView();
    void setThirdView();
    void rotateView(float yaw, float pitch);

    float x, y, z;          // Camera position
    float lookX, lookY, lookZ;  // Look at point
    float upX, upY, upZ;    // Up vector

private:
    float yaw;
    float pitch;
    void updateCameraVectors();
};

#endif // !CAMERA_H

