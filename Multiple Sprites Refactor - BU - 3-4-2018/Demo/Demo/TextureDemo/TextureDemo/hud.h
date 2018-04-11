#pragma once

#include "Window.h"
#include "GameEntity.h"
#include "Player.h"
#include <vector>
#include <iostream>
#include "Shader.h"


class Hud {
public:
	Hud(GLuint* textures);
	void display(Shader &shader, Player* player);
	//stuff
private:
	GLuint* textures;

};