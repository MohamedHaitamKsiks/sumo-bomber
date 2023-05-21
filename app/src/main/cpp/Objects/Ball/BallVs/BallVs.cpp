//
// Created by ksiks_wa3r on 5/14/23.
//

#include "BallVs.h"

void BallVs::onDestroy() {
	transitionManager->changeSceneTo("sc_main");
}

void BallVs::onExplosion() {
	//calculate score
	if (position.y < Screen::getCenter().y)
		scoreManager->gameModeVs.blue++;
	else
		scoreManager->gameModeVs.red++;

	//show score
	hud->showScore();
}


void BallVs::onCreate() {
	//super call
	Ball::onCreate();
	//params
	EXPLOSION_DURATION = 15.0f;
	explosionTimer = EXPLOSION_DURATION;
	DESTROY_DURATION = 3.0f;
	BOUNCE_NUMBER = 3;
	//get hud
	hud = (HudVs*) Instance::find("HudVs");

}

void BallVs::onUpdate(float delta) {
	Ball::onUpdate(delta);
	hud->fuseValue = explosionTimer / EXPLOSION_DURATION;

}

//draw
void BallVs::onDraw(Graphics &graphics) {
	//draw ball
	Ball::onDraw(graphics);
}
