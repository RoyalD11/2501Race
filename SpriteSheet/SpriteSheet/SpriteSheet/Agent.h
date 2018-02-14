#pragma once

#include "GameEntity.h"

class Agent : public GameEntity {

	enum class State {
		CHASE, FLEE, WANDER
	};

public:
	Agent(glm::vec3 &entityPos, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements);

	virtual void update(double deltaTime) override;


	// Setters
	inline void setTargetPos(glm::vec3 &target) { targetPos = target; }
private:
	glm::vec3 velocity;
	float speed; 
	glm::vec3 max_velocity;
	glm::vec3 max_speed;
	
	State currentState;
	glm::vec3 targetPos;
};