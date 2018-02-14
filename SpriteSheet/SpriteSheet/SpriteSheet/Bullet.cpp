#include "Bullet.h"

Bullet::Bullet(glm::vec3 &entityPos, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements, glm::vec3 &bulletVelocity)
	: GameEntity(entityPos, entityScale, entityRotationAmount, entityTexture, entityNumElements), velocity(bulletVelocity)
{
}

void Bullet::update(double deltaTime) {
	position += velocity * (float)deltaTime;
}