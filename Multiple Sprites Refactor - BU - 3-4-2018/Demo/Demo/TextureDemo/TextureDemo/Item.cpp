#include "Item.h"

Item::Item(glm::vec3 &entityPos, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLuint entityNumElements)
	: GameEntity(entityPos, entityScale, entityRotationAmount, entityTexture, entityNumElements)
{
	int currentItem;
	bool hit;
}

//Can be used to cycle the item options on the screen, similat to mario cart item boxes
void Item::animate(GLuint t) {
	texture = t;
}

//Will be used to check collision detection between player and item boxes
//Dont know if collision is being done properly, as I am using the equation for two circles
//But when collision happens a random number is chosen and that is the item we will get.
void Item::collision(Player player) {
	float colDetect = pow((player.getPosition().x - position.x), 2) + pow((player.getPosition().y - position.y), 2);
	if (pow(colDetect, 0.5) <= scale.x) {
		currentItem = randomItem();
		hit = true;

		//Temp solution, just moves it way off screen
		//To be changed later, 
		position.y = 100000000;

	}
}

int Item::getCurrentItem() {
	return currentItem;
}

//Returns a random number between 0 and 4
int Item::randomItem() {
	return rand() % 5;
}

//Will be used to reset the item box to the screen a set time after collision has happened
//We should pass is the initial position of the box
void Item::resetBox(float x, float y) {
	position.x = x;
	position.y = y;
}



