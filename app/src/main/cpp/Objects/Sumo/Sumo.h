//
// Created by ksiks_wa3r on 4/18/23.
//

#ifndef SUMO_BOMBER_SUMO_H
#define SUMO_BOMBER_SUMO_H

#include "asengine.h"

#include "../CameraController/CameraController.h"
#include "../Ball/Ball.h"

using namespace ASEngine;

enum SumoState {
	SUMO_IDLE,
	SUMO_DASH,
	SUMO_CATCH,
	SUMO_STUN
};

class Sumo: public GameObject {

	//sumo states
	SumoState state = SUMO_IDLE;
	//velocity
	vec2 direction{0.0f, 0.0f};
	vec2 velocity{0.0f, 0.0f};
	const float MAX_SPEED = 120.0f;
	const float ACC = 900.0f;

	//controls
	bool pointerDown = false;
	int pointerIndex = -1;
	vec2 pointerDownPosition{0.0f, 0.0f};
	//controls
	Rectangle joystickArea{};
	Rectangle buttonArea{};
	//how much the joystick have in the button area
	float joystickButtonRation = 0.6f;

	//animation
	float walkRotation = 0.0f;
	const float MAX_WALK_ROTATION = M_PI / 20.0f;
	vec2 walkDirection{0.0f, -1.0f};

	//current frame
	int frame = 0;
	const int GRAB_FRAME = 1;
	const int NORMAL_FRAME = 0;

	//walk dust particles
	static ParticleDescriptor walkDustDescriptor;
	ParticleEmitter walkDustEmitter{};

	//dash
	const float DASH_SPEED = 600.0f;

	//stun after dash
	float stunTimer = 0.0f;
	const float STUN_DURATION = 1.0f;

	//grab
	float pitchAngle = 0.0f;
	float pitchAngleSpeed = 1.22f * M_PI;
	float arrowScale = 0.0f;
	const float GRAB_DURATION = 3.0f;
	float grabTimer = GRAB_DURATION;
	//heat
	const float GRAB_HEAT_SCALE = 1.5f;
	const float OVERHEAT_STUN_DURATION = 1.0f;
	const float OVERHEAT_PUSHBACK_SPEED = 200.0f;
	const float OVERHEAT_BALL_SPEED = 50.0f;
	//heat modulate
	Color modulate = Color::white;
	const Color heatModulate = {4.0f, 1.0f, 1.0f, 1.0f};
	//smoke particles
	static ParticleDescriptor smokeDescriptor;
	ParticleEmitter smokeEmitter{};

	//ball
	Ball* ball = nullptr;
	bool ballEntered = false;

	//camera
	CameraController* camera = nullptr;

	//area
	Rectangle playFieldArea;

	//time
	float time = 0.0f;

	//on create
	void onCreate();

	//on update
	void onUpdate(float delta);
	//collide with playfield
	void collideWithPlayField(float delta);
	//start dash
	void dash();
	//start stun
	void stun();

	//ball grab/throw
	void grab();
	void pitch();
	void overheat();

	//draw to screen
	void onDraw(Graphics& graphics);
	//draw sumo
	void drawSumo(Graphics& graphics, vec2 position, vec2 scale, float rotation);
	//draw joystick
	void drawJoystick(Graphics& graphics);

	//on ball entered
	void onBallEntered();

	//on input
	void onInputEvent(InputEvent event);


};


#endif //SUMO_BOMBER_SUMO_H
