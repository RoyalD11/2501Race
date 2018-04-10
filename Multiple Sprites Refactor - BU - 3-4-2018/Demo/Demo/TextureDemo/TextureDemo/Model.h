#pragma once

//Controller Class

#include "GameEntity.h"
#include "Background.h"
#include "Player.h"
#include "Shader.h"
#include "Enemy.h"

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

	void simpleCarBounce(float m1, float m2, float R,
		glm::vec3 p1, glm::vec3 &v1,
		glm::vec3 p2, glm::vec3 &v2 );

	void collision2D(char mode, float alpha, float R,
		float m1, float m2, float r1, float r2,
		glm::vec3 &p1, glm::vec3 &v1, 
		glm::vec3 &p2, glm::vec3 &v2,
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
	
};