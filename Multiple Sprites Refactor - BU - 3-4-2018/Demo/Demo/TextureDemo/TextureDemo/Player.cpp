#include "Player.h"
#include <stdio.h>
#include <iostream>

Player::Player(glm::vec3 &entityPos, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements, std::string type, glm::vec3 &playerVelocity)
	: GameEntity(entityPos, entityScale, entityRotationAmount, entityTexture, entityNumElements, type)
{
	//Sets the initial position and velocity
	position = glm::vec3(2.2, 3, 0);
	targetPosition = glm::vec3(0, 0, 0);
	velocity = glm::vec3(0, 0, 0);
	
	maxSpeed = glm::vec3(2.5, 2.5, 0);

	acceleration = glm::vec3(0.005, 0.005, 0);
	max_accel = glm::vec3(0.01, 0.01, 0);

	dVelocity = glm::vec3(0, 0, 0);
	iVelocity = glm::vec3(0, 0, 0);
	rotationAmount = -90;

	hitWall = false;
	
	points = 0;
	shot = 0;
	ammo_cap = 5;
	
	checkpoint = false;

	death_counter = 0;
	hun, tho = 0;

}

//Updates the position of the spaceship based on how the ship has rotated and its current velocity
//The constant being multipled in the cos and sin function is used to convert from degrees to radians
void Player::update(double deltaTime) {
	if (hitWall) { velocity *= glm::vec3(0.9, 0.9, 0); }
	if (death_counter > 3000) { death = true; }

	//dVelocity = (targetPosition - position);
	dVelocity.x = (targetPosition.x - position.x) / deltaTime;
	dVelocity.y = (targetPosition.y - position.y) / deltaTime;
	targetPosition = position;
	acceleration = (max_accel * (dVelocity - velocity));// / (glm::abs(dVelocity - velocity));

	velocity.x += (acceleration.x * deltaTime);
	velocity.y += (acceleration.y * deltaTime);
	
	
	if (velocity.x > maxSpeed.x || velocity.x < (-1 * maxSpeed.x)) {
		velocity.x = (maxSpeed.x*velocity.x) / (glm::abs(velocity.x));
	}
	if (velocity.y > maxSpeed.y || velocity.y < (-1 * maxSpeed.y)) {
		velocity.y = (maxSpeed.y*velocity.y) / (glm::abs(velocity.y));
	}
	

	//position.x += velocity.x * deltaTime;
	//position.y += velocity.y * deltaTime;

	position.x += cos(rotationAmount * 0.01745333) * deltaTime * velocity.y;
	position.y += sin(rotationAmount * 0.01745333) * deltaTime * velocity.y;

	updatePoints();
	

}

//Sets the ships velocity, and make sure the max speed is maintained and that it can slow to a stop if wanted
void Player::moveTo(float x, float y) {
	targetPosition.x += x;
	targetPosition.y += y;
}

void Player::moveTo(glm::vec3 inputVelocity) {
	targetPosition.x += inputVelocity.x;
	targetPosition.y += inputVelocity.y;
}


float Player::getVelocityY() {
	return velocity.y;
}

float Player::getVelocityX() {
	return velocity.x;
}

void Player::setVelocityY(float change) {
	velocity.x+=change;
}

void Player::setVelocityX(float change) {
	velocity.y+=change;
}

void Player::setMaxAccel(glm::vec3 mod) {
	max_accel = mod;
}

void Player::setTopSpeed(glm::vec3 mod) {
	maxSpeed = mod;
}

bool Player::checkSwitch() {
	return checkpoint;
}

void Player::lapCheckpoint(bool in) {
	checkpoint = in;
}

void Player::initActiveBullet(GLuint t, int s) {
	current_active_bullet = new Bullet(glm::vec3(6.0f, 0.0f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), 0.0f, t, s, "bullet", glm::vec3(0.0f, 0.0f, 0.0f));
}

void Player::setActiveBullet(Bullet* b) {
	current_active_bullet = b;
}

void Player::updatePoints() {
	hun = (points % 1000 - points % 100) / 100;
	tho = (points - hun) / 1000;
}

//Sets the ships rotation based on the direction you inputed from main
void Player::setRotation(float increment) {
	rotationAmount += increment + turningBuff;
}

void Player::rotateToMouse(float xpos, float ypos) {
	//std::cout << xpos << "\n";
	//std::cout << ypos << "\n";
	float newx = xpos - 400;
	float newy = ypos - 300;

	rotationAmount = atan2(newy, newx) * (180 / 3.14);
	rotationAmount *= -1;

	//std::cout << "\n\n" << rotationAmount << "\n\n";
}

float Player::getRotation() {
	return rotationAmount;
}


