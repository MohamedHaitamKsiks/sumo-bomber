//
// Created by ksiks_wa3r on 4/24/23.
//

#include "TitleScreen.h"

void TitleScreen::onCreate() {
	//creating buttons
	for (int i = 0; i < types.size(); i++) {
		//add button
		Button* button = (Button *) (Instance::create("Button"));
		button->type = types[i];
		//start
		vec2 buttonStartPosition = vec2{
			-Screen::getCenter().x,
			44.0f * ((float) i) + 140.0f
		};
		//end
		vec2 buttonEndPosition = vec2{
				Screen::getCenter().x,
				44.0f * ((float) i) + 140.0f
		};
		//show up
		button->show(0.15f * float(i) + 0.3f, buttonStartPosition, buttonEndPosition);
		//push button to the buttons list
		buttons.push_back(button);
	}
}

void TitleScreen::onUpdate(float delta) {
	//background animation
	backgroundPosition = backgroundPosition + backgroundSpeed * delta;
	//overflow background position => loop
	if (backgroundPosition.x > 64.0f)
		backgroundPosition.x -= 64.0f;
	//same for y
	if (backgroundPosition.y > 64.0f)
		backgroundPosition.y -= 64.0f;

	//time
	time += delta;
}

void TitleScreen::onDraw(Graphics &graphics) {
	//draw background
	for (int j = 0; j < 32; j++) {
		for (int i = 0; i < 32; i++) {
			//tile params
			int tileIndex = (i + j) % 2;
			vec2 tilePosition = backgroundPosition + vec2{
				float(i - 2) * 32.0f - 10.0f,
				float(j - 2) * 32.0f - 12.0f
			};
			graphics.drawSprite("spr_wood_floor", (i + j) % 2, tilePosition	);
		}
	}

	//background dim
	Color dim = Color{0.0f, 0.0f, 0.0f, 0.34f};
	graphics.drawRectangle(vec2::zero(), Screen::getSize(), dim);

	//draw title
	//game title position
	vec2 gameTitlePosition = vec2{
		Screen::getCenter().x,
		110.0f
	};
	//game title animation
	gameTitlePosition = gameTitlePosition + vec2{1.0f, 0.0f}.rotate(time) * 4.0f * sin(0.5f * time);
	float gameTitleRotation = -sin(time) * M_PI / 80.0f;
	//draw
	graphics.drawSprite("spr_game_title", 0, gameTitlePosition, vec2::one(), gameTitleRotation);
}

void TitleScreen::onInputEvent(InputEvent event) {
	
}
