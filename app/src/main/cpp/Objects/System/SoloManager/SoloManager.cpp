//
// Created by ksiks_wa3r on 5/22/23.
//

#include "SoloManager.h"
#include "../../Ball/BallSolo/BallSolo.h"
#include "../SettingManager/SettingManager.h"

void SoloManager::onCreate() {
	//score
	scoreManager = (ScoreManager*) Instance::find("ScoreManager");
	scoreManager->gameModeSolo.score = 0;
	//areas
	//red
	redArea.position = vec2::zero();
	redArea.size = vec2{Screen::getSize().x, Screen::getSize().y * 0.3f};
	//player
	playerArea.position = vec2{0.0f, Screen::getSize().y * 0.3f};
	playerArea.size = vec2{Screen::getSize().x, Screen::getSize().y * 0.4f};
	//blue
	blueArea.position = vec2{0.0f, Screen::getSize().y * 0.7f};
	blueArea.size = vec2{Screen::getSize().x, Screen::getSize().y * 0.3f};
	//color blind
	SettingManager* settingManager = (SettingManager*) Instance::find("SettingManager");
	hasAccessibility = settingManager->colorBlindAccessibility;
}

void SoloManager::onUpdate(float delta) {
	time += delta;
	//timer to spawn balls
	spawnTimer -= delta;
	if (spawnTimer < 0.0f && state == SOLO_GAME_PLAYING) {
		spawnBall();
		spawnTimer = SPAWN_DURATION * Interpolate::linear(1.0f, 0.4f, time / 30.0f);
	}
}

void SoloManager::onDraw(Graphics &graphics) {
	//draw player area
	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 6; i++) {
			vec2 tilePosition = vec2{
					float(i) * 32.0f - 8.0f,
					float(j) * 32.0f + playerArea.position.y
			};
			graphics.drawSprite("spr_wood_floor", (i + j) % 2, position + tilePosition, scale, rotation);
		}
	}

	//draw red area
	for (int j = 0; j < 3; j++) {
		for (int i = 0; i < 6; i++) {
			vec2 tilePosition = vec2{
					float(i) * 32.0f - 8.0f,
					float(j) * 32.0f
			};
			graphics.drawSprite("spr_floor", (i + j) % 2 + 2, position + tilePosition, scale, rotation);
		}
	}

	//draw blue area
	for (int j = 0; j < 3; j++) {
		for (int i = 0; i < 6; i++) {
			vec2 tilePosition = vec2{
					float(i) * 32.0f - 8.0f,
					float(j) * 32.0f + blueArea.position.y
			};
			graphics.drawSprite("spr_floor", (i + j) % 2, position + tilePosition, scale, rotation);
		}
	}

	//red
	Color redAreaColor = Color{0.2f, 0.0f, 0.0f, 0.3f};
	Color redAreaColorFade = Color{0.3f, 0.0f, 0.0f, 0.0f};
	graphics.drawRectangle(vec2{0.0f, 0.0f}, vec2{0.0f, 0.0f}, {redAreaColor, redAreaColor, redAreaColorFade, redAreaColorFade});

	//blue
	Color blueAreaColor = Color{0.1f, 0.0f, 0.2f, 0.3f};
	Color blueAreaColorFade = Color{0.1f, 0.0f, 0.3f, 0.0f};
	graphics.drawRectangle(vec2{0.0f, Screen::getCenter().y}, Screen::getSize(), {blueAreaColorFade, blueAreaColorFade, blueAreaColor, blueAreaColor});

	//draw separation lines
	//red
	for (int i = 0; i < 10; i++) {
		vec2 linePosition = vec2 {
				float(i) * 32.0f - 8.0f,
				playerArea.position.y
		};
		graphics.drawSprite("spr_line_floor", 0, linePosition);
	}
	//blue
	for (int i = 0; i < 10; i++) {
		vec2 linePosition = vec2 {
				float(i) * 32.0f - 8.0f,
				blueArea.position.y
		};
		graphics.drawSprite("spr_line_floor", 0, linePosition);
	}

	//draw signs for accessibility
	if (hasAccessibility) {
		//draw + area
		for (int j = 0; j < 3; j++) {
			for (int i = 0; i < 6; i++) {
				vec2 tilePosition = vec2{
						float(i) * 32.0f - 8.0f + 16.0f,
						float(j) * 32.0f + 16.0f
				};
				Color modulate = Color{1.0f, 1.0f, 1.0f, 0.3f -  0.3f * float(j) / 3.0f};
				graphics.drawSprite("spr_sign", 1, position + tilePosition, scale, rotation, modulate);
			}
		}

		//draw - area
		for (int j = 0; j < 3; j++) {
			for (int i = 0; i < 6; i++) {
				vec2 tilePosition = vec2{
						float(i) * 32.0f - 8.0f + 16.0f,
						float(j) * 32.0f + 16.0f + blueArea.position.y
				};
				Color modulate = Color{1.0f, 1.0f, 1.0f, 0.3f * float(j + 1) / 3.0f};
				graphics.drawSprite("spr_sign", 0, position + tilePosition, scale, rotation, modulate);
			}
		}
	}

}

void SoloManager::onInputEvent(InputEvent event) {

}

void SoloManager::spawnBall() {
	//create ball
	vec2 ballPosition = vec2{
		playerArea.position.x + Random::rand_rangef(32.0f, playerArea.size.x - 32.0f),
		playerArea.position.y + Random::rand_rangef(32.0f, playerArea.size.y - 32.0f)
	};
	BallSolo* ball = (BallSolo*) Instance::create("BallSolo");
	ball->position = ballPosition;
	ball->soloManager = this;

}

void SoloManager::lose() {
	if (state != SOLO_GAME_PLAYING)
		return;
	state = SOLO_GAME_OVER;
	//show game over
	HudSolo* hudSolo = (HudSolo*) Instance::find("HudSolo");
	hudSolo->showGameOver();
	/*TransitionManager* transitionManager = (TransitionManager*) Instance::find("TransitionManager");
	transitionManager->changeSceneTo("TransitionManager");*/
}
