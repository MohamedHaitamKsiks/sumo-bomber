//
// Created by ksiks_wa3r on 5/14/23.
//

#ifndef SUMO_BOMBER_HUDVS_H
#define SUMO_BOMBER_HUDVS_H

#include <string>
#include <sstream>

#include "asengine.h"
#include "../../System/ScoreManager/ScoreManager.h"
#include "../../Sumo/Sumo.h"

using namespace ASEngine;

class HudVs: public GameObject {
public:
	float fuseValue = 1.0f;
	void showScore();

private:
	//fuse particles
	ParticleEmitter fuseEmitter{};
	ParticleEmitter smokeEmitter{};
	static ParticleDescriptor fuseDescriptor;

	//score visibility
	bool isScoreVisible = false;
	float scoreOffset = 0.0f;
	float backgroundDim = 0.5f;
	const float SHOW_SCORE_SPEED = 6.0f;
	//delai
	float delaiTimer = DELAI_DURATION;
	const float DELAI_DURATION = 1.0f;

	//score manager
	ScoreManager* scoreManager;

	void onCreate();

	void onUpdate(float delta);

	void onDraw(Graphics& graphics);

	void onInputEvent(InputEvent event);

};


#endif //SUMO_BOMBER_HUDVS_H
