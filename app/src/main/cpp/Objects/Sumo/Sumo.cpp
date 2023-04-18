//
// Created by ksiks_wa3r on 4/18/23.
//

#include "Sumo.h"

//walk dust descriptor
ParticleDescriptor Sumo::walkDustDescriptor {};

void Sumo::onCreate() {
	//dust particles
	//descriptor
	walkDustDescriptor.angle = {-M_PI / 8.0f, M_PI / 8.0f};
	walkDustDescriptor.scale = {0.3, 0.5};
	walkDustDescriptor.scaleSpeed = -1.0f;
	walkDustDescriptor.velocity = {10.0f, 20.0f};
	//emitter
	walkDustEmitter.life = 1.0f;
	walkDustEmitter.explosiveness = 0.8;
	walkDustEmitter.emitionRadius = 4.0f;
	walkDustEmitter.particleDescriptor = &walkDustDescriptor;
	walkDustEmitter.spriteId = "spr_sumo_dust";
	walkDustEmitter.particlesNumber = 20;

	//collision mask
	mask.size = vec2{32.0f, 32.0f};

	//play field area
	playFieldArea.position = vec2{0.0f, Screen::getCenter().y};
	playFieldArea.size = vec2{Screen::getSize().x, Screen::getCenter().y};

	//get ball object
	ball = (Ball*) Instance::find("Ball");
	//get camera
	camera = (CameraController*) Instance::find("CameraController");
}

void Sumo::onUpdate(float delta) {
	//set mask position to center
	mask.position = position - mask.size / 2.0f;

	//movement
	if (state == SUMO_IDLE || state == SUMO_CATCH) {
		//velocity
		velocity = direction * MAX_SPEED;
	}

	//default state behaviour
	if (state == SUMO_IDLE) {
		//calculate rotation
		if (velocity.lengthSquared() > 0) {
			walkDirection = (walkDirection * 1.50 + direction * 0.5).normalized();
			rotation = -walkDirection.angle() - M_PI / 2.0f + walkRotation;
		}
		//walk animation
		float walkSpeedScale = velocity.length() / MAX_SPEED;
		walkRotation = MAX_WALK_ROTATION * sin(16.0f * time) * walkSpeedScale;

		//collision with ball
		bool collision = collideWithInstance(ball, velocity * delta);
		//ball just entered
		if (collision && !ballEntered) {
			grab();
			ballEntered = true;
		}
		//ball just existed
		else if (!collision){
			ballEntered = false;
		}

	}
	//dash
	else if (state == SUMO_DASH) {
		scale = (scale * 1.5f + vec2::one() * 0.5f) / 2.0f;
	}
	//stun
	else if (state == SUMO_STUN) {
		velocity = velocity - velocity.normalized() * ACC * delta;
		if (velocity.length() < ACC * delta)
			velocity = vec2::zero();
		//stun timer
		stunTimer -= delta;
		if (stunTimer < 0.0f)
			state = SUMO_IDLE;
	}
	//catch
	else if (state == SUMO_CATCH) {
		arrowScale = (arrowScale * 1.3 + 1.0f * 0.7) / 2.0f;
		pitchAngle += pitchAngleSpeed * delta;
		rotation = pitchAngle + M_PI;
	}

	//update walk dust emitter
	walkDustEmitter.position = position;
	walkDustEmitter.rotation = rotation;
	walkDustEmitter.update(delta);

	//collision with playfield
	collideWithPlayField(delta);

	//add velocity
	position = position + velocity * delta;

	//calculate time
	time += delta;

}


void Sumo::collideWithPlayField(float delta) {
	//collision with outside walls
	Rectangle maskNextPosition = mask;
	//on the x axis
	maskNextPosition.position.x = maskNextPosition.position.x + velocity.x * delta;
	//check collision
	if (!maskNextPosition.inside(playFieldArea)) {
		//if dash stop dash
		if (state == SUMO_DASH) {
			stun();
			velocity.x *= -0.5f;
			return;
		}
		else if (state == SUMO_STUN) {
			velocity.x *= -0.5f;
		}
		else {
			velocity.x = 0.0f;
		}
	}
	//on the y axis
	maskNextPosition = mask;
	maskNextPosition.position.y = maskNextPosition.position.y + velocity.y * delta;
	//check collision
	if (!maskNextPosition.inside(playFieldArea)) {
		//if dash stop dash
		if (state == SUMO_DASH) {
			stun();
			velocity.y *= -0.5f;
			return;
		}
		else if (state == SUMO_STUN) {
			velocity.y *= -0.5f;
		}
		else {
			velocity.y = 0.0f;
		}

	}
}


void Sumo::dash() {
	if (state != SUMO_IDLE || direction.lengthSquared() < 0.0001f)
		return;
	//set state to dash
	state = SUMO_DASH;
	//set velocity
	velocity = direction.normalized() * DASH_SPEED;
	rotation = - direction.angle() - M_PI / 2.0f;
	walkDirection = direction.normalized();
	//scale
	scale.x = 0.4;
	scale.y = 2.0f;
	//shake camera for juice
	camera->shake(2.0);
}

void Sumo::stun() {
	stunTimer = STUN_DURATION;
	state = SUMO_STUN;
	scale = vec2::one();
	walkDustEmitter.emit();
	camera->shake();
}


void Sumo::grab() {
	state = SUMO_CATCH;
	frame = GRAB_FRAME;
	//rotate
	pitchAngle = -ball->velocity.angle();
	rotation = pitchAngle + M_PI;
	//grab ball
	ball->grab();
	//shake camera
	camera->shake(2.0f, 0.1);
	arrowScale = 0.0f;

}

void Sumo::pitch() {
	state = SUMO_IDLE;
	frame = NORMAL_FRAME;
	//
	vec2 pitchDirection = vec2{1.0f, 0.0f}.rotate(pitchAngle);
	walkDirection = pitchDirection;
	vec2 ballVelocity = pitchDirection * 1000.0f;
	ball->pitch(position, ballVelocity);
}


void Sumo::onDraw(Graphics &graphics) {
	//draw sumo
	drawSumo(graphics, position, scale, rotation);
	//draw joystick
	drawJoystick(graphics);
}

void Sumo::drawSumo(Graphics& graphics, vec2 position, vec2 scale, float rotation) {
	graphics.drawSprite("spr_sumo_blue", frame, position + vec2{0.0f, 8.0f}, scale, rotation, Color::black);
	//draw dust
	walkDustEmitter.draw(graphics);
	graphics.drawSprite("spr_sumo_blue", frame, position, scale, rotation);
	//draw particle stun
	if (state == SUMO_STUN)
		graphics.drawSprite("spr_sumo_stun_particles", time * 8.0f, position, scale, rotation);
	//pitch arrow
	if (state == SUMO_CATCH) {
		graphics.drawSprite("spr_pitch_arrow", 0, position, scale * arrowScale, pitchAngle);
	}


}


void Sumo::drawJoystick(Graphics &graphics) {
	if (!pointerDown)
		return;
	//draw joystick for ui
	Color joystickColor = Color{1.0f, 1.0f, 1.0f, 0.4};
	//draw base
	graphics.drawSprite("spr_joystick", 0, pointerDownPosition, joystickColor);
	//draw stick
	graphics.drawSprite("spr_joystick", 1, pointerDownPosition + direction * 32.0f, joystickColor);

}


void Sumo::onInputEvent(InputEvent event) {
	//pointer diff is used to calculate stick position
	vec2 pointerDiff{};

	switch (event.type) {
		//init joystick by clicking on screen randomly (later It should be restricted to the player field)
		case ASEngine::INPUT_EVENT_POINTER_DOWN:
			//pitch
			if (state == SUMO_CATCH) {
				pitch();
				break;
			}
			//dash
			if (pointerDown) {
				if ( event.pointerIndex != pointerIndex && playFieldArea.pointInside(event.pointerPosition))
					dash();
				break;
			}
			//joystick
			pointerDown = true;
			pointerDownPosition = event.pointerPosition;
			pointerIndex = event.pointerIndex;
			break;
		//joysick move
		case ASEngine::INPUT_EVENT_POINTER_MOVE:
			//check pointer index
			if (!pointerDown || event.pointerIndex != pointerIndex)
				break;
			//movement direction
			pointerDiff = event.pointerPosition - pointerDownPosition;
			if (pointerDiff.lengthSquared() < 32.0f * 32.0f)
				direction = pointerDiff / 32.0f;
			else
				direction = pointerDiff.normalized();
			//pointerDownPosition = event.pointerPosition;
			break;
		//release joystick
		case ASEngine::INPUT_EVENT_POINTER_UP:
			//only if pointer index == pointer index
			if (event.pointerIndex != pointerIndex)
				break;
			pointerDown = false;
			direction = vec2::zero();
			break;

	}
}


