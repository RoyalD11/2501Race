#include "Model.h"


Model::Model(GLFWwindow* window) {
	updateables = std::vector <GameEntity*>();
	time = 0;
	this->window = window;
	reload = 50;
	spriteCount = 3;
	ambulanceCount = 22;
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
			else{ player->hitWall = false; }
			
			if (bgObjects[i]->type == 7) {
				std::cout << "Passed start! \n";
				player->ammo.push_back(new Bullet(glm::vec3(6.0f, 0.0f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), 0.0f, texture[2], size, glm::vec3(0.0f, 0.0f, 0.0f)));
				break;
			}
		}
			
	}

	if (spriteCount == 6) {
		spriteCount = 3;
	}
	if (ambulanceCount == 25) {
		ambulanceCount = 22;
	}

	

	if (time <= 0) {
		for (int i = 0; i < enemies.size(); i++) {
			enemies[i]->setTarget(player->getPosition());
			if (i != 1) enemies[i]->animate(texture[spriteCount]);
			else if(i == 1) enemies[i]->animate(texture[ambulanceCount]);
		}
		time = 100;
		spriteCount++;
	}

	time--;
}


void Model::loadGameObjects() {
	Player* player = new Player(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.35f, 0.35f, 0.35f), 0.0f, texture[0], size, glm::vec3(0.0f, 0.0f, 0.0f));

	Enemy* police1 = new Enemy(glm::vec3(2.4, 3.5, 0), glm::vec3(0.5f, 0.5f, 0.5f), 0.0f, texture[4], size, player, glm::vec3(1.5, 1.5, 0), glm::vec3(3, 3, 0));
	Enemy* Ambulance = new Enemy(glm::vec3(2.5, 3.2, 0), glm::vec3(0.5f, 0.5f, 0.5f), 0.0f, texture[22], size, player, glm::vec3(3, 3, 0), glm::vec3(1.5, 1.5, 0));
	Enemy* police2 = new Enemy(glm::vec3(2.3, 3.8, 0), glm::vec3(0.5f, 0.5f, 0.5f), 0.0f, texture[4], size, player, glm::vec3(2, 2, 0), glm::vec3(2, 2, 0));
	Enemy* police3 = new Enemy(glm::vec3(2.2, 4, 0), glm::vec3(0.5f, 0.5f, 0.5f), 0.0f, texture[4], size, player, glm::vec3(2, 2, 0), glm::vec3(3, 3, 0));


	//Bullet constructor
	Bullet* bullet = new Bullet(glm::vec3(6.0f, 0.0f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), 0.0f, texture[2], size, glm::vec3(0.0f, 0.0f, 0.0f));
	Bullet* bullet2 = new Bullet(glm::vec3(6.0f, 0.0f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), 0.0f, texture[2], size, glm::vec3(0.0f, 0.0f, 0.0f));
	Bullet* bullet3 = new Bullet(glm::vec3(6.0f, 0.0f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), 0.0f, texture[2], size, glm::vec3(0.0f, 0.0f, 0.0f));
	Bullet* bullet4 = new Bullet(glm::vec3(6.0f, 0.0f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), 0.0f, texture[2], size, glm::vec3(0.0f, 0.0f, 0.0f));
	Bullet* bullet5 = new Bullet(glm::vec3(6.0f, 0.0f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), 0.0f, texture[2], size, glm::vec3(0.0f, 0.0f, 0.0f));
	Bullet* bullet6 = new Bullet(glm::vec3(6.0f, 0.0f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), 0.0f, texture[2], size, glm::vec3(0.0f, 0.0f, 0.0f));
	Bullet* bullet7 = new Bullet(glm::vec3(6.0f, 0.0f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), 0.0f, texture[2], size, glm::vec3(0.0f, 0.0f, 0.0f));
	Bullet* bullet8 = new Bullet(glm::vec3(6.0f, 0.0f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), 0.0f, texture[2], size, glm::vec3(0.0f, 0.0f, 0.0f));
	Bullet* bullet9 = new Bullet(glm::vec3(6.0f, 0.0f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), 0.0f, texture[2], size, glm::vec3(0.0f, 0.0f, 0.0f));
	Bullet* bullet10 = new Bullet(glm::vec3(6.0f, 0.0f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), 0.0f, texture[2], size, glm::vec3(0.0f, 0.0f, 0.0f));




	this->player = player;


	//Array that holds all the bullets
	Bullet* ammo[AMMO_CAP];
	ammo[0] = bullet;
	ammo[1] = bullet2;
	ammo[2] = bullet3;
	ammo[3] = bullet4;
	ammo[4] = bullet5;
	ammo[5] = bullet6;
	ammo[6] = bullet7;
	ammo[7] = bullet8;
	ammo[8] = bullet9;
	ammo[9] = bullet10;

	//push back objects
	updateables.push_back(player);

	updateables.push_back(bullet);
	updateables.push_back(bullet2);
	updateables.push_back(bullet3);
	updateables.push_back(bullet4);
	updateables.push_back(bullet5);
	updateables.push_back(bullet6);
	updateables.push_back(bullet7);
	updateables.push_back(bullet8);
	updateables.push_back(bullet9);
	updateables.push_back(bullet10);


	updateables.push_back(police1);
	updateables.push_back(police2);
	updateables.push_back(police3);
	updateables.push_back(Ambulance);
	//updateables.push_back(test);

	enemies.push_back(police1);
	enemies.push_back(police2);
	enemies.push_back(police3);
	enemies.push_back(Ambulance);
}

void Model::removeGameObjects() {

}

