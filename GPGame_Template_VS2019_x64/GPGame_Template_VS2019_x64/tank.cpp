#include "tank.h"
#include <iostream>
#include <sstream>

#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "shapes.h"
#include "graphics.h"

float x, y, z;

Cube base;
Cube head;
Cube cannon;

glm::vec4 color;

// PUBLIC

Tank::Tank() {

	x = 1.0f;
	y = 0.5f;
	z = 1.0f;

}

void Tank::startup(Graphics myGraphics, bool player) {

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

void Tank::move(int movement) {

	if (movement == UP) {
		z += 0.01f;
	}

	if (movement == DOWN) {
		z -= 0.01f;
	}

	if (movement == RIGHT) {
		x -= 0.01f;
	}

	if (movement == LEFT) {
		x += 0.01f;
	}

}

void Tank::sceneUpdate(Graphics myGraphics) {

	base.mv_matrix = myGraphics.viewMatrix * getBaseMatrix();
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


// PRIVATE

glm::mat4 Tank::getBaseMatrix() {
	glm::mat4 matrix = glm::translate(glm::vec3(x, y, z)) *
		glm::mat4(10.0f) *
		glm::scale(glm::vec3(1.5f, 0.7f, 1.0f));
	return matrix;
}

glm::mat4 Tank::getHeadMatrix() {
	glm::mat4 matrix = glm::translate(glm::vec3(x, y + 0.5f, z))*
		glm::mat4(10.0f)*
		glm::scale(glm::vec3(0.5f, 0.5f, 0.5f));
	return matrix;
}

glm::mat4 Tank::getCannonMatrix() {
	glm::mat4 matrix = glm::translate(glm::vec3(x + 1.0f, y + 0.6f, z))*
		glm::mat4(10.0f)*
		glm::scale(glm::vec3(1.5f, 0.2f, 0.2f));
	return matrix;
}