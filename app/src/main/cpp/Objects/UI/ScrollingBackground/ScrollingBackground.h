//
// Created by ksiks_wa3r on 5/23/23.
//

#ifndef SUMO_BOMBER_SCROLLINGBACKGROUND_H
#define SUMO_BOMBER_SCROLLINGBACKGROUND_H

#include "asengine.h"

using namespace ASEngine;

class ScrollingBackground : public GameObject {
	//background animation
	vec2 backgroundPosition = vec2{0.0f, 0.0f};
	vec2 backgroundSpeed = vec2{
			20.0f,
			10.0f
	};
	void onCreate();

	void onUpdate(float delta);

	void onDraw(Graphics& graphics);

	void onInputEvent(InputEvent event);
};


#endif //SUMO_BOMBER_SCROLLINGBACKGROUND_H
