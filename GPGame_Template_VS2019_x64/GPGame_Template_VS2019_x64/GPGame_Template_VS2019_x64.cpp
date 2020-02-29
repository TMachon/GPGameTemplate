// Simplified Renderer application for GP course
// Features:
// Reduced OpenGL version from 4.5 to 3.3 to allow it to render in older laptops.
// Added Shapes library for rendering cubes, spheres and vectors.
// Added examples of matrix multiplication on Update.
// Added resize screen and keyboard callbacks.
// Added FPS camera functionality
// Update 2019/01 updated libraries and created project for VS2017 including directory dependant links to libraries.
// Update 2020/01 updated libraries for x64 and for VS2020, also adding MAC compiled Libraries.

// Suggestions or extra help please do email me at S.Padilla@hw.ac.uk

// Standard C++ libraries
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
using namespace std;

// Helper graphic libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

#include <list>

#include "graphics.h"
#include "shapes.h"
#include "tank.h"
#include "wall.h"
#include "missile.h"

#define NB_WALLS 2

// MAIN FUNCTIONS
void startup();
void updateCamera();
void updateMovement();
void updateSceneElements();
void renderScene();

// CALLBACK FUNCTIONS
void onResizeCallback(GLFWwindow* window, int w, int h);
void onKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void onMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void onMouseMoveCallback(GLFWwindow* window, double x, double y);
void onMouseWheelCallback(GLFWwindow* window, double xoffset, double yoffset);

// VARIABLES
bool        quit = false;
float       deltaTime = 0.0f;    // Keep track of time per frame.
float		myDeltaTime = 0.0f;
float       lastTime = 0.0f;    // variable to keep overall time.
bool        keyStatus[1024];    // Hold key status.
bool		mouseEnabled = true; // keep track of mouse toggle.

// MAIN GRAPHICS OBJECT
Graphics    myGraphics;

// DEMO OBJECTS
Cube        myFloor;

//USER
Tank		player;
Tank		test;

std::vector<Wall> wallList;
std::vector<Tank> tankList;

glm::vec3	defaultCameraPostion;
GLfloat		defaultCameraPitch;

std::vector<Missile> missileList;

// Some global variable to do the animation.
float t = 0.001f;            // Global variable for animation
float alea = 0.0f;
float xrand = 0.0;

int main()
{
	float xpos = 0.0f;
	float ypos = 0.5f;
	float zpos = 0.0f;
	int errorGraphics = myGraphics.Init();			// Launch window and graphics context
	if (errorGraphics) return 0;					// Close if something went wrong...

	startup();										// Setup all necessary information for startup (aka. load texture, shaders, models, etc).



	// MAIN LOOP run until the window is closed
	while (!quit) {

		// Update the camera transform based on interactive inputs or by following a predifined path.
		

		updateCamera();

		updateMovement();

		// Update position, orientations and any other relevant visual state of any dynamic elements in the scene.
		updateSceneElements();

		// Render a still frame into an off-screen frame buffer known as the backbuffer.
		renderScene();

		

		// Swap the back buffer with sthe front buffer, making the most recently rendered image visible on-screen.
		glfwSwapBuffers(myGraphics.window);        // swap buffers (avoid flickering and tearing)

	}


	myGraphics.endProgram();            // Close and clean everything up...

   // cout << "\nPress any key to continue...\n";
   // cin.ignore(); cin.get(); // delay closing console to read debugging errors.

	return 0;
}

void startup() {

	// Keep track of the running time
	GLfloat currentTime = (GLfloat)glfwGetTime();    // retrieve timelapse
	deltaTime = currentTime;                        // start delta time
	lastTime = currentTime;                            // Save for next frame calculations.

	// Callback graphics and key update functions - declared in main to avoid scoping complexity.
	// More information here : https://www.glfw.org/docs/latest/input_guide.html
	glfwSetWindowSizeCallback(myGraphics.window, onResizeCallback);            // Set callback for resize
	glfwSetKeyCallback(myGraphics.window, onKeyCallback);                    // Set Callback for keys
	glfwSetMouseButtonCallback(myGraphics.window, onMouseButtonCallback);    // Set callback for mouse click
	glfwSetCursorPosCallback(myGraphics.window, onMouseMoveCallback);        // Set callback for mouse move
	glfwSetScrollCallback(myGraphics.window, onMouseWheelCallback);            // Set callback for mouse wheel.

	// Calculate proj_matrix for the first time.
	myGraphics.aspect = (float)myGraphics.windowWidth / (float)myGraphics.windowHeight;
	myGraphics.proj_matrix = glm::perspective(glm::radians(50.0f), myGraphics.aspect, 0.1f, 1000.0f);

	// Load Geometry examples

	myFloor.Load();
	myFloor.fillColor = glm::vec4(130.0f / 255.0f, 96.0f / 255.0f, 61.0f / 255.0f, 1.0f);    // Sand Colour
	myFloor.lineColor = glm::vec4(130.0f / 255.0f, 96.0f / 255.0f, 61.0f / 255.0f, 1.0f);    // Sand again

	// Optimised Graphics
	myGraphics.SetOptimisations();        // Cull and depth testing

	//USER

	//camera
	defaultCameraPostion = glm::vec3(0.0f, 27.0f, -21.0f);
	defaultCameraPitch = -63.5f;
	myGraphics.cameraPosition = defaultCameraPostion;
	myGraphics.cameraPitch = defaultCameraPitch;
	
	//test = Tank();
	test = Tank(0.0f, 0.5f, 3.0f);
	player = Tank(1.0f, 0.5f, 1.0f);

	player.startup(myGraphics, true);
	test.startup(myGraphics, false);
	tankList.push_back(test);

	Wall wall1 = Wall();
	Wall wall2 = Wall();
	Wall wall3 = Wall();
	Wall wall4 = Wall();
	wall1.startup(myGraphics, 0.0f, 0.5f, 10.0f, 30.0f, 2.0f, 1.0f, false);
	wall2.startup(myGraphics, -15.0f, 0.5f, -5.0f, 1.0f, 2.0f, 30.0f, false);
	wall3.startup(myGraphics, 0.0f, 0.5f, -20.0f, 30.0f, 2.0f, 1.0f, false);
	wall4.startup(myGraphics, 15.0f, 0.5f, -5.0f, 1.0f, 2.0f, 30.0f, false);
	wallList.push_back(wall1);
	wallList.push_back(wall2);
	wallList.push_back(wall3);
	wallList.push_back(wall4);
}

bool checkCollisionTank(Tank tank1, Tank tank2) {
	return (tank1.getX() + tank1.getXSize() / 2 > tank2.getX() - tank2.getXSize() / 2 &&
		tank1.getX() - tank1.getXSize() / 2 < tank2.getX() + tank2.getXSize() / 2 &&
		tank1.getY() + tank1.getYSize() / 2 > tank2.getY() - tank2.getYSize() / 2 &&
		tank1.getY() - tank1.getYSize() / 2 < tank2.getY() + tank2.getYSize() / 2 &&
		tank1.getZ() + tank1.getZSize() / 2 > tank2.getZ() - tank2.getZSize() / 2 &&
		tank1.getZ() - tank1.getZSize() / 2 < tank2.getZ() + tank2.getZSize() / 2);
		
}

bool checkCollisionWall(Tank tank, Wall wall) {
	return (tank.getX() + tank.getXSize() / 2 > wall.getX() - wall.getXSize() / 2 &&
		tank.getX() - tank.getXSize() / 2 < wall.getX() + wall.getXSize() / 2 &&
		tank.getY() + tank.getYSize() / 2 > wall.getY() - wall.getYSize() / 2 &&
		tank.getY() - tank.getYSize() / 2 < wall.getY() + wall.getYSize() / 2 &&
		tank.getZ() + tank.getZSize() / 2 > wall.getZ() - wall.getZSize() / 2 &&
		tank.getZ() - tank.getZSize() / 2 < wall.getZ() + wall.getZSize() / 2);
}

bool checkCollision(Tank tank) {
	/**/
	for (int i = 0; i < wallList.size(); i++) {
		if (checkCollisionWall(tank, wallList[i])) {
			return true;
		}
	}
	/**/
	for (int i = 0; i < tankList.size(); i++) {
		if (tank.getId() != tankList[i].getId() && checkCollisionTank(tank, tankList[i])) {
			return true;
		}
	}
	/**/
	if (!tank.isPlayer()) {
		if (checkCollisionTank(tank, player)) {
			return true;
		}
	}
	/**/
	return false;
}

void updateCamera() {

	// calculate movement for FPS camera
	GLfloat xoffset = myGraphics.mouseX - myGraphics.cameraLastX;
	GLfloat yoffset = myGraphics.cameraLastY - myGraphics.mouseY;    // Reversed mouse movement
	myGraphics.cameraLastX = (GLfloat)myGraphics.mouseX;
	myGraphics.cameraLastY = (GLfloat)myGraphics.mouseY;

	//myGraphics.cameraLastX = (GLfloat)myGraphics.mouseX;
	//myGraphics.cameraLastY = (GLfloat)myGraphics.mouseY;

	GLfloat sensitivity = 0.05f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	myGraphics.cameraYaw += xoffset;
	myGraphics.cameraPitch += yoffset;

	// check for pitch out of bounds otherwise screen gets flipped
	if (myGraphics.cameraPitch > 89.0f) myGraphics.cameraPitch = 89.0f;
	if (myGraphics.cameraPitch < -89.0f) myGraphics.cameraPitch = -89.0f;

	// Calculating FPS camera movement (See 'Additional Reading: Yaw and Pitch to Vector Calculations' in VISION)
	glm::vec3 front;
	front.x = cos(glm::radians(myGraphics.cameraYaw)) * cos(glm::radians(myGraphics.cameraPitch));
	front.y = sin(glm::radians(myGraphics.cameraPitch));
	front.z = sin(glm::radians(myGraphics.cameraYaw)) * cos(glm::radians(myGraphics.cameraPitch));

	myGraphics.cameraFront = glm::normalize(front);

	// Update movement using the keys
	GLfloat cameraSpeed = 3.0f * deltaTime;
	if (keyStatus[GLFW_KEY_W]) myGraphics.cameraPosition += cameraSpeed * myGraphics.cameraFront;
	if (keyStatus[GLFW_KEY_S]) myGraphics.cameraPosition -= cameraSpeed * myGraphics.cameraFront;
	if (keyStatus[GLFW_KEY_A]) myGraphics.cameraPosition -= glm::normalize(glm::cross(myGraphics.cameraFront, myGraphics.cameraUp)) * cameraSpeed;
	if (keyStatus[GLFW_KEY_D]) myGraphics.cameraPosition += glm::normalize(glm::cross(myGraphics.cameraFront, myGraphics.cameraUp)) * cameraSpeed;



	// IMPORTANT PART
	// Calculate my view matrix using the lookAt helper function
	if (mouseEnabled) {
		myGraphics.viewMatrix = glm::lookAt(myGraphics.cameraPosition,			// eye
			myGraphics.cameraPosition + myGraphics.cameraFront,					// centre
			myGraphics.cameraUp);												// up
	}

}

void updateMovement() {
	

	//Player collision
	// if there is a collision
	if (checkCollision(player)) {
		while (checkCollision(player)) {
			if (player.getLastMovement() == DOWN) {
				player.move(UP, false);
			}
			else if (player.getLastMovement() == UP) {
				player.move(DOWN, false);
			}
			else if (player.getLastMovement() == LEFT) {
				player.move(RIGHT, false);
			}
			else if (player.getLastMovement() == RIGHT) {
				player.move(LEFT, false);
			}
		}
	}

	// if there is no collision
	else {
		if (keyStatus[GLFW_KEY_UP]) {
			player.move(UP, true);
		}
		else if (keyStatus[GLFW_KEY_DOWN]) {
			player.move(DOWN, true);
		}
		else if (keyStatus[GLFW_KEY_RIGHT]) {
			player.move(RIGHT, true);
		}
		else if (keyStatus[GLFW_KEY_LEFT]) {
			player.move(LEFT, true);
		}

		if (keyStatus[GLFW_KEY_SPACE]) {
			missileList.push_back(Missile(player));
			missileList.back().startup(myGraphics);
		}
	}

	/**/

	//Bot collision
	for (int i = 0; i < tankList.size(); i++) {

		if (checkCollision(tankList[i])) {
			cout << tankList[i].getLastMovement() << endl;
			if (tankList[i].getLastMovement() == DOWN) {
				tankList[i].move(UP, false);
			}
			else if (tankList[i].getLastMovement() == UP) {
				tankList[i].move(DOWN, false);
			}
			else if (tankList[i].getLastMovement() == LEFT) {
				tankList[i].move(RIGHT, false);
			}
			else if (tankList[i].getLastMovement() == RIGHT) {
				tankList[i].move(LEFT, false);
			}
		}

		// if there is no collision
		else {
			if (tankList[i].getSame() < MAX_MOVE) {
				tankList[i].move(tankList[i].getLastMovement(), true);
				tankList[i].incSame();
			} else {
				tankList[i].resetSame();
				int move = rand() % 5;
				if (move == 0) {
					tankList[i].move(UP, true);
				}
				else if (move == 1) {
					tankList[i].move(DOWN, true);
				}
				else if (move == 2) {
					tankList[i].move(RIGHT, true);
				}
				else if (move == 3) {
					tankList[i].move(LEFT, true);
				}
			}
		}
	}

}



void updateSceneElements() {

	glfwPollEvents();                                // poll callbacks

	// Calculate frame time/period -- used for all (physics, animation, logic, etc).
	GLfloat currentTime = (GLfloat)glfwGetTime();    // retrieve timelapse
	deltaTime = currentTime - lastTime;                // Calculate delta time
	lastTime = currentTime;                            // Save for next frame calculations.
	myDeltaTime += currentTime;

	// Do not forget your ( T * R * S ) http://www.opengl-tutorial.org/beginners-tutorials/tutorial-3-matrices/
	
	if (myDeltaTime > 500) {
		if (rand() % 99 > 50) {
			xrand += (float)rand() / (float)(RAND_MAX / 0.1f);
		}
		else {
			xrand -= (float)rand() / (float)(RAND_MAX / 0.1f);
		}
		myDeltaTime = 0.0f;
	}

	// Calculate floor position and resize
	myFloor.mv_matrix = myGraphics.viewMatrix *
		glm::translate(glm::vec3(0.0f, 0.0f, 0.0f)) *
		glm::scale(glm::vec3(1000.0f, 0.001f, 1000.0f)) *
		glm::mat4(1.0f);
	myFloor.proj_matrix = myGraphics.proj_matrix;

	//USER UpdateScene
	player.sceneUpdate(myGraphics);
	for (int i = 0; i < wallList.size(); i++) {
		wallList[i].sceneUpdate(myGraphics);
	}

	for (int i = 0; i < tankList.size(); i++) {
		tankList[i].sceneUpdate(myGraphics);
	}

	for (int i = 0; i < missileList.size(); i++) {
		missileList[i].sceneUpdate(myGraphics);
	}

	t += 0.01f; // increment movement variable

	if (glfwWindowShouldClose(myGraphics.window) == GL_TRUE) quit = true; // If quit by pressing x on window.

}

void renderScene() {
	// Clear viewport - start a new frame.
	myGraphics.ClearViewport();

	// Draw objects in screen
	myFloor.Draw();

	//USER
	player.render();
	for (int i = 0; i < wallList.size(); i++) {
		wallList[i].render();
	}

	for (int i = 0; i < tankList.size(); i++) {
		tankList[i].render();
	}

	for (int i = 0; i < missileList.size(); i++) {
		missileList[i].render();
	}
}


// CallBack functions low level functionality.
void onResizeCallback(GLFWwindow* window, int w, int h) {    // call everytime the window is resized
	//myGraphics.windowWidth = w;
	//myGraphics.windowHeight = h;

	glfwGetFramebufferSize(window, &myGraphics.windowWidth, &myGraphics.windowHeight);

	myGraphics.aspect = (float)w / (float)h;
	myGraphics.proj_matrix = glm::perspective(glm::radians(50.0f), myGraphics.aspect, 0.1f, 1000.0f);
}

void onKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) { // called everytime a key is pressed
	if (action == GLFW_PRESS) keyStatus[key] = true;
	else if (action == GLFW_RELEASE) keyStatus[key] = false;

	// toggle showing mouse.
	if (keyStatus[GLFW_KEY_M]) {
		mouseEnabled = !mouseEnabled;
		myGraphics.ToggleMouse();
	}
	// If exit key pressed.
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void onMouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {

}

void onMouseMoveCallback(GLFWwindow* window, double x, double y) {
	int mouseX = static_cast<int>(x);
	int mouseY = static_cast<int>(y);

	myGraphics.mouseX = mouseX;
	myGraphics.mouseY = mouseY;

	// helper variables for FPS camera
	if (myGraphics.cameraFirstMouse) {
		myGraphics.cameraLastX = (GLfloat)myGraphics.mouseX; myGraphics.cameraLastY = (GLfloat)myGraphics.mouseY; myGraphics.cameraFirstMouse = false;
	}
}

void onMouseWheelCallback(GLFWwindow* window, double xoffset, double yoffset) {
	int yoffsetInt = static_cast<int>(yoffset);
}
