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

glm::mat4 matrix_init_tank_base;

Tank::Tank() {
	x = 1.0f;
	y = 0.5f;
	z = 1.0f;
	matrix_init_tank_base = 
		glm::translate(glm::vec3(x, y, z)) *
		glm::mat4(10.0f) *
		glm::scale(glm::vec3(1.0f, 1.0f, 1.0f));
}

void Tank::startup(Graphics myGraphics) {
	base.Load();
	/**
	head.Load();
	cannon.Load();
	/**/
	base.fillColor = glm::vec4(60.0f, 60.0f, 62.0f, 1.0f);
	base.mv_matrix = myGraphics.viewMatrix * matrix_init_tank_base;
	base.proj_matrix = myGraphics.proj_matrix;
	base.Draw();
}

void Tank::move(Graphics myGraphics) {
	base.mv_matrix = myGraphics.viewMatrix * matrix_init_tank_base;
	base.proj_matrix = myGraphics.proj_matrix;
}

void Tank::draw() {
	base.Draw();
}