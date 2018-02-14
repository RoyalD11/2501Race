#include "Enemy.h"

Enemy::Enemy(glm::vec3 &entityPos, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements, Player *playerEntity)
	: GameEntity(entityPos, entityScale, entityRotationAmount, entityTexture, entityNumElements), player(playerEntity)
{
}

void Enemy::update(double deltaTime) {
	position = player->getPosition() + glm::vec3(0.5f * glm::sin(glfwGetTime() * 3.0f), 0.5f * glm::cos(glfwGetTime() * 3.0f), 0.0f);
}