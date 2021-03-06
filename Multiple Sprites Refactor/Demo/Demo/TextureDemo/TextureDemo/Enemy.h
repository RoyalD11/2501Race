#pragma once

#include "GameEntity.h"
#include "Player.h"
#include "Bullet.h"
#include <cmath>

class Enemy : public GameEntity {
public:
	Enemy(glm::vec3 &entityPos, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements, Player *playerEntity);

	virtual void update(double deltaTime) override;

	void animate(GLuint t);

	//method added to the enemy class
	void collision(Bullet bullet);

private:
	Player *player;
	bool check;
	float calc;
};