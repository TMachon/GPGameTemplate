#ifndef PARTICULE_H_INCLUDED
#define PARTICULE_H_INCLUDED

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

#define X_SIZE 0.4f
#define Y_SIZE 0.4f
#define Z_SIZE 0.4f

class Particule {

public:

	Particule(float x_in, float y_in, float z_in);
	void startup(Graphics& myGraphics);
	void sceneUpdate(Graphics& myGraphics);
	void render();
	float getX();
	float getY();
	float getZ();
	float getXSize();
	float getYSize();
	float getZSize();
	int getId();
	int getLifeTime();

private:

	Cube body;
	int direction;
	float x, y, z;
	float velocity;
	int id;
	int lifetime;
};

#endif