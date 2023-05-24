//
// Created by ksiks_wa3r on 5/14/23.
//

#ifndef SUMO_BOMBER_BALLSOLO_H
#define SUMO_BOMBER_BALLSOLO_H

#include "asengine.h"
#include "../Ball.h"
#include "../../System/SoloManager/SoloManager.h"
#include "../../UI/HudSolo/HudSolo.h"

using namespace ASEngine;

enum BallColor {
	BALL_RED,
	BALL_BLUE
};

enum BallSoloState {
	BALL_SOLO_NONE,
	BALL_SOLO_DRAG,
	BALL_SOLO_RELEASED,
};

class BallSolo : public Ball {
public:
	SoloManager* soloManager = nullptr;
	BallColor color;
	BallSoloState soloState = BALL_SOLO_NONE ;

private:
	//hud
	HudSolo* hudSolo;
	//input
	int pointerIndex = -1;
	bool pointerDown = false;
	vec2 previousPosition{};
	//drag
	const float DRAG_ELEVATION = 12.0f;
	void collideWithArea(float delta,Rectangle area);
	//settings
	bool hasAccessibility = false;

	//on create
	void onCreate();
	//on update
	void onUpdate(float delta);
	void onDraw(Graphics& graphics);
	//on input
	void onInputEvent(InputEvent event);

	//on explosion
	void onExplosion();
	//on destroy
	void onDestroy();
};


#endif //SUMO_BOMBER_BALLSOLO_H
