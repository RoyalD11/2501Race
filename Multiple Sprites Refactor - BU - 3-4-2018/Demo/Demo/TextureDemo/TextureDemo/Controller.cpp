#include "Controller.h"


Controller::Controller(Model* m) {
	this->model = m;
}

void Controller::input(GLFWwindow* window) {

	//Key bindings, W and S toggle speeding up and slowing down, calls the setVelocity method from the player class
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		//redo ALL controls here
		model->player->moveTo(0, 0.001);
		//model->player->setVelocity(model->player->getPosition());
	}
}