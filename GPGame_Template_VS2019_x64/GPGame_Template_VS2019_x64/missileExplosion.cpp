#include "missileExplosion.h"
#include <iostream>
#include <sstream>
#include <ctime>


#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "shapes.h"
#include "graphics.h"

MissileExplosion::MissileExplosion(float x, float y, float z, Graphics& myGraphics) {
	// Generate random number of particle for the explosion
	int nb = 10+(rand() % 10);
	//Populate the list
	for (int i = 0; i < nb; i++) {
		particuleList.push_back(Particule(x, y, z));
	}
}

void MissileExplosion::sceneUpdate(Graphics& myGraphics) {
	//Update position particle list
	for (int i = 0; i < particuleList.size(); i++) {
		particuleList[i].sceneUpdate(myGraphics);
		if (particuleList[i].getLifeTime() <= 0) {
			particuleList.erase(particuleList.begin() + i);
		}
	}
}

void MissileExplosion::render() {
	//render particle
	for (int i = 0; i < particuleList.size(); i++) {
		particuleList[i].render();
	}
}

vector<Particule> MissileExplosion::getParticleList() {
	return particuleList;
}