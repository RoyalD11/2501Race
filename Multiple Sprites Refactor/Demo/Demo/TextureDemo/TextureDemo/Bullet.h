#pragma once

#include "GameEntity.h"

class Bullet : public GameEntity {
public:
	Bullet(glm::vec3 &entityPos, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements, glm::vec3 &bulletVelocity);

	virtual void update(double deltaTime) override;
private:
	glm::vec3 velocity;
};