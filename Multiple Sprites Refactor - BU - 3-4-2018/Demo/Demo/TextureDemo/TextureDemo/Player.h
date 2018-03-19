#pragma once

#include "GameEntity.h"

class Player : public GameEntity {
public:
	Player(glm::vec3 &entityPos, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements, glm::vec3 &playerVelocity);

	virtual void update(double deltaTime) override;

	void Player::setRotation(float increment);

	void Player::moveTo(float x, float y);

	void Player::rotateToMouse(float x, float y);

	void Player::moveTo(glm::vec3 inputVelocity);

	float Player::getRotation();

	glm::vec3 Player::getVelocity();

	float Player::getVelocityY();

	float Player::getVelocityX();

private:

};