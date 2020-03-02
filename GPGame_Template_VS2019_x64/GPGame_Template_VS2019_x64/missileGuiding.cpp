#include "MissileGuiding.h"
#include <iostream>
#include <sstream>
#include <ctime>

#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "shapes.h"
#include "graphics.h"

MissileGuiding::MissileGuiding(int id_in, Tank tank, Tank player) {

	direction = tank.getLastMovement();
	velocity = 0.055f;

	x_size = y_size = z_size = 0.35f;

	x = tank.getX();
	y = tank.getY();
	z = tank.getZ();

	x_destination = player.getX();
	y_destination = player.getY();
	z_destination = player.getZ();

	goUp = (z < z_destination);
	goDown = (z > z_destination);
	goRight = (x > x_destination);
	goLeft = (x < x_destination);

	id = id_in;

	alive = true;
}

void MissileGuiding::startup(Graphics& myGraphics) {

	body.Load();
	body.fillColor = glm::vec4(60.0f / 225.0f, 50.0f / 225.0f, 125.0f / 225.0f, 1.0f);
}

void MissileGuiding::sceneUpdate(Graphics& myGraphics) {
	
	if (goUp) {
		z += velocity;
		goUp = (z < z_destination);
	}
	if (goDown) {
		z -= velocity;
		goDown = (z > z_destination);
	}
	if (goRight) {
		x -= velocity;
		goRight = (x > x_destination);
	}
	if (goLeft) {
		x += velocity;
		goLeft = (x < x_destination);
	}

	alive = (goUp || goDown || goRight || goLeft);

	body.mv_matrix = myGraphics.viewMatrix * glm::translate(glm::vec3(x, y, z)) *
		glm::mat4(1.0f) *
		glm::scale(glm::vec3(x_size, y_size, z_size));
	body.proj_matrix = myGraphics.proj_matrix;
}

void MissileGuiding::render() {
	body.Draw();
}

float MissileGuiding::getX() {
	return x;
}

float MissileGuiding::getY() {
	return y;
}

float MissileGuiding::getZ() {
	return z;
}

float MissileGuiding::getXSize() {
	return x_size;
}

float MissileGuiding::getYSize() {
	return y_size;
}

float MissileGuiding::getZSize() {
	return z_size;
}

int MissileGuiding::getId() {
	return id;
}

bool MissileGuiding::isAlive() {
	return alive;
}