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

int BallVson::onConnect(){
    int enable = 1;
    setsockopt(socketDescriptor, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable));
    sockaddr_in localAddress{};
    localAddress.sin_family = AF_INET;
    localAddress.sin_port = htons(12345);  // Example port number
    localAddress.sin_addr.s_addr = INADDR_ANY;  // Bind to any available interface
    bind(socketDescriptor, reinterpret_cast<sockaddr*>(&localAddress), sizeof(localAddress));
    sockaddr_in remoteAddress{};
    remoteAddress.sin_family = AF_INET;
    remoteAddress.sin_port = htons(8976);  // Example remote port number

    inet_pton(AF_INET, "10.62.90.127", &remoteAddress.sin_addr);  // Use  IP address

    int t = connect(socketDescriptor, reinterpret_cast<sockaddr*>(&remoteAddress), sizeof(remoteAddress));
    char buffer[1024];

}
