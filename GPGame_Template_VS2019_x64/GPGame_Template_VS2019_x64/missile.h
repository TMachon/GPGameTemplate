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

//Constant Missile direction
#define UP 1
#define DOWN 2
#define RIGHT 3
#define LEFT 4

class Missile {

public:

	Missile(int id, Tank tank);
	void sceneUpdate(Graphics& myGraphics);
	void render();
	//Getter
	float getX();
	float getY();
	float getZ();
	float getXSize();
	float getYSize();
	float getZSize();
	int getId();
	bool isAlive(); // is missile alive

private:

	Cube body;
	int direction;
	float x, y, z;
	float x_size;
	float y_size;
	float z_size;
	float velocity;
	int id;
	bool alive;
};

#endif