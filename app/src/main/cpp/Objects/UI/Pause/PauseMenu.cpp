//
// Created by Haaxm on 5/22/2023.
//

#include "PauseMenu.h"
#include "../../../engine/GameObject/Instance.h"


void PauseMenu::onCreate() {
        visible = false;
        pausable = false;
        //mask size
        mask.size = vec2{124.0f, 124.0f};
        position = vec2{0,0
        };
        for (int i = 0; i < types.size(); i++) {
            //add button
            Button* button = (Button *) (Instance::create("Button"));
            button->type = types[i];
            button->visible = visible;
            button->pausable = pausable;
            button->active = false;
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

    void PauseMenu::onUpdate(float delta) {
        if (Instance::paused && !visible){
            visible = true;
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
            graphics.drawRectangle(vec2{Screen::getCenter().x,
                                        44.0f*2  + 140.0f}, mask.size, Color{1.0f, 0.0f, 0.0f, 0.4f});
        }
    }

    void PauseMenu::onInputEvent(InputEvent event) {

    }



    void PauseMenu::show(float delai, vec2 startPosition, vec2 endPosition) {

    }
