//
// Created by ksiks_wa3r on 4/18/23.
//

#include "Ball.h"

void Ball::onCreate() {
	mask.size = vec2{16.0f, 16.0f};
	//level area
	levelArea.position = vec2::zero();
	levelArea.size = Screen::getSize();
	//get camera
	camera = (CameraController*) Instance::find("CameraController");
}

void Ball::onUpdate(float delta) {
	//set mask position to center
	mask.position = position - mask.size / 2.0f;

	//collision with wall
	collideWithLevelArea(delta);

	//rotation
	rotation = -velocity.angle() - M_PI / 2.0f;

	//stretch the ball
	scale.x = 1.0f - velocity.length() * stretchRatio;
	scale.y = 1.0f + velocity.length() * stretchRatio;

	//update position
	position = position + velocity * delta;

	//update frame
	frame += animationSpeed * velocity.length() * delta;
	//update time
	time += delta;
}

void Ball::onDraw(Graphics &graphics) {
	graphics.drawSprite("spr_ball", frame, position + vec2{0.0f, 8.0f}, scale, rotation, Color::black);
	graphics.drawSprite("spr_ball", frame, position, scale, rotation);
}

void Ball::onInputEvent(InputEvent event) {

}

//grab ball
void Ball::grab() {
	visible = false;
	collsionEnabled = false;
	velocity = vec2::zero();
}

//throw
void Ball::pitch(vec2 _position, vec2 _velocity) {
	visible = true;
	collsionEnabled = true;
	velocity = _velocity;
	position = _position;
}

void Ball::collideWithLevelArea(float delta) {
	//collision with outside walls
	Rectangle maskNextPosition = mask;
	//on the x axis
	maskNextPosition.position.x = maskNextPosition.position.x + velocity.x * delta;
	//check collision
	if (!maskNextPosition.inside(levelArea)) {
		velocity.x *= -1.0f;
		camera->shake(velocity.length() * shakeRatio, 0.15);
	}
	//on the y axis
	maskNextPosition = mask;
	maskNextPosition.position.y = maskNextPosition.position.y + velocity.y * delta;
	//check collision
	if (!maskNextPosition.inside(levelArea)) {
		velocity.y *= -1.0f;
		camera->shake(velocity.length() * shakeRatio, 0.15);
	}
}

