#include "missile.h"
#include <iostream>
#include <sstream>
#include <ctime>

#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "shapes.h"
#include "graphics.h"

Missile::Missile(int id_in, Tank tank) {

	direction = tank.getLastMovement();
	y = 1.25f;
	velocity = 0.15f;

	x_size = y_size = z_size = 0.2f;

	id = id_in;

	alive = true;
	// Calculate initial missile position
	if (direction == UP) {
		x = tank.getX();
		z = tank.getZ() + tank.getZSize() / 2 + 0.1f;
	}
	else if (direction == DOWN) {
		x = tank.getX();
		z = tank.getZ() - tank.getZSize() / 2 - 0.1f;
	}
	else if (direction == RIGHT) {
		x = tank.getX() - tank.getXSize() / 2 - 0.1f;
		z = tank.getZ();
	}
	else if (direction == LEFT) {
		x = tank.getX() + tank.getXSize() / 2 + 0.1f;
		z = tank.getZ();
	}

	body.Load();
	body.fillColor = glm::vec4(12.0f / 225.0f, 12.0f / 225.0f, 12.0f / 225.0f, 1.0f);
}

void Missile::sceneUpdate(Graphics& myGraphics) {
	if (direction == UP) {
		// Check for out of bound the arena
		if (z < 9.0f) {
			z += velocity;
		}
		else {
			//If the missile reach the limit of the arena
			alive = false;
		}
		
	}
	else if (direction == DOWN) {
		// Check for out of bound the arena
		if (z > -19.0f) {
			z -= velocity;
		}
		else {
			//If the missile reach the limit of the arena
			alive = false;
		}
		
	}
	else if (direction == RIGHT) {
		// Check for out of bound the arena
		if (x > -14.0f) {
			x -= velocity;
		}
		else {
			//If the missile reach the limit of the arena
			alive = false;
		}
		
	}
	else if (direction == LEFT) {
		// Check for out of bound the arena
		if (x < 14.0f) {
			x += velocity;
		}
		else {
			//If the missile reach the limit of the arena
			alive = false;
		}
		
	}
	body.mv_matrix = myGraphics.viewMatrix * glm::translate(glm::vec3(x, y, z)) *
		glm::mat4(1.0f) *
		glm::scale(glm::vec3(x_size, y_size, z_size));
	body.proj_matrix = myGraphics.proj_matrix;
}

void Missile::render() {
	body.Draw();
}

float Missile::getX() {
	return x;
}

float Missile::getY() {
	return y;
}

float Missile::getZ() {
	return z;
}

float Missile::getXSize() {
	return x_size;
}

float Missile::getYSize() {
	return y_size;
}

float Missile::getZSize() {
	return z_size;
}

int Missile::getId() {
	return id;
}

bool Missile::isAlive() {
	return alive;
}