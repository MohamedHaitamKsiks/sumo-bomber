//
// Created by ksiks_wa3r on 5/23/23.
//

#ifndef SUMO_BOMBER_BUTTONTOGGLE_H
#define SUMO_BOMBER_BUTTONTOGGLE_H

#include "asengine.h"
#include "../../CameraController/CameraController.h"

using namespace ASEngine;

class ButtonToggle : public GameObject{

public:
	std::string text = "";
	bool* value = nullptr;

private:
	//camera
	CameraController* camera;

	//click animation
	float buttonScale = 1.0f;
	const float ANIMATION_SPEED = 20.0f;

	//events
	void onCreate();

	void onUpdate(float delta);

	void onDraw(Graphics& graphics);

	void onInputEvent(InputEvent event);

	void onToggle();

};


#endif //SUMO_BOMBER_BUTTONTOGGLE_H
