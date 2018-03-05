#include "Background.h"

Background::Background(glm::vec3 &entityPos, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements)
	: GameEntity(entityPos, entityScale, entityRotationAmount, entityTexture, entityNumElements)
{
	position.x = 0;
	position.y = 0;
}

//Updates the position of the spaceship based on how the ship has rotated and its current velocity
//The constant being multipled in the cos and sin function is used to convert from degrees to radians
void Background::update(double deltaTime) {

}

//Sets the ships velocity, and make sure the max speed is maintained and that it can slow to a stop if wanted
void Background::setVelocity(float z) {

}

float Background::getVelocity() {
	return velocity;
}

//Sets the ships rotation based on the direction you inputed from main
void Background::setRotation(float increment) {
}

float Background::getRotation() {
	return rotationAmount;
}
