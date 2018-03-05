#include "Player.h"

Player::Player(glm::vec3 &entityPos, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements, glm::vec3 &playerVelocity)
	: GameEntity(entityPos, entityScale, entityRotationAmount, entityTexture, entityNumElements)
{
	//Sets the initial position and velocity
	position.x = 0;
	position.y = 0;
	velocity = 0;

}

//Updates the position of the spaceship based on how the ship has rotated and its current velocity
//The constant being multipled in the cos and sin function is used to convert from degrees to radians
void Player::update(double deltaTime) {
	position.x += cos(rotationAmount * 0.01745333) * (float)deltaTime * velocity;
	position.y += sin(rotationAmount * 0.01745333) * (float)deltaTime * velocity;

	//These four if statements make it so the ship will loop around the screen, so if you leave from the top you come back from the bottom etc
	/*
	if (position.x > 1) {
		position.x = -0.98;
	}

	if (position.x < -1) {
		position.x = 0.98;
	}

	if (position.y > 1) {
		position.y = -0.98;
	}

	if (position.y < -1) {
		position.y = 0.98;
	}
	*/
}

//Sets the ships velocity, and make sure the max speed is maintained and that it can slow to a stop if wanted
void Player::setVelocity(float z) {

	if (velocity > 0 || velocity < 5) {
		velocity += z;
	}
	if (velocity <= 0) {
		velocity = 0;
	}
	if (velocity >= 5) {
		velocity = 5;
	}
}

float Player::getVelocity() {
	return velocity;
}

//Sets the ships rotation based on the direction you inputed from main
void Player::setRotation(float increment) {
	rotationAmount += increment;
}

float Player::getRotation() {
	return rotationAmount;
}
