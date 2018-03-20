#include "Background.h"

//Extra library so I can hold all the bullets
#include <list>

Background::Background(glm::vec3 &entityPos, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements, glm::vec3 &bulletVelocity)
	: GameEntity(entityPos, entityScale, entityRotationAmount, entityTexture, entityNumElements), velocity(bulletVelocity)
{
	loadFromText();
}

//Updates the position of the bullet, also rotates the bullet as it moves through the air
//The constant being multipled in the cos and sin function is used to convert from degrees to radians
void Background::update(double deltaTime) {

}


void Background::setPosition(float change) {
	position.y = change;
	position.x = change;
	velocity.x = change;
	velocity.y = change;
	bulletRotate = change;

}

void Background::loadFromText() {
	std::ifstream fileHndl;

	fileHndl.open("Assets/map1.txt");
	fileHndl >> mapRows;
	fileHndl >> mapCols;

	mapData = new int *[mapRows];
	for (int i = 0; i < mapRows; i++) {
		mapData[i] = new int[mapCols];
	}

	for (int i = 0; i < mapRows; i++) {
		for (int j = 0; j < mapCols; j++) {
			fileHndl >> mapData[i][j];
		}
	}

	int row1 = mapRows;
	int col1 = mapCols;
	for (int i = 0; i < row1; i++) {
		for (int j = 0; j < col1; j++) {
			map1 = mapData;
		}
	}
	std::cout << "Map Loaded";
}
