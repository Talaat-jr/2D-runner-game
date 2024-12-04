#include "Sun.h"
#include "Text.h"
#include "Bird.h"
#include "Color.h"
#include "Player.h"
#include "Obstacle.h"
#include "NoGravity.h"
#include "HealthBar.h"
#include "DoublePoint.h"
#include "Collectable.h"
#include "LowerBoundary.h"

#include <iostream>
#include <string>
#include <vector>
#include <SFML/Audio.hpp>
#include <glut.h>

int timer = 20e3;
const double GROUND_Y = 75 ;
const double CEILING_Y = 470;
double gameSpeed = 1.0f;

Player player = Player(100, GROUND_Y, 10);

sf::Music backgroundSound;
sf::Music obstacleSound;
sf::Music collectableSound;
sf::Music powerUpSound;
sf::Music winSound;
sf::Music loseSound;

std::vector<Obstacle> obstacles;
std::vector<Collectable> collectables;
std::vector<NoGravity> noGravities;
std::vector<DoublePoint> douplePoints;

Color red = Color(1.0f, 0.0f, 0.0f);
Color green = Color(0.0f, 1.0f, 0.0f);
Color blue = Color(0.0f, 0.0f, 1.0f);
Color brown = Color(0.5f, 0.3f, 0.0f);


HealthBar healthBar = HealthBar(100, CEILING_Y + 65, 5, &player);
LowerBoundary lowerBoundary = LowerBoundary(200, GROUND_Y);
Sun sun = Sun(800, 600);

Bird bird = Bird(100, CEILING_Y - 65, &gameSpeed);

Text lives = Text(200, 250, "lives: " + std::to_string(player.getLives()), red, GLUT_BITMAP_TIMES_ROMAN_24);
Text score = Text(300, CEILING_Y + 50, "Score: " + std::to_string(player.getScore()), green, GLUT_BITMAP_TIMES_ROMAN_24);
Text timerText = Text(500, CEILING_Y + 50, "Time Left: " + std::to_string(timer / 1000), blue, GLUT_BITMAP_TIMES_ROMAN_24);

// Rendering functions
void displayGameOver() {
	Text gameOver = Text(350, 300, "Game Over Loser!, your score is: " + std::to_string(player.getScore()), red, GLUT_BITMAP_TIMES_ROMAN_24);
	gameOver.draw();
}

void displayGameWon() {
	Text gameWon = Text(350, 300, "You Won!, your score is: " + std::to_string(player.getScore()), green, GLUT_BITMAP_TIMES_ROMAN_24);
	gameWon.draw();
}

void displayEndGame() {
	if (player.getLives() <= 0) {
		if (loseSound.getStatus() != sf::Sound::Playing) 
			loseSound.play();

		displayGameOver();
	}
	else {
		if (winSound.getStatus() != sf::Sound::Playing)
			winSound.play();

		displayGameWon();
	}
}

void displayTimer() {
	timerText.setText("Time Left: " + std::to_string(timer / 1000));
	timerText.draw();
}

void displayScore() {
	score.setText("Score: " + std::to_string(player.getScore()));
	score.draw();
}

void displayLives() {
	healthBar.draw();
}

void drawBorders() {

	lowerBoundary.draw();
	sun.animate();
	sun.draw();

	// Ground Border
	brown.apply();
	glBegin(GL_QUADS);
	glVertex2f(0.0f, GROUND_Y);
	glVertex2f(800.0f, GROUND_Y);
	glVertex2f(800.0f, GROUND_Y + 10.0f);
	glVertex2f(0.0f, GROUND_Y + 10.0f);
	glEnd();
}

void displayPlayer() {
	player.animate();
	player.draw();
}

void displayBird() {
	bird.animate();
	bird.draw();
}

void displayGame() {
	displayLives();
	displayScore();
	displayTimer();
	displayPlayer();
	displayBird();
}

// Initialization functions
void loadSounds(){
	backgroundSound.openFromFile("sounds/runboy.wav");
	obstacleSound.openFromFile("sounds/obstacle.wav");
	collectableSound.openFromFile("sounds/collectable.wav");
	powerUpSound.openFromFile("sounds/powerup.wav");
	winSound.openFromFile("sounds/win.wav");
	loseSound.openFromFile("sounds/lose.wav");

	backgroundSound.setLoop(true);
	winSound.setLoop(true);
	loseSound.setLoop(true);

	backgroundSound.play();
}

void spawnPlayer(){
	player = Player(100, GROUND_Y+15, 10);
}

void spawnObstacles() {
	int heights[] = { 30, 100, 130 };

	for (int i = 0; i < 300; i++) {
		Obstacle obstacle = Obstacle(600 * (i + 1), heights[i%2]+ GROUND_Y, &gameSpeed);
		obstacles.push_back(obstacle);
	}
}

void spawnCollectables() {
	int heights[] = { 100, 150, 220, 130, 100, 180 };
	for (int i = 0; i < 300; i++) {
		Collectable collectable = Collectable(300 * (i + 1)+100, heights[i%6] + GROUND_Y, &gameSpeed);
		collectables.push_back(collectable);
	}
}

void spawnPowrUps(){
	double duration = 2e3;
	int heights[] = { 100, 150, 220, 130, 100, 180 };
	for (int i = 0; i < 50; i++) {
		if (i % 4 != 0) {
			DoublePoint doublePoint = DoublePoint(500 * (i + 1) + 50, heights[i % 6] + GROUND_Y, duration, &gameSpeed);
			douplePoints.push_back(doublePoint);
		}
		else {
			NoGravity noGravity = NoGravity(500 * (i + 1) - 50, heights[i % 6] + GROUND_Y, duration, &gameSpeed);
			noGravities.push_back(noGravity);
		}
	}
}

void initGame() {
	loadSounds();
	spawnPlayer();
	spawnObstacles();
	spawnCollectables();
	spawnPowrUps();
}

void resetGame() {
	obstacles.clear();
	collectables.clear();
	noGravities.clear();
	douplePoints.clear();
	initGame();
}

// Game logic functions
bool isGameOver() {
	return player.getLives() <= 0 || timer <= 0;
}

void deactivateNoGravity(int value) {
	player.deactivateNoGravity();
}

void deactivateDoublePoint(int value) {
	player.deactivateDoublePoint();
}

void shiftObjects(double dx, double dy) {
	for (auto& collectable : collectables) {
		collectable.move(dx, dy);
	}

	for (auto& obstacle : obstacles) {
		obstacle.move(dx, dy);
	}

	for (auto& noGravity : noGravities) {
		noGravity.move(dx, dy);
	}

	for (auto& doublePoint : douplePoints) {
		doublePoint.move(dx, dy);
	}
}

void checkCollisions() {
	
	for (auto& obstacle : obstacles) {
		if (player.isColliding(obstacle)) {
			obstacleSound.play();
			player.decrementLives();
			shiftObjects(500, 0);
		}
	}


	for (auto it = collectables.begin(); it != collectables.end();) {
		if (player.isColliding(*it)) {
			collectableSound.play();
			player.incrementScore();
			if (player.isDoublePoint()) {
				player.incrementScore();
			}
			score.setText("Score: " + std::to_string(player.getScore()));
			it = collectables.erase(it);
		}
		else {
			++it;
		}
	}

	for (auto it = noGravities.begin(); it != noGravities.end();) {
		if (player.isColliding(*it)) {
			powerUpSound.play();
			player.activateNoGravity();
			glutTimerFunc((*it).getDuration(), deactivateNoGravity, 0);
			it = noGravities.erase(it);
		}
		else {
			++it;
		}
	}

	for (auto it = douplePoints.begin(); it != douplePoints.end();) {
		if (player.isColliding(*it)) {
			powerUpSound.play();
			player.activateDoublePoint();
			glutTimerFunc((*it).getDuration(), deactivateDoublePoint, 0);
			it = douplePoints.erase(it);
		}
		else {
			++it;
		}
	}

}

// Glut functions
void Display() {
	glClear(GL_COLOR_BUFFER_BIT);

	if (isGameOver()) {
		backgroundSound.stop();
		displayEndGame();
	}
	else {
		displayGame();
		drawBorders();
		
		for (auto& collectable : collectables) {
			collectable.animate();
			collectable.draw();
		}

		for (auto& obstacle : obstacles) {
			obstacle.animate();
			obstacle.draw();
		}

		for (auto& noGravity : noGravities) {
			noGravity.animate();
			noGravity.draw();
		}

		for (auto& doublePoint : douplePoints) {
			doublePoint.animate();
			doublePoint.draw();
		}

		checkCollisions();
	}

	glFlush();
}

void Timer(int value) {
	double elapsedTime = glutGet(GLUT_ELAPSED_TIME);
	timer = timer - (elapsedTime / 1000);

	gameSpeed += 0.01;
	
	glutPostRedisplay();
	glutTimerFunc(1, Timer, 0);
}

void Keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'w':
		player.jump();
		break;
	case 's':
		player.duck();
		break;
	}
}

void KeyboardUp(unsigned char key, int x, int y) {
	switch (key) {
	case 's':
		player.standUp();
		break;
	}
}

void spcialKeys(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP:
		player.jump();
		break;
	case GLUT_KEY_DOWN:
		player.duck();
		break;
	}
}

void specialKeysUp(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_DOWN:
		player.standUp();
		break;
	}
}

void main(int argc, char** argr) {
	glutInit(&argc, argr);

	glutInitWindowSize(800, 600);
	glutInitWindowPosition(550, 250);

	glutCreateWindow("Run Boy Run Boy");
	initGame();
	glutDisplayFunc(Display);
	glutTimerFunc(10, Timer, 0);

	glutKeyboardFunc(Keyboard);
	glutKeyboardUpFunc(KeyboardUp);
	glutSpecialFunc(spcialKeys);
	glutSpecialUpFunc(specialKeysUp);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	gluOrtho2D(0.0, 800, 0.0, 600);

	glutMainLoop();
}