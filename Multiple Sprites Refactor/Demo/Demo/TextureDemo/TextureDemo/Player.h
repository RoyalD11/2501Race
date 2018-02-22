#pragma once

#include "GameEntity.h"

class Player : public GameEntity {
public:
	Player(glm::vec3 &entityPos, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements, glm::vec3 &playerVelocity);

	virtual void update(double deltaTime) override;

	void Player::setRotation(float increment);

	void Player::setVelocity(float z);

	float Player::getRotation();

	float Player::getVelocity();

private:
	float velocity;
};