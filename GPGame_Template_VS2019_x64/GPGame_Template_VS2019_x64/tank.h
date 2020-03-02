#ifndef TANK_H_INCLUDED
#define TANK_H_INCLUDED

#pragma once

#include <iostream>
#include <vector>
using namespace std;

#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "graphics.h"
#include "shapes.h"

//Constant for movement
#define UP 1
#define DOWN 2
#define RIGHT 3
#define LEFT 4

#define MAX_MOVE 100 // Used for the ennemies tank

/* Define how many movement do the ennemies tank
/  in a direction before changing direction
/  It makes the ennemies tank movement more realistic
*/


class Tank {

public:
	Tank();
	Tank(int, float, float, float, Graphics& myGraphics); //Constructor for player
	Tank(int id_in, Graphics& myGraphics); // Constructor for ennemies tank
	void move(int movement, bool updateMovement); // Move the tank
	void moveDebug(int movement);
	void sceneUpdate(Graphics& myGraphics); // Update object
	void render(); // Render object

	//Getter
	float getX();
	float getY();
	float getZ();
	float getXSize();
	float getYSize();
	float getZSize();
	Cube  getBase();
	Cube getHead();
	Cube getCannon();
	int getLastMovement(); // Return the direction of last movement
	int getSame();
	int getId();
	bool isPlayer();

	//Setter
	void setPosition(float x_in, float y_in, float z_in);
	void setLastMovement(int movement);
	void resetSame();
	void incSame();


private:
	glm::mat4 getBaseMatrix();
	glm::mat4 getHeadMatrix();
	glm::mat4 getCannonMatrix();

	//3 part of the tank
	Cube base; // Tank hitbox
	Cube head;
	Cube cannon;

	float x, y, z; //Tank position
	float x_size, y_size, z_size; // Tank size (for the base cube)
	glm::vec4 color;
	int last_movement;
	int same; //Use for ennemies tank 
	int id;
	bool player; // Is tank player 
};

#endif