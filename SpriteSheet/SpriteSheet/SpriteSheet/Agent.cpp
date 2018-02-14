#include "Agent.h"

Agent::Agent(glm::vec3 &entityPos, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements)
	: GameEntity(entityPos, entityScale, entityRotationAmount, entityTexture, entityNumElements),
	  targetPos(0.0f, 0.0f, 0.0f), velocity(0.0f, 0.0f, 0.0f)
{
	currentState = State::CHASE;
	speed = 0.5f;
	max_velocity = glm::vec3(0.9, 0.9, 0.0);
	max_speed = glm::vec3(0.6, 0.6, 0.0);
}

void Agent::update(double deltaTime) {
	if (currentState == State::CHASE) {
		//velocity = glm::normalize(targetPos - position);
		//position += velocity * speed * (float)deltaTime;
		glm::vec3 v_t =  targetPos - position;
		glm::vec3 a = max_speed * (v_t - velocity) / glm::length(v_t - velocity);
		velocity = velocity + a*(float)deltaTime;
		position += velocity * (float)deltaTime;
	}
	if (currentState == State::FLEE) {
		glm::vec3 v_t = position - targetPos;
		glm::vec3 a = max_speed * (v_t - velocity) / glm::length(v_t - velocity);
		velocity = velocity + a*(float)deltaTime;
		position += velocity * (float)deltaTime;
	}
	if (currentState == State::WANDER) {
		velocity = glm::normalize(targetPos -  position);
		position += velocity * (float)deltaTime;
	}

}