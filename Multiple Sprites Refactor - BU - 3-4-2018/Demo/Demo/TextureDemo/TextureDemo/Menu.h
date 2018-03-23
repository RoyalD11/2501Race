#pragma once

#include "GameEntity.h"


class Menu : public GameEntity {
public:
	Menu(glm::vec3 &entityPos, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements, glm::vec3 &entityVelocity);


	void setPosition(float x,float y);
	virtual void update(double deltaTime) override;
private:

};