//
// Created by haaxm on 5/23/2023.
//

#ifndef SUMO_BOMBER_BALLVSON_H
#define SUMO_BOMBER_BALLVSON_H

#include "asengine.h"
#include <sys/socket.h>     // Socket functions and structures
#include <netinet/in.h>     // Internet address structures and functions
#include <arpa/inet.h>      // IP address manipulation functions
#include <unistd.h>

#include "../../UI/HudVs/HudVs.h"
#include "BallVs.h"

using namespace ASEngine;

class BallVson: public  Ball{
    int socketDescriptor = Instance::socketDescriptor;
    HudVs* hud;
    //oncreate
    void onCreate();
    //on draw
    void onDraw(Graphics& graphics);
    //on explosion
    void onExplosion();
    //on destroy
    void onDestroy();
    //on update
    void onUpdate(float delta);

    int onConnect();
};


#endif //SUMO_BOMBER_BALLVS_H
