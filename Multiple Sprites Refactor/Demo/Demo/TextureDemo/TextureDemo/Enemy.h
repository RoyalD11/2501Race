#pragma once

#include "GameEntity.h"
#include "Player.h"

class Enemy : public GameEntity {
public:
	Enemy(glm::vec3 &entityPos, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements, Player *playerEntity);

	virtual void update(double deltaTime) override;
private:
	Player *player;
};