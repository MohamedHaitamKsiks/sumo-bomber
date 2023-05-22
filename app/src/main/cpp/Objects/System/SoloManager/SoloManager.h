//
// Created by ksiks_wa3r on 5/22/23.
//

#ifndef SUMO_BOMBER_SOLOMANAGER_H
#define SUMO_BOMBER_SOLOMANAGER_H

#include "asengine.h"

using namespace ASEngine;

class SoloManager : public GameObject{

public:
	//ball dragged
	bool isBallDragged = false;

	//areas
	Rectangle blueArea{};
	Rectangle redArea{};
	Rectangle playerArea{};

	//spawn timer
	const float SPAWN_DURATION = 1.5f;
	float spawnTimer = SPAWN_DURATION;
	float time = 0.0f;
	//spawn a new ball
	void spawnBall();

private:
	//events
	void onCreate();

	void onUpdate(float delta);

	void onDraw(Graphics& graphics);

	void onInputEvent(InputEvent event);
};


#endif //SUMO_BOMBER_SOLOMANAGER_H
