#include "Model.h"


Model::Model(GLFWwindow* window) {
	updateables = std::vector <GameEntity*>();
	time = 0;
	this->window = window;
	reload = 50;
	
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
		if (!(bgObjects[i]->getPosition().x - player->getPosition().x > 0.5 ||
			bgObjects[i]->getPosition().x - player->getPosition().x < -0.5 ||
			bgObjects[i]->getPosition().y - player->getPosition().y > 0.5 ||
			bgObjects[i]->getPosition().y - player->getPosition().y < -0.5))
		{
			if (bgObjects[i]->type == 6) {
				player->hitWall = true;
				//std::cout << "a collision!";
				break;
			}
			else{ player->hitWall = false; }
			
			if (bgObjects[i]->type == 7) {
				std::cout << "Passed start!";
				player->ammo.push_back(new Bullet(glm::vec3(6.0f, 0.0f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), 0.0f, texture[2], size, glm::vec3(0.0f, 0.0f, 0.0f)));
			}
			
		}
			
	}

	for (int i = 0; i < enemies.size(); i++) {
		if (time % 100 == 0) {
			enemies[i]->setTarget(player->getPosition());
		}
	}
}


