#pragma once

#include "GameEntity.h"
#include "Background.h"

//Extra library so I can hold all the bullets
#include <list>

class Background : public GameEntity {
public:
	Background(glm::vec3 &entityPos, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements, glm::vec3 &bulletVelocity);

	virtual void update(double deltaTime) override;


	void Background::setPosition(float change);

private:
	glm::vec3 velocity;
	float bulletRotate;
};