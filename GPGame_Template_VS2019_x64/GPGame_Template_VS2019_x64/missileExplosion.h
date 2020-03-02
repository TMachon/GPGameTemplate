#ifndef MISSILE_EXPLOSION_H_INCLUDED
#define MISSILE_EXPLOSION_H_INCLUDED

#include "particule.h"
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

#pragma once
class MissileExplosion {
public:
	MissileExplosion(float x, float y, float z, Graphics& myGraphics);
	void sceneUpdate(Graphics& myGraphics); //Update position particle list
	void render();//Render particle
	vector<Particule> getParticleList();

private:
	std::vector<Particule> particuleList;
};

#endif
