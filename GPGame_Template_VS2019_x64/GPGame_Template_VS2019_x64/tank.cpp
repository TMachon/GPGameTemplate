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

glm::mat4 matrix_init_tank_base;
glm::mat4 matrix_init_tank_head;
glm::mat4 matrix_init_tank_cannon;

Tank::Tank() {

	x = 1.0f;
	y = 0.5f;
	z = 1.0f;

	color = glm::vec4(50.0f / 225.0f, 52.0f / 225.0f, 60.0f / 225.0f, 1.0f);

	matrix_init_tank_base = 
		glm::translate(glm::vec3(x, y, z)) *
		glm::mat4(10.0f) *
		glm::scale(glm::vec3(1.5f, 0.7f, 1.0f));

	matrix_init_tank_head =
		glm::translate(glm::vec3(x, y+0.5f, z)) *
		glm::mat4(10.0f) *
		glm::scale(glm::vec3(0.5f, 0.5f, 0.5f));

	matrix_init_tank_cannon =
		glm::translate(glm::vec3(x+1.0f, y + 0.6f, z)) *
		glm::mat4(10.0f) *
		glm::scale(glm::vec3(1.5f, 0.2f, 0.2f));
}

void Tank::startup(Graphics myGraphics) {

	base.Load();
	head.Load();
	cannon.Load();

	base.fillColor = color;
	head.fillColor = color;
	cannon.fillColor = color;
}

void Tank::move(Graphics myGraphics) {

	base.mv_matrix = myGraphics.viewMatrix * matrix_init_tank_base;
	base.proj_matrix = myGraphics.proj_matrix;

	head.mv_matrix = myGraphics.viewMatrix * matrix_init_tank_head;
	head.proj_matrix = myGraphics.proj_matrix;

	cannon.mv_matrix = myGraphics.viewMatrix * matrix_init_tank_cannon;
	cannon.proj_matrix = myGraphics.proj_matrix;
}

void Tank::draw() {

	base.Draw();
	head.Draw();
	cannon.Draw();

}