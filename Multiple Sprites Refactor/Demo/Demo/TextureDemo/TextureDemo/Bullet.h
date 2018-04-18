#pragma once

#include "GameEntity.h"

//Extra library so I can hold all the bullets
#include <list>

class Bullet : public GameEntity {
public:
	Bullet(glm::vec3 &entityPos, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements, glm::vec3 &bulletVelocity);

	virtual void update(double deltaTime) override;

	//Prototype of the fire function added
	void fire(glm::vec3 playerPos, float playerRotation);

	void Bullet::setPosition(float change);

private:
	glm::vec3 velocity;
	float bulletRotate;
};