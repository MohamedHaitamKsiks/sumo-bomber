//
// Created by ksiks_wa3r on 4/24/23.
//

#ifndef SUMO_BOMBER_TITLESCREEN_H
#define SUMO_BOMBER_TITLESCREEN_H

#include <vector>

#include "asengine.h"
#include "../Button/Button.h"

using namespace ASEngine;

class TitleScreen : public GameObject {

	float time = 0.0f;
	//background animation
	vec2 backgroundPosition = vec2{0.0f, 0.0f};
	vec2 backgroundSpeed = vec2{
		20.0f,
		10.0f
	};

	std::vector<ButtonType> types = {
			BUTTON_SOLO,
			BUTTON_VS,
			BUTTON_ONLINE,
			BUTTON_SETTINGS
	};

	std::vector<Button*> buttons = {};

	void onCreate();

	void onUpdate(float delta);

	void onDraw(Graphics& graphics);

	void onInputEvent(InputEvent event);


};


#endif //SUMO_BOMBER_TITLESCREEN_H
