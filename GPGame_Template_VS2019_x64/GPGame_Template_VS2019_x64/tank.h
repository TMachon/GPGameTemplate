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
#include "shapes.h"

#define UP 1
#define DOWN 2
#define RIGHT 3
#define LEFT 4


class Tank {

public:
	Tank();
	Tank(float, float, float);
	void move(int movement);
	void moveDebug(int movement);
	void startup(Graphics& myGraphics, bool player);
	void sceneUpdate(Graphics& myGraphics);
	void render();

	//Getter
	float getX();
	float getY();
	float getZ();
	float getXSize();
	float getYSize();
	float getZSize();
	Cube  getBase();
	Cube getHead();
	Cube getCannon();
	int getLastMovement();

	//Setter
	void setPosition(float x_in, float y_in, float z_in);
	void setLastMovement(int movement);


private:
	glm::mat4 getBaseMatrix();
	glm::mat4 getHeadMatrix();
	glm::mat4 getCannonMatrix();
	Cube base;
	Cube head;
	Cube cannon;
	float x, y, z;
	float x_size;
	float y_size;
	float z_size;
	glm::vec4 color;
	int last_movement;

};

#endif