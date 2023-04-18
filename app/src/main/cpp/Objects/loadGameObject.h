//
// Created by ksiks_wa3r on 3/27/23.
//

#ifndef ANDROIDSIMPLEENGINE_LOADGAMEOBJECT_H
#define ANDROIDSIMPLEENGINE_LOADGAMEOBJECT_H

#include "asengine.h"
#include <string>

//include game objects
#include "Sumo/Sumo.h"
#include "Terrain/Terrain.h"
#include "CameraController/CameraController.h"
#include "Ball/Ball.h"

//add every game object here
static void loadGameObjects() {
	ASEngine::Instance::addGameObject<Sumo>("Sumo");
	ASEngine::Instance::addGameObject<Terrain>("Terrain");
	ASEngine::Instance::addGameObject<CameraController>("CameraController");
	ASEngine::Instance::addGameObject<Ball>("Ball");
}

#endif //ANDROIDSIMPLEENGINE_LOADGAMEOBJECT_H
