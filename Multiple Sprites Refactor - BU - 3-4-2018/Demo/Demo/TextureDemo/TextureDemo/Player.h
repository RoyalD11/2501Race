#pragma once

#include "GameEntity.h"
#include "Bullet.h"
#include "Background.h"

class Player : public GameEntity {
public:
	Player(glm::vec3 &entityPos, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements, std::string type, glm::vec3 &playerVelocity);

	virtual void update(double deltaTime) override;

	void Player::setRotation(float increment);

	void Player::moveTo(float x, float y);

	void Player::rotateToMouse(float x, float y);

	void Player::moveTo(glm::vec3 inputVelocity);

	float Player::getRotation();

	float Player::getVelocityX();

	float Player::getVelocityY();

	void Player::setVelocityY(float change);

	void Player::setVelocityX(float change);

	void Player::setMaxAccel(glm::vec3 mod);

	void Player::setTopSpeed(glm::vec3 mod);

	void Player::initActiveBullet(GLuint t, int s);

	void setActiveBullet(Bullet* b);

	void updatePoints();

	bool hitWall;

	int points;
	int hun;
	int tho;

	int current_lap = 1;

	int turningBuff;
	int shot;
	int ammo_cap;

	bool death;
	int death_counter;

	bool checkSwitch();
	void lapCheckpoint(bool in);

	std::vector<Bullet*> ammo = std::vector<Bullet*>();

	Bullet* current_active_bullet;

private:
	bool checkpoint;
};