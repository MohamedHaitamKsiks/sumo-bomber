//
// Created by ksiks_wa3r on 4/18/23.
//

#include "Terrain.h"

void Terrain::onCreate() {

}

void Terrain::onUpdate(float delta) {

}

void Terrain::onDraw(Graphics &graphics) {
	//draw floor
	//red
	for (int j = 0; j < 7; j++) {
		for (int i = 0; i < 8; i++) {
			vec2 tilePosition = vec2{
				float(i) * 32,
				float(j) * 32 - 4.0f
			};
			graphics.drawSprite("spr_floor", (i + j) % 2 + 2, position + tilePosition, scale * 2.0f, rotation);
		}
	}
	//blue
	for (int j = 0; j < 7; j++) {
		for (int i = 0; i < 8; i++) {
			vec2 tilePosition = vec2{
					float(i) * 32,
					float(j + 7) * 32 + 4.0f
			};
			graphics.drawSprite("spr_floor", (i + j) % 2, position + tilePosition, scale * 2.0f, rotation);
		}
	}

	//draw separation line
	vec2 linePosition = vec2 {
		-32.0f,
		Screen::getCenter().y - 4.0f
	};
	//line scale
	vec2 lineScale = vec2{16.0f, 0.5f};
	graphics.drawSprite("spr_floor", 4, linePosition, lineScale, rotation);

	//draw shadow
	//vertical shadow
	vec2 shadowPosition = vec2 {
			Screen::getSize().x - 14.0f,
			-32.0f
	};
	//shadow scale
	vec2 shadowScale = vec2{4.0f, 28.0f};
	//shadow color
	Color shadowColor = {0.0f, 0.0f, 0.0f, 0.3f};
	graphics.drawSprite("spr_floor", 4, shadowPosition, shadowScale, rotation, shadowColor);

	//horisontal shadow
	//draw separation line
	shadowPosition = vec2 {
			-58.0f,
			-32.0f
	};
	//shadow scale
	shadowScale = vec2{14.0f, 3.0f};
	graphics.drawSprite("spr_floor", 4, shadowPosition, shadowScale, rotation, shadowColor);
}

void Terrain::onInputEvent(InputEvent event) {

}
