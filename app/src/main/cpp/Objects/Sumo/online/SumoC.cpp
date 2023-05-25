//
// Created by Lenovo on 5/22/2023.
//

#include "SumoC.h"

void SumoC::onCreate() {
    Sumo::onCreate();
}


int SumoC::Connect(){
    return 0;
}

void SumoC::onInputEvent(InputEvent event) {

}

void SumoC::onUpdate(float delta){
    char buffer[1024];
    int bytesRead = recv(socketDescriptor, buffer, sizeof(buffer), 0);

    if (bytesRead == -1) {
        std::cerr << "Failed to receive data from the server." << std::endl;
    } else if (bytesRead == 0) {
        std::cout << "Connection closed by the server." << std::endl;
    } else {
        std::cout << "Received " << bytesRead << " bytes from the server: " << buffer << std::endl;
    }

    Sumo::onUpdate(delta);
}