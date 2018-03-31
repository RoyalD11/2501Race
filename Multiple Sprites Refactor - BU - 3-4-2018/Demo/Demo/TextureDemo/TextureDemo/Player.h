#pragma once

#include "GameEntity.h"
#include "Bullet.h"
#include "Background.h"

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

	float Player::getVelocityX();

	float Player::getVelocityY();

	void Player::setVelocityY(float change);

	void Player::setVelocityX(float change);

	void Player::setMaxAccel(glm::vec3 mod);

	void Player::setTopSpeed(glm::vec3 mod);

	bool hitWall;

	int coins;

	int turningBuff;


	std::vector<Bullet*> ammo = std::vector<Bullet*>();

private:

};