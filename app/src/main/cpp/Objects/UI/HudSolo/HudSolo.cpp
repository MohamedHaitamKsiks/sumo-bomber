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

	//gameover visible
	if (isGameOverVisible) {
		graphics.drawRectangle(vec2::zero(), Screen::getSize(), Color{0.0f, 0.0f, 0.0f, 0.4f});
		graphics.drawSprite("spr_game_over", 0, vec2{Screen::getCenter().x, 100.0f});
	}
}

void HudSolo::onInputEvent(InputEvent event) {

}

void HudSolo::addPoint() {
	scoreManager->gameModeSolo.score++;
}

void HudSolo::showGameOver() {
	isGameOverVisible = true;
	//creating buttons
	for (int i = 0; i < types.size(); i++) {
		//add button
		Button* button = (Button *) (Instance::create("Button"));
		button->type = types[i];
		button->layer = layer;
		//start
		vec2 buttonStartPosition = vec2{
				-Screen::getCenter().x,
				44.0f * ((float) i) + 180.0f
		};
		//end
		vec2 buttonEndPosition = vec2{
				Screen::getCenter().x,
				44.0f * ((float) i) + 180.0f
		};
		//show up
		button->show(0.15f * float(i) + 0.3f, buttonStartPosition, buttonEndPosition);
	}
}
