//
// Created by ksiks_wa3r on 5/14/23.
//

#ifndef SUMO_BOMBER_BALLVS_H
#define SUMO_BOMBER_BALLVS_H

#include "asengine.h"
#include "../Ball.h"
#include "../../UI/HudVs/HudVs.h"

using namespace ASEngine;

class BallVs: public  Ball{
	HudVs* hud;
	//oncreate
	void onCreate();
	//on draw
	void onDraw(Graphics& graphics);
	//on explosion
	void onExplosion();
	//on destroy
	void onDestroy();
	//on update
	void onUpdate(float delta);
};


#endif //SUMO_BOMBER_BALLVS_H
