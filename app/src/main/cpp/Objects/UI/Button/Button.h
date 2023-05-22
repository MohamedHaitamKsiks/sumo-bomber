//
// Created by ksiks_wa3r on 4/24/23.
//

#ifndef SUMO_BOMBER_BUTTON_H
#define SUMO_BOMBER_BUTTON_H

#include "asengine.h"

#include "../../CameraController/CameraController.h"
#include "ButtonParticle.h"
#include "../TransitionManager/TransitionManager.h"

using namespace ASEngine;

enum ButtonType {
	BUTTON_NONE,
	BUTTON_SOLO,
	BUTTON_VS,
	BUTTON_ONLINE,
	BUTTON_SETTINGS,
	BUTTON_RESUME,
	BUTTON_MAINSCR
};

class Button : public GameObject{

public:
	//type
	ButtonType type = BUTTON_NONE;
	//button active
	bool active = true;
	//show
	void show(float delai, vec2 startPosition, vec2 endPosition);
private:
	//scene's camera
	CameraController* camera;
	//scene's transition
	TransitionManager* transitionManager;
	//click delai
	const float CLICK_DELAI_DURATION = 0.5f;
	float clickDelaiTimer = 0.0f;
	//click scale animation
	float clickScale = 1.0f;
	bool clicked = false;
	//show up animation
	float showTimer = 0.0f;
	vec2 showEndPosition = vec2{0.0f, 0.0f};
	const float SHOW_SPEED = 14.5f;

	void onCreate();

	void onUpdate(float delta);

	void onDraw(Graphics& graphics);

	void onInputEvent(InputEvent event);

	void onClick();



};


#endif //SUMO_BOMBER_BUTTON_H
