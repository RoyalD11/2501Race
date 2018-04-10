#include "Menu.h"

Menu::Menu(glm::vec3 &entityPos, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements, glm::vec3 &entityVelocity)
	: GameEntity(entityPos, entityScale, entityRotationAmount, entityTexture, entityNumElements, type) {

}
void Menu::update(double deltaTime) {

}

void Menu::setPosition(float x, float y) {
	position.x = x;
	position.y = y;
}
