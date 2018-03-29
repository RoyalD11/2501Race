#pragma once

//Controller Class

#include "GameEntity.h"
#include "Background.h"
#include "Player.h"
#include "Shader.h"
#include "Enemy.h"

#include "Window.h"
#include <vector>

#define AMMO_CAP 10


class Model {
public:
	Model(GLFWwindow* window);

	//All GameObjects in Game
	std::vector <GameEntity*> updateables = std::vector <GameEntity*>();
	std::vector <Enemy*>      enemies = std::vector <Enemy*>();
	std::vector <Background*> bgObjects = std::vector <Background*>();
	

	void loadFromText();

	void update(double deltaTime, Shader shader);

	void loadGameObjects();
	void removeGameObjects();
	

	int time;
	GLFWwindow* window;

	GLuint* texture;
	int size;
	int reload;
	
	Player* player;

	
};