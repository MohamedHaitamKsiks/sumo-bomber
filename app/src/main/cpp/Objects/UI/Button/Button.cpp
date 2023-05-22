//
// Created by ksiks_wa3r on 4/24/23.
//

#include "Button.h"

void Button::onCreate() {
	//mask size
	mask.size = vec2{124.0f, 40.0f};
	//camera
	camera = (CameraController *) Instance::find("CameraController");
	//transition manager
	transitionManager = (TransitionManager *) Instance::find("TransitionManager");
}

void Button::onUpdate(float delta) {
	//clicked animation
	if (clicked && visible) {
		clickScale = Interpolate::linear(clickScale, 0.75, 30.0f * delta);
		if (abs(clickScale - 0.75f) < 0.01f) {
			visible = false;
			//shake camera
			camera->shake(2.0f);
			//cleare particles
			vec2 particleOffset = vec2{
				31.0f,
				Random::rand_rangef(-8.0f, 8.0f)
			};
			vec2 particleVelocity = vec2{
				Random::rand_rangef(25.0f, 55.0f),
				particleOffset.y * 20.0f
			};
			//left
			ButtonParticle* leftParticle = (ButtonParticle*) Instance::create("ButtonParticle");
			leftParticle->type = BUTTON_PART_LEFT;
			leftParticle->position = position - particleOffset;
			leftParticle->velocity = particleVelocity * -1.0f;
			//right
			ButtonParticle* rightParticle = (ButtonParticle*) Instance::create("ButtonParticle");
			rightParticle->type = BUTTON_PART_RIGHT;
			rightParticle->position = position + particleOffset;
			rightParticle->velocity = particleVelocity;
		}
	}

	//click timer
	if (clicked) {
		clickDelaiTimer -= delta;
		if (clickDelaiTimer < 0.0f)
			onClick();
	}

	//show up animation
	showTimer -= delta;
	if (showTimer < 0.0f) {
		position = Interpolate::linear(position, showEndPosition, SHOW_SPEED * delta);
	}

	//mask position
	mask.position = position - mask.size / 2.0f;

}

void Button::onDraw(Graphics &graphics) {
	if (clicked)
		graphics.drawSprite("spr_button_clicked", 0, position, scale * clickScale, 0.0f);
	else
		graphics.drawSprite("spr_buttons", (int) type, position);
	//graphics.drawRectangle(mask.position, mask.size, Color{1.0f, 0.0f, 0.0f, 0.4f});
}

void Button::onInputEvent(InputEvent event) {
	if (active && event.type == ASEngine::INPUT_EVENT_POINTER_DOWN && mask.pointInside(event.pointerPosition)) {
		clicked = true;
		clickDelaiTimer = CLICK_DELAI_DURATION;
		//camera->shake();
	}
}

void Button::onClick() {
	clicked = false;
	switch (type) {
		case BUTTON_NONE:
			// nothing
			break;
		case BUTTON_SOLO:
			// Redirect to solo scene
			transitionManager->changeSceneTo("sc_main");
			break;
		case BUTTON_VS:
			// Redirect to versus scene
			transitionManager->changeSceneTo("sc_main");
			break;
		case BUTTON_ONLINE:
			// Redirect to online scene
			transitionManager->changeSceneTo("sc_main");
			break;
		case BUTTON_SETTINGS:
			// Redirect to settings scene
			transitionManager->changeSceneTo("sc_main");
			break;
		case BUTTON_RESUME:
			// Redirect to resume scene

			Instance::togglePause();
			break;
		case BUTTON_MAINSCR:
			// Redirect to main screen scene
            Instance::togglePause();
			transitionManager->changeSceneTo("sc_start");

			break;
		default:
			// Handle unrecognized button type
			break;
	}
}

void Button::show(float delai, vec2 startPosition, vec2 endPosition) {
	showTimer = delai;
	position = startPosition;
	showEndPosition = endPosition;
}
