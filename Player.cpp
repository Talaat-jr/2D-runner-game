#include "Player.h"
#include "Color.h"
#include "Text.h"
#include <cmath>
#include <glut.h>

double Player::PLAYER_WIDTH = 40;
double Player::PLAYER_HEIGHT = 80;

Color black = Color(0.0f, 0.0f, 0.0f);

Player::Player(double x, double y, double speed) : BoundingBox(x, y, PLAYER_WIDTH, PLAYER_HEIGHT, false),
x(x), y(y), width(PLAYER_WIDTH), height(PLAYER_HEIGHT), speed(speed), score(0), lives(5), gravity(-3.5f),
isJumping(false), reachedApex(false), jumpVelocity(3.0f), ground(y), jumpHeight(150), DoublePoint(false), NoGravity(false), isDucking(false) {}

void Player::draw() {
	drawCharacter(x, y, 100.0f, isDucking);
}

void Player::move(double dx, double dy) {
	x += dx;
	y += dy;
}

void Player::jump() {
	if (!isJumping) {
		jumpVelocity = 50.2f;
		isJumping = true;
		reachedApex = false;
	}
}

void Player::animate() {
	if (isJumping) {
		if (!reachedApex) {
			y += jumpVelocity;
			if (y >= ground + jumpHeight) {
				reachedApex = true;
			}
		}

		if (reachedApex) {
			y += gravity;
		}

		if (y <= ground) {
			y = ground;
			isJumping = false;
			jumpVelocity = 0.0f;
		}
	}

	gravity -= 0.01;
	BoundingBox::x = x;
	BoundingBox::y = y;
	BoundingBox::width = width;
	BoundingBox::height = height;
}

void Player::duck() {
	height = 65;
	isDucking = true;
}

void Player::standUp() {
	height = 90;
	isDucking = false;
}

void Player::moveTo(double x, double y) {
	this->x = x;
	this->y = y;
}

//state
void Player::setLives(int lives) {
	this->lives = lives;
}

void Player::setScore(int score) {
	this->score = score;
}


void Player::setSpeed(double speed) {
	this->speed = speed;
}

int Player::getLives() {
	return lives;
}

int Player::getScore() {
	return score;
}

double Player::getSpeed() {
	return speed;
}

void Player::decrementLives() {
	lives--;
}

void Player::incrementScore() {
	score+=50;
}

bool Player::isDoublePoint() {
	return DoublePoint;
}

bool Player::isNoGravity() {
	return NoGravity;
}

void Player::activateDoublePoint() {
	DoublePoint = true;
}

void Player::activateNoGravity() {
	gravity = -0.5;
	NoGravity = true;
}

void Player::deactivateDoublePoint() {
	DoublePoint = false;
}

void Player::deactivateNoGravity() {
	gravity = -4.5;
	NoGravity = false;
}

void Player::drawCharacter(float x, float y, float size, bool isDucking) {

	Color skin = Color(1.0f, 0.8f, 0.6f);
	Color black = Color(0.0f, 0.0f, 0.0f);
	Color blue = Color(0.0f, 0.5f, 1.0f);
	Color brown = Color(0.4f, 0.2f, 0.0f);
	Color darkBlue = Color(0.0f, 0.0f, 0.8f);

	// Define height adjustments for ducking
	float bodyHeight = isDucking ? size * 0.2f : size * 0.3f;
	float legHeight = isDucking ? size * 0.15f : size * 0.3f;
	float bodyTop = y + bodyHeight + legHeight;

	// Head (Circle)
	skin.apply();
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, bodyTop + size * 0.2f); // Center of the head
	for (int i = 0; i <= 20; ++i) {
		float angle = i * 2.0f * 3.14159f / 20;
		glVertex2f(x + cos(angle) * size * 0.15f, bodyTop + size * 0.2f + sin(angle) * size * 0.15f);
	}
	glEnd();

	// Facial Details: Eyes and Mouth (GL_TRIANGLE_FAN & GL_LINES)
	black.apply();
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x - size * 0.05f, bodyTop + size * 0.25f); // Left eye
	for (int i = 0; i <= 20; ++i) {
		float angle = i * 2.0f * 3.14159f / 20;
		glVertex2f(x - size * 0.05f + cos(angle) * size * 0.02f, bodyTop + size * 0.25f + sin(angle) * size * 0.02f);
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x + size * 0.05f, bodyTop + size * 0.25f); // Right eye
	for (int i = 0; i <= 20; ++i) {
		float angle = i * 2.0f * 3.14159f / 20;
		glVertex2f(x + size * 0.05f + cos(angle) * size * 0.02f, bodyTop + size * 0.25f + sin(angle) * size * 0.02f);
	}
	glEnd();

	glBegin(GL_LINES); // Mouth as a small line
	glVertex2f(x - size * 0.03f, bodyTop + size * 0.18f);
	glVertex2f(x + size * 0.03f, bodyTop + size * 0.18f);
	glEnd();

	// Body (Rectangle) (GL_QUADS)
	blue.apply();
	glBegin(GL_QUADS);
	glVertex2f(x - size * 0.1f, y + legHeight); // Bottom-left of the body
	glVertex2f(x + size * 0.1f, y + legHeight); // Bottom-right of the body
	glVertex2f(x + size * 0.1f, y + legHeight + bodyHeight); // Top-right of the body
	glVertex2f(x - size * 0.1f, y + legHeight + bodyHeight); // Top-left of the body
	glEnd();

	// Arms (Slim Rectangles) (GL_QUADS)
	skin.apply();
	glBegin(GL_QUADS);
	// Left Arm
	glVertex2f(x - size * 0.2f, y + legHeight + bodyHeight * 0.8f);
	glVertex2f(x - size * 0.1f, y + legHeight + bodyHeight * 0.8f);
	glVertex2f(x - size * 0.1f, y + legHeight + bodyHeight * 0.6f);
	glVertex2f(x - size * 0.2f, y + legHeight + bodyHeight * 0.6f);

	// Right Arm
	glVertex2f(x + size * 0.1f, y + legHeight + bodyHeight * 0.8f);
	glVertex2f(x + size * 0.2f, y + legHeight + bodyHeight * 0.8f);
	glVertex2f(x + size * 0.2f, y + legHeight + bodyHeight * 0.6f);
	glVertex2f(x + size * 0.1f, y + legHeight + bodyHeight * 0.6f);
	glEnd();

	// Belt (Outline) (GL_LINE_LOOP)
	black.apply();
	glBegin(GL_LINE_LOOP);
	glVertex2f(x - size * 0.12f, y + legHeight + bodyHeight * 0.4f); // Bottom-left of the belt
	glVertex2f(x + size * 0.12f, y + legHeight + bodyHeight * 0.4f); // Bottom-right
	glVertex2f(x + size * 0.12f, y + legHeight + bodyHeight * 0.42f); // Top-right
	glVertex2f(x - size * 0.12f, y + legHeight + bodyHeight * 0.42f); // Top-left
	glEnd();

	// Legs (Rectangles) (GL_QUADS)
	darkBlue.apply();
	glBegin(GL_QUADS);
	// Left Leg
	glVertex2f(x - size * 0.05f, y); // Bottom-left of left leg
	glVertex2f(x, y); // Bottom-right of left leg
	glVertex2f(x, y + legHeight); // Top-right of left leg
	glVertex2f(x - size * 0.05f, y + legHeight); // Top-left of left leg

	// Right Leg
	glVertex2f(x, y); // Bottom-left of right leg
	glVertex2f(x + size * 0.05f, y); // Bottom-right of right leg
	glVertex2f(x + size * 0.05f, y + legHeight); // Top-right of right leg
	glVertex2f(x, y + legHeight); // Top-left of right leg
	glEnd();

	// Feet (Small Rectangles) (GL_QUADS)
	brown.apply();
	glBegin(GL_QUADS);
	// Left Foot
	glVertex2f(x - size * 0.08f, y);
	glVertex2f(x - size * 0.01f, y);
	glVertex2f(x - size * 0.01f, y - size * 0.05f);
	glVertex2f(x - size * 0.08f, y - size * 0.05f);

	// Right Foot
	glVertex2f(x + size * 0.01f, y);
	glVertex2f(x + size * 0.08f, y);
	glVertex2f(x + size * 0.08f, y - size * 0.05f);
	glVertex2f(x + size * 0.01f, y - size * 0.05f);
	glEnd();
}

