#pragma once

//Controller Class

#include "GameEntity.h"
#include "Background.h"
#include "Player.h"
#include "Shader.h"
#include "Enemy.h"
#include "Menu.h"

#include "Window.h"
#include <vector>
#include <algorithm>




class Model {
public:
	Model(GLFWwindow* window, int* state);

	//All GameObjects in Game
	std::vector <GameEntity*> updateables = std::vector <GameEntity*>();
	std::vector <Enemy*>      enemies = std::vector <Enemy*>();
	std::vector <Background*> bgObjects = std::vector <Background*>();
	std::vector <GameEntity*> cars = std::vector <GameEntity*>();
	

	void update(double deltaTime, Shader shader);

	void loadGameObjects();
	void removeGameObjects();
	void startCountDown();
	void firePlayerBullets();
	void loadPlayerBullets();
	void checkLap();
	void printStats();
	void initBackgrounds(int size, GLuint imports[10]);
	void initHud();


	void boxCollision(GameEntity* a, GameEntity* b);




	//Override function
	void basicCollision(char mode, double alpha, double R,
		double m1, double m2, double r1, double r2,
		double& x1, double& y1, double& x2, double& y2,
		double& vx1, double& vy1, double& vx2, double& vy2,
		int& error);



	void endGame(bool winloss);

	//Used for re-loading game
	void unmountGame();
	

	int time;

	GLFWwindow* window;
	int* state;
	GLuint* texture;

	//char* map = "map3.txt";
	std::string map = "map3.txt";

	int size;
	int reload;
	int spriteCount;
	int lap;
	bool startRace;

	Background* currentTile;

	/*Constant player specific variables*/
	Player* player;
	int player_wins;
	int player_ammo_cap;
	int player_deaths;
	int player_points;

private:
	std::vector<Menu*> hundred;
	std::vector<Menu*> thousand;
	
};