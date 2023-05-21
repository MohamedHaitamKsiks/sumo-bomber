//
// Created by ksiks_wa3r on 5/14/23.
//

#include "HudVs.h"

//descirptor
ParticleDescriptor HudVs::fuseDescriptor = {};

void HudVs::onCreate() {
	//get score manager
	scoreManager = (ScoreManager *) Instance::find("ScoreManager");
	//set layer
	layer = 1;
	//create paricles
	//descriptor
	rotation = 0.0f;
	fuseDescriptor.angle = 0.0f;
	fuseDescriptor.direction = {0.0f, 2.0f * M_PI};
	fuseDescriptor.scale = {0.3f, 0.6f};
	fuseDescriptor.velocity = {30.0f, 40.0f};
	fuseDescriptor.frameRate = 6.0f;
	//emitter
	fuseEmitter.life = 1.0f;
	fuseEmitter.explosiveness = 0.0f;
	fuseEmitter.emitionRadius = 0.0f;
	fuseEmitter.particleDescriptor = &fuseDescriptor;
	fuseEmitter.spriteId = "spr_fuse_particles";
	fuseEmitter.particlesNumber = 10;
	//smoke emitter
	smokeEmitter.life = 1.0f;
	smokeEmitter.explosiveness = 0.0f;
	smokeEmitter.emitionRadius = 0.0f;
	smokeEmitter.particleDescriptor = &Sumo::smokeDescriptor;
	smokeEmitter.spriteId = "spr_sumo_smoke_particle";
	smokeEmitter.particlesNumber = 10;
}

void HudVs::onUpdate(float delta) {
	//update smoke particle
	smokeEmitter.position = vec2{
			Screen::getSize().x * fuseValue,
			Screen::getCenter().y - 12.0f
	};
	smokeEmitter.emit();
	smokeEmitter.update(delta);
	//update fuse particle
	fuseEmitter.position = vec2{
		Screen::getSize().x * fuseValue,
		Screen::getCenter().y - 12.0f
	};
	fuseEmitter.emit();
	fuseEmitter.update(delta);
	//animate score
	if (isScoreVisible) {
		delaiTimer -= delta;
		if (delaiTimer > 0.0f) {
			return;
		}
		backgroundDim = Interpolate::linear(backgroundDim, 0.5f, SHOW_SCORE_SPEED * delta);
		scoreOffset = Interpolate::linear(scoreOffset, - 24.0f, SHOW_SCORE_SPEED * delta);
	}
}

void HudVs::onDraw(Graphics &graphics) {
	//draw fuse
	Texture fuseTexture = Sprite("spr_bomb_fuse").texture;
	Rectangle fusePart = {};
	fusePart.size = vec2{
		(float) (fuseTexture.width()) * fuseValue,
		(float) fuseTexture.height()
	};
	fusePart.position = vec2::zero();
	graphics.drawTexturePart(fuseTexture, fusePart, vec2{-4.0f, Screen::getCenter().y - 16.0f}, vec2::one(), 0.0f, Color::black);
	graphics.drawTexturePart(fuseTexture, fusePart, vec2{0.0f, Screen::getCenter().y - 24.0f}, vec2::one(), 0.0f);

	//draw fuse emitter
	smokeEmitter.draw(graphics);
	//fuseEmitter.draw(graphics);

	//draw score
	if(!isScoreVisible) {
		return;
	}
	//draw background dim
	graphics.drawRectangle(vec2::zero(), Screen::getSize(), Color{0.0, 0.0, 0.0, backgroundDim});

	//get score strings
	//red
	std::stringstream scoreRed;
	scoreRed << scoreManager->gameModeVs.red;
	//blue
	std::stringstream scoreBlue;
	scoreBlue << scoreManager->gameModeVs.blue;

	//player red
	//score support
	vec2 supportPosition = vec2{
			scoreOffset,
			Screen::getSize().y * 0.25f - 10.0f
	};
	graphics.drawSprite("spr_score_support", 0, supportPosition);
	//draw player red score
	vec2 textPosition = vec2{
		scoreOffset + 42.0f,
		Screen::getSize().y * 0.25f
	};
	graphics.drawText(scoreRed.str(), textPosition, "ft_pixel_large", 3);

	//player blue
	//score support
	supportPosition = vec2{
			-scoreOffset + Screen::getSize().x,
			Screen::getSize().y * 0.75f - 10.0f
	};
	graphics.drawSprite("spr_score_support", 0, supportPosition, vec2{-1.0f, 1.0f}, 0.0f);
	//draw player blue score
	textPosition = vec2{
		Screen::getSize().x -64.0f - scoreOffset,
		Screen::getSize().y * 0.75f
	};
	graphics.drawText(scoreBlue.str(), textPosition, "ft_pixel_large", 3);
}

void HudVs::onInputEvent(InputEvent event) {

}

void HudVs::showScore() {
	layer = 10;
	isScoreVisible = true;
	delaiTimer = DELAI_DURATION;
	scoreOffset = Screen::getSize().x + 32.0f;
	backgroundDim = 0.0f;
}
