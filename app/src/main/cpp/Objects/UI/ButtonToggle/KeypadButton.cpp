//
// Created by Lenovo on 5/24/2023.
//

#include "KeypadButton.h"


void KeypadButton::onCreate() {
    camera = (CameraController*) Instance::find("CameraController");
    mask.size = vec2{
            38.0f,
            38.0f
    };
}

void KeypadButton::onUpdate(float delta) {

    //animation
}

void KeypadButton::onDraw(Graphics &graphics) {
    if (!value)
        return;
    graphics.drawText(text, position + vec2{6.0f, 0.0f}, "ft_pixel", 3);
    if (buttonScale < 0.9f)
        graphics.drawSprite("spr_button_toggle_pressed", 0, position + vec2{Screen::getSize().x, 0.0f}, vec2::one() * buttonScale, 0.0);
    else
        graphics.drawSprite("spr_button_toggle", int(*value), position + vec2{Screen::getSize().x, 0.0f}, vec2::one() * buttonScale, 0.0);
}

void KeypadButton::onInputEvent(InputEvent event) {
    if (event.type == ASEngine::INPUT_EVENT_POINTER_DOWN && mask.pointInside(event.pointerPosition)) {
        onToggle();
        camera->shake();
        buttonScale = 0.7f;
    }
}

void KeypadButton::onToggle() {
    if (!value)
        return;
    *value = !(*value);
}
