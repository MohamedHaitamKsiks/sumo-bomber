//
// Created by ksiks_wa3r on 5/23/23.
//

#include "ScrollingBackground.h"

void ScrollingBackground::onCreate() {
	layer = 0;
}

void ScrollingBackground::onUpdate(float delta) {

	//background animation
	backgroundPosition = backgroundPosition + backgroundSpeed * delta;
	//overflow background position => loop
	if (backgroundPosition.x > 64.0f)
		backgroundPosition.x -= 64.0f;
	//same for y
	if (backgroundPosition.y > 64.0f)
		backgroundPosition.y -= 64.0f;
}

void ScrollingBackground::onDraw(Graphics &graphics) {

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

}

void ScrollingBackground::onInputEvent(InputEvent event) {

}
