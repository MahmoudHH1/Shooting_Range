#include <cmath>
#include "Game.h"
#include "Player.h"
#include "Bullet.h"
#include <Target.h>
#include <string>
#include <stdio.h>
#include <iostream>

#include <glut.h>

//static float xPos = 0.0f;  // X position of the target
//static float speed = 0.001f; // Speed of the movement (adjust as needed)
//static float amplitude = 1.0f; // Maximum distance to move to the left and right

Game::Game(Player player) : player(player), gameTime(60.0f), timeRemaining(60.0f),
score(0), gameActive(true), gameWin(false) {

}

static float xPos = 0.0f;  // X position of the target
static float speed = 0.001f; // Speed of the movement (adjust as needed)
static float amplitude = 1.0f; // Maximum distance to move to the left and right

static void drawCube(float size) {
	glutSolidCube(size);
}

static void drawCircle(float radius, int segments) {
	glBegin(GL_POLYGON);
	for (int i = 0; i < segments; ++i) {
		float angle = 2.0f * 3.14 * i / segments;
		float x = radius * cos(angle);
		float y = radius * sin(angle);
		glVertex3f(x, y + 1.7, 1.9f);  // Use 3D coordinates (x, y, z) here
	}
	glEnd();
}

static void drawCircle(float radius, int segments, float xOffset, float yOffset, float zOffset) {
	glBegin(GL_POLYGON);
	for (int i = 0; i < segments; ++i) {
		float angle = 2.0f * 3.14 * i / segments;
		float x = radius * cos(angle) + xOffset;
		float y = radius * sin(angle) + yOffset;
		glVertex3f(x + 3, y + 3, 4.5f);  // Use 3D coordinates (x, y, z)
	}
	glEnd();
}

static void drawCylinder(float baseRadius, float topRadius, float height, int slices) {
	GLUquadric* quadric = gluNewQuadric();
	gluCylinder(quadric, baseRadius, topRadius, height, slices, 1);
	gluDeleteQuadric(quadric);
}

// Function to animate the target's movement
//void animateTargetMovement() {
//	// Update the position using a sine function to create smooth left-right motion
//	xPos = amplitude * sin(glutGet(GLUT_ELAPSED_TIME) * speed);
//	// The position will oscillate between -amplitude and +amplitude
//}

//static void drawTarget() {
//	int segments = 200;  // Higher number for smoother circles
//	float centerX = 0.0f, centerY = 0.0f; // Target is centered at (0, 0)
//
//	// Draw the bullseye target (multiple concentric circles)
//	glPushMatrix();
//
//	// Position the target in the center of the front wall (x=0, y=0, z=-6.0f)
//	glTranslatef(xPos, 0.0f, 5.5f);  // Move target to the front wall and animate along the x-axis
//
//	// Optional: Adjust target height (if needed, otherwise leave y=0.0f)
//	glTranslatef(0.0f, 0.0f, -2.0f);  // Place the target a little higher or lower if needed
//
//	// Draw the largest ring (outermost)
//	glColor3f(1.0f, 0.0f, 0.0f);  // Red
//	drawCircle(0.9f, segments);  // Outer circle radius = 2.0
//	glTranslatef(0.0f, 0.0f, -0.01f); // Move each subsequent circle slightly forward or backward
//
//	// Draw the second ring
//	glColor3f(1.0f, 1.0f, 0.0f);  // Yellow
//	drawCircle(0.6f, segments);  // Second circle radius = 1.5
//	glTranslatef(0.0f, 0.0f, -0.01f); // Move each subsequent circle slightly forward or backward
//
//	// Draw the third ring
//	glColor3f(0.0f, 0.0f, 0.0f);  // Black
//	drawCircle(0.4f, segments);  // Third circle radius = 1.0
//	glTranslatef(0.0f, 0.0f, -0.01f); // Move each subsequent circle slightly forward or backward
//
//	// Draw the fourth ring
//	glColor3f(1.0f, 1.0f, 1.0f);  // White
//	drawCircle(0.3f, segments);  // Fourth circle radius = 0.5
//	glTranslatef(0.0f, 0.0f, -0.01f); // Move each subsequent circle slightly forward or backward
//
//	// Draw the center dot
//	glColor3f(0.0f, 0.0f, 0.0f);  // Black
//	drawCircle(0.05f, segments);  // Center circle radius = 0.2
//
//	glPopMatrix();
//}


void drawMedal(float radius, float r, float g, float b) {
	glBegin(GL_POLYGON);
	glColor3f(r, g, b);  // Set color for the medal
	for (int i = 0; i < 360; i++) {
		float angle = i * 3.14159f / 180.0f;
		float x = radius * cos(angle);
		float y = radius * sin(angle);
		glVertex2f(x, y);
	}
	glEnd();
}



static void drawOlympicLogo() {
	int segments = 100;  // Higher number for smoother circles
	float radius = 0.3f;  // Smaller radius for each ring
	float spacing = radius * 2.2f;  // Space between the centers of neighboring rings

	glPushMatrix();

	// Move the Olympic logo to the left wall position (adjust as needed)
	glTranslatef(-6.0f, -0.9f, 0.5f);  // Adjust the position on the left wall

	// Draw the rings with the appropriate colors
	// Ring 1: Blue (Top-left)
	glColor3f(0.0f, 0.0f, 1.0f);  // Blue color
	drawCircle(radius, segments, -spacing, 0.0f, 0.0f);  // Center at (-spacing, 0)

	// Ring 2: Yellow (Top-center)
	glColor3f(1.0f, 1.0f, 0.0f);  // Yellow color
	drawCircle(radius, segments, 0.0f, 0.0f, 0.0f);  // Center at (0, 0)

	// Ring 3: Black (Top-right)
	glColor3f(0.0f, 0.0f, 0.0f);  // Black color
	drawCircle(radius, segments, spacing, 0.0f, 0.0f);  // Center at (spacing, 0)

	// Ring 4: Green (Bottom-left)
	glColor3f(0.0f, 1.0f, 0.0f);  // Green color
	drawCircle(radius, segments, -radius, -spacing, 0.0f);  // Center at (-radius, -spacing)

	// Ring 5: Red (Bottom-right)
	glColor3f(1.0f, 0.0f, 0.0f);  // Red color
	drawCircle(radius, segments, radius, -spacing, 0.0f);  // Center at (radius, -spacing)

	glPopMatrix();
}

static void drawGuns() {
	int numGuns = 2;          // Number of guns to draw
	float gunSpacing = 1.5f;  // Vertical spacing between guns
	float startY = 2.5f;      // Starting height for the guns
	float gunLength = 1.0f;   // Length of each gun
	float gunHeight = 0.2f;   // Height of each gun
	float barrelRadius = 0.1f; // Radius of the gun barrel

	glPushMatrix();

	// Move guns to the left wall
	glTranslatef(4.9f, 0.0f, 0.0f);  // Slightly off the wall to avoid z-fighting

	for (int i = 0; i < numGuns; i++) {
		glPushMatrix();

		// Calculate the vertical position for the current gun
		float currentY = startY - i * gunSpacing;
		glTranslatef(0.0f, currentY, 0.0f);

		// Draw gun body
		glColor3f(0.2f, 0.2f, 0.2f);  // Dark gray
		glPushMatrix();
		glScalef(gunLength, gunHeight, 0.2f);  // Scale to form a rectangular body
		drawCube(1.0f);
		glPopMatrix();

		// Draw gun barrel
		glColor3f(0.1f, 0.1f, 0.1f);  // Black
		glPushMatrix();
		glTranslatef(gunLength / 2.0f, 0.0f, 0.0f);  // Position the barrel at the end of the body
		drawCylinder(barrelRadius, barrelRadius, 0.5f, 20);  // Barrel length of 0.5
		glPopMatrix();

		// Optionally add other details like a trigger or scope

		glPopMatrix();
	}

	glPopMatrix();
}


void drawFourSpheres() {
	// Radius for the spheres
	float radius = 0.5f;

	glTranslatef(-5.0f, 1.5f, -2.5f);

	// Draw the first sphere (bottom)
	glPushMatrix();
	glColor3f(1.0f, 0.0f, 0.0f);  // Red color for the first sphere
	glTranslatef(0.0f, -0.75f, 0.0f);  // Move the sphere down
	glutSolidSphere(radius, 16, 16);  // Draw the sphere
	glPopMatrix();


	// Draw the second sphere
	glPushMatrix();
	glColor3f(0.0f, 1.0f, 0.0f);  // Green color for the second sphere
	glTranslatef(0.0f, -0.25f, 0.0f);  // Position it above the first sphere
	glutSolidSphere(radius, 16, 16);  // Draw the sphere
	glPopMatrix();

	// Draw the third sphere
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 1.0f);  // Blue color for the third sphere
	glTranslatef(0.0f, 0.25f, 0.0f);  // Position it above the second sphere
	glutSolidSphere(radius, 16, 16);  // Draw the sphere
	glPopMatrix();

	// Draw the fourth sphere (top)
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 0.0f);  // Yellow color for the fourth sphere
	glTranslatef(0.0f, 0.75f, 0.0f);  // Position it above the third sphere
	glutSolidSphere(radius, 16, 16);  // Draw the sphere
	glPopMatrix();
}


void drawRoom() {
	// Draw floor
	glPushMatrix();
	glTranslatef(0.0f, -6.0f, 0.0f);
	glColor3f(0.5f, 0.5f, 0.5f); // Light gray floor color
	drawCube(13.0f); // Floor
	glPopMatrix();

	// Draw front wall
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -6.0f);
	glColor3f(0.9f, 0.5f, 0.5f); // Red wall color
	glScalef(13.0f, 5.0f, 1.0f);
	drawCube(1.0f); // Wall
	glPopMatrix();

	// Draw back wall
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 6.0f);
	glColor3f(0.9f, 0.5f, 0.5f); // Red wall color
	glScalef(13.0f, 5.0f, 1.0f);
	drawCube(1.0f); // Wall
	glPopMatrix();

	// Draw left wall
	glPushMatrix();
	glTranslatef(-6.0f, 0.0f, 0.0f);
	glColor3f(0.5f, 0.9f, 0.5f); // Green wall color
	glScalef(1.0f, 5.0f, 13.0f);
	drawCube(1.0f); // Wall
	glPopMatrix();

	// Draw right wall
	glPushMatrix();
	glTranslatef(6.0f, 0.0f, 0.0f);
	glColor3f(0.5f, 0.9f, 0.5f); // Green wall color
	glScalef(1.0f, 5.0f, 13.0f);
	drawCube(1.0f); // Wall
	glPopMatrix();



	// Draw Olympic logo
	drawOlympicLogo();


	drawGuns();

	drawFourSpheres();
}


void Game::shootBullet(float startX, float startY, float startZ, float dirX, float dirY, float dirZ, float speed) {
	for (int i = 0; i < MAX_BULLETS; ++i) {
		if (!bullets[i].active) {  // Find an inactive bullet
			bullets[i].x = startX;
			bullets[i].y = startY;
			bullets[i].z = startZ;

			std::cout << " playerx " << player.x << " player.y " << player.y << " playerz " << player.z<<std::endl;
			std::cout << "bulletx " << bullets[i].x << " bullet y " << bullets[i].y << " bullet z  " << bullets[i].z<<std::endl;
			std::cout << "targetx" << target.x<<" target y "<<target.y<<" targetz "<<target.z << std::endl;

			// Normalize the direction vector
			float magnitude = sqrt(dirX * dirX + dirY * dirY + dirZ * dirZ);
			bullets[i].dx = dirX / magnitude;
			bullets[i].dy = dirY / magnitude;
			bullets[i].dz = dirZ / magnitude;

			bullets[i].speed = speed;
			bullets[i].active = true;  // Activate the bullet
			break;  // Use only one bullet
		}
	}
}

bool Game::checkCollisions() {
	
	if (abs(player.x - target.x) > 0.7 && abs(player.x - target.x) <= 1) {
		return true;
	}
	return false;
}

void Game::updateBullets(float deltaTime) {
	for (int i = 0; i < MAX_BULLETS; ++i) {
		if (bullets[i].active) {
			// Update bullet position
			bullets[i].x += bullets[i].dx * bullets[i].speed * deltaTime;
			bullets[i].y += bullets[i].dy * bullets[i].speed * deltaTime;
			bullets[i].z += bullets[i].dz * bullets[i].speed * deltaTime;

			// Check for collision with target
			if (checkCollisions()) {
				// Calculate score based on distance from center
				float distance = target.getDistanceFromCenter(bullets[i].x, bullets[i].y, bullets[i].z);


				score += 10;
				if (score >= 100)
				{
					gameWin = true;
					gameActive = false;
				}
				// Deactivate the bullet after hitting the target
				bullets[i].active = false;

				// Optional: Add visual or sound effect for hit
			}

			// Deactivate bullets that go out of bounds
			if (bullets[i].z < -10.0f || bullets[i].z > 10.0f ||
				bullets[i].y < -10.0f || bullets[i].y > 10.0f ||
				bullets[i].x < -10.0f || bullets[i].x > 10.0f) {
				bullets[i].active = false;
			}
		}
	}
}




void Game::drawBullets() {
	for (Bullet bullet : bullets) {

		glPushMatrix();
		glTranslatef(bullet.x, bullet.y, bullet.z);
		glColor3f(1.0f, 1.0f, 0.0f);  // Yellow color for bullets
		glutSolidSphere(0.1f, 16, 16);  // Bullet as a small sphere
		glPopMatrix();
	}
}



void Game::updateScore(const Bullet& bullet) {
	// Calculate distance from bullet hit to target center
	float targetX = xPos;  // Use the animated target's X position
	float targetY = 1.7f;  // Target's Y position from drawCircle
	float targetZ = 3.9f;  // Target's Z position

	float distance = calculateDistance(bullet.x, bullet.y, bullet.z, targetX, targetY, targetZ);

	// Score based on distance from center
	if (distance < 0.05f) score += 100;      // Bullseye
	else if (distance < 0.3f) score += 75;   // White ring
	else if (distance < 0.4f) score += 50;   // Black ring
	else if (distance < 0.6f) score += 25;   // Yellow ring
	else if (distance < 0.9f) score += 10;   // Red ring
}

float Game::calculateDistance(float x1, float y1, float z1, float x2, float y2, float z2) {
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) + pow(z2 - z1, 2));
}

bool Game::checkBulletTargetCollision(const Bullet& bullet) {
	// Target's position (center of the bullseye)
	float targetX = xPos;  // Animated target position
	float targetY = 1.7f;  // From drawCircle
	float targetZ = 3.9f;  // Target's Z position

	// Calculate distance from bullet to target center
	float distance = calculateDistance(bullet.x, bullet.y, bullet.z, targetX, targetY, targetZ);

	// Check if bullet is within the largest ring (radius 0.9f)
	return distance <= 0.9f;
}

void Game::drawScore() {
	// Save current matrix
	glPushMatrix();

	// Position score display in top-right corner
	glColor3f(1.0f, 1.0f, 1.0f);  // White text
	glRasterPos3f(4.0f, 2.5f, -5.0f);

	// Convert score to string
	std::string scoreText = "Score: " + std::to_string(score);

	// Draw each character
	for (char c : scoreText) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
	}

	glPopMatrix();
}

void Game::drawTimer() {
	glPushMatrix();

	// Position timer display in top-left corner
	glColor3f(1.0f, 1.0f, 1.0f);  // White text
	glRasterPos3f(-5.0f, 2.5f, -5.0f);

	// Convert time to string (showing only whole seconds)
	std::string timeText = "Time: " + std::to_string(static_cast<int>(timeRemaining));

	// Draw each character
	for (char c : timeText) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
	}

	glPopMatrix();
}

void Game::update() {
	if (!gameActive) return;

	// Update target animation
	target.update();

	// Update timer
	float deltaTime = 1.0f / 60.0f;  // Assuming 60 FPS
	timeRemaining -= deltaTime;

	// Update bullets
	updateBullets(deltaTime);

	// Check for bullet-target collisions
	for (Bullet& bullet : bullets) {
		if (bullet.active && checkBulletTargetCollision(bullet)) {
			updateScore(bullet);
			bullet.active = false;  // Deactivate bullet after hit
		}
	}

	// Check if game is over
	if (timeRemaining <= 0) {
		gameActive = false;
		timeRemaining = 0;
	}

	glutPostRedisplay();
}

void Game::draw() {

	if (gameActive) {
		player.drawPlayer();
		drawRoom();
		target.drawTarget();
		drawBullets();
		drawScore();
		drawTimer();
	}

	// Display game outcome if game is over or won
	if (!gameActive) {
		glPushMatrix();

		if (gameWin) {
			glColor3f(0.0f, 1.0f, 0.0f);  // Green text for "Game Won"
			glRasterPos3f(-1.0f, 0.0f, -5.0f);
			std::string gameWonText = "CONGRATULATIONS! YOU WON! Final Score: " + std::to_string(score);
			for (char c : gameWonText) {
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
			}
		}
		else {
			glColor3f(1.0f, 0.0f, 0.0f);  // Red text for "Game Over"
			glRasterPos3f(-1.0f, 0.0f, -5.0f);
			std::string gameOverText = "GAME OVER - Final Score: " + std::to_string(score);
			for (char c : gameOverText) {
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
			}
		}

		glPopMatrix();
	}
}


void Game::handleKeyPress(unsigned char key, int x, int y) {
	if (!gameActive && key != 27) return;  // Only allow ESC when game is over

	switch (key) {
	case 'w':
		player.moveForward();
		break;
	case 's':
		player.moveBackward();
		break;
	case 'd':
		player.moveRight();
		break;
	case 'a':
		player.moveLeft();
		break;
	case ' ':  // Spacebar to shoot
		if (gameActive) {
			// Get player's position and view direction
			float px = player.x;
			float py = player.y;
			float pz = player.z;
			float dirX = 0.0f;
			float dirY = -1.5f;
			float dirZ = 5.0f;
			std::cout << "Player Position: (" << player.x << ", " << player.y << ", " << player.z << ")\n";
			std::cout << "Direction: (" << dirX << ", " << dirY << ", " << dirZ << ")\n";
			shootBullet(px+4.0, py, pz + 2.3f, dirX, dirY, dirZ, 10.0f);
		}
		break;
	case '1':
		camera.setFirstView();
		break;
	case '2':
		camera.setSecondView();
		break;
	case '3':
		camera.setThirdView();
		break;
	case 27:  // ESC
		exit(0);
		break;
	}

	glutPostRedisplay();
}

