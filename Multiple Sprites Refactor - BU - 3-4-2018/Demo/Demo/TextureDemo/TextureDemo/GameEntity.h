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
#include <stdlib.h>
#include <vector>

#include "Shader.h"

class GameEntity {
public:
	GameEntity(glm::vec3 &entityPos, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements, std::string &entityType);

	virtual void update(double deltaTime) = 0;
	//virtual void camera(glm::vec3 &entityPos) = 0;
	void render(Shader &shader, glm::vec3 cameraPos, float theta);
	void staticRender(Shader &shader);

	inline glm::vec3 getPosition() { return position; }
	inline glm::vec3 getVelocity() { return velocity; }
	inline glm::vec3 getScale() { return scale; }
	inline std::string getType() { return type; }
	inline void setPosition(glm::vec3 p) { position += p; }
	inline void setVelocity(glm::vec3 v) { velocity = v; }

	std::vector<GameEntity*> collidables;

protected:

	//Object/Update Variables
	glm::vec3 position;
	glm::vec3 velocity;

	glm::vec3 maxSpeed;

	glm::vec3 acceleration;
	glm::vec3 max_accel;

	glm::vec3 iVelocity;
	glm::vec3 targetPosition;
	glm::vec3 dVelocity;

	std::string type;

	//Display/Render Variables
	glm::vec3 scale;
	float rotationAmount;
	GLuint texture;
	GLint numElements;
};