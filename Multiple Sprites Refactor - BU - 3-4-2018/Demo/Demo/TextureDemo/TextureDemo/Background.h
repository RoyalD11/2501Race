#pragma once

#include "GameEntity.h"
#include "BgEntity.h"
#include <iostream>
#include <fstream>
#include <vector>

class Background : public GameEntity {
public:
	Background(glm::vec3 &entityPos, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements);

	virtual void update(double deltaTime) override;

	void setPosition(float change);


private:
	GLuint* textures;
	glm::vec3 velocity;
};