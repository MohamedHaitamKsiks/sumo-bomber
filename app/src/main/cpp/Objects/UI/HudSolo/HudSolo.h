//
// Created by ksiks_wa3r on 5/22/23.
//

#ifndef SUMO_BOMBER_HUDSOLO_H
#define SUMO_BOMBER_HUDSOLO_H

#include "asengine.h"
#include "../../System/ScoreManager/ScoreManager.h"
#include "../Button/Button.h"

using namespace ASEngine;

class HudSolo : public GameObject{

public:
	//add point
	void addPoint();
	//game over
	void showGameOver();

private:
	//game over visibility
	bool isGameOverVisible = false;
	//score manager
	ScoreManager* scoreManager;

	//buttons list
	std::vector<ButtonType> types = {
			BUTTON_RETRY,
			BUTTON_MAINSCR
	};

	float scoreOffset = 0.0f;

	//create
	void onCreate();

	void onUpdate(float delta);

	void onDraw(Graphics& graphics);

	void onInputEvent(InputEvent event);

};


#endif //SUMO_BOMBER_HUDSOLO_H
