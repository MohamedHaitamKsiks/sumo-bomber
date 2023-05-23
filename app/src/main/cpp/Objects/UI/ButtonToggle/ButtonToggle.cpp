//
// Created by ksiks_wa3r on 5/23/23.
//

#include "ButtonToggle.h"

void ButtonToggle::onCreate() {
	camera = (CameraController*) Instance::find("CameraController");
	mask.size = vec2{
		Screen::getSize().x,
		38.0f
	};
}

void ButtonToggle::onUpdate(float delta) {
	mask.position.x = position.x;
	mask.position.y = position.y - 32.0f;
	//animation
	buttonScale = Interpolate::linear(buttonScale, 1.0f, delta * ANIMATION_SPEED);
}

void ButtonToggle::onDraw(Graphics &graphics) {
	if (!value)
		return;
	graphics.drawText(text, position + vec2{6.0f, 0.0f}, "ft_pixel", 3);
	if (buttonScale < 0.9f)
		graphics.drawSprite("spr_button_toggle_pressed", 0, position + vec2{Screen::getSize().x, 0.0f}, vec2::one() * buttonScale, 0.0);
	else
		graphics.drawSprite("spr_button_toggle", int(*value), position + vec2{Screen::getSize().x, 0.0f}, vec2::one() * buttonScale, 0.0);
}

void ButtonToggle::onInputEvent(InputEvent event) {
	if (event.type == ASEngine::INPUT_EVENT_POINTER_DOWN && mask.pointInside(event.pointerPosition)) {
		onToggle();
		camera->shake();
		buttonScale = 0.7f;
	}
}

void ButtonToggle::onToggle() {
	if (!value)
		return;
	*value = !(*value);
}
