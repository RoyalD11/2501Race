#pragma once

#include "GameEntity.h"
#include "Background.h"
#include <iostream>
#include <fstream>

//Extra library so I can hold all the bullets
#include <list>

class Background : public GameEntity {
public:
	Background(glm::vec3 &entityPos, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements, glm::vec3 &bulletVelocity);

	virtual void update(double deltaTime) override;


	void setPosition(float change);
	void loadFromText();

private:
	int mapRows;
	int mapCols;

	int row1, col1;
	int** map1;
	int **mapData;


	glm::vec3 velocity;
	float bulletRotate;
};