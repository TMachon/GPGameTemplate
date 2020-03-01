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
	int nb = rand() % 100;
	for (int i = 0; i < nb; i++) {
		particuleList.push_back(Particule(x, y, z));
		particuleList.back().startup(myGraphics);
	}
}

void MissileExplosion::sceneUpdate(Graphics& myGraphics) {
	for (int i = 0; i < particuleList.size(); i++) {
		particuleList[i].sceneUpdate(myGraphics);
		if (particuleList[i].getLifeTime() <= 0) {
			particuleList.erase(particuleList.begin() + i);
		}
	}
}

void MissileExplosion::render() {
	for (int i = 0; i < particuleList.size(); i++) {
		particuleList[i].render();
	}
}

vector<Particule> MissileExplosion::getParticleList() {
	return particuleList;
}