#include "Model.h"


Model::Model(GLFWwindow* window) {
	updateables = std::vector <GameEntity*>();
	time = 0;
	this->window = window;
}


void Model::loadFromText() {
	

}


//Full game function!
void Model::update(double deltaTime, Shader shader) {
	time++;
	for (int i = 0; i < updateables.size(); i++) {
		
		//calls render and update functions		
		updateables[i]->update(deltaTime);
		if (!(updateables[i]->getPosition().x - player->getPosition().x > 2 ||
			updateables[i]->getPosition().x - player->getPosition().x < -2 ||
			updateables[i]->getPosition().y - player->getPosition().y > 2 ||
			updateables[i]->getPosition().y - player->getPosition().y < -2))
		{
			updateables[i]->render(shader, player->getPosition(), player->getRotation());
		}
	}

	for (int i = 0; i < bgObjects.size(); i++) {
		if ((!(bgObjects[i]->getPosition().x - player->getPosition().x > 0.5 ||
			bgObjects[i]->getPosition().x - player->getPosition().x < -0.5 ||
			bgObjects[i]->getPosition().y - player->getPosition().y > 0.5 ||
			bgObjects[i]->getPosition().y - player->getPosition().y < -0.5)) &&
			bgObjects[i]->type == 6)
		{
			player->hitWall = true;
			std::cout << "a collision!";
			break;
		}
		else {
			player->hitWall = false;
		}
	}

	for (int i = 0; i < enemies.size(); i++) {
		if (time % 100 == 0) {
			enemies[i]->setTarget(player->getPosition());
		}
	}
}


