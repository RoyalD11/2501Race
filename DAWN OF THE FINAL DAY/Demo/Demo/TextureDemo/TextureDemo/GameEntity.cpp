#include "GameEntity.h"

GameEntity::GameEntity(glm::vec3 &entityPos, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements, std::string &entityType)
	: position(entityPos), scale(entityScale), rotationAmount(entityRotationAmount), texture(entityTexture), numElements(entityNumElements), type(entityType)
{
}

void GameEntity::render(Shader &shader, glm::vec3 cameraPos, float theta) {
	// Bind the entities texture
	glBindTexture(GL_TEXTURE_2D, texture);

	//Declaration of variables
	glm::mat4 translationMatrix;
	glm::mat4 scaleMatrix;
	glm::mat4 rotationMatrix;
	glm::mat4 transformationMatrix;

	//translationMatrix = glm::translate(glm::mat4(1.0f), position - cameraPos);


	//ISROT based transformations
	//Set Scale
	scaleMatrix = glm::scale(glm::mat4(1.0f), scale);

	//Set rotation
	rotationMatrix = glm::rotate(glm::mat4(1.0f), rotationAmount, glm::vec3(0.0f, 0.0f, 1.0f));

	//Set Translation
	translationMatrix = glm::translate(glm::mat4(1.0f), position - cameraPos);

	//Apply transformations
	transformationMatrix = translationMatrix * rotationMatrix * scaleMatrix;
	shader.setUniformMat4("x", transformationMatrix);

	
	// Draw the entity
	glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_INT, 0);

}

void GameEntity::staticRender(Shader &shader) {
	// Bind the entities texture
	glBindTexture(GL_TEXTURE_2D, texture);

	//Declaration of variables
	glm::mat4 translationMatrix;
	glm::mat4 scaleMatrix;
	glm::mat4 rotationMatrix;
	glm::mat4 transformationMatrix;

	//translationMatrix = glm::translate(glm::mat4(1.0f), position - cameraPos);


	//ISROT based transformations
	//Set Scale
	scaleMatrix = glm::scale(glm::mat4(1.0f), scale);

	//Set rotation
	rotationMatrix = glm::rotate(glm::mat4(1.0f), rotationAmount, glm::vec3(0.0f, 0.0f, 1.0f));

	//Set Translation
	translationMatrix = glm::translate(glm::mat4(1.0f), position);

	//Apply transformations
	transformationMatrix = translationMatrix * rotationMatrix * scaleMatrix;
	shader.setUniformMat4("x", transformationMatrix);


	// Draw the entity
	glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_INT, 0);

}