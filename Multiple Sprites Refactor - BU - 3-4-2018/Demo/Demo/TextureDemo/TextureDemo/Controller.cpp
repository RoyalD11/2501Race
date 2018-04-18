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
		storeController(window, state);
		break;
	case 3: 
		mapController(window, state);
		break;
	}

	
	if (glfwGetKey(window, GLFW_KEY_SLASH) == GLFW_PRESS) {
		model->map = "map2.txt";
	}
	if (glfwGetKey(window, GLFW_KEY_PERIOD) == GLFW_PRESS) {
		model->map = "map3.txt";
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

	

	
	
	//Space is used to fire a blade, calls the fire method from the bullet class
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		//Shoots a bullet if the number shot is less than the cap, due to framerate relaod is set to a high amount lower it if using a slower machine
		model->firePlayerBullets();
		
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

	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
		model->unmountGame();
		*state = 0;
	}


	//Prints current stats to console
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
		model->printStats();
	}

	/*
	================CHEATS========================
	*/

	//Lap Cheat
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
		model->lap = 4;
	}

	//Point Cheat
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
		model->player->points += 100;
	}


	double* xpos = new double[1];
	double* ypos = new double[1];

	glfwGetCursorPos(window, xpos, ypos);

	//model->player->rotateToMouse(*xpos, *ypos);
}

void Controller::menuController(GLFWwindow* window, int* state) {
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
		if (*state == 0) {
			*state = 3;

			//Loads the GAME
			//model->loadGameObjects();
			//model->loadPlayerBullets();
		}
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		if (*state == 0) {
			*state = 2;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
		if (*state == 0) {
			*state = 8;
		}
	}
	
}

void Controller::storeController(GLFWwindow* window,int* state) {
	int callback=0;

	if ((glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) && glfwGetKey(window, GLFW_KEY_M) != callback) {
		*state = 0;
	}
	if ((glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) && glfwGetKey(window, GLFW_KEY_X) != callback) {
		//player upgrade top speed
		if (model->player_points >= 500) {
			callback = glfwGetKey(window, GLFW_KEY_X);
			//model->player->setTopSpeed(glm::vec3(3, 3, 0));
			glm::vec3 speed = glm::vec3(model->player_top_speed.x + 0.5, model->player_top_speed.y + 0.5, 0);
			model->player_top_speed = speed;
			model->player_points -= 500;
			std::cout << "Max Speed Upgarde bought. \n";
		}
		else {
			//nothing
		}
	}
	if ((glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) && glfwGetKey(window, GLFW_KEY_Z) != callback) {
		callback = glfwGetKey(window, GLFW_KEY_Z);
		//player upgrade buff handling
		if (model->player_points < 500 && model->turning_buff <= 0.25) {
			model->turning_buff += 0.25;
			model->player_points -= 500;
			std::cout << "Handling Upgarde bought. \n";
		}
		else {
			//nothing
		}

	}
	if ((glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS ) && glfwGetKey(window, GLFW_KEY_C) != callback) {
		callback = glfwGetKey(window, GLFW_KEY_C);
		//player upgrade ammo cap
		if (model->player_points >= 1000) {
			model->player_ammo_cap += 5;
			model->player_points -= 1000;
			std::cout << "Ammo Upgarde bought. \n";
			std::cout << "Current Ammo per Lap Cap:" << model->player_ammo_cap << "\n";
			std::cout << model->player->points << "\n";
		}
		else {
			//nothing
		}
	}


}

void Controller::mapController(GLFWwindow* window, int* state) {
	if ((glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)) {
		*state = 0;
	}
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
		model->map = "map3.txt";
		*state = 1;
		model->loadGameObjects();
		model->loadPlayerBullets();
	}
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
		model->map = "map2.txt";
		*state = 1;
		model->loadGameObjects();
		model->loadPlayerBullets();
	}
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
		model->map = "map1.txt";
		*state = 1;
		model->loadGameObjects();
		model->loadPlayerBullets();
	}
	
}