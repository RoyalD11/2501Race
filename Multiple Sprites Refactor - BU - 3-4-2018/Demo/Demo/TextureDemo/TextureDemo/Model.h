#pragma once

//Controller Class

#include "GameEntity.h"
#include "Background.h"
#include "Player.h"
#include "Shader.h"
#include "Enemy.h"

#include "Window.h"
#include <vector>




class Model {
public:
	Model(GLFWwindow* window, int* state);

	//All GameObjects in Game
	std::vector <GameEntity*> updateables = std::vector <GameEntity*>();
	std::vector <Enemy*>      enemies = std::vector <Enemy*>();
	std::vector <Background*> bgObjects = std::vector <Background*>();
	
	

	void update(double deltaTime, Shader shader);

	void loadGameObjects();
	void removeGameObjects();
	void startCountDown();
	void firePlayerBullets();
	void loadPlayerBullets();
	void checkLap();
	void printStats();
	void initBackgrounds(int size, GLuint imports[10]);

	void endGame(bool winloss);

	//Used for re-loading game
	void unmountGame();
	

	int time;

	GLFWwindow* window;
	int* state;
	GLuint* texture;

	int size;
	int reload;
	int spriteCount;
	int lap;
	bool startRace;

	/*Constant player specific variables*/
	Player* player;
	int player_wins;
	int player_deaths;
	int player_points;
	
};