#include "Player.h"


Player::Player(glm::vec3 &entityPos, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements, glm::vec3 &playerVelocity)
	: GameEntity(entityPos, entityScale, entityRotationAmount, entityTexture, entityNumElements)
{
	//Sets the initial position and velocity
	position = glm::vec3(0, 0, 0);
	targetPosition = glm::vec3(0, 0, 0);
	velocity = glm::vec3(0, 0, 0);
	
	maxSpeed = glm::vec3(0.1, 0.1, 0);

	acceleration = glm::vec3(0, 0, 0);
	max_accel = glm::vec3(0.05, 0.05, 0);

	dVelocity = glm::vec3(0, 0, 0);
	rotationAmount = 0;
}

//Updates the position of the spaceship based on how the ship has rotated and its current velocity
//The constant being multipled in the cos and sin function is used to convert from degrees to radians
void Player::update(double deltaTime) {
	/*
	dVelocity = targetPosition - position;
	acceleration = (max_accel * (dVelocity - velocity)) / (glm::abs(dVelocity-velocity));
	velocity += (acceleration * (float)deltaTime);
	
	
	if (velocity.x> maxSpeed.x) {
		velocity.x = maxSpeed.x;//(maxSpeed.x*velocity.x) / (glm::abs(velocity.x));
	}
	if (velocity.x > maxSpeed.y) {
		velocity.y = maxSpeed.y;//(maxSpeed.y*velocity.y) / (glm::abs(velocity.y));
	}
	
	
	std::cout << (int)position.x << "\n";
	std::cout << (int)velocity.x << "\n";
	std::cout << deltaTime << "\n\n";
	position += velocity * (float)deltaTime;
	*/
	
	//position += velocity;
	//position.x += cos(rotationAmount * 0.01745333) * (float)deltaTime * velocity.x;
	//position.y += sin(rotationAmount * 0.01745333) * (float)deltaTime * velocity.y;
}

//Sets the ships velocity, and make sure the max speed is maintained and that it can slow to a stop if wanted
void Player::moveTo(float x, float y) {

	targetPosition.x = x;
	targetPosition.y = y;
}

void Player::moveTo(glm::vec3 inputVelocity) {
	targetPosition.x = inputVelocity.x;
	targetPosition.y = inputVelocity.y;
}

glm::vec3 Player::getVelocity() {
	return velocity;
}

//Sets the ships rotation based on the direction you inputed from main
void Player::setRotation(float increment) {
	rotationAmount += increment;
}

float Player::getRotation() {
	return rotationAmount;
}
