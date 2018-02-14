#pragma once

#include "GameEntity.h"

class Animation : public GameEntity {
public:
	Animation(glm::vec3 &entityPos, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements);


	virtual void update(double deltaTime) override;

	// Setters
	inline void setTargetPos(glm::vec3 &target) { targetPos = target; }

	// pass the position, spriteHeight,spriteHeight and frameindex to shader
	void setupSprite(Shader shader, glm::vec2 position, float spriteHeight, float spriteWidth, int counter);
	int currentFrame;
	double frameTime, currentFrameTime; // frameTime: time before switching to the next frame. currentFrameTime will hold the current frames time
private:
	int _spriteWidth, _spriteHeight;
	glm::vec3 velocity;

	glm::vec3 targetPos;
};