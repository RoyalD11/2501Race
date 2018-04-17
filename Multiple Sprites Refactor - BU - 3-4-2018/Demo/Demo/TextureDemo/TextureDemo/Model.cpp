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

	//Renders players points HUD
	for (int i = 0; i < player->tho; i++) {
		thousand[i]->staticRender(shader);
	}
	
	for (int i = 0; i < player->hun; i++) {
		hundred[i]->staticRender(shader);
	}


	//if (startRace) { startCountDown(); }
	if (player->death) { endGame(false); }

	int a = 0;
	for (int i = 0; i < updateables.size(); i++) {
		if (a < enemies.size()) {
			if (enemies[a]->collision(*player->current_active_bullet)) {
				updateables.erase(std::remove(updateables.begin(), updateables.end(), enemies[a]), updateables.end());
				enemies.erase(enemies.begin() + a);
				cars.erase(cars.begin() + a);
			}
			else {
				a++;
			}
		}


		//Updates all GameEntitys positions	
		updateables[i]->update(deltaTime);

		// **  Only displays if on the screen **
		//	   (makes its easier on lower end graphics cards)
		if (!(updateables[i]->getPosition().x - player->getPosition().x > 2 ||
			updateables[i]->getPosition().x - player->getPosition().x < -2 ||
			updateables[i]->getPosition().y - player->getPosition().y > 2 ||
			updateables[i]->getPosition().y - player->getPosition().y < -2))
		{
			updateables[i]->render(shader, player->getPosition(), player->getRotation());
		}

		

		//Car Collsion detection, for elastic collision ect
		/*
		if (updateables[i]->getType() == "enemy" || updateables[i]->getType() == "player") {
			int status = 0;
			for (int j = 0; j < cars.size(); j++) {
				if (updateables[i] != cars[j]) {
					
					double alpha = 0;
					double x1 = updateables[i]->getPosition().x;
					double y1 = updateables[i]->getPosition().y;
					double x2 = cars[j]->getPosition().x;
					double y2 = cars[j]->getPosition().y;

					double vx1 = updateables[i]->getVelocity().x;
					double vy1 = updateables[i]->getVelocity().y;
					double vx2 = cars[j]->getVelocity().x;
					double vy2 = cars[j]->getVelocity().y;

					basicCollision('s', alpha, 0, 1, 10, 0.01, 0.01,
						x1, y1, x2, y2,
						vx1, vy1, vx2, vy2, status);

					if (status == 0) {
						std::cout << updateables[i]->getPosition().x << " , " << updateables[i]->getPosition().y << "          " << cars[j]->getPosition().x << " , " << cars[j]->getPosition().y << "\n";
						std::cout << updateables[i]->getType() << " collided  with " << cars[j]->getType() << "Positions: \n";
						std::cout << updateables[i]->getPosition().x << " , " << updateables[i]->getPosition().y << "          " << cars[j]->getPosition().x << " , " << cars[j]->getPosition().y << "\n \n";
					}

					//updateables[i]->setPosition(glm::vec3(x1, y1, 0));
					//cars[j]->setPosition(glm::vec3(x2, y2, 0));
					updateables[i]->setVelocity(glm::vec3(vx1, vy1, 0));
					cars[j]->setVelocity(glm::vec3(vx2, vy2, 0));
					
					//boxCollision(updateables[i], cars[j]);
				}
			}
		}
		*/
	}

	//     ** Background Smart rendering and tile detection **

	for (int i = 0; i < bgObjects.size(); i++) {

		if (!(bgObjects[i]->getPosition().x - player->getPosition().x > 0.5 * bgObjects[i]->getScale().x ||
			bgObjects[i]->getPosition().x - player->getPosition().x < -0.5 * bgObjects[i]->getScale().x ||
			bgObjects[i]->getPosition().y - player->getPosition().y > 0.5 *bgObjects[i]->getScale().y ||
			bgObjects[i]->getPosition().y - player->getPosition().y < -0.5 * bgObjects[i]->getScale().y) &&
			bgObjects[i] != currentTile)
		{
			currentTile = bgObjects[i];
			if (bgObjects[i]->bgType == 6) {
				player->hitWall = true;
				//std::cout << "a collision!";
				break;
			}
			else { player->hitWall = false; }

			//passes start;
			if (bgObjects[i]->bgType == 7) {
				if (player->checkSwitch()) {
					//player->ammo.push_back(new Bullet(glm::vec3(6.0f, 0.0f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), 0.0f, texture[2], size, glm::vec3(0.0f, 0.0f, 0.0f)));
					loadPlayerBullets();
					player->lapCheckpoint(false);
					lap++;

					//add new enemy each succesful lap
					std::vector<GLuint> tempTextures;
					tempTextures.push_back(texture[22]);
					tempTextures.push_back(texture[23]);
					tempTextures.push_back(texture[24]);
					Enemy* p = new Enemy(glm::vec3(2.4, 3.5, 0), glm::vec3(0.35f, 0.2f, 0.5f),
						0.0f, texture[4], size, "enemy", player,
						glm::vec3(3, 3, 0),
						glm::vec3(3, 3, 0), tempTextures);
					updateables.insert(updateables.begin(), p);
					enemies.push_back(p);

					std::cout << "Lap: " << lap << "\n";
				}
			}
			//passes lap checkpoint
			if (bgObjects[i]->bgType == 8) {
				player->lapCheckpoint(true);
			}

			//Checks for coin tile
			if (bgObjects[i]->bgType == 9) {
				player->points+=100;
			}
			
		}
		
		// ** render background **
		if (!(bgObjects[i]->getPosition().x - player->getPosition().x > 2 ||
			bgObjects[i]->getPosition().x - player->getPosition().x < -2 ||
			bgObjects[i]->getPosition().y - player->getPosition().y > 2 ||
			bgObjects[i]->getPosition().y - player->getPosition().y < -2))
		{
			bgObjects[i]->render(shader, player->getPosition(), player->getRotation());
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
	Player* player = new Player(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.35f, 0.35f, 0.35f), 0.0f, texture[0], size, "player", glm::vec3(0.0f, 0.0f, 0.0f));
	player->ammo_cap = player_ammo_cap;
	player->initActiveBullet(texture[2], size);

	std::vector<GLuint> tempTextures;
	tempTextures.push_back(texture[3]);
	tempTextures.push_back(texture[4]);
	tempTextures.push_back(texture[5]);

	
	//Enemy* police1 = new Enemy(glm::vec3(2.4, 3.5, 0), glm::vec3(0.5f, 0.5f, 0.5f), 0.0f, texture[4], size, "enemy", player, glm::vec3(1.5, 1.5, 0), glm::vec3(3, 3, 0), tempTextures);

	Enemy* police1 = new Enemy(glm::vec3(2.4, 3.5, 0), glm::vec3(0.35, 0.2f, 0.5f), 0.0f, texture[4], size, "enemy", player, glm::vec3(1.8, 1.8, 0), glm::vec3(3, 3, 0), tempTextures);
	
	Enemy* police4 = new Enemy(glm::vec3(2.5, 3.2, 0), glm::vec3(0.35, 0.2f, 0.5f), 0.0f, texture[4], size, "enemy", player, glm::vec3(3, 3, 0), glm::vec3(1.5, 1.5, 0), tempTextures);
	Enemy* police2 = new Enemy(glm::vec3(2.3, 3.8, 0), glm::vec3(0.35, 0.2f, 0.5f), 0.0f, texture[4], size, "enemy", player, glm::vec3(2, 2, 0), glm::vec3(2, 2, 0), tempTextures);
	Enemy* police3 = new Enemy(glm::vec3(2.2, 4, 0), glm::vec3(0.35, 0.2f, 0.5f), 0.0f, texture[4], size, "enemy", player, glm::vec3(2, 2, 0), glm::vec3(3, 3, 0), tempTextures);
	


	this->player = player;



	//push back objects
	updateables.push_back(player);

	updateables.push_back(police1);
	//updateables.push_back(police2);
	//updateables.push_back(police3);
	//updateables.push_back(police4);
	

	enemies.push_back(police1);
	//enemies.push_back(police2);
	//enemies.push_back(police3);
	//enemies.push_back(police4);
	
	
	cars.push_back(police1);
	//cars.push_back(police2);
	//cars.push_back(police3);
	//cars.push_back(police4);

	cars.push_back(player);
	

	currentTile = new Background(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), 0.0f, texture[0], size, "bg", 0);

	GLuint temp[10] = { texture[7], texture[8], texture[9], texture[10], texture[11], texture[12], texture[13], texture[21], texture[25], texture[26] };
	initBackgrounds(size, temp);

	initHud();
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
			player->setActiveBullet(player->ammo[player->shot]);
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
		player->ammo.push_back(new Bullet(glm::vec3(6.0f, 0.0f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), 0.0f, texture[2], size, "bullet", glm::vec3(0.0f, 0.0f, 0.0f)));
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
	std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	std::cout << "Player Race Balance: " << player->points << "\n";
	std::cout << "Current Lap:         " << lap << "\n";
	std::cout << "Player Ammo:         " << player->ammo.size() << "\n";
	std::cout << "Player Heat:         " << player->death_counter << " / 5000   \n";
	std::cout << "=====================================================\n";
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

	//fileHndl.open("Assets/map3.txt");
	fileHndl.open("Assets/" + map);
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
				temp = new Background(glm::vec3(i - 0.5, j - 0.5, 0.0f), glm::vec3(1, 1, 0.5), 0.0f, imports[0], size, "bg", 0);
			}
			else if (mapData[i][j] == 1) {
				//d-r
				temp = new Background(glm::vec3(i - 0.5, j - 0.5, 0.0f), glm::vec3(1, 1, 0.5), 0.0f, imports[1], size, "bg", 1);
			}
			else if (mapData[i][j] == 2) {
				//l-u
				temp = new Background(glm::vec3(i - 0.5, j - 0.5, 0.0f), glm::vec3(1, 1, 0.5), 0.0f, imports[2], size, "bg", 2);
			}
			else if (mapData[i][j] == 3) {
				//d-l
				temp = new Background(glm::vec3(i - 0.5, j - 0.5, 0.0f), glm::vec3(1, 1, 0.5), 0.0f, imports[3], size, "bg", 3);
			}
			else if (mapData[i][j] == 4) {
				//up
				temp = new Background(glm::vec3(i - 0.5, j - 0.5, 0.0f), glm::vec3(1, 1, 0.5), 0.0f, imports[4], size, "bg", 4);
			}
			else if (mapData[i][j] == 5) {
				//side
				temp = new Background(glm::vec3(i - 0.5, j - 0.5, 0.0f), glm::vec3(1, 1, 0.5), 0.0f, imports[5], size, "bg", 5);
			}
			else if (mapData[i][j] == 6) {
				//edge
				temp = new Background(glm::vec3(i - 0.5, j - 0.5, 0.0f), glm::vec3(1, 1, 0.5), 0.0f, imports[6], size, "bg", 6);
			}
			else if (mapData[i][j] == 7) {
				//edge
				temp = new Background(glm::vec3(i - 0.5, j - 0.5, 0.0f), glm::vec3(1, 1, 0.5), 0.0f, imports[7], size, "bg", 7);
			}
			else if (mapData[i][j] == 8) {
				//Lap checkpoint
				temp = new Background(glm::vec3(i - 0.5, j - 0.5, 0.0f), glm::vec3(1, 1, 0.5), 0.0f, imports[5], size, "bg", 8);
			}

			else if (mapData[i][j] == 9) {
				//coin tile A
				temp = new Background(glm::vec3(i - 0.5, j - 0.5, 0.0f), glm::vec3(1, 1, 0.5), 0.0f, imports[8], size, "bg", 9);
			}

			bgObjects.push_back(temp);
			//updateables.push_back(temp);
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
	cars.clear();

	//reset values
	time = 0;
	reload = 50;
	spriteCount = 3;
	startRace = true;
	lap = 1;
}

void Model::basicCollision(char mode, double alpha, double R,
	double m1, double m2, double r1, double r2,
	double& x1, double& y1, double& x2, double& y2,
	double& vx1, double& vy1, double& vx2, double& vy2,
	int& error) {

		double  r12, m21, d, gammav, gammaxy, 
			dgamma, dr, dc, sqs, t,
			dvx2, a, x21, y21, vx21, 
			vy21, pi2, vx_cm, vy_cm;

		//     ***initialize some variables ****
		pi2 = 2 * acos(-1.0E0);
		error = 0;
		r12 = r1 + r2;
		m21 = m2 / m1;
		x21 = x2 - x1;
		y21 = y2 - y1;
		vx21 = vx2 - vx1;
		vy21 = vy2 - vy1;

		vx_cm = (m1*vx1 + m2 * vx2) / (m1 + m2);
		vy_cm = (m1*vy1 + m2 * vy2) / (m1 + m2);

		//     ****  return old positions and velocities if relative velocity =0 ****
		if (vx21 == 0 && vy21 == 0) { error = 1; return; }


		//     *** calculate relative velocity angle             
		gammav = atan2(-vy21, -vx21);




		//******** this block only if initial positions are given *********

		if (mode != 'f') {


			d = sqrt(x21*x21 + y21 * y21);

			//     **** return if distance between balls smaller than sum of radii ***
			if (d<r12) { error = 2; return; }

			//     *** calculate relative position angle and normalized impact parameter ***
			gammaxy = atan2(y21, x21);
			dgamma = gammaxy - gammav;
			if (dgamma>pi2) { dgamma = dgamma - pi2; }
			else if (dgamma<-pi2) { dgamma = dgamma + pi2; }
			dr = d * sin(dgamma) / r12;

			//     **** return old positions and velocities if balls do not collide ***
			if ((fabs(dgamma)>pi2 / 4 && fabs(dgamma)<0.75*pi2) || fabs(dr)>1)
			{
				error = 1; return;
			}


			//     **** calculate impact angle if balls do collide ***
			alpha = asin(dr);


			//     **** calculate time to collision ***
			dc = d * cos(dgamma);
			if (dc>0) { sqs = 1.0; }
			else { sqs = -1.0; }
			t = (dc - sqs * r12*sqrt(1 - dr * dr)) / sqrt(vx21*vx21 + vy21 * vy21);
			//    **** update positions ***
			x1 = x1 + vx1 * t;
			y1 = y1 + vy1 * t;
			x2 = x2 + vx2 * t;
			y2 = y2 + vy2 * t;


		}

		//******** END 'this block only if initial positions are given' *********



		//     ***  update velocities ***

		a = tan(gammav + alpha);

		dvx2 = -2 * (vx21 + a * vy21) / ((1 + a * a)*(1 + m21));

		vx2 = vx2 + dvx2;
		vy2 = vy2 + a * dvx2;
		vx1 = vx1 - m21 * dvx2;
		vy1 = vy1 - a * m21*dvx2;

		//     ***  velocity correction for inelastic collisions ***

		vx1 = (vx1 - vx_cm)*R + vx_cm;
		vy1 = (vy1 - vy_cm)*R + vy_cm;
		vx2 = (vx2 - vx_cm)*R + vx_cm;
		vy2 = (vy2 - vy_cm)*R + vy_cm;


		return;
}

void Model::boxCollision(GameEntity* a, GameEntity* b) {
	//float w = 0.5 * (a.width() + b.width());
	//float h = 0.5 * (a.height() + b.height());
	float w = 0.5 * (0.01);
	float h = 0.5 * (0.02);
	float dx = a->getPosition().x -b->getPosition().x;
	float dy = a->getPosition().y - b->getPosition().y;

	if (abs(dx) <= w && abs(dy) <= h)
	{
		/* collision! */
		float wy = w * dy;
		float hx = h * dx;
		std::cout << "( " << a->getPosition().x << " , " << a->getPosition().y << " )\n";

		if (wy > hx) {
			if (wy > -hx) {
				/* collision at the top */
				a->setPosition(glm::vec3(a->getPosition().x, a->getPosition().y - 0.1, 0));

			}
			else {
				a->setPosition(glm::vec3(a->getPosition().x + 0.1, a->getPosition().y, 0));
			}
			/* on the left */
		}
		else {
			if (wy > -hx) {
				a->setPosition(glm::vec3(a->getPosition().x - 0.1, a->getPosition().y, 0));
				/* on the right */
			}
			else {
				/* at the bottom */
				a->setPosition(glm::vec3(a->getPosition().x, a->getPosition().y + 0.1, 0));
			}
			
		}
		std::cout << "( " << a->getPosition().x << " , " << a->getPosition().y << " )\n \n \n";

	}
}

void Model::initHud() {
	
	for (int i = 0; i < 10; i++) {
		Menu* coin;
		Menu* bill;
		coin = new Menu(glm::vec3(i*-0.1, -0.8, 0), glm::vec3(0.2, 0.2, 2), 0.0f, texture[27], size, glm::vec3(0, 0, 0));
		hundred.push_back(coin);

		bill = new Menu(glm::vec3(i*-0.1, -0.7, 0), glm::vec3(0.2, 0.2, 2), 0.0f, texture[28], size, glm::vec3(0, 0, 0));
		thousand.push_back(bill);
	}
}