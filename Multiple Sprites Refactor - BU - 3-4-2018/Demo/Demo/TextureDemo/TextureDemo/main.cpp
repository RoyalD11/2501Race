#define GLEW_STATIC


#include <iostream>
#include <stdexcept>
#include <string>
#include <GL/glew.h> // window management library
#include <GL/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> //
#include <SOIL/SOIL.h> // read image file
#include <chrono>
#include <thread>
#include <cmath>

//Extra libraries I added
#include <stdio.h>
#include "Shader.h"
#include "Window.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Camera.h"
#include "Sound.h"
#include "Background.h"
#include "Model.h"
#include "Controller.h"
#include <vector>
#include "Menu.h"

using namespace std;
int GAMESTATE = 0;


// Macro for printing exceptions
#define PrintException(exception_object)\
	std::cerr << exception_object.what() << std::endl



// Globals that define the OpenGL window and viewport
const std::string window_title_g = "ZoomZoomGame";
const unsigned int window_width_g = 800;
const unsigned int window_height_g = 600;
const glm::vec3 viewport_background_color_g(0.0, 0.0, 0.2);

// Camera

GLint WID = 800;
GLint HEI = 600;
Camera  camera(glm::vec3(0.0f, 0.0f, 3.0f));
GLfloat lastX = WID / 2.0;
GLfloat lastY = HEI / 2.0;
bool keys[1024];
bool firstMouse = true;


GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;


//Const I added for Bullet Detection
//const int AMMO_CAP = 10;

// Global texture info
GLuint tex[25];

// Create the geometry for a square (with two triangles)
// Return the number of array elements that form the square
int CreateSquare(void) {
	// The face of the square is defined by four vertices and two triangles

	// Number of attributes for vertices and faces
//	const int vertex_att = 7;  // 7 attributes per vertex: 2D (or 3D) position (2), RGB color (3), 2D texture coordinates (2)
//	const int face_att = 3; // Vertex indices (3)

	GLfloat vertex[]  = {
		//  square (two triangles)
		   //  Position      Color             Texcoords
		-0.5f, 0.5f,	 1.0f, 0.0f, 0.0f,		0.0f, 0.0f, // Top-left
		0.5f, 0.5f,		 0.0f, 1.0f, 0.0f,		1.0f, 0.0f, // Top-right
		0.5f, -0.5f,	 0.0f, 0.0f, 1.0f,		1.0f, 1.0f, // Bottom-right
		-0.5f, -0.5f,	 1.0f, 1.0f, 1.0f,		0.0f, 1.0f  // Bottom-left
	};


	GLuint face[] = {
		0, 1, 2, // t1
		2, 3, 0  //t2
	};

	GLuint vbo, ebo;

	// Create buffer for vertices
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);

	// Create buffer for faces (index buffer)
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(face), face, GL_STATIC_DRAW);

	// Return number of elements in array buffer (6 in this case)
	return sizeof(face) / sizeof(GLuint);
}


void setthisTexture(GLuint w, char *fname)
{
	glBindTexture(GL_TEXTURE_2D, w);

	int width, height;
	unsigned char* image = SOIL_load_image(fname, &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void setallTexture(void)
{
	//Holds all textures/sprites used
	glGenTextures(25, tex);
	setthisTexture(tex[0], "Sprites/Black_viper.png");
	setthisTexture(tex[1], "Sprites/orb.png");
	setthisTexture(tex[2], "Sprites/saw.png");
	setthisTexture(tex[3], "Sprites/cop1.png");
	setthisTexture(tex[4], "Sprites/cop2.png");
	setthisTexture(tex[5], "Sprites/cop1.png");
	setthisTexture(tex[6], "Sprites/Background.png");

	//track textures
	setthisTexture(tex[7], "Sprites/new/side-to-up.png");
	setthisTexture(tex[8], "Sprites/new/up-to-side.png");
	setthisTexture(tex[9], "Sprites/new/side-to-up-i.png");
	setthisTexture(tex[10], "Sprites/new/up-to-side-i.png");
	setthisTexture(tex[11], "Sprites/new/str.png");
	setthisTexture(tex[12], "Sprites/new/side2.png");
	setthisTexture(tex[13], "Sprites/new/grass.png");
	setthisTexture(tex[21], "Sprites/new/start-v.png");
	setthisTexture(tex[25], "Sprites/new/side-coin.png");
	setthisTexture(tex[26], "Sprites/up-coin.png");

	//text prompts for menus
	setthisTexture(tex[14], "Sprites/MAINTITLE.png");
	setthisTexture(tex[15], "Sprites/STORE.png");
	setthisTexture(tex[16], "Sprites/MAPSELECT.png");
	setthisTexture(tex[17], "Sprites/ingamemenuprompt.png");
	setthisTexture(tex[18], "Sprites/ingamemenu.png");
	setthisTexture(tex[19], "Sprites/quitprompt.png");
	setthisTexture(tex[20], "Sprites/mainmenuprompt.png");

	//Other Cars
	setthisTexture(tex[22], "Sprites/swat1.png");
	setthisTexture(tex[23], "Sprites/swat2.png");
	setthisTexture(tex[24], "Sprites/swat1.png");

	//Hud Sprites
	setthisTexture(tex[27], "Sprites/coin.png");
	setthisTexture(tex[28], "Sprites/cash.png");

	glBindTexture(GL_TEXTURE_2D, tex[0]);
}




// Main function that builds and runs the game
int main(void){
	try {


		// Setup window
		Window window(window_width_g, window_height_g, window_title_g);

		// Set up z-buffer for rendering
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		// Enable Alpha blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Create geometry of the square
		int size = CreateSquare();

		// Set up shaders
		Shader shader("shader.vert", "shader.frag");

		setallTexture();

		//Sets Model and controller objects
		Model* model = new Model(window.getWindow(), &GAMESTATE);
		Controller* controller = new Controller(model);

		model->texture = tex;
		model->size = size;
		controller->current_state = GAMESTATE;

		//model->loadGameObjects();
		//model->loadPlayerBullets();

		// Setup game objects
		//Background* bg = new Background(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.35f, 0.35f, 0.35f), 0.0f, tex[6], size);
		//menu items creation
		Menu* title     = new Menu(glm::vec3(0, 0, 0), glm::vec3(2, 2, 2), 0.0f, tex[14], size, glm::vec3(0, 0, 0));
		Menu* store     = new Menu(glm::vec3(0, 0, 0), glm::vec3(2, 2, 2), 0.0f, tex[15], size, glm::vec3(0, 0, 0));
		Menu* mapselect = new Menu(glm::vec3(0, 0, 0), glm::vec3(2, 2, 2), 0.0f, tex[16], size, glm::vec3(0, 0, 0));
		

		//Setup sound object
		Sound playersound;
		Sound audio;

		// Run the main loop
		bool animating = 1;
		double lastTime = glfwGetTime();



		glm::mat4 applyWorld = glm::mat4(
			1.0, 0.0, 0.0, 0.0,
			0.0, 1.0, 0.0, 0.0,
			0.0, 0.0, 1.0, 0.0,
			0.0, 0.0, 0.0, 1.0
		);

		


		for (int i = 0; i < model->enemies.size(); i++) {
			model->enemies[i]->setTarget(model->player->getPosition());
		}


		while (!glfwWindowShouldClose(window.getWindow())) {

			audio.playSound(GAMESTATE);
			controller->input(window.getWindow(), &GAMESTATE);


			// Clear background
			window.clear(viewport_background_color_g);

			// Select proper shader program to use
			shader.enable();


			
			if (GAMESTATE == 0) {

				title->setPosition(0, 0);
				title->staticRender(shader);
			}
			if (GAMESTATE == 2) {

				store->setPosition(0, 0);
				store->staticRender(shader);
			}
			if (GAMESTATE == 3) {

				mapselect->setPosition(0, 0);
				mapselect->staticRender(shader);
			}

			if (GAMESTATE == 1) {

				// Update entities, I added the bullet.update
				double currentTime = glfwGetTime();
				double deltaTime = currentTime - lastTime;
				lastTime = currentTime;


				model->update(deltaTime, shader);
				model->checkLap();
			}

			// Update other events like input handling
			glfwPollEvents();


			// Push buffer drawn in the background onto the display
			glfwSwapBuffers(window.getWindow());
		}
	}
    catch (std::exception &e){
		// print exception and sleep so error can be read
        PrintException(e);
		std::this_thread::sleep_for(std::chrono::milliseconds(100000));
    }

    return 0;
}

