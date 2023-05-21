//
// Created by ksiks_wa3r on 5/13/23.
//

#ifndef SUMO_BOMBER_SCOREMANAGER_H
#define SUMO_BOMBER_SCOREMANAGER_H

#include "asengine.h"

using namespace ASEngine;

struct GameModeSolo {
	uint32_t score = 0;
	uint32_t hightScore = 0;
	//reset score
	void reset() {
		score = 0;
	}
};

struct GameModeVs {
	uint32_t red = 0;
	uint32_t blue = 0;
	//reset score
	void reset() {
		red = 0;
		blue = 0;
	}
};


class ScoreManager: public GameObject {

public:
	//scores
	GameModeVs gameModeVs{};
	GameModeSolo gameModeSolo{};

private:
	void onCreate();

	void onUpdate(float delta);

	void onDraw(Graphics& graphics);

	void onInputEvent(InputEvent event);

};


#endif //SUMO_BOMBER_SCOREMANAGER_H
