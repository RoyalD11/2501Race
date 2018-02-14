#include "Animation.h"

Animation::Animation(glm::vec3 &entityPos, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture , GLint entityNumElements)
	: GameEntity(entityPos, entityScale, entityRotationAmount, entityTexture, entityNumElements),
	targetPos(0.0f, 0.0f, 0.0f), velocity(0.0f, 0.0f, 0.0f)
{
	currentFrame = 0;  // the current frame to draw
	frameTime = 0.07;
	currentFrameTime = 0.0;
}

void Animation::update(double deltaTime) {
	currentFrameTime += deltaTime;

	// update to the next frame if it is time
	if (currentFrameTime >= frameTime) {
		currentFrame = (currentFrame + 1) % 8;
		currentFrameTime -= frameTime;
	}
}


// pass the position, spriteHeight,spriteHeight and frameindex to shader
void Animation::setupSprite(Shader shader, glm::vec2 position, float spriteHeight, float spriteWidth, int counter)
{
	_spriteWidth = spriteWidth;
	_spriteHeight = spriteHeight;
	targetPos = glm::vec3(position,0);

	shader.setUniform1i("frameindex", counter);
	shader.setUniform2f("position", position);
	shader.setUniform1f("spriteHeight", spriteHeight);
	shader.setUniform1f("spriteWidth", spriteWidth);
}

