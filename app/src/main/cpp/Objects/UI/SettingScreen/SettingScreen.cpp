//
// Created by ksiks_wa3r on 5/23/23.
//

#include "SettingScreen.h"
#include "../ButtonToggle/ButtonToggle.h"
#include "../../System/SettingManager/SettingManager.h"
#include "../Button/Button.h"

void SettingScreen::onCreate() {
	layer = 100;
	//get setting manager
	SettingManager* settingManager = (SettingManager*) Instance::find("SettingManager");

	//create buttons
	ButtonToggle* audioButton = (ButtonToggle*) Instance::create("ButtonToggle");
	audioButton->text = "Audio";
	audioButton->value = &(settingManager->audio);
	audioButton->position.y = 130.0f;
	audioButton->layer = layer;

	ButtonToggle* accessibilityButton = (ButtonToggle*) Instance::create("ButtonToggle");
	accessibilityButton->text = "C.B.A.";
	accessibilityButton->value = &(settingManager->colorBlindAccessibility);
	accessibilityButton->position.y = 180.0f;
	accessibilityButton->layer = layer;

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

void SettingScreen::onUpdate(float delta) {

}

void SettingScreen::onDraw(Graphics &graphics) {
	//draw settings title
	graphics.drawSprite("spr_settings", 0, vec2{Screen::getCenter().x, 70.0f});
}

void SettingScreen::onInputEvent(InputEvent event) {

}
