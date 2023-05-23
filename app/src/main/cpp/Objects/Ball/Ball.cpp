//
// Created by ksiks_wa3r on 4/18/23.
//

#include "Ball.h"

ParticleDescriptor Ball::explosionDescriptor = {};

void Ball::onCreate() {
	collsionEnabled = false;
	mask.size = vec2{16.0f, 16.0f};
	//level area
	levelArea.position = vec2::zero();
	levelArea.size = Screen::getSize();
	//get camera
	camera = (CameraController*) Instance::find("CameraController");
	//get transition manager
	transitionManager = (TransitionManager*) Instance::find("TransitionManager");
	//get score manager
	scoreManager = (ScoreManager*) Instance::find("ScoreManager");
	//explosion particles
	//descriptor
	explosionDescriptor.velocity = 0.0f;
	explosionDescriptor.scale = {0.8f, 1.3f};
	explosionDescriptor.angle = {0.0f, 2.0f * M_PI};
	explosionDescriptor.frameRate = {10.0f, 16.0f};
	//emitter
	explosionEmitter.particleDescriptor = &explosionDescriptor;
	explosionEmitter.repeat = false;
	explosionEmitter.explosiveness = 0.8f;
	explosionEmitter.emitionRadius = 10.0f;
	explosionEmitter.particlesNumber = 5;
	explosionEmitter.explosiveness = 0.5f;
	explosionEmitter.spriteId = "spr_ball_explosion";
	//set object id
	objectId = "Ball";
	//layer
	layer = 1;
	//fall
	fall();

}

void Ball::onUpdate(float delta) {
	//set mask position to center
	mask.position = position - mask.size / 2.0f;

	//collision with wall
	collideWithLevelArea(delta);

	//rotation
	if (velocity.length() > 0.0f)
		rotation = -velocity.angle() - M_PI / 2.0f;

	//stretch the ball
	scale.x = 1.0f - velocity.length() * stretchRatio;
	scale.y = 1.0f + velocity.length() * stretchRatio;

	//decelate
	velocity = velocity - velocity.normalized() * DEC * delta;
	if (velocity.length() < DEC * delta)
		velocity = vec2::zero();

	//update position
	position = position + velocity * delta;

	//update frame
	frame += animationSpeed * velocity.length() * delta;

	//explosion timer
	explosionTimer -= delta;
	if (state == BALL_DEFAULT && explosionTimer < 0.0f) {
		state = BALL_PREPARE_EXPLOSION;
		//stop ball
		velocity = vec2::zero();
		//set to top
		layer = 1;
	}

	//prepare explosion
	if (state == BALL_PREPARE_EXPLOSION) {
		//scale down animation for explosion
		ballExplosionScale = Interpolate::linear(ballExplosionScale, EXPLOSION_SCALE, EXPLOSION_SCALE_SPEED * delta);
		if (abs(ballExplosionScale - EXPLOSION_SCALE) < 0.05f) {
			state = BALL_EXPLOSION;
			explosionEmitter.emit();
			camera->shake();
			//emit explosion signal
			onExplosion();
			destroyTimer = DESTROY_DURATION;
		}
	}

	//explosion
	if (state == BALL_EXPLOSION) {
		destroyTimer -= delta;
		if (destroyTimer < 0.0f) {
			onDestroy();
			Instance::destroy(this);
		}
	}

	explosionEmitter.position = position;
	explosionEmitter.update(delta);

	//bounce
	if (state == BALL_FALL) {
		//elevation gravity
		elevationSpeed -= GRAVITY * delta;
		//bounce
		if (elevation + elevationSpeed * delta < 0.0f) {
			bounce();
		}
		//elevation
		elevation += elevationSpeed * delta;
	}

	//update time
	time += delta;
}

void Ball::onDraw(Graphics &graphics) {
	if (state == BALL_DEFAULT || state == BALL_FALL) {
		//shadow scale
		vec2 shadowScale = scale * Interpolate::linear(vec2::one(), vec2::zero(), elevation / ELEVATION_START);
		Color shadowColor = Interpolate::linear(Color::black, Color::transparent, elevation / ELEVATION_START);
		//draw shadow
		graphics.drawSprite(spriteId, frame, position + vec2{0.0f, 8.0f}, shadowScale, rotation, shadowColor);
		//check if is flashed
		bool flash = (explosionTimer < FLASH_DURATION) && (sin(2.0f * M_PI * FLASH_FREQ * time) >= 0.0f);\
		//elevation
		vec2 elevationOffset = vec2 {
			0.0f,
			-elevation
		};
		//elevation scale
		vec2 elevationScale = vec2 {
			1.0f - 0.15f * abs(elevationSpeed) / GRAVITY,
			1.0f + 0.15f * abs(elevationSpeed) / GRAVITY
		};
		//draw ball
		if (!flash)
			graphics.drawSprite(spriteId, frame, position + elevationOffset, scale * elevationScale, rotation);
		else
			graphics.drawSprite("spr_ball_light", frame, position + elevationOffset, scale * elevationScale, rotation);
	}
	else if (state == BALL_PREPARE_EXPLOSION) {
		//draw shadow
		graphics.drawSprite("spr_ball_light", frame, position + vec2{0.0f, 8.0f}, scale * ballExplosionScale, rotation, Color::black);
		//draw ball
		graphics.drawSprite("spr_ball_light", frame, position, scale * ballExplosionScale, rotation);
	}
	//draw explosion
	explosionEmitter.draw(graphics);

}


void Ball::onInputEvent(InputEvent event) {
	return;
}


//bounce vall
void Ball::bounce() {
	if (bounceCounter > 0) {
		elevationSpeed *= -BOUNCE_SPEED_RATIO;
		bounceCounter--;
	}
	else {
		elevationSpeed = 0.0f;
		elevation = 0.0f;
		collsionEnabled = true;
		state = BALL_DEFAULT;
		layer = 1;
	}
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

//start fall (call function when creating the ball)
void Ball::fall() {
	//set state
	state = BALL_FALL;
	//set elevation
	elevation = ELEVATION_START;
	elevationSpeed = 0.0f;
	//set bounce counter
	bounceCounter = BOUNCE_NUMBER;
}

