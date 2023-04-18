//
// Created by ksiks_wa3r on 4/18/23.
//

#ifndef SUMO_BOMBER_BALL_H
#define SUMO_BOMBER_BALL_H

#include "asengine.h"

using namespace ASEngine;

#include "../CameraController/CameraController.h"

class Ball : public GameObject{
	//animation
	const float animationSpeed = 8.0f / 100.0f;
	const float stretchRatio = 1.0f / 7000.0f;
	const float shakeRatio = 1.0f / 1000.0f;
	//time
	float time = 0.0f;

	//level area
	Rectangle levelArea{};

	//get camera
	CameraController* camera;

	//animation
	float frame = 0.0f;

	void onCreate();

	void onUpdate(float delta);

	void collideWithLevelArea(float delta);

	void onDraw(Graphics& graphics);

	void onInputEvent(InputEvent event);

public:
	//physics
	vec2 velocity{0.0f, 10.0f};

	//grab ball
	void grab();

	//throw ball
	void pitch(vec2 _position, vec2 _velocity);

};


#endif //SUMO_BOMBER_BALL_H
