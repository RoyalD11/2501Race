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
	void input(GLFWwindow* window);
	
	Model* model;
};