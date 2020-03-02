#include "wall.h"
#include <iostream>
#include <sstream>

#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "shapes.h"
#include "graphics.h"

// PUBLIC
Wall::Wall() {

}

Wall::Wall(Graphics myGraphics, float x_in, float y_in, float z_in, float x_size_in, float y_size_in, float z_size_in, bool soft_in) {
	x_wall = x_in;
	y_wall = y_in;
	z_wall = z_in;
	x_size_wall = x_size_in;
	y_size_wall = y_size_in;
	z_size_wall = z_size_in;
	soft = soft_in;

	color_wall = glm::vec4(200.0f / 225.0f, 80.0f / 225.0f, 50.0f / 225.0f, 1.0f);
	cube.Load();
	cube.fillColor = color_wall;
}

void Wall::sceneUpdate(Graphics myGraphics) {

	cube.mv_matrix = myGraphics.viewMatrix * glm::translate(glm::vec3(x_wall, y_wall, z_wall)) *
		glm::mat4(1.0f) *
		glm::scale(glm::vec3(x_size_wall, y_size_wall, z_size_wall));
	cube.proj_matrix = myGraphics.proj_matrix;
}

void Wall::render() {
	cube.Draw();
}

float Wall::getX() {
	return x_wall;
}

float Wall::getY() {
	return y_wall;
}

float Wall::getZ() {
	return z_wall;
}

float Wall::getXSize() {
	return x_size_wall;
}

float Wall::getYSize() {
	return y_size_wall;
}

float Wall::getZSize() {
	return z_size_wall;
}

glm::vec4 Wall::getTopLeft() {
	return glm::vec4(x_wall + x_size_wall/2, y_wall, z_wall + z_size_wall/2, 1.0f);
}

glm::vec4 Wall::getTopRight() {
	return glm::vec4(x_wall - x_size_wall/2, y_wall, z_wall + z_size_wall/2, 1.0f);
}

glm::vec4 Wall::getBottomLeft() {
	return glm::vec4(x_wall + x_size_wall/2, y_wall, z_wall - z_size_wall/2, 1.0f);
}

glm::vec4 Wall::getBottomRight() {
	return glm::vec4(x_wall - x_size_wall/2, y_wall, z_wall - z_size_wall/2, 1.0f);
}