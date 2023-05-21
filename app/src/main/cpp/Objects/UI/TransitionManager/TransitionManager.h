//
// Created by ksiks_wa3r on 4/28/23.
//

#ifndef SUMO_BOMBER_TRANSITIONMANAGER_H
#define SUMO_BOMBER_TRANSITIONMANAGER_H

#include "asengine.h"

using namespace ASEngine;

enum TransitionState {
	TRANSITION_OUT,
	TRANSITION_IN
};


class TransitionManager : public GameObject{

public:
	//change scene
	void changeSceneTo(const SceneID& sceneId);
	//fade
	void fadeIn();
	void fadeOut();

private:
	//fade variables
	float fade = 0.0f;
	float currentFade = 1.0f;
	const float FADE_SPEED = 8.0f;
	//transition state
	TransitionState state = TRANSITION_OUT;
	//next scene
	SceneID nextSceneId = "";

	//game events
	void onCreate();

	void onUpdate(float delta);

	void onDraw(Graphics& graphics);

	void onInputEvent(InputEvent event);

};


#endif //SUMO_BOMBER_TRANSITIONMANAGER_H
