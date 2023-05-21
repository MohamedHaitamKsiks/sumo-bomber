//
// Created by ksiks_wa3r on 4/18/23.
//

#include "Sumo.h"

//walk dust descriptor
ParticleDescriptor Sumo::walkDustDescriptor {};

//smoke desciptor
ParticleDescriptor Sumo::smokeDescriptor {};

void Sumo::onCreate() {
	layer = 1;
	//dust particles
	//descriptor
	walkDustDescriptor.angle = {-M_PI / 8.0f, M_PI / 8.0f};
	walkDustDescriptor.scale = {0.3, 0.5};
	walkDustDescriptor.scaleSpeed = -1.0f;
	walkDustDescriptor.velocity = {10.0f, 20.0f};
	//emitter
	walkDustEmitter.life = 1.0f;
	walkDustEmitter.explosiveness = 0.2;
	walkDustEmitter.emitionRadius = 4.0f;
	walkDustEmitter.particleDescriptor = &walkDustDescriptor;
	walkDustEmitter.spriteId = "spr_sumo_dust";
	walkDustEmitter.particlesNumber = 20;

	//smoke particles
	//descriptor
	smokeDescriptor.angle = {0.0f, 2.0f * M_PI};
	smokeDescriptor.direction = {0.0f, 2.0f * M_PI};
	smokeDescriptor.scale = 1.0f;
	smokeDescriptor.velocity = {30.0f, 40.0f};
	smokeDescriptor.frameRate = 4.0f;
	//emitter
	smokeEmitter.life = 2.0f;
	smokeEmitter.explosiveness = 0.0f;
	smokeEmitter.emitionRadius = 4.0f;
	smokeEmitter.particleDescriptor = &smokeDescriptor;
	smokeEmitter.spriteId = "spr_sumo_smoke_particle";
	smokeEmitter.particlesNumber = 10;

	//collision mask
	mask.size = vec2{32.0f, 32.0f};

	//sprite color
	if (objectId == "SumoRed")
		sumoSpriteId = "spr_sumo_red";
	else
		sumoSpriteId = "spr_sumo_blue";

	//direction
	if (objectId == "SumoRed") {
		walkDirection = vec2{0.0f, 1.0f};
		rotation = M_PI;
	}
	else {
		walkDirection = vec2{0.0f, -1.0f};
	}


	//play field area
	if (objectId == "SumoRed")
		playFieldArea.position = vec2{0.0f, 0.0f};
	else
		playFieldArea.position = vec2{0.0f, Screen::getCenter().y};
	//size
	playFieldArea.size = vec2{Screen::getSize().x, Screen::getCenter().y};

	//control araes
	//joystick area
	joystickArea.position = playFieldArea.position;
	//player red
	if (objectId == "SumoRed")
		joystickArea.position.x = playFieldArea.position.x + playFieldArea.size.x * (1.0f - joystickButtonRation);
	else
		joystickArea.position.x = playFieldArea.position.x;

	joystickArea.size = vec2{
			playFieldArea.size.x * joystickButtonRation,
			playFieldArea.size.y
	};

	//button area
	buttonArea.position = vec2{
		playFieldArea.position.x + joystickArea.size.x,
		playFieldArea.position.y
	};
	//player red
	if (objectId == "SumoRed")
		buttonArea.position = vec2{
				playFieldArea.position.x,
				playFieldArea.position.y
		};
	else
		buttonArea.position = vec2{
				playFieldArea.position.x + joystickArea.size.x,
				playFieldArea.position.y
		};

	buttonArea.size = vec2{
		playFieldArea.size.x * (1.0f - joystickButtonRation),
		playFieldArea.size.y
	};

	//get ball object
	//ball = (Ball*) Instance::find("Ball");
	//get camera
	camera = (CameraController*) Instance::find("CameraController");
}

void Sumo::onUpdate(float delta) {
	//set mask position to center
	mask.position = position - mask.size / 2.0f;

	//movement
	if (state == SUMO_IDLE || state == SUMO_CATCH) {
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
		arrowScale = Interpolate::linear(arrowScale, 1.0f, 25.0f * delta);;
		//pitchAngle += pitchAngleSpeed * delta;
		if (direction.length() > 0.0f)
			pitchAngle = -direction.angle();
		rotation = pitchAngle + M_PI;
		//grab timer
		grabTimer -= delta;
		if (grabTimer < 0.0f || ball->state == BALL_PREPARE_EXPLOSION)
			overheat();
		//smokeEmitter.particlesNumber = int(20.0f * (1.0f - grabTimer / GRAB_DURATION));

	}

	//grab cooldown
	if (state != SUMO_CATCH) {
		grabTimer += delta;
		grabTimer = fmin(grabTimer, GRAB_DURATION);
	}

	//heat effect
	float interpolationScale = 1.0f - grabTimer / GRAB_DURATION;
	modulate = Interpolate::linear(Color::white, heatModulate, interpolationScale);
	//emit smokes
	if (grabTimer < OVERHEAT_STUN_DURATION)
		smokeEmitter.emit();

	//update walk dust emitter
	walkDustEmitter.position = position;
	walkDustEmitter.rotation = rotation;
	walkDustEmitter.update(delta);

	//smoke emitter
	smokeEmitter.position = position;
	smokeEmitter.update(delta);

	//collision with playfield
	collideWithPlayField(delta);


	//collision with ball
	if (state != SUMO_CATCH) {
		Ball* collisionBall = (Ball*) collideWithObject("Ball", velocity * delta);
		//ball just entered
		if (collisionBall && !ballEntered) {
			ball = collisionBall;
			onBallEntered();
			ballEntered = true;
		}
		//ball just existed
		else if (!collisionBall){
			ballEntered = false;
		}
	}

	//grab rotation animation
	grabRotation = Interpolate::linear(grabRotation, 0.0f, 10.0f * delta);

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

void Sumo::overheat() {
	//stun
	stunTimer = OVERHEAT_STUN_DURATION;
	frame = NORMAL_FRAME;
	state = SUMO_STUN;
	//direction
	float angle = pitchAngle - M_PI / 2.0f;
	vec2 pitchDirection = vec2{1.0f, 0.0f}.rotate(angle);
	//pushback
	velocity = vec2{1.0f, 0.0f}.rotate(angle) * -OVERHEAT_PUSHBACK_SPEED;
	//release ball
	vec2 ballVelocity = pitchDirection * OVERHEAT_BALL_SPEED;
	ball->pitch(position, ballVelocity);
	//shake
	camera->shake();
}

void Sumo::grab() {
	state = SUMO_CATCH;
	frame = GRAB_FRAME;
	//rotate
	pitchAngle = -ball->velocity.angle();
	rotation = pitchAngle + M_PI;
	grabRotation = - M_PI;
	//grab ball
	ball->grab();
	//shake camera
	camera->shake(2.0f, 0.1);
	arrowScale = 0.0f;
}

void Sumo::pitch() {
	state = SUMO_IDLE;
	frame = NORMAL_FRAME;
	//pitch direction
	vec2 pitchDirection = vec2{1.0f, 0.0f}.rotate(pitchAngle);
	walkDirection = pitchDirection;
	grabRotation = 2.0f * M_PI;
	vec2 ballVelocity = pitchDirection * 250.0f;
	ball->pitch(position, ballVelocity);
}

//on ball entered
void Sumo::onBallEntered() {
	//check ball state
	if (ball->state != BALL_DEFAULT)
		return;

	if (state == SUMO_IDLE) {
		grab();
	}
	else if (state == SUMO_DASH) {
		ball->velocity.y *= -1.0f;
		camera->slowMotion(0.2f, 0.2f);
	}

}

void Sumo::onDraw(Graphics &graphics) {
	//draw sumo
	drawSumo(graphics, position, scale, rotation + grabRotation);
	//draw joystick
	drawJoystick(graphics);
}

void Sumo::drawSumo(Graphics& graphics, vec2 position, vec2 scale, float rotation) {
	//heat shake effect
	float heatScale = Interpolate::linear(0.0f, GRAB_HEAT_SCALE, 0.5f - grabTimer / GRAB_DURATION);
	vec2 heatDirection = vec2{1.0f, 0.0f}.rotate(2.0f * M_PI * time);
	vec2 heatOffset = heatDirection * heatScale * sin(10.0f * 2.0f * M_PI * time );
	//draw
	graphics.drawSprite(sumoSpriteId, frame, position + heatOffset + vec2{0.0f, 8.0f}, scale, rotation, Color::black);
	//draw dust
	walkDustEmitter.draw(graphics);
	//draw smoke
	smokeEmitter.draw(graphics);
	graphics.drawSprite(sumoSpriteId, frame, position + heatOffset, scale, rotation, modulate);
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
	Color joystickColor = Color{1.0f, 1.0f, 1.0f, 0.6f};
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
			if (state == SUMO_CATCH && buttonArea.pointInside(event.pointerPosition)) {
				pitch();
				break;
			}
			//dash
			if (pointerDown) {
				if ( event.pointerIndex != pointerIndex && buttonArea.pointInside(event.pointerPosition))
					dash();
				break;
			}
			//check joystick in arae
			if (!joystickArea.pointInside(event.pointerPosition))
				break;
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


