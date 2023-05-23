//
// Created by Haaxm on 5/22/2023.
//

#include "PauseMenu.h"
#include "../../../engine/GameObject/Instance.h"


void PauseMenu::onCreate() {
        //layer
        layer = 10000;
        visible = false;
        pausable = false;
        //mask size
        mask.size = vec2{124.0f, 124.0f};
        position = vec2{0,0};
        for (int i = 0; i < types.size(); i++) {
            //add button
            Button* button = (Button *) (Instance::create("Button"));
            button->type = types[i];
            button->visible = visible;
            button->pausable = pausable;
            button->active = false;
			button->layer = layer + 1;
            //push button to the buttons list
            buttons.push_back(button);
        }
    }

    void PauseMenu::onUpdate(float delta) {
        if (Instance::paused && !visible){
            visible = true;
			show();
            for (auto& button : buttons) {
                button->visible = true;
                button->active = true;
            }

        }else{
            if (!Instance::paused && visible){
                visible = false;
                for (auto& button : buttons) {
                    button->visible = false;
                    button->active = false;
                }
            }
        }

    }

    void PauseMenu::onDraw(Graphics &graphics) {
        if (Instance::paused) {
            graphics.drawRectangle(vec2::zero(), Screen::getSize(), Color{0.0f, 0.0f, 0.0f, 0.4f});
            graphics.drawSprite("spr_paused", 0, vec2{Screen::getCenter().x, 100.0f});
		}
    }

    void PauseMenu::onInputEvent(InputEvent event) {
        if (event.type == InputEventType::INPUT_EVENT_KEY_DOWN && event.key == AKEYCODE_BACK ){
            Instance::togglePause();
			Instance::timeScale = 1.0f;
            ALOG("clicked on return %i", event.key );
        }
    }

    void PauseMenu::show() {
        for (int i = 0; i < buttons.size(); i++) {
            Button* button = buttons[i];
            //start
            vec2 buttonStartPosition = vec2{
                    -Screen::getCenter().x,
                    44.0f * ((float) i) + 160.0f
            };
            //end
            vec2 buttonEndPosition = vec2{
                    Screen::getCenter().x,
                    44.0f * ((float) i) + 160.0f
            };
            //show up
            button->show(0.15f * float(i) + 0.3f, buttonStartPosition, buttonEndPosition);
        }
    }
