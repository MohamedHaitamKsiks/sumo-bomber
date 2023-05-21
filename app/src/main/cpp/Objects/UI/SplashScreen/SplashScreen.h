//
// Created by ksiks_wa3r on 4/28/23.
//

#ifndef SUMO_BOMBER_SPLASHSCREEN_H
#define SUMO_BOMBER_SPLASHSCREEN_H

#include "asengine.h"

using namespace ASEngine;

#include "../TransitionManager/TransitionManager.h"

class SplashScreen : public GameObject {

	float SPLASH_SCREEN_DURATION = 2.5;
	float splashScreenTimer = SPLASH_SCREEN_DURATION;
	bool splashScreenTimerFinished = false;

	TransitionManager* transitionManager;

	void onCreate();

	void onUpdate(float delta);

	void onDraw(Graphics& graphics);

	void onInputEvent(InputEvent event);

};


#endif //SUMO_BOMBER_SPLASHSCREEN_H
