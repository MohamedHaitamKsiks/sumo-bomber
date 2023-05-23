//
// Created by ksiks_wa3r on 5/23/23.
//

#include "OnlineScreen.h"
#include "../Button/Button.h"

void OnlineScreen::onCreate() {
	layer = 1000;
	//exit button
	Button* exitButton = (Button*) Instance::create("Button");
	exitButton->type = BUTTON_MAINSCR;
	exitButton->layer = layer;
	//start
	vec2 buttonStartPosition = vec2{
			-Screen::getCenter().x,
			240.0f
	};
	//end
	vec2 buttonEndPosition = vec2{
			Screen::getCenter().x,
			240.0f
	};
	//show up
	exitButton->show(0.15f, buttonStartPosition, buttonEndPosition);
}

void OnlineScreen::onUpdate(float delta) {

}

void OnlineScreen::onDraw(Graphics &graphics) {
	graphics.drawSprite("spr_comming_soon", 0, vec2{Screen::getCenter().x, 100.0f});
}

void OnlineScreen::onInputEvent(InputEvent event) {

}
