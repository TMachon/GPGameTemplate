#ifndef TANK_H_INCLUDED
#define TANK_H_INCLUDED

#pragma once

#include <iostream>
#include <vector>
using namespace std;

#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "graphics.h"

#define UP 1
#define DOWN 2
#define RIGHT 3
#define LEFT 4


class Tank {

public:
	Tank();
	void move(int movement);
	void startup(Graphics myGraphics, bool player);
	void sceneUpdate(Graphics myGraphics);
	void render();

private:
	glm::mat4 getBaseMatrix();
	glm::mat4 getHeadMatrix();
	glm::mat4 getCannonMatrix();

};

#endif