//
// Created by ksiks_wa3r on 5/22/23.
//

#include "HudSolo.h"

void HudSolo::onCreate() {
	layer = 10000;
	scoreManager = (ScoreManager*) Instance::find("ScoreManager");
	scoreOffset = Screen::getSize().x * 1.5f;
}

void HudSolo::onUpdate(float delta) {
	scoreOffset = Interpolate::linear(scoreOffset, 0.0f, delta * 4.0f);
}

void HudSolo::onDraw(Graphics &graphics) {
	//blue
	std::stringstream score;
	score << scoreManager->gameModeSolo.score;

	//player red
	//score support
	vec2 supportPosition = vec2{
			scoreOffset - 8.0f,
			Screen::getSize().y * 0.12f - 6.0f
	};
	graphics.drawSprite("spr_score_support", 0, supportPosition, vec2::one() * 0.7f, 0.0f);
	//draw player red score
	vec2 textPosition = vec2{
			scoreOffset + 16.0f,
			Screen::getSize().y * 0.12f
	};
	graphics.drawText(score.str(), textPosition, "ft_pixel", 3);
}

void HudSolo::onInputEvent(InputEvent event) {

}

void HudSolo::addPoint() {
	scoreManager->gameModeSolo.score++;
}
