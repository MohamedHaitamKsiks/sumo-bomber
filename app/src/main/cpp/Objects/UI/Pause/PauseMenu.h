//
// Created by haaxm on 5/22/2023.
//

#ifndef SUMO_BOMBER_PAUSEMENU_H
#define SUMO_BOMBER_PAUSEMENU_H


#include "asengine.h"

using namespace ASEngine;



#include "../../../engine/GameObject/GameObject.h"
#include "../TransitionManager/TransitionManager.h"
#include "../../CameraController/CameraController.h"
#include "../Button/Button.h"

    class PauseMenu : public GameObject{

    public:
        //type
        std::vector<ButtonType> types = {
                BUTTON_RESUME,
                BUTTON_MAINSCR,
        };
        //button active
        std::vector<Button*> buttons = {};
        bool active = true;
        //show
        void show();
    private:
        //scene's camera
        CameraController* camera;
        //scene's transition
        TransitionManager* transitionManager;
        //time
        float time = 0.0f;

        void onCreate();

        void onUpdate(float delta);

        void onDraw(Graphics& graphics);

        void onInputEvent(InputEvent event);

        void onClick();


    };



#endif //SUMO_BOMBER_PAUSEMENU_H
