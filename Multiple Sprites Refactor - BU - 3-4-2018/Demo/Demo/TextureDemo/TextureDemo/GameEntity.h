#pragma once

//#include <Libraries/include/GL/glew.h>
//#include <glew.h>

#include <GL/glew.h>
#include <GL/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>

#include "Shader.h"

class GameEntity {
public:
	GameEntity(glm::vec3 &entityPos, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements);

	virtual void update(double deltaTime) = 0;
	//virtual void camera(glm::vec3 &entityPos) = 0;
	void render(Shader &shader, glm::vec3 cameraPos, float theta);

	inline glm::vec3 getPosition() { return position; }

protected:

	//Object/Update Variables
	glm::vec3 position;
	glm::vec3 velocity;

	glm::vec3 maxSpeed;

	glm::vec3 acceleration;
	glm::vec3 max_accel;

	glm::vec3 targetPosition;
	glm::vec3 dVelocity;


	//Display/Render Variables
	glm::vec3 scale;
	float rotationAmount;
	GLuint texture;
	GLint numElements;
};