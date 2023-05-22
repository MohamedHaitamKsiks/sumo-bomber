//
// Created by Haaxm on 5/22/2023.
//

#include "PauseMenu.h"
#include "../../../engine/GameObject/Instance.h"


void PauseMenu::onCreate() {
        //mask size
        mask.size = vec2{124.0f, 40.0f};
        //camera
    }

    void PauseMenu::onUpdate(float delta) {


    }

    void PauseMenu::onDraw(Graphics &graphics) {
        if (active) {
            graphics.drawRectangle(mask.position, mask.size, Color{1.0f, 0.0f, 0.0f, 0.4f});
        }
    }

    void PauseMenu::onInputEvent(InputEvent event) {

    }



    void PauseMenu::show(float delai, vec2 startPosition, vec2 endPosition) {

    }
