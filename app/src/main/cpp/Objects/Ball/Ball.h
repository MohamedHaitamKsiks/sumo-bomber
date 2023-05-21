//
// Created by ksiks_wa3r on 4/18/23.
//

#ifndef SUMO_BOMBER_BALL_H
#define SUMO_BOMBER_BALL_H

#include "asengine.h"

using namespace ASEngine;

#include "../CameraController/CameraController.h"
#include "../UI/TransitionManager/TransitionManager.h"
#include "../System/ScoreManager/ScoreManager.h"

enum BallState {
	BALL_FALL,
	BALL_DEFAULT,
	BALL_PREPARE_EXPLOSION,
	BALL_EXPLOSION
};

class Ball : public GameObject{
public:
	//explosion
	BallState state = BALL_DEFAULT;
	//physics
	vec2 velocity{0.0f, 10.0f};
	const float DEC = 40.0f;

	//start fall
	void fall();

	//grab ball
	void grab();

	//throw ball
	void pitch(vec2 _position, vec2 _velocity);

protected:
	//get transition manager
	TransitionManager* transitionManager;
	//get score manager
	ScoreManager* scoreManager;

	//fall before serve
	float elevation = 0.0f;
	float elevationSpeed = 0.0f;
	const float ELEVATION_START = 300.0f;
	const float GRAVITY = 500.0f;
	//bounce from falling
	const float BOUNCE_SPEED_RATIO = 0.25f;
	int BOUNCE_NUMBER = 3;
	int bounceCounter = 0;
	//destroy timer
	float DESTROY_DURATION = 1.0f;
	float destroyTimer = 0.0;

	//explosion
	float EXPLOSION_DURATION = 5.0f;
	float explosionTimer = EXPLOSION_DURATION;

	//prepare explosion animation
	float ballExplosionScale = 1.0f;
	const float EXPLOSION_SCALE_SPEED = 10.0f;
	const float EXPLOSION_SCALE = 1.25f;

	//quick flashs before explosion
	const float FLASH_FREQ = 6.0f;
	const float FLASH_DURATION = 1.0f;

	//animation
	const float animationSpeed = 8.0f / 100.0f;
	const float stretchRatio = 1.0f / 7000.0f;
	const float shakeRatio = 1.0f / 1000.0f;

	//explosion particles
	static ParticleDescriptor explosionDescriptor;
	ParticleEmitter explosionEmitter;

	//time
	float time = 0.0f;

	//level area
	Rectangle levelArea{};

	//get camera
	CameraController* camera;

	//animation
	float frame = 0.0f;

	//events
	virtual void onExplosion() = 0;
	virtual void onDestroy() = 0;

	//bounce
	void bounce();

	void onCreate();

	void onUpdate(float delta);

	void collideWithLevelArea(float delta);

	void onDraw(Graphics& graphics);

	void onInputEvent(InputEvent event);


};


#endif //SUMO_BOMBER_BALL_H
