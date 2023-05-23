//
// Created by ksiks_wa3r on 5/14/23.
//

#include "BallSolo.h"
#include "../../System/SettingManager/SettingManager.h"

void BallSolo::onCreate() {
	Ball::onCreate();
	float direction = Random::rand_rangef(0.0f, 2.0f * M_PI);
	velocity = vec2{1.0f, 0.0f}.rotate(direction) * 100.0f;
	mask.size = vec2::one() * 32.0f;
	//timer
	explosionTimer = 3.0f;
	//fall
	BOUNCE_NUMBER = 1;
	fall();
	//ball color
	BallColor colors[] = {BALL_BLUE, BALL_RED};
	color = colors[Random::randi() % 2];
	//get hud solo
	hudSolo = (HudSolo*) Instance::find("HudSolo");
	//get accessibility
	SettingManager* settingManager = (SettingManager*) Instance::find("SettingManager");
	hasAccessibility = settingManager->colorBlindAccessibility;
}

void BallSolo::onUpdate(float delta) {
	Ball::onUpdate(delta);
	//layer
	layer = int(position.y + 1.0f);

	//none
	if (soloState == BALL_SOLO_NONE) {
		collideWithArea(delta, soloManager->playerArea);
	}
	//drag
	else if (soloState == BALL_SOLO_DRAG) {
		elevation = DRAG_ELEVATION;
	}
	//released
	else if (soloState == BALL_SOLO_RELEASED) {
		//explosionTimer = EXPLOSION_DURATION;
		if (color == BALL_BLUE)
			collideWithArea(delta, soloManager->blueArea);
		else
			collideWithArea(delta, soloManager->redArea);
	}

}


void BallSolo::onDraw(Graphics &graphics) {
	if (color == BALL_BLUE)
		spriteId = "spr_ball_blue";
	else
		spriteId = "spr_ball_red";
	Ball::onDraw(graphics);
	//draw accessibility
	if (hasAccessibility && state != BALL_EXPLOSION) {
		graphics.drawSprite("spr_sign", int(color == BALL_RED), position - vec2{0.0f, elevation}, vec2::one() * 0.8f, 0.0f);
	}
	//graphics.drawRectangle(mask.position, mask.size, Color::green);
}


void BallSolo::onInputEvent(InputEvent event) {
	switch (event.type) {
		case INPUT_EVENT_POINTER_DOWN:
			if (state == BALL_DEFAULT && !soloManager->isBallDragged && soloState == BALL_SOLO_NONE && mask.pointInside(event.pointerPosition)) {
				soloManager->isBallDragged = true;
				soloState = BALL_SOLO_DRAG;
				pointerIndex = event.pointerIndex;
				velocity = vec2::zero();
				previousPosition = event.pointerPosition;
			}
			break;

		case INPUT_EVENT_POINTER_MOVE:
			if (state == BALL_DEFAULT && soloState == BALL_SOLO_DRAG && event.pointerIndex == pointerIndex) {
				previousPosition = event.pointerPosition;
				position = event.pointerPosition;
			}
			break;

		case INPUT_EVENT_POINTER_UP:
			if (state == BALL_DEFAULT && soloState == BALL_SOLO_DRAG && event.pointerIndex == pointerIndex) {
				soloManager->isBallDragged = false;
				//put bomb in right place
				if ( (color == BALL_RED && soloManager->redArea.pointInside(position)) ||
				(color == BALL_BLUE && soloManager->blueArea.pointInside(position)) ) {
					soloState = BALL_SOLO_RELEASED;
					//velocity
					velocity = (event.pointerPosition - previousPosition).normalized() * -150.0f;
					//fall
					fall();
					elevation = DRAG_ELEVATION;
				}
				else if (soloManager->playerArea.pointInside(position)) {
					soloState = BALL_SOLO_NONE;
					//velocity
					velocity = (event.pointerPosition - previousPosition).normalized() * -150.0f;
					//fall
					fall();
					elevation = DRAG_ELEVATION;
				}
				else {
					camera->slowMotion();
					explosionTimer = 0.0f;
					//lose
					soloManager->lose();
				}
			}
			break;
	}
}

void BallSolo::onExplosion() {
	if (soloState == BALL_SOLO_DRAG || soloState == BALL_SOLO_NONE) {
		soloManager->isBallDragged = false;
		camera->slowMotion();
		//lose
		soloManager->lose();
	} else {
		hudSolo->addPoint();
	};

}

void BallSolo::onDestroy() {

}

void BallSolo::collideWithArea(float delta, Rectangle area) {
	//collision with player area
	Rectangle maskNextPosition{};
	maskNextPosition.position = mask.position;
	maskNextPosition.size = vec2::zero();
	//on the x axis
	maskNextPosition.position.x = maskNextPosition.position.x + velocity.x * delta;
	//check collision
	if (!maskNextPosition.inside(area)) {
		velocity.x *= -1.0f;
		camera->shake(velocity.length() * shakeRatio, 0.15);
	}
	//on the y axis
	maskNextPosition = mask;
	maskNextPosition.position.y = maskNextPosition.position.y + velocity.y * delta;
	//check collision
	if (!maskNextPosition.inside(area)) {
		velocity.y *= -1.0f;
		camera->shake(velocity.length() * shakeRatio, 0.15);
	}
}


