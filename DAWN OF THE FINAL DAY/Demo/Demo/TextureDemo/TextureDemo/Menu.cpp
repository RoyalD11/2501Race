#include "Menu.h"

Menu::Menu(glm::vec3 &entityPos, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements, glm::vec3 &entityVelocity, Player* p)
	: GameEntity(entityPos, entityScale, entityRotationAmount, entityTexture, entityNumElements, type), player(p) {
}
Menu::Menu(glm::vec3 &entityPos, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements, glm::vec3 &entityVelocity)
	: GameEntity(entityPos, entityScale, entityRotationAmount, entityTexture, entityNumElements, type) {
}
Menu::Menu(glm::vec3 &entityPos, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements, glm::vec3 &entityVelocity, std::string type)
	: GameEntity(entityPos, entityScale, entityRotationAmount, entityTexture, entityNumElements, type) {
}

void Menu::update(double deltaTime) {
	
	//falling snow
	if (type == "effects1") {
		position.y -= 0.005;
		if (position.y <= -2) {
			position.y = 2;
		}
	}

	//hectic sandstorm
	else if (type == "effects2") {
		position.x -= 0.005;
		if (position.x <= -2) {
			position.x = 2;
		}
	}
}

void Menu::setPosition(float x, float y) {

	position.x = x;
	position.y = y;
}
