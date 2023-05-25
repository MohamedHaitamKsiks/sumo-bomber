//
// Created by Lenovo on 5/23/2023.
//


#include "BallVSon.h"

void BallVson::onDestroy() {
    transitionManager->changeSceneTo("sc_main");
}

void BallVson::onExplosion() {
    //calculate score
    if (position.y < Screen::getCenter().y)
        scoreManager->gameModeVs.blue++;
    else
        scoreManager->gameModeVs.red++;

    //show score
    hud->showScore();
}


void BallVson::onCreate() {
    //super call
    Ball::onCreate();
    //params
    EXPLOSION_DURATION = 15.0f;
    explosionTimer = EXPLOSION_DURATION;
    DESTROY_DURATION = 3.0f;
    BOUNCE_NUMBER = 3;
    //get hud
    hud = (HudVs*) Instance::find("HudVs");

}

void BallVson::onUpdate(float delta) {
    Ball::onUpdate(delta);
    hud->fuseValue = explosionTimer / EXPLOSION_DURATION;

}

//draw
void BallVson::onDraw(Graphics &graphics) {
    //draw ball
    Ball::onDraw(graphics);
}

