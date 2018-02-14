#include <iostream>
#include <stdexcept>
#include <string>
#define GLEW_STATIC
#include <GL/glew.h> // window management library
#include <GL/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> //
#include <SOIL/SOIL.h> // read image file
#include <chrono>
#include <thread>

//Extra libraries I added
#include <stdio.h>

#include "Shader.h"
#include "Window.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

// Macro for printing exceptions
#define PrintException(exception_object)\
	std::cerr << exception_object.what() << std::endl

// Globals that define the OpenGL window and viewport
const std::string window_title_g = "Multiple Sprites Demo";
const unsigned int window_width_g = 800;
const unsigned int window_height_g = 600;
const glm::vec3 viewport_background_color_g(0.0, 0.0, 0.2);


//Const I added for Bullet Detection
const int AMMO_CAP = 10;

// Global texture info
GLuint tex[3];

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
//	tex = new GLuint[3];
	glGenTextures(3, tex);
	setthisTexture(tex[0], "Black_viper.png");
	setthisTexture(tex[1], "orb.png");
	setthisTexture(tex[2], "saw.png");

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

		// Setup game objects
		Player player(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.35f, 0.35f, 0.35f), 0.0f, tex[0], size, glm::vec3(0.0f, 0.0f, 0.0f));
		Enemy enemy(glm::vec3(0.3f, 0.8f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), 0.0f, tex[1], size, &player);

		//Added Enemies
		Enemy enemy2(glm::vec3(0.1f, -0.9f, -0.1f), glm::vec3(0.2f, 0.2f, 0.2f), 0.0f, tex[1], size, &player);
		Enemy enemy3(glm::vec3(0.5f, -0.4f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), 0.0f, tex[1], size, &player);
		Enemy enemy4(glm::vec3(-0.7f, 0.2f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), 0.0f, tex[1], size, &player);
		Enemy enemy5(glm::vec3(-0.3f, -0.6f, -0.1f), glm::vec3(0.2f, 0.2f, 0.2f), 0.0f, tex[1], size, &player);
		Enemy enemy6(glm::vec3(0.2f, 0.2f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), 0.0f, tex[1], size, &player);

		//Bullet constructor
		Bullet bullet(glm::vec3(6.0f, 0.0f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), 0.0f, tex[2], size, glm::vec3(0.0f, 0.0f, 0.0f));
		Bullet bullet2(glm::vec3(6.0f, 0.0f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), 0.0f, tex[2], size, glm::vec3(0.0f, 0.0f, 0.0f));
		Bullet bullet3(glm::vec3(6.0f, 0.0f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), 0.0f, tex[2], size, glm::vec3(0.0f, 0.0f, 0.0f));
		Bullet bullet4(glm::vec3(6.0f, 0.0f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), 0.0f, tex[2], size, glm::vec3(0.0f, 0.0f, 0.0f));
		Bullet bullet5(glm::vec3(6.0f, 0.0f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), 0.0f, tex[2], size, glm::vec3(0.0f, 0.0f, 0.0f));
		Bullet bullet6(glm::vec3(6.0f, 0.0f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), 0.0f, tex[2], size, glm::vec3(0.0f, 0.0f, 0.0f));
		Bullet bullet7(glm::vec3(6.0f, 0.0f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), 0.0f, tex[2], size, glm::vec3(0.0f, 0.0f, 0.0f));
		Bullet bullet8(glm::vec3(6.0f, 0.0f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), 0.0f, tex[2], size, glm::vec3(0.0f, 0.0f, 0.0f));
		Bullet bullet9(glm::vec3(6.0f, 0.0f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), 0.0f, tex[2], size, glm::vec3(0.0f, 0.0f, 0.0f));
		Bullet bullet10(glm::vec3(6.0f, 0.0f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), 0.0f, tex[2], size, glm::vec3(0.0f, 0.0f, 0.0f));


		//Array that holds all the bullets
		Bullet* ammo[AMMO_CAP];
		ammo[0] = &bullet;
		ammo[1] = &bullet2;
		ammo[2] = &bullet3;
		ammo[3] = &bullet4;
		ammo[4] = &bullet5;
		ammo[5] = &bullet6;
		ammo[6] = &bullet7;
		ammo[7] = &bullet8;
		ammo[8] = &bullet9;
		ammo[9] = &bullet10;
		

        // Run the main loop
        bool animating = 1;
		double lastTime = glfwGetTime();
		
		//Int I added to count the number of shots released, does not work as intended due to my frame rate shooting all the bullets at once. should shoot one at a time
		int shot = 0;
		int reload = 0;
		

        while (!glfwWindowShouldClose(window.getWindow())){
            // Clear background
			window.clear(viewport_background_color_g);

            // Select proper shader program to use
			shader.enable();
			
			// Update entities, I added the bullet.update
			double currentTime = glfwGetTime();
			double deltaTime = currentTime - lastTime;
			lastTime = currentTime;
			player.update(deltaTime);
			enemy.update(deltaTime);

			//Added enemies update methods
			enemy2.update(deltaTime);
			enemy3.update(deltaTime);
			enemy4.update(deltaTime);
			enemy5.update(deltaTime);
			enemy6.update(deltaTime);

			//Added Bullets update methods
			for (int i = 0; i<AMMO_CAP; i++) ammo[i]->update(deltaTime);


			//Key bindings, W and S toggle speeding up and slowing down, calls the setVelocity method from the player class
			if (glfwGetKey(window.getWindow(), GLFW_KEY_W) == GLFW_PRESS) {
				player.setVelocity(0.001);
			}
			else {
				player.setVelocity(-0.001);

			}

			if (glfwGetKey(window.getWindow(), GLFW_KEY_S) == GLFW_PRESS) {
				player.setVelocity(-0.005);
			}

			//Q is used to rotate the ship in a positive direction, calls the setRotation method from the player class
			if (glfwGetKey(window.getWindow(), GLFW_KEY_Q) == GLFW_PRESS) {
				player.setRotation(0.25);
			}
			
			//E is used to rotate the ship in a positive direction, calls the setRotation method from the player class
			if (glfwGetKey(window.getWindow(), GLFW_KEY_E) == GLFW_PRESS) {
				player.setRotation(-0.25);
			}

			if (reload > 0) {
				reload--;
			}

			//Space is used to fire a blade, calls the fire method from the bullet class
			if (glfwGetKey(window.getWindow(), GLFW_KEY_SPACE) == GLFW_PRESS) {
				
				//Shoots a bullet if the number shot is less than the cap, due to framerate relaod is set to a high amount lower it if using a slower machine
				if (shot < AMMO_CAP && reload <=0) {
					ammo[shot]->fire(player.getPosition(), player.getRotation());
					shot++;
					reload = 500;
				}
			}


			// Render entities, I added the bullet.render
			player.render(shader);
			
			enemy.render(shader);

			//Added enemies render methods
			enemy2.render(shader);
			enemy3.render(shader);
			enemy4.render(shader);
			enemy5.render(shader);
			enemy6.render(shader);

			//Added bullets render methods and where i check for collision detection
			for (int i = 0; i < shot; i++) {
				ammo[i]->render(shader);
				enemy.collision(*ammo[i]);
				enemy2.collision(*ammo[i]);
				enemy3.collision(*ammo[i]);
				enemy4.collision(*ammo[i]);
				enemy5.collision(*ammo[i]);
				enemy6.collision(*ammo[i]);
			}
			
		//	glDrawArrays(GL_TRIANGLES, 0, 6); // if glDrawArrays be used, glDrawElements will be ignored 

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


 