#pragma once

//Controller Class

#include "GameEntity.h"
#include "Player.h"
#include "Shader.h"
#include "Enemy.h"

#include "Window.h"
#include <vector>

class Model {
public:
	Model();
	void update(float deltaTime);

	//All GameObjects in Game
	std::vector <GameEntity*> updateables = std::vector <GameEntity*>();
	std::vector <Enemy*>      enemies = std::vector <Enemy*>();

	//Specific Gameobject Pointers
	Player* player;
};