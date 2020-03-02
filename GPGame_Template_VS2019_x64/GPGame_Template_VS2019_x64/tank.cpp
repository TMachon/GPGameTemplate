#include "tank.h"
#include <iostream>
#include <sstream>
#include <ctime>


#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "shapes.h"
#include "graphics.h"

// PUBLIC

Tank::Tank() {

}

//Player constructor
Tank::Tank(int id_in, float x_int, float y_int, float z_int, Graphics& myGraphics, bool player_in) {

	//Init tank position

	x = x_int;
	y = y_int;
	z = z_int;

	x_size = 1.0f;
	y_size = 1.0f;
	z_size = 1.0f;

	same = 0;

	id = id_in;

	player = player_in;
	if (player) color = glm::vec4(150.0f / 225.0f, 172.0f / 225.0f, 160.0f / 225.0f, 1.0f); // Define bright color for the player tank
	else color = glm::vec4(50.0f / 225.0f, 52.0f / 225.0f, 60.0f / 225.0f, 1.0f); // Define dark color for the ennemies tank

	// Load the 3 part of the tank
	base.Load();
	head.Load();
	cannon.Load();

	// Fill the same color for all part
	base.fillColor = color;
	head.fillColor = color;
	cannon.fillColor = color;
	last_movement = UP; // Initialize last_movement
}

void Tank::move(int movement, bool updateMovement) {

	if (updateMovement) last_movement = movement; // save the movement

	if (movement == UP) {
		//Check for out of band the arena
		if (z < 9.0f) {
			z += 0.05f;
		}
		
	}

	if (movement == DOWN) {
		//Check for out of band the arena
		if (z > -19.0f) {
			z -= 0.05f;
		}
		
	}

	if (movement == RIGHT) {
		//Check for out of band the arena
		if (x > -14.0f) {
			x -= 0.05f;
		}
		
	}

	if (movement == LEFT) {
		//Check for out of band the arena
		if (x < 14.0f) {
			x += 0.05f;
		}
	}

}

void Tank::moveDebug(int movement) {

	last_movement = movement;

	if (movement == UP) {
		z += 0.02f;
	}

	if (movement == DOWN) {
		z -= 0.02f;
	}

	if (movement == RIGHT) {
		x -= 0.02f;
	}

	if (movement == LEFT) {
		x += 0.02f;
	}

}

void Tank::sceneUpdate(Graphics& myGraphics) {

	//Update tank position
	base.mv_matrix = myGraphics.viewMatrix * glm::translate(glm::vec3(x, y, z)) *
		glm::mat4(1.0f) *
		glm::scale(glm::vec3(x_size, y_size, z_size)); 
	base.proj_matrix = myGraphics.proj_matrix;

	head.mv_matrix = myGraphics.viewMatrix * getHeadMatrix();
	head.proj_matrix = myGraphics.proj_matrix;

	cannon.mv_matrix = myGraphics.viewMatrix * getCannonMatrix();
	cannon.proj_matrix = myGraphics.proj_matrix;

}

void Tank::render() {

	//Draw different part
	base.Draw();
	head.Draw();
	cannon.Draw();

}

/** Getter **/

float Tank::getX() {
	return x;
}

float Tank::getY() {
	return y;
}

float Tank::getZ() {
	return z;
}

float Tank::getXSize() {
	return x_size;
}

float Tank::getYSize() {
	return y_size;
}

float Tank::getZSize() {
	return z_size;
}

int Tank::getSame() {
	return same;
}

glm::mat4 Tank::getBaseMatrix() {
	glm::mat4 matrix = glm::translate(glm::vec3(x, y, z)) *
		glm::mat4(1.0f) *
		glm::scale(glm::vec3(x_size, y_size, z_size));
	return matrix;
}

glm::mat4 Tank::getHeadMatrix() {
	glm::mat4 matrix = glm::translate(glm::vec3(x, y_size+0.25f, z))*
		glm::mat4(1.0f)*
		glm::scale(glm::vec3(0.5f, 0.5f, 0.5f));
	return matrix;
}

glm::mat4 Tank::getCannonMatrix() {
	glm::mat4 matrix = glm::translate(glm::vec3(x, y_size + 0.25f, z + 0.5f))*
		glm::mat4(1.0f)*
		glm::scale(glm::vec3(0.2f, 0.2f, 0.5f));

	if (last_movement == UP) {
		matrix = glm::translate(glm::vec3(x, y_size + 0.25f, z + 0.5f)) *
			glm::mat4(1.0f) *
			glm::scale(glm::vec3(0.2f, 0.2f, 0.5f));
	}
	else if (last_movement == DOWN) {
		matrix = glm::translate(glm::vec3(x, y_size + 0.25f, z - 0.5f)) *
			glm::mat4(1.0f) *
			glm::scale(glm::vec3(0.2f, 0.2f, 0.5f));
	}
	else if (last_movement == LEFT) {
		matrix = glm::translate(glm::vec3(x + 0.5f, y_size + 0.25f, z)) *
			glm::mat4(1.0f) *
			glm::scale(glm::vec3(0.5f, 0.2f, 0.2f));
	}
	else if (last_movement == RIGHT) {
		matrix = glm::translate(glm::vec3(x - 0.5f, y_size + 0.25f, z)) *
			glm::mat4(1.0f) *
			glm::scale(glm::vec3(0.5f, 0.2f, 0.2f));
	}
	return matrix;
}

Cube Tank::getBase() {
	return base;
}

Cube Tank::getHead() {
	return head;
}

Cube Tank::getCannon() {
	return cannon;
}

int Tank::getLastMovement() {
	return last_movement;
}

int Tank::getId() {
	return id;
}

bool Tank::isPlayer() {
	return player;
}

void Tank::resetSame() {
	same = 0;
}

//Setter

void Tank::setPosition(float x_in, float y_in, float z_in) {
	x = x_in;
	y = y_in;
	z = z_in;
}

void Tank::setLastMovement(int movement) {
	last_movement = movement;
}
//Increase same variable 
void Tank::incSame() {
	same++;
}