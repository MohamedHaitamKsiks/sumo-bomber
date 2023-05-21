//
// Created by ksiks_wa3r on 5/14/23.
//

#ifndef SUMO_BOMBER_BALLSOLO_H
#define SUMO_BOMBER_BALLSOLO_H

#include "asengine.h"
#include "../Ball.h"

using namespace ASEngine;

class BallSolo : public Ball {
	//on explosion
	void onExplosion();
	//on destroy
	void onDestroy();
};


#endif //SUMO_BOMBER_BALLSOLO_H
