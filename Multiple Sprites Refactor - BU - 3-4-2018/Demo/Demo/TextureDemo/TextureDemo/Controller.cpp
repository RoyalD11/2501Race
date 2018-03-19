#include "Controller.h"


Controller::Controller(Model* m) {
	this->model = m;
}

void Controller::input(GLFWwindow* window) {
	
	//Checks player specific movement within function
	playerMovement(window);
	
}



void Controller::playerMovement(GLFWwindow* window) {
	//Key bindings, W and S toggle speeding up and slowing down, calls the setVelocity method from the player class
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		//redo ALL controls here
		//model->player->moveTo(0, 1);
		model->player->moveTo(0, 1.5);
		//std::cout << "W Key Pressed \n";
		//model->player->setVelocity(model->player->getPosition());
	}

	//Used to slow down to a stop when button not held
	else if (model->player->getVelocityX() < 0 && model->player->getVelocityY() < 0) {
		model->player->moveTo(0, 0.5);
	}
	else if (model->player->getVelocityX() > 0 && model->player->getVelocityY() > 0) {
		model->player->moveTo(0, -0.5);
	}
	else if (model->player->getVelocityX() > 0 && model->player->getVelocityY() < 0) {
		model->player->moveTo(0, 0.5);
	}
	else if (model->player->getVelocityX() < 0 && model->player->getVelocityY() > 0) {
		model->player->moveTo(0, -0.5);
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		//redo ALL controls here
		//model->player->moveTo(0, 1);
		model->player->moveTo(0, -1.5);
		//std::cout << "W Key Pressed \n";
		//model->player->setVelocity(model->player->getPosition());
	}

	

	

	

	//A and D are used to rotate the player
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		//model->player->moveTo(-1.5, 0);
		model->player->setRotation(0.5);

	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		//model->player->moveTo(1.5,0);
		model->player->setRotation(-0.5);
	}


	double* xpos = new double[1];
	double* ypos = new double[1];

	glfwGetCursorPos(window, xpos, ypos);

	//model->player->rotateToMouse(*xpos, *ypos);
}