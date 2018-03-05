#pragma once

#include "GameEntity.h"

class Background : public GameEntity {
public:
	Background(glm::vec3 &entityPos, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements);

	virtual void update(double deltaTime) override;

	void  Background::setRotation(float increment);

	void  Background::setVelocity(float z);

	float Background::getRotation();
		  
	float Background::getVelocity();

};