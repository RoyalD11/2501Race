#include "Controller.h"


Controller::Controller(Model* m) {
	this->model = m;
}

void Controller::input(GLFWwindow* window, int* state) {

	

	switch (*state) {
	case 0: 
		menuController(window, state);
		break;
	case 1: 
		//Checks player specific movement within function
		playerMovement(window, state);
		break;
	case 2: 
		break;
	case 3: 
		break;
	}

	
	

}



void Controller::playerMovement(GLFWwindow* window, int* state) {
	//Key bindings, W and S toggle speeding up and slowing down, calls the setVelocity method from the player class
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		//redo ALL controls here
		//model->player->moveTo(0, 1);
		model->player->moveTo(0, 0.5);
	}

	//Used to slow down to a stop when button not held
	else if (model->player->getVelocityX() < 0 && model->player->getVelocityY() < 0) {
		model->player->moveTo(0, 0.25);
	}
	else if (model->player->getVelocityX() > 0 && model->player->getVelocityY() > 0) {
		model->player->moveTo(0, -0.25);
	}
	else if (model->player->getVelocityX() > 0 && model->player->getVelocityY() < 0) {
		model->player->moveTo(0, 0.25);
	}
	else if (model->player->getVelocityX() < 0 && model->player->getVelocityY() > 0) {
		model->player->moveTo(0, -0.25);
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		//redo ALL controls here
		//model->player->moveTo(0, 1);
		model->player->moveTo(0, -0.5);
		//std::cout << "W Key Pressed \n";
		//model->player->setVelocity(model->player->getPosition());
	}

	

	//Timer to keep track of when next shot can be fired
	if (model->reload > 0) {
		model->reload--;
	}
	
	//Space is used to fire a blade, calls the fire method from the bullet class
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		//Shoots a bullet if the number shot is less than the cap, due to framerate relaod is set to a high amount lower it if using a slower machine
		if (model->player->ammo.size() > 0 && model->reload <=0) {
			model->player->ammo[shot]->fire(model->player->getPosition(), model->player->getRotation());
			model->updateables.insert(model->updateables.begin(), model->player->ammo[shot]);
			shot++;
			model->reload = 500;
			std::cout << "FIRE \n \n";
		}
	}
	
	

	//A and D are used to rotate the player
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		//model->player->moveTo(-1.5, 0);
		model->player->setRotation(0.7);

	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		//model->player->moveTo(1.5,0);
		model->player->setRotation(-0.7);
	}

	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
		model->removeGameObjects();
		*state = 0;
	}


	double* xpos = new double[1];
	double* ypos = new double[1];

	glfwGetCursorPos(window, xpos, ypos);

	//model->player->rotateToMouse(*xpos, *ypos);
}

void Controller::menuController(GLFWwindow* window, int* state) {
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		if (*state == 0) {
			*state = 1;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		if (*state == 0) {
			*state = 2;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		if (*state == 0) {
			*state = 8;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
		if (*state == 2) {
			*state = 0;
		}
	}
}

void Controller::storeController(GLFWwindow* window, int* state) {

}