#pragma once

#include <iostream>
#include <vector>
using namespace std;

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "graphics.h"

class Tank {

public:
	Tank();
	void startup(Graphics myGraphics);
	void move(Graphics myGraphics);
	void draw();

};