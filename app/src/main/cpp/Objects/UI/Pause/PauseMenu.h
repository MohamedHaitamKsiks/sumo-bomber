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
                BUTTON_MAINSCR,
                BUTTON_RESUME,

        };
        //button active
        std::vector<Button*> buttons = {};
        bool active = true;
        //show
        void show(float delai, vec2 startPosition, vec2 endPosition);
    private:
        //scene's camera
        CameraController* camera;
        //scene's transition
        TransitionManager* transitionManager;




        void onCreate();

        void onUpdate(float delta);

        void onDraw(Graphics& graphics);

        void onInputEvent(InputEvent event);

        void onClick();


    };



#endif //SUMO_BOMBER_PAUSEMENU_H
