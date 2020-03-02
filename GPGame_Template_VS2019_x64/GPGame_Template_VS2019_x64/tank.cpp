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

Tank::Tank(int id_in, float x_int, float y_int, float z_int) {
	x = x_int;
	y = y_int;
	z = z_int;

	x_size = 1.0f;
	y_size = 1.0f;
	z_size = 1.0f;

	same = 0;

	id = id_in;
}

void Tank::startup(Graphics& myGraphics, bool player_in) {

	player = player_in;
	if (player) {
		color = glm::vec4(150.0f / 225.0f, 172.0f / 225.0f, 160.0f / 225.0f, 1.0f);
	}
	else {
		color = glm::vec4(50.0f / 225.0f, 52.0f / 225.0f, 60.0f / 225.0f, 1.0f);
	}

	base.Load();
	head.Load();
	cannon.Load();

	base.fillColor = color;
	head.fillColor = color;
	cannon.fillColor = color;
}

void Tank::move(int movement, bool updateMovement) {

	if (updateMovement) last_movement = movement;

	if (movement == UP) {
		if (z < 9.0f) {
			z += 0.01f;
		}
		
	}

	if (movement == DOWN) {
		if (z > -19.0f) {
			z -= 0.01f;
		}
		
	}

	if (movement == RIGHT) {
		
		if (x > -14.0f) {
			x -= 0.01f;
		}
		
	}

	if (movement == LEFT) {
		if (x < 14.0f) {
			x += 0.01f;
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

	base.Draw();
	head.Draw();
	cannon.Draw();

}

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

void Tank::setPosition(float x_in, float y_in, float z_in) {
	x = x_in;
	y = y_in;
	z = z_in;
}


// PRIVATE

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

void Tank::resetSame() {
	same = 0;
}

int Tank::getSame() {
	return same;
}

void Tank::setLastMovement(int movement) {
	last_movement = movement;
}

void Tank::incSame() {
	same++;
}


int Tank::getId() {
	return id;
}

bool Tank::isPlayer() {
	return player;
}