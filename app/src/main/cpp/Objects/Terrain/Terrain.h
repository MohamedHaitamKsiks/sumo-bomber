//
// Created by ksiks_wa3r on 4/18/23.
//

#ifndef SUMO_BOMBER_TERRAIN_H
#define SUMO_BOMBER_TERRAIN_H

#include "asengine.h"

using namespace ASEngine;

class Terrain : public GameObject{

	void onCreate();

	void onUpdate(float delta);

	void onDraw(Graphics& graphics);

	void onInputEvent(InputEvent event);

};


#endif //SUMO_BOMBER_TERRAIN_H
