#pragma once

#include "GameEntity.h"
#include "Player.h"
#include "Bullet.h"
#include <cmath>

class Enemy : public GameEntity {
public:
	Enemy(glm::vec3 &entityPos, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements, Player *playerEntity, glm::vec3 maxSpeed, glm::vec3 accel, std::vector<GLuint> tex);

	virtual void update(double deltaTime) override;

	void animate();

	//method added to the enemy class
	bool collision(Bullet bullet);
	void rotateTo(float x, float y);
	bool getIfHit();
	void setTarget(glm::vec3 pos);
	std::vector<GLuint> tex;
	void checkPlayerDeath();

private:
	Player *player;
	bool check;
	float calc;
	bool hit;
	int time = 0;
	int spriteCount;
};