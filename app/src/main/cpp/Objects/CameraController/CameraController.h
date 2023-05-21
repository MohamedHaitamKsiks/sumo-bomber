//
// Created by ksiks_wa3r on 4/18/23.
//

#ifndef SUMO_BOMBER_CAMERACONTROLLER_H
#define SUMO_BOMBER_CAMERACONTROLLER_H

#include "asengine.h"

using namespace ASEngine;

class CameraController : public GameObject{

	//camera shake params
	float mag = 0.0f;
	float dur = 0.0f;
	float freq = 1.0f;

	//time
	float time = 0.0f;

	//slow motion timer
	float slowMotionTimer = 0.0f;
	bool slowMotionEnabled = false;

	void onCreate();

	void onUpdate(float delta);

	void onDraw(Graphics& graphics);

	void onInputEvent(InputEvent event);

public:
	//slow motion
	void slowMotion(float _scale = 0.2, float _dur = 1.0f);
	//shake
	void shake(float _mag = 4.0f, float _dur = 0.3f, float _freq = 20.0f);


};


#endif //SUMO_BOMBER_CAMERACONTROLLER_H
