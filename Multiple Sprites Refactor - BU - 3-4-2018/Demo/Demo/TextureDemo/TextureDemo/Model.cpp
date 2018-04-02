#include "Model.h"


Model::Model(GLFWwindow* window, int* state) {
	this->state = state;
	updateables = std::vector <GameEntity*>();
	time = 0;
	this->window = window;
	reload = 50;
	spriteCount = 3;
	startRace = true;
	lap = 1;
	player_deaths = 0;
	player_points = 0;
	player_wins = 0;
	player_ammo_cap = 5;
}



//Full game function!
void Model::update(double deltaTime, Shader shader) {

	
	//if (startRace) { startCountDown(); }
	if (player->death) { endGame(false); }

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

	//Blank Background used for placeholder
	Background* currentTile = new Background(glm::vec3(0,0,0), glm::vec3(0, 0, 0), 0.0f, texture[0], size, 0);

	for (int i = 0; i < bgObjects.size(); i++) {
		
		if (!(bgObjects[i]->getPosition().x - player->getPosition().x > 0.5 ||
			bgObjects[i]->getPosition().x - player->getPosition().x < -0.5 ||
			bgObjects[i]->getPosition().y - player->getPosition().y > 0.5 ||
			bgObjects[i]->getPosition().y - player->getPosition().y < -0.5) &&
			bgObjects[i] != currentTile)
		{
			currentTile = bgObjects[i];
			if (bgObjects[i]->type == 6) {
				player->hitWall = true;
				//std::cout << "a collision!";
				break;
			}
			else { player->hitWall = false; }

			//passes start;
			if (bgObjects[i]->type == 7) {
				if (player->checkSwitch()) {
					//player->ammo.push_back(new Bullet(glm::vec3(6.0f, 0.0f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), 0.0f, texture[2], size, glm::vec3(0.0f, 0.0f, 0.0f)));
					loadPlayerBullets();
					player->lapCheckpoint(false);
					lap++;
					std::cout << "Lap: " << lap << "\n";
				}
			}
			//passes lap checkpoint
			if (bgObjects[i]->type == 8) {
				player->lapCheckpoint(true);
			}

			//Checks for coin tile
			if (bgObjects[i]->type == 9) {
				player->points++;
			}
		}
	}
	
	if (time <= 0) {
		for (int i = 0; i < enemies.size(); i++) {
			enemies[i]->setTarget(player->getPosition());
		}
		time = 100;
	}
	//Timer to keep track of when next shot can be fired
	if (reload > 0) {
		reload--;
	}
	time--;
}


void Model::loadGameObjects() {
	Player* player = new Player(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.35f, 0.35f, 0.35f), 0.0f, texture[0], size, glm::vec3(0.0f, 0.0f, 0.0f));
	player->ammo_cap = player_ammo_cap;

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

	GLuint temp[10] = { texture[7], texture[8], texture[9], texture[10], texture[11], texture[12], texture[13], texture[21], texture[25], texture[26] };
	initBackgrounds(size, temp);
}

void Model::removeGameObjects() {

}

void Model::startCountDown() {
	int timer = 10000;
	while (timer >= 0) {

		//This is where we will cal animations for start
		std::cout << "\n";
		timer--;
		
	}
	
	startRace = false;
}

void Model::firePlayerBullets() {
	if (reload <= 0) {
		if (player->shot < player->ammo_cap && player->ammo.size() != 0) {
			player->ammo[player->shot]->fire(player->getPosition(), player->getRotation());
			updateables.insert(updateables.begin(), player->ammo[player->shot]);
			player->shot++;
			reload = 500;
			std::cout << "FIRE \n";
		}
		else {
			std::cout << "Out of ammo! \n";
			reload = 500;
			player->shot = 0;
			player->ammo.clear();
		}
	}
}

void Model::loadPlayerBullets() {
	//loads bullets into player
	for (int i = 0; i < player->ammo_cap; i++) {
		player->ammo.push_back(new Bullet(glm::vec3(6.0f, 0.0f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), 0.0f, texture[2], size, glm::vec3(0.0f, 0.0f, 0.0f)));
	}
}

void Model::checkLap() {
	if (lap > 3) {

		//Updates global points and ends game
		endGame(true);
	}
}

void Model::endGame(bool winloss) {


	//resets gamestate back to menu
	*state = 0;

	if (winloss) {
		player_wins++;
		player_points += player->points;
	}
	else { player_deaths++; }
	
	//end game
	unmountGame();
}

void Model::printStats() {
	std::cout << "\n \n";
	std::cout << "Player Race Balance: " << player->points << "\n";
	std::cout << "Current Lap:         " << lap << "\n";
	std::cout << "Player Ammo:         " << player->ammo.size() << "\n";
	std::cout << "Player Total Points: " << player_points << "\n";
	std::cout << "Player Total Wins:   " << player_wins << "\n";
	std::cout << "Player Total Deaths: " << player_deaths << "\n";
}


//Load Background from text file
void Model::initBackgrounds(int size, GLuint imports[10]) {

	std::ifstream fileHndl;

	int mapRows;
	int mapCols;
	int **mapData;
	int** map1;

	fileHndl.open("Assets/map3.txt");
	fileHndl >> mapRows;
	fileHndl >> mapCols;

	mapData = new int*[mapRows];
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
	Background* temp;
	//GLuint texture = imports[0];
	for (int i = 0; i < mapRows; i++) {
		for (int j = 0; j < mapCols; j++) {
			std::cout << mapData[i][j] << " ";
			if (mapData[i][j] == 0) {
				//r-u
				temp = new Background(glm::vec3(i - 0.5, j - 0.5, 0.0f), glm::vec3(1, 1, 0.5), 0.0f, imports[0], size, 0);
			}
			else if (mapData[i][j] == 1) {
				//d-r
				temp = new Background(glm::vec3(i - 0.5, j - 0.5, 0.0f), glm::vec3(1, 1, 0.5), 0.0f, imports[1], size, 1);
			}
			else if (mapData[i][j] == 2) {
				//l-u
				temp = new Background(glm::vec3(i - 0.5, j - 0.5, 0.0f), glm::vec3(1, 1, 0.5), 0.0f, imports[2], size, 2);
			}
			else if (mapData[i][j] == 3) {
				//d-l
				temp = new Background(glm::vec3(i - 0.5, j - 0.5, 0.0f), glm::vec3(1, 1, 0.5), 0.0f, imports[3], size, 3);
			}
			else if (mapData[i][j] == 4) {
				//up
				temp = new Background(glm::vec3(i - 0.5, j - 0.5, 0.0f), glm::vec3(1, 1, 0.5), 0.0f, imports[4], size, 4);
			}
			else if (mapData[i][j] == 5) {
				//side
				temp = new Background(glm::vec3(i - 0.5, j - 0.5, 0.0f), glm::vec3(1, 1, 0.5), 0.0f, imports[5], size, 5);
			}
			else if (mapData[i][j] == 6) {
				//edge
				temp = new Background(glm::vec3(i - 0.5, j - 0.5, 0.0f), glm::vec3(1, 1, 0.5), 0.0f, imports[6], size, 6);
			}
			else if (mapData[i][j] == 7) {
				//edge
				temp = new Background(glm::vec3(i - 0.5, j - 0.5, 0.0f), glm::vec3(1, 1, 0.5), 0.0f, imports[7], size, 7);
			}
			else if (mapData[i][j] == 8) {
				//Lap checkpoint
				temp = new Background(glm::vec3(i - 0.5, j - 0.5, 0.0f), glm::vec3(1, 1, 0.5), 0.0f, imports[5], size, 8);
			}

			else if (mapData[i][j] == 9) {
				//coin tile A
				temp = new Background(glm::vec3(i - 0.5, j - 0.5, 0.0f), glm::vec3(1, 1, 0.5), 0.0f, imports[8], size, 9);
			}

			bgObjects.push_back(temp);
			updateables.push_back(temp);
		}
		std::cout << "\n";
	}
	std::cout << "Map Loaded \n";
	std::cout << "Press 'U' to call Current Games stats \n";
}


void Model::unmountGame() {
	//clear arrays
	updateables.clear();
	enemies.clear();
	bgObjects.clear();

	//reset values
	time = 0;
	reload = 50;
	spriteCount = 3;
	startRace = true;
	lap = 1;
}