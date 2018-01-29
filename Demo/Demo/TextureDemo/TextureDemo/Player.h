#pragma once

#include "GameEntity.h"

class Player : public GameEntity {
public:

	int x_vel;
	int y_vel;

	Player(glm::vec3 &entityPos, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements);

	virtual void update(double deltaTime) override;

	void setPosition(float x, float y);
	//void setVel
};