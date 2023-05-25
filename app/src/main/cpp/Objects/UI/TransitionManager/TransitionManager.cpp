//
// Created by ksiks_wa3r on 4/28/23.
//

#include "TransitionManager.h"


void TransitionManager::onCreate() {
	//set persistance
	persistant = true;
	//fade out
	fade = 0.0f;
	//layer
	layer = 100000;
}

void TransitionManager::onUpdate(float delta) {
	//fade
	currentFade = Interpolate::linear(currentFade, fade, FADE_SPEED * delta);
	//transistion in
	if (nextSceneId.length() > 0 && state == TRANSITION_IN && abs(currentFade - fade) < 0.01f ) {
		Scene::changeSceneTo(nextSceneId);
		nextSceneId = "";
		fadeOut();
	}
}

void TransitionManager::onDraw(Graphics &graphics) {
	vec2 fadeRectSize = vec2{
		currentFade * Screen::getSize().x,
		Screen::getSize().y
	};
	graphics.drawRectangle(vec2::zero(), fadeRectSize, Color::black);
}


void TransitionManager::fadeIn() {
	state = TRANSITION_IN;
	fade = 1.5f;
}

void TransitionManager::fadeOut() {
	state = TRANSITION_OUT;
	fade = 0.0f;
}


void TransitionManager::changeSceneTo(const SceneID &sceneId) {
	nextSceneId = sceneId;
	fadeIn();
}


void TransitionManager::onInputEvent(InputEvent event) {

}
