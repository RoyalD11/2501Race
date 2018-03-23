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
const int AMMO_CAP = 10;

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
	setthisTexture(tex[3], "Sprites/police2.png");
	setthisTexture(tex[4], "Sprites/police3.png");
	setthisTexture(tex[5], "Sprites/police1.png");
	setthisTexture(tex[6], "Sprites/Background.png");

	//track textures
	setthisTexture(tex[7], "Sprites/side-to-up.png");
	setthisTexture(tex[8], "Sprites/up-to-side.png");
	setthisTexture(tex[9], "Sprites/side-to-up-i.png");
	setthisTexture(tex[10], "Sprites/up-to-side-i.png");
	setthisTexture(tex[11], "Sprites/str.png");
	setthisTexture(tex[12], "Sprites/side.png");
	setthisTexture(tex[13], "Sprites/edge.png");

	//text prompts for menus
	setthisTexture(tex[14], "Sprites/gametitle.png");
	setthisTexture(tex[15], "Sprites/storeprompt.png");
	setthisTexture(tex[16], "Sprites/startprompt.png");
	setthisTexture(tex[17], "Sprites/ingamemenuprompt.png");
	setthisTexture(tex[18], "Sprites/ingamemenu.png");
	setthisTexture(tex[19], "Sprites/quitprompt.png");
	setthisTexture(tex[20], "Sprites/mainmenuprompt.png");


	glBindTexture(GL_TEXTURE_2D, tex[0]);
}

void initBackgrounds(Model* model, int size, GLuint imports[7]) {
	std::ifstream fileHndl;


	int mapRows;
	int mapCols;
	int **mapData;
	int** map1;

	fileHndl.open("Assets/map3.txt");
	fileHndl >> mapRows;
	fileHndl >> mapCols;

	mapData = new int *[mapRows];
	for (int i = 0; i < mapRows; i++) {
		mapData[i] = new int[mapCols];
	}

	for (int i = 0; i < mapRows; i++) {
		for (int j = 0; j < mapCols; j++) {
			fileHndl >> mapData[i][j];
		}
	}

	int row1 = mapRows;
	int col1 = mapCols;
	Background* temp;
	//GLuint texture = imports[0];
	for (int i = 0; i < row1; i++) {
		for (int j = 0; j < col1; j++) {
			std::cout << mapData[i][j];
			if (mapData[i][j] == 0) {
				//r-u
				temp = new Background(glm::vec3(i - 0.5, j - 0.5, 0.0f), glm::vec3(1, 1, 0.5), 0.0f, imports[0], size, 0);
			}
			else if (mapData[i][j] == 1) {
				//d-r
				temp = new Background(glm::vec3(i - 0.5, j - 0.5, 0.0f), glm::vec3(1, 1, 0.5), 0.0f, imports[1], size, 1);
			}
			else if (mapData[i][j] == 2) {
				//l-u
				temp = new Background(glm::vec3(i - 0.5, j - 0.5, 0.0f), glm::vec3(1, 1, 0.5), 0.0f, imports[2], size, 2);
			}
			else if (mapData[i][j] == 3) {
				//d-l
				temp = new Background(glm::vec3(i - 0.5, j - 0.5, 0.0f), glm::vec3(1, 1, 0.5), 0.0f, imports[3], size, 3);
			}
			else if (mapData[i][j] == 4) {
				//up
				temp = new Background(glm::vec3(i - 0.5, j - 0.5, 0.0f), glm::vec3(1, 1, 0.5), 0.0f, imports[4], size, 4);
			}
			else if (mapData[i][j] == 5) {
				//side
				temp = new Background(glm::vec3(i - 0.5, j - 0.5, 0.0f), glm::vec3(1, 1, 0.5), 0.0f, imports[5], size, 5);
			}
			else if (mapData[i][j] == 6) {
				//edge
				temp = new Background(glm::vec3(i - 0.5, j - 0.5, 0.0f), glm::vec3(1, 1, 0.5), 0.0f, imports[6], size, 6);
			}
			model->bgObjects.push_back(temp);
			model->updateables.push_back(temp);
		}
		std::cout << "\n";
	}
	std::cout << "Map Loaded";
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

		Model* model = new Model();
		//Controller* controller = new Controller(model);

		//Made arraylist updateables.
		//std::vector <GameEntity*> updateables = std::vector <GameEntity*>();


		// Setup game objects
		//Background* bg = new Background(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.35f, 0.35f, 0.35f), 0.0f, tex[6], size);
		Player* player = new Player(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.35f, 0.35f, 0.35f), 0.0f, tex[0], size, glm::vec3(0.0f, 0.0f, 0.0f));
		Enemy* enemy = new Enemy(glm::vec3(0.3f, 0.8f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), 0.0f, tex[1], size, player);

		Enemy* police = new Enemy(glm::vec3(0.2f, 0.2f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f), 0.0f, tex[4], size, player);

		//Bullet constructor
		Bullet* bullet = new Bullet(glm::vec3(6.0f, 0.0f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), 0.0f, tex[2], size, glm::vec3(0.0f, 0.0f, 0.0f));
		Bullet* bullet2 = new Bullet(glm::vec3(6.0f, 0.0f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), 0.0f, tex[2], size, glm::vec3(0.0f, 0.0f, 0.0f));
		Bullet* bullet3 = new Bullet(glm::vec3(6.0f, 0.0f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), 0.0f, tex[2], size, glm::vec3(0.0f, 0.0f, 0.0f));
		Bullet* bullet4 = new Bullet(glm::vec3(6.0f, 0.0f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), 0.0f, tex[2], size, glm::vec3(0.0f, 0.0f, 0.0f));
		Bullet* bullet5 = new Bullet(glm::vec3(6.0f, 0.0f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), 0.0f, tex[2], size, glm::vec3(0.0f, 0.0f, 0.0f));
		Bullet* bullet6 = new Bullet(glm::vec3(6.0f, 0.0f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), 0.0f, tex[2], size, glm::vec3(0.0f, 0.0f, 0.0f));
		Bullet* bullet7 = new Bullet(glm::vec3(6.0f, 0.0f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), 0.0f, tex[2], size, glm::vec3(0.0f, 0.0f, 0.0f));
		Bullet* bullet8 = new Bullet(glm::vec3(6.0f, 0.0f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), 0.0f, tex[2], size, glm::vec3(0.0f, 0.0f, 0.0f));
		Bullet* bullet9 = new Bullet(glm::vec3(6.0f, 0.0f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), 0.0f, tex[2], size, glm::vec3(0.0f, 0.0f, 0.0f));
		Bullet* bullet10 = new Bullet(glm::vec3(6.0f, 0.0f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), 0.0f, tex[2], size, glm::vec3(0.0f, 0.0f, 0.0f));

		//menu items creation
		Menu* title = new Menu(glm::vec3(6.0f, 0.0f, 0.0f), glm::vec3(1, 0.4f, 0.5f), 0.0f, tex[14], size, glm::vec3(0.0f, 0.0f, 0.0f));
		Menu* quitprompt = new Menu(glm::vec3(6.0f, 0.0f, 0.0f), glm::vec3(1, 0.4f, 0.5f), 0.0f, tex[19], size, glm::vec3(0.0f, 0.0f, 0.0f));
		Menu* menuprompt = new Menu(glm::vec3(6.0f, 0.0f, 0.0f), glm::vec3(1, 0.4f, 0.5f), 0.0f, tex[20], size, glm::vec3(0.0f, 0.0f, 0.0f));
		Menu* startprompt = new Menu(glm::vec3(6.0f, 0.0f, 0.0f), glm::vec3(1, 0.4f, 0.5f), 0.0f, tex[16], size, glm::vec3(0.0f, 0.0f, 0.0f));
		Menu* storeprompt = new Menu(glm::vec3(6.0f, 0.0f, 0.0f), glm::vec3(1, 0.4f, 0.5f), 0.0f, tex[15], size, glm::vec3(0.0f, 0.0f, 0.0f));
		Menu* ingamelist = new Menu(glm::vec3(6.0f, 0.0f, 0.0f), glm::vec3(1, 0.4f, 0.5f), 0.0f, tex[18], size, glm::vec3(0.0f, 0.0f, 0.0f));
		Menu* escprompt = new Menu(glm::vec3(6.0f, 0.0f, 0.0f), glm::vec3(1, 0.4f, 0.5f), 0.0f, tex[17], size, glm::vec3(0.0f, 0.0f, 0.0f));


		//Background* test = new Background(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(10, 10, 10), 0.0f, tex[6], size);


		//Array that holds all the bullets
		Bullet* ammo[AMMO_CAP];
		ammo[0] = bullet;
		ammo[1] = bullet2;
		ammo[2] = bullet3;
		ammo[3] = bullet4;
		ammo[4] = bullet5;
		ammo[5] = bullet6;
		ammo[6] = bullet7;
		ammo[7] = bullet8;
		ammo[8] = bullet9;
		ammo[9] = bullet10;

		//push back objects
		model->updateables.push_back(player);

		model->updateables.push_back(bullet);
		model->updateables.push_back(bullet2);
		model->updateables.push_back(bullet3);
		model->updateables.push_back(bullet4);
		model->updateables.push_back(bullet5);
		model->updateables.push_back(bullet6);
		model->updateables.push_back(bullet7);
		model->updateables.push_back(bullet8);
		model->updateables.push_back(bullet9);
		model->updateables.push_back(bullet10);


		model->updateables.push_back(police);
		//model->updateables.push_back(test);

		model->enemies.push_back(police);


		GLuint temp[8] = { tex[7], tex[8], tex[9], tex[10], tex[11], tex[12], tex[13] };
		initBackgrounds(model, size, temp);



		//Setup sound object
		Sound playersound;

		// Run the main loop
		bool animating = 1;
		double lastTime = glfwGetTime();

		//Int I added to count the number of shots released, does not work as intended due to my frame rate shooting all the bullets at once. should shoot one at a time
		int shot = 0;
		int reload = 0;
		int anicounter = 3;
		int wait = 250;


		glm::mat4 applyWorld = glm::mat4(
			1.0, 0.0, 0.0, 0.0,
			0.0, 1.0, 0.0, 0.0,
			0.0, 0.0, 1.0, 0.0,
			0.0, 0.0, 0.0, 1.0
		);

		Controller* controller = new Controller(model);

		controller->model->player = player;
		while (!glfwWindowShouldClose(window.getWindow())) {
			if (GAMESTATE == 0) {
				// Clear background
				window.clear(viewport_background_color_g);

				// Select proper shader program to use
				shader.enable();

				title->setPosition(0, 0.8);
				title->staticRender(shader);

				startprompt->setPosition(0, 0.5);
				startprompt->staticRender(shader);

				storeprompt->setPosition(0, 0.1);
				storeprompt->staticRender(shader);

				quitprompt->setPosition(0, -0.3);
				quitprompt->staticRender(shader);

				controller->input(window.getWindow(), &GAMESTATE);
				// Update other events like input handling
				glfwPollEvents();


				// Push buffer drawn in the background onto the display
				glfwSwapBuffers(window.getWindow());
			}
			if(GAMESTATE == 2) {
				// Clear background
				window.clear(viewport_background_color_g);

				// Select proper shader program to use
				shader.enable();

				menuprompt->setPosition(0, 0);
				menuprompt->staticRender(shader);

				controller->input(window.getWindow(), &GAMESTATE);
				// Update other events like input handling
				glfwPollEvents();


				// Push buffer drawn in the background onto the display
				glfwSwapBuffers(window.getWindow());
			}

			police->setTarget(model->player->getPosition());

			if( GAMESTATE == 1) {
				// Clear background
				window.clear(viewport_background_color_g);

				// Select proper shader program to use
				shader.enable();

				// Update entities, I added the bullet.update
				double currentTime = glfwGetTime();
				double deltaTime = currentTime - lastTime;
				lastTime = currentTime;


				model->update(deltaTime, shader);



				//Added Bullets update methods
				for (int i = 0; i < AMMO_CAP; i++) ammo[i]->update(deltaTime);

				controller->input(window.getWindow(), &GAMESTATE);


				//if pasyer is moving play engine sound
				//playersound.playersound(player->getVelocity());

				//Timer to keep track of when next shot can be fired
				if (reload > 0) {
					reload--;
				}

				//Space is used to fire a blade, calls the fire method from the bullet class
				if (glfwGetKey(window.getWindow(), GLFW_KEY_SPACE) == GLFW_PRESS) {
					//Shoots a bullet if the number shot is less than the cap, due to framerate relaod is set to a high amount lower it if using a slower machine
					if (shot < AMMO_CAP && reload <= 0) {
						ammo[shot]->fire(player->getPosition(), player->getRotation());
						shot++;
						reload = 500;
					}
				}



				//Out of bounds check to make sure we only loop through the elements we want to use
				if (anicounter == 6) {
					anicounter = 3;
				}

				//Calls animate to change the texture of the police car
				police->animate(tex[anicounter]);

				//Timer that slows the speed of the animation
				if (wait > 0) {
					wait--;
				}

				//If timer has finished increment to the next texture to be displayed and reset the timer
				if (wait == 0) {
					anicounter++;
					wait = 150;
				}


				//Added bullets render methods and where i check for collision detection
				for (int i = 0; i < shot; i++) {
					ammo[i]->render(shader, player->getPosition(), player->getRotation());
					police->collision(*ammo[i]);
				}


				// Update other events like input handling
				glfwPollEvents();


				// Push buffer drawn in the background onto the display
				glfwSwapBuffers(window.getWindow());

			}
	}
}
    catch (std::exception &e){
		// print exception and sleep so error can be read
        PrintException(e);
		std::this_thread::sleep_for(std::chrono::milliseconds(100000));
    }

    return 0;
}

