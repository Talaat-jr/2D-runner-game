#pragma once
#include "BoundingBox.h"

class Player : public BoundingBox {
	double x;
	double y;
	double width;
	double height;

	double speed;
	int score;
	int lives;
	double gravity;

	bool isJumping;
	bool reachedApex;
	double jumpVelocity;
	double ground;
	double jumpHeight;
	bool isDucking;

	bool DoublePoint;
	bool NoGravity;
public:
	static double PLAYER_WIDTH;
	static double PLAYER_HEIGHT;

	Player(double x, double y, double speed);

	void draw();

	void animate();

	void move(double dx, double dy);

	void jump();

	void duck();

	void standUp();

	void moveTo(double x, double y);

	//state

	void setLives(int lives);

	void setScore(int score);

	void setSpeed(double speed);

	int getLives();

	int getScore();

	double getSpeed();

	void decrementLives();

	void incrementScore();

	bool isDoublePoint();

	bool isNoGravity();

	void activateDoublePoint();

	void deactivateDoublePoint();

	void activateNoGravity();

	void deactivateNoGravity();

	void drawCharacter(float x, float y, float size, bool isDucking);

};