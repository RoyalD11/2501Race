#include "Player.h"

Player::Player(glm::vec3 &entityPos, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements) 
	: GameEntity(entityPos, entityScale, entityRotationAmount, entityTexture, entityNumElements)
{
	x_vel = 0;
	y_vel = 0;
	position.x = 0;
	position.y = 0;
}


void Player::update(double deltaTime) {
	//position.x = 0.8f * sin(glfwGetTime());
	//position.x = x_vel;
	//position.y = y_vel;
}

void Player::setPosition(float x, float y) {
	position.x += x;
	position.y += y;
}



