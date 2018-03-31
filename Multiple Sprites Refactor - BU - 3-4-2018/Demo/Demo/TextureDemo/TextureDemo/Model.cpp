#include "Model.h"


Model::Model(GLFWwindow* window) {
	updateables = std::vector <GameEntity*>();
	time = 0;
	this->window = window;
	reload = 50;
	spriteCount = 3;
}


void Model::loadFromText() {
	

}


//Full game function!
void Model::update(double deltaTime, Shader shader) {
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
			else { player->hitWall = false; }

			if (bgObjects[i]->type == 7) {
				std::cout << "Passed start! \n";
				if (player->ammo.size() < ammo_cap ) player->ammo.push_back(new Bullet(glm::vec3(6.0f, 0.0f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), 0.0f, texture[2], size, glm::vec3(0.0f, 0.0f, 0.0f)));
				break;
			}
		}
		
			
	}


	if (time <= 0) {
		for (int i = 0; i < enemies.size(); i++) {
			enemies[i]->setTarget(player->getPosition());
		}
		time = 100;
	}
	time--;
}


void Model::loadGameObjects() {
	Player* player = new Player(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.35f, 0.35f, 0.35f), 0.0f, texture[0], size, glm::vec3(0.0f, 0.0f, 0.0f));

	std::vector<GLuint> tempTextures;
	tempTextures.push_back(texture[3]);
	tempTextures.push_back(texture[4]);
	tempTextures.push_back(texture[5]);


	Enemy* police1 = new Enemy(glm::vec3(2.4, 3.5, 0), glm::vec3(0.5f, 0.5f, 0.5f), 0.0f, texture[4], size, player, glm::vec3(1.5, 1.5, 0), glm::vec3(3, 3, 0), tempTextures);
	Enemy* police4 = new Enemy(glm::vec3(2.5, 3.2, 0), glm::vec3(0.5f, 0.5f, 0.5f), 0.0f, texture[4], size, player, glm::vec3(3, 3, 0), glm::vec3(1.5, 1.5, 0), tempTextures);
	Enemy* police2 = new Enemy(glm::vec3(2.3, 3.8, 0), glm::vec3(0.5f, 0.5f, 0.5f), 0.0f, texture[4], size, player, glm::vec3(2, 2, 0), glm::vec3(2, 2, 0), tempTextures);
	Enemy* police3 = new Enemy(glm::vec3(2.2, 4, 0), glm::vec3(0.5f, 0.5f, 0.5f), 0.0f, texture[4], size, player, glm::vec3(2, 2, 0), glm::vec3(3, 3, 0), tempTextures);



	this->player = player;



	//push back objects
	updateables.push_back(player);

	updateables.push_back(police1);
	updateables.push_back(police2);
	updateables.push_back(police3);
	updateables.push_back(police4);
	//updateables.push_back(test);

	enemies.push_back(police1);
	enemies.push_back(police2);
	enemies.push_back(police3);
	enemies.push_back(police4);

}

void Model::removeGameObjects() {

}

