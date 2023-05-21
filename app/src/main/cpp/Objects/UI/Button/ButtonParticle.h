//
// Created by ksiks_wa3r on 4/28/23.
//

#ifndef SUMO_BOMBER_BUTTONPARTICLE_H
#define SUMO_BOMBER_BUTTONPARTICLE_H

#include "asengine.h"

using namespace ASEngine;

enum ButtonParticleType {
	BUTTON_PART_LEFT,
	BUTTON_PART_RIGHT
};

class ButtonParticle : public GameObject{
public:
	//particle type
	ButtonParticleType type = BUTTON_PART_LEFT;
	//movement
	vec2 velocity = {0.0f, 0.0f};
	const float GRAVITY = 600.0f;
	const float ROTATION_SPEED = -M_PI;

	void onCreate();

	void onUpdate(float delta);

	void onDraw(Graphics& graphics);

	void onInputEvent(InputEvent event);


};


#endif //SUMO_BOMBER_BUTTONPARTICLE_H
