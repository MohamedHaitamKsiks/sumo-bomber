//
// Created by ksiks_wa3r on 4/11/23.
//

#include "ParticleEmitter.h"

namespace ASEngine {

	ParticleEmitter::ParticleEmitter() {

	}

	ParticleEmitter::~ParticleEmitter() {
		particles.clear();
	}

	//add particle
	void ParticleEmitter::addParticle() {
		//find first free index
		uint32_t freeIndex = 0;
		while (particles[freeIndex].life > 0.0f) {
			freeIndex++;
		}

		//if freeIndex is end
		if (freeIndex == EMITTER_MAX_PARTICLES)
			return;

		//set life
		particles[freeIndex].life = life;

		//set position
		float positionAngle = Random::rand_rangef(0.0f, 2.0f * M_PI);
		float positionRadius = Random::rand_rangef(0.0f, emitionRadius);
		particles[freeIndex].position = position + vec2::one().rotate(positionAngle) * positionRadius;

		//set velocity
		float velocity = Random::rand_rangef(particleDescriptor->velocity.min, particleDescriptor->velocity.max);
		float direction =  Random::rand_rangef(particleDescriptor->direction.min, particleDescriptor->direction.max) + rotation;
		particles[freeIndex].velocity = vec2::one().rotate(direction) * velocity;

		//set angle
		particles[freeIndex].angle = Random::rand_rangef(particleDescriptor->angle.min, particleDescriptor->angle.max) + rotation;

		//set scale
		particles[freeIndex].scale = Random::rand_rangef(particleDescriptor->scale.min, particleDescriptor->scale.max);

		//set scale speed
		particles[freeIndex].scaleSpeed = Random::rand_rangef(particleDescriptor->scaleSpeed.min, particleDescriptor->scaleSpeed.max);

		//set frame
		float frame = Random::rand_rangef(particleDescriptor->frame.min, particleDescriptor->frame.max);
		particles[freeIndex].frame = uint32_t (float(Sprite(spriteId).frames) * frame);

		//set frame rate
		float frameRate = Random::rand_rangef(particleDescriptor->frameRate.min, particleDescriptor->frameRate.max);
		particles[freeIndex].frameRate = frameRate;

		//current particle number
		if (freeIndex == currentParticlesNumber) {
			currentParticlesNumber++;
			currentActiveParticles++;
			if (currentParticlesNumber > EMITTER_MAX_PARTICLES)
				currentParticlesNumber = EMITTER_MAX_PARTICLES;
		}
	}

	//start emition
	void ParticleEmitter::emit() {
		if (emitted)
			return;
		emitted = true;
		time = 0.0f;
		addParticle();
	}

	//next step of particles
	void ParticleEmitter::update(float delta) {
		//update time
		time += delta;
		//add particle
		while (emitted && time > float(currentActiveParticles) * (life * ( explosiveness)) / float(particlesNumber)) {
			if (currentActiveParticles >= particlesNumber && !repeat) {
				emitted = false;
				break;
			}
			addParticle();
		}

		//update particles params
		for (int i = 0; i < currentParticlesNumber; i++)  {
			//check life
			if (particles[i].life < 0.0f)
				continue;

			//update life
			particles[i].life -= delta;
			//destroy particle
			if (particles[i].life < 0.0f && i == currentParticlesNumber - 1)
				currentParticlesNumber--;
			//remove 1 from current active particles
			if (particles[i].life < 0.0f)
				currentActiveParticles--;

			//update position
			particles[i].position = particles[i].position + particles[i].velocity * delta;
			//update scale
			particles[i].scale += particles[i].scaleSpeed * delta;
			if (particles[i].scale < 0.0f)
				particles[i].scale = 0.0f;
			//update frame rate
			particles[i].frame += particles[i].frameRate * delta;
			//check animation loop
			if (!isSpriteAnimationLoop)
				particles[i].frame = fmin(particles[i].frame, float(Sprite(spriteId).frames - 1) );

		}

	}

	//draw particles
	void ParticleEmitter::draw(Graphics &graphics) {
		//particles  draw
		for (int i = 0; i < currentParticlesNumber; i++) {
			//check life
			if (particles[i].life < 0.0f)
				continue;
			graphics.drawSprite(spriteId, uint32_t(particles[i].frame), particles[i].position, vec2::one() * particles[i].scale, particles[i].angle + M_PI  -particles[i].velocity.angle(), Color::white);
		}
	}


} // ASEngine