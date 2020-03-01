#include "particule.h"
#include <iostream>
#include <sstream>
#include <ctime>

#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "shapes.h"
#include "graphics.h"

Particule::Particule(float x_in, float y_in, float z_in) {
	x = x_in;
	y = y_in;
	z = z_in;
	velocity = 0.15f;
	lifetime = rand() % 50;
}

void Particule::startup(Graphics& myGraphics) {

	body.Load();
	int r = rand() % 100 + 1;
	int g = rand() % 100 + 1;
	int b = rand() % 100 + 1;
	body.fillColor = glm::vec4(r / 225.0f, 10.f / 225.0f, 10.0f / 255.0f, 1.0f);
}

void Particule::sceneUpdate(Graphics& myGraphics) {
	float rand_x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX/2);
	float rand_y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX/2);
	float rand_z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX/2);

	x = x + (rand_x - 1.0f) * velocity;
	y = y + (rand_y - 1.0f) * velocity;
	z = z + (rand_z - 1.0f) * velocity;

	lifetime--;

	body.mv_matrix = myGraphics.viewMatrix * glm::translate(glm::vec3(x, y, z)) *
		glm::mat4(1.0f) *
		glm::scale(glm::vec3(X_SIZE, Y_SIZE, Z_SIZE));
	body.proj_matrix = myGraphics.proj_matrix;
}

void Particule::render() {
	body.Draw();
}

float Particule::getX() {
	return x;
}

float Particule::getY() {
	return y;
}

float Particule::getZ() {
	return z;
}

float Particule::getXSize() {
	return X_SIZE;
}

float Particule::getYSize() {
	return Y_SIZE;
}

float Particule::getZSize() {
	return Z_SIZE;
}

int Particule::getId() {
	return id;
}

int Particule::getLifeTime() {
	return lifetime;
}