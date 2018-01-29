#include "Bullet.h"

Bullet::Bullet(glm::vec3 &entityPos, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements, glm::vec3 &bulletVelocity)
	: GameEntity(entityPos, entityScale, entityRotationAmount, entityTexture, entityNumElements), velocity(bulletVelocity)
{
}

void Bullet::update(double deltaTime) {
	position += velocity * (float)deltaTime;
}

void Bullet::fire(glm::vec3 playerpos) {
	position.x = playerpos.x;
	position.y = playerpos.y;
	velocity.x = 2;
	velocity.y = 2;
}