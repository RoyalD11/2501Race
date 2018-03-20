#pragma once

#include "GameEntity.h"
#include "Background.h"
#include <iostream>
#include <fstream>

//Extra library so I can hold all the bullets
#include <vector>

class BgEntity : public GameEntity {
public:
	BgEntity(glm::vec3 &entityPos, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements, int type);

	virtual void update(double deltaTime) override;

	void setPosition(float change);

private:
	int type;
};