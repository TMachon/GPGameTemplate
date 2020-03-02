#include "MissileGuiding.h"
#include <iostream>
#include <sstream>
#include <ctime>
#include <algorithm>

#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "shapes.h"
#include "graphics.h"

MissileGuiding::MissileGuiding(int id_in, Tank tank, Tank target, int field[30][30]) {

	direction = tank.getLastMovement();
	velocity = 0.055f;

	x_size = y_size = z_size = 0.35f;

	x = tank.getX();
	y = tank.getY();
	z = tank.getZ();

	x_steps = vector<float>();
	z_steps = vector<float>();
	x_steps.push_back(target.getX());
	z_steps.push_back(target.getZ());

	goUp = (z < target.getZ());
	goDown = (z > target.getZ());
	goRight = (x > target.getX());
	goLeft = (x < target.getX());

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
		goUp = (z < z_steps[0]);
	}
	if (goDown) {
		z -= velocity;
		goDown = (z > z_steps[0]);
	}
	if (goRight) {
		x -= velocity;
		goRight = (x > x_steps[0]);
	}
	if (goLeft) {
		x += velocity;
		goLeft = (x < x_steps[0]);
	}

	if (!(goUp || goDown || goRight || goLeft)) {
		x_steps.erase(x_steps.begin());
		z_steps.erase(z_steps.begin());
		if (x_steps.size() > 0) {
			goUp = (z < z_steps[0]);
			goDown = (z > z_steps[0]);
			goRight = (x > x_steps[0]);
			goLeft = (x < x_steps[0]);
		}
		else {
			alive = false;
		}
	}

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