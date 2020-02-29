#include "missile.h"
#include <iostream>
#include <sstream>

#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "shapes.h"
#include "graphics.h"

Missile::Missile(Tank tank) {

	direction = tank.getLastMovement();
	y = 1.25f;
	velocity = 0.75f;

	x_size = y_size = z_size = 0.2f;

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
}

void Missile::startup(Graphics& myGraphics) {

	body.Load();
	body.fillColor = glm::vec4(12.0f / 225.0f, 12.0f / 225.0f, 12.0f / 225.0f, 1.0f);
}

void Missile::sceneUpdate(Graphics& myGraphics) {
	if (direction == UP) {
		z += velocity;
	}
	else if (direction == DOWN) {
		z -= velocity;
	}
	else if (direction == RIGHT) {
		x -= velocity;
	}
	else if (direction == LEFT) {
		x += velocity;
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