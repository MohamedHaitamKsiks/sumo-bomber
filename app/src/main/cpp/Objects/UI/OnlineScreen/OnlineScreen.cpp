//
// Created by ksiks_wa3r on 5/23/23.
//

#include "OnlineScreen.h"
#include "../Button/Button.h"
#include "../ButtonToggle/KeypadButton.h"

void OnlineScreen::onCreate() {
	layer = 1000;
    //play button
    Button* playbutton = (Button*) Instance::create("Button");
    playbutton->type = BUTTON_PLYONLINE;
    playbutton->layer = layer;

    //start
    vec2 pbuttonStartPosition = vec2{
            -Screen::getCenter().x,
            -44 + 240.0f
    };
    //end
    vec2 pbuttonEndPosition = vec2{
            Screen::getCenter().x,
            -44 + 240.0f
    };
    //show up
    playbutton->show(0.15f, pbuttonStartPosition, pbuttonEndPosition);
	//exit button
	Button* exitButton = (Button*) Instance::create("Button");
	exitButton->type = BUTTON_MAINSCR;
	exitButton->layer = layer;
	//start
	vec2 buttonStartPosition = vec2{
			-Screen::getCenter().x,
			240.0f
	};
	//end
	vec2 buttonEndPosition = vec2{
			Screen::getCenter().x,
			240.0f
	};
	//show up
	exitButton->show(0.15f, buttonStartPosition, buttonEndPosition);

    ;
    //keypad

    // Create the keypad buttons

    Button* keypad = (Button*) Instance::create("Button");
    keypad->type = Text_input;
    keypad->layer = layer;
    //start
    vec2 buttonkStartPosition = vec2{
            -Screen::getCenter().x,
            90.0f
    };
    //end
    vec2 buttonkEndPosition = vec2{
            Screen::getCenter().x,
            90.0f
    };
        Instance::server();

    keypad->show(0.15f, buttonkStartPosition, buttonkEndPosition);
}

void OnlineScreen::onUpdate(float delta) {

}

void OnlineScreen::onDraw(Graphics &graphics) {
	graphics.drawText(Instance::ipaddr, vec2{0,70.0f}, "ft_pixel", 2);
	graphics.drawText(Instance::text, vec2{0,90.0f}, "ft_pixel", 2);
}

void OnlineScreen::onInputEvent(InputEvent event) {

}
