//
// Created by ksiks_wa3r on 4/28/23.
//

#include "SplashScreen.h"



void SplashScreen::onCreate() {
	transitionManager = (TransitionManager*) Instance::find("TransitionManager");
}

void SplashScreen::onUpdate(float delta) {
	splashScreenTimer -= delta;
	if (splashScreenTimer < 0.0f && !splashScreenTimerFinished) {
		transitionManager->changeSceneTo("sc_title");
		splashScreenTimerFinished = true;
	}

}

void SplashScreen::onDraw(Graphics &graphics) {
	graphics.drawSprite("spr_splash_screen", 0, position);
}

void SplashScreen::onInputEvent(InputEvent event) {

}
