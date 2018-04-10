#pragma once

//Controller Class

#include "GameEntity.h"
#include <GL/glew.h>
#include <GL/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

#include "Shader.h"
#include "Model.h"
#include "Window.h"

class Controller {
public:
	Controller(Model* m);
	void input(GLFWwindow* window,int* state);

	//Gamestate controllers
	void playerMovement(GLFWwindow* window, int* state);
	void menuController(GLFWwindow* window, int* state);
	void storeController(GLFWwindow* window, int* state);
	void mapController(GLFWwindow* window, int* state);


	int current_state;
	int shot = 0;
	
	Model* model;
};