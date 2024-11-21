#ifndef TARGET_H 
#define TARGET_H

class Target {

public:
	float x, y, z, raduis;

	void drawTarget();
	void update();
	void animateTargetMovement();
	void drawCircle(float raduis , int segments);
	float getDistanceFromCenter(float bulletX, float bulletY, float bulletZ);
	bool checkCollision(float bulletX, float bulletY, float bulletZ);

	Target(float x, float y, float z , float raduis);
	Target();
};

#endif