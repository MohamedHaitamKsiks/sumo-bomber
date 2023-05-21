//
// Created by ksiks_wa3r on 4/28/23.
//

#include "ButtonParticle.h"

void ButtonParticle::onCreate() {

}

void ButtonParticle::onUpdate(float delta) {
	//rotation
	float velocitySign = 0.0f;
	if (abs(velocity.x) > 0.0f)
		velocitySign = velocity.x / abs(velocity.x);
	rotation += velocitySign * ROTATION_SPEED * delta;

	//gravity
	velocity.y += GRAVITY * delta;

	position = position + velocity * delta;
}

void ButtonParticle::onDraw(Graphics &graphics) {
	graphics.drawSprite("spr_button_particles", (int) type, position, scale, rotation);
}

void ButtonParticle::onInputEvent(InputEvent event) {

}
