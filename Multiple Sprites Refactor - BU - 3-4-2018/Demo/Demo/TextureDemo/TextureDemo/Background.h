#pragma once

#include "GameEntity.h"
#include <iostream>
#include <fstream>
#include <vector>

class Background : public GameEntity {
public:
	Background(glm::vec3 &entityPos, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements, std::string type, int bgType);
	virtual void update(double deltaTime) override;

	void setPosition(float change);
	int bgType;
	


private:
	GLuint* textures;
	//glm::vec3 velocity;
};