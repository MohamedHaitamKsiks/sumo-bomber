//
// Created by ksiks_wa3r on 5/23/23.
//

#ifndef SUMO_BOMBER_SETTINGSCREEN_H
#define SUMO_BOMBER_SETTINGSCREEN_H

#include "asengine.h"

using namespace ASEngine;

class SettingScreen : public GameObject{

public:


private:
	void onCreate();

	void onUpdate(float delta);

	void onDraw(Graphics& graphics);

	void onInputEvent(InputEvent event);

};


#endif //SUMO_BOMBER_SETTINGSCREEN_H
