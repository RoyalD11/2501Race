#include "Controller.h"


Controller::Controller(Model* m) {
	this->model = m;
}

void Controller::input(GLFWwindow* window,int* state) {
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
	//Checks player specific movement within function
	playerMovement(window);
	
}



void Controller::playerMovement(GLFWwindow* window) {
	//Key bindings, W and S toggle speeding up and slowing down, calls the setVelocity method from the player class
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		//redo ALL controls here
		//model->player->moveTo(0, 1);
		model->player->moveTo(0, 0.5);
		//std::cout << "W Key Pressed \n";
		//model->player->setVelocity(model->player->getPosition());
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
	/*
	//Space is used to fire a blade, calls the fire method from the bullet class
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		//Shoots a bullet if the number shot is less than the cap, due to framerate relaod is set to a high amount lower it if using a slower machine
		if (model->player->ammo.size() > 0 && model->reload <=0) {
			Bullet* b = new Bullet(model->player->getPosition(), glm::vec3(0.2f, 0.2f, 0.2f), 0.0f, model->texture[2], model->size, glm::vec3(0.0f, 0.0f, 0.0f));
			model->updateables.push_back(b);
			//model->player->ammo[0]->fire(model->player->getPosition(), model->player->getRotation());
			model->reload = 500;
			std::cout << "FIRE \n \n";
		}
	}
	*/
	

	//A and D are used to rotate the player
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		//model->player->moveTo(-1.5, 0);
		model->player->setRotation(0.7);

	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		//model->player->moveTo(1.5,0);
		model->player->setRotation(-0.7);
	}


	double* xpos = new double[1];
	double* ypos = new double[1];

	glfwGetCursorPos(window, xpos, ypos);

	//model->player->rotateToMouse(*xpos, *ypos);
}