#ifndef GAME_H 
#define GAME_H 
#include "Player.h"
#include "Camera.h"
#include "Bullet.h"
#include "Target.h"
#include<glut.h>

#define MAX_BULLETS  1000

class Game
{
public:
	Player player;
	Camera camera;
	Bullet bullets[MAX_BULLETS];
	Target target;
	float gameTime;        // Total game time in seconds
	float timeRemaining;   // Time remaining in seconds
	int score;            // Player's score
	bool gameActive;      // Game state flag
	bool gameWin;
	Game(Player player );

	void draw();
	void update();
	void handleKeyPress(unsigned char key, int x, int y);
	bool checkBulletTargetCollision(const Bullet& bullet);
	void updateScore(const Bullet& bullet);
	void drawScore();
	void drawTimer();
	void drawBullets();
	bool checkCollisions();
	float calculateDistance(float x1, float y1, float z1, float x2, float y2, float z2);
	void updateBullets(float deltaTime); 
	void shootBullet(float startX, float startY, float startZ,
		float dirX, float dirY, float dirZ,
		float speed);


};

#endif // !GAME_H ;

