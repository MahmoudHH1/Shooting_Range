#include <cmath>
#include "Camera.h"
#include <glut.h>

Camera::Camera() {
	setFirstView();
	yaw = -90.0f;
	pitch = 0.0f;
}

void Camera::rotateView(float yawOffset, float pitchOffset) {
	yaw += yawOffset;
	pitch += pitchOffset;

	// Constrain pitch
	if (pitch > 89.0f) pitch = 89.0f;
	if (pitch < -89.0f) pitch = -89.0f;

	updateCameraVectors();
}

void Camera::updateCameraVectors() {
	// Calculate new look direction
	float radYaw = yaw * 3.14159f / 180.0f;
	float radPitch = pitch * 3.14159f / 180.0f;

	lookX = cos(radYaw) * cos(radPitch);
	lookY = sin(radPitch);
	lookZ = sin(radYaw) * cos(radPitch);

	// Normalize look direction
	float len = sqrt(lookX * lookX + lookY * lookY + lookZ * lookZ);
	lookX /= len;
	lookY /= len;
	lookZ /= len;

	// Update look-at point relative to camera position
	lookX += x;
	lookY += y;
	lookZ += z;
}

void Camera::setFirstView() {
	x = 5.0f;     // Place the camera 5 units to the right of the scene on the X-axis
	y = 5.0f;     // Place the camera 5 units above the scene on the Y-axis
	z = 10.0f;    // Move the camera further away along the Z-axis (increased from 5.0f to 10.0f)
	lookX = 0.0f;  // Look towards the center of the scene (origin)
	lookY = 0.0f;	
	lookZ = 0.0f;
	upX = 0.0f;   // "Up" vector is aligned along the Y-axis to keep orientation
	upY = 2.0f;
	upZ = 0.0f;
}

void Camera::setSecondView() {
	x = 0.0f;   // Position the camera directly above the scene along the X-axis (can adjust this if needed)
	y = 20.0f;  // Place the camera high above the scene, so it looks downward
	z = 0.0f;   // Keep the camera centered along the Z-axis (can adjust for different offsets)

	lookX = 0.0f;  // The camera should look at the center of the scene, or at the player's position (e.g., player coordinates)
	lookY = 0.0f;  // Adjust this to the player's Y-coordinate if needed
	lookZ = 0.0f;  // Same for Z-coordinate, this is typically the origin for top-down views

	upX = 0.0f;    // Camera's "up" vector points along the Y-axis (for top-down, it should be positive along Y)
	upY = 0.0f;    // We want the camera to be looking straight down, so no up vector tilt along the Y-axis
	upZ = 4.0f;    // "Up" direction is along the Z-axis
}

void Camera::setThirdView() {
	// Position the camera at the back of the room, looking toward the scene
	x = 0.0f;   // Keep the camera centered on the X-axis (can adjust if needed)
	y = 10.0f;  // Position the camera high above the scene, looking downward
	z = -10.0f; // Move the camera back along the Z-axis (this is behind the scene, adjust to fit)

	// Set the camera to look at the center of the scene (or player's position)
	lookX = 0.0f;  // The camera should look at the center of the scene
	lookY = 0.0f;  // Look toward the center or player's Y-coordinate
	lookZ = 0.0f;  // Same for Z-coordinate, typically the origin for top-down views

	// The "up" vector points along the Y-axis (no tilt)
	upX = 0.0f;    // No horizontal tilt
	upY = 1.0f;    // The "up" direction is along the Y-axis
	upZ = 0.0f;    // No tilt along the Z-axis (standard orientation)

}


