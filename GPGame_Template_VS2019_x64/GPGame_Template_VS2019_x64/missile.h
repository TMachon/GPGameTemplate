#ifndef MISSILE_H_INCLUDED
#define MISSILE_H_INCLUDED

#pragma once

#include <iostream>
#include <vector>
using namespace std;

#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "tank.h"
#include "graphics.h"
#include "shapes.h"

#define UP 1
#define DOWN 2
#define RIGHT 3
#define LEFT 4

class Missile {

public:

	Missile(Tank tank);
	void startup(Graphics& myGraphics);
	void sceneUpdate(Graphics& myGraphics);
	void render();

private:

	Cube body;
	int direction;
	float x, y, z;
	float velocity;

};

#endif