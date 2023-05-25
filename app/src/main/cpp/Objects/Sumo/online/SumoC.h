//
// Created by Lenovo on 5/22/2023.
//

#ifndef SUMO_BOMBER_SUMOC_H
#define SUMO_BOMBER_SUMOC_H


#include "asengine.h"
#include <sys/socket.h>     // Socket functions and structures
#include <netinet/in.h>     // Internet address structures and functions
#include <arpa/inet.h>      // IP address manipulation functions
#include "../Sumo.h"
using namespace ASEngine;
class SumoC : public Sumo {
    int socketDescriptor = socket(AF_INET, SOCK_DGRAM, 0);

    //on create
    void onCreate() override ;
    void onInputEvent(InputEvent event) override;
    void onUpdate(float delta) override;
    int Connect();
};



#endif //SUMO_BOMBER_SUMOC_H
