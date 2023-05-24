//
// Created by ksiks_wa3r on 5/23/23.
//

#ifndef SUMO_BOMBER_SETTINGMANAGER_H
#define SUMO_BOMBER_SETTINGMANAGER_H

#include "asengine.h"
using namespace ASEngine;

class SettingManager : public GameObject {

public:
	bool audio = false;
	bool colorBlindAccessibility = false;
private:
	OboeSinePlayer sinePlayer;
	bool isPlaying = false;

	void onCreate();

	void onUpdate(float delta);

	void onDraw(Graphics& graphics);

	void onInputEvent(InputEvent event);
};


#endif //SUMO_BOMBER_SETTINGMANAGER_H
