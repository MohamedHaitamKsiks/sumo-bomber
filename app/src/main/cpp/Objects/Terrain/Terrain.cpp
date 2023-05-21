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
	for (int j = 0; j < 16; j++) {
		for (int i = 0; i < 16; i++) {
			vec2 tilePosition = vec2{
				float(i - 2) * 32,
				float(j - 2) * 32
			};
			graphics.drawSprite("spr_wood_floor", (i + j) % 2, position + tilePosition, scale, rotation);
		}
	}

	//areas
	vec2 areaSize = vec2{
		Screen::getSize().x,
		Screen::getCenter().y
	};
	//red
	Color redAreaColor = Color{0.3f, 0.0f, 0.0f, 0.4f};
	Color redAreaColorFade = Color{0.3f, 0.0f, 0.0f, 0.0f};
	graphics.drawRectangle(vec2{0.0f, 0.0f}, areaSize, {redAreaColor, redAreaColor, redAreaColorFade, redAreaColorFade});

	//blue
	Color blueAreaColor = Color{0.1f, 0.0f, 0.3f, 0.4f};
	Color blueAreaColorFade = Color{0.1f, 0.0f, 0.3f, 0.0f};
	graphics.drawRectangle(vec2{0.0f, Screen::getCenter().y}, areaSize, {blueAreaColorFade, blueAreaColorFade, blueAreaColor, blueAreaColor});


	//draw separation line
	for (int i = 0; i < 10; i++) {
		vec2 linePosition = vec2 {
				float(i) * 32.0f - 8.0f,
				Screen::getCenter().y
		};
		graphics.drawSprite("spr_line_floor", 0, linePosition);
	}


	//draw shadow
	Color shadowColor = Color {0.0f, 0.0f, 0.0f, 0.5f};
	vec2 shadowSize = vec2{
		64.0f,
		Screen::getSize().y
	};
	//graphics.drawRectangle(vec2{0.0f, 0.0f}, shadowSize, {shadowColor, Color::transparent, Color::transparent, shadowColor});
	//graphics.drawRectangle(vec2{Screen::getSize().x - shadowSize.x, 0.0f}, shadowSize, {Color::transparent, shadowColor, shadowColor,Color::transparent});

	return;
	/*
	//draw shadow
	//vertical shadow
	vec2 shadowPosition = vec2 {
			Screen::getSize().x - 14.0f,
			-32.0f
	};
	//shadow scale
	vec2 shadowScale = vec2{4.0f, 28.0f};
	//shadow color
	Color shadowColor = Color{0.0f, 0.0f, 0.0f, 0.3f};
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
*/

}

void Terrain::onInputEvent(InputEvent event) {

}
