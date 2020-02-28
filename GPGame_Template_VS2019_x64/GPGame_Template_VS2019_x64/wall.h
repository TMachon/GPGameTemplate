#ifndef WALL_H_INCLUDED
#define WALL_H_INCLUDED

#pragma once

#include <iostream>
#include <vector>
using namespace std;

#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "graphics.h"


class Wall {

public:
	Wall();
	void startup(Graphics myGraphics, float x, float y, float z, float x_size, float y_size, float z_size, bool soft);
	void sceneUpdate(Graphics myGraphics);
	void render();
	float getX();
	float getY();
	float getZ();
	float getXSize();
	float getYSize();
	float getZSize();

	glm::vec4 getTopLeft();
	glm::vec4 getTopRight();
	glm::vec4 getBottomLeft();
	glm::vec4 getBottomRight();
};

#endif