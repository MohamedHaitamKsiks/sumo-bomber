//
// Created by Lenovo on 5/22/2023.
//

#include "SumoR.h"


void SumoR::onCreate()  {

    Sumo::onCreate();
    int enable = 1;
    setsockopt(socketDescriptor, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable));
    sockaddr_in localAddress{};
    localAddress.sin_family = AF_INET;
    localAddress.sin_port = htons(12345);  // Example port number
    localAddress.sin_addr.s_addr = INADDR_ANY;  // Bind to any available interface
    bind(socketDescriptor, reinterpret_cast<sockaddr*>(&localAddress), sizeof(localAddress));
    Connect();

}

int SumoR::Connect(){
    sockaddr_in remoteAddress{};
    remoteAddress.sin_family = AF_INET;
    remoteAddress.sin_port = htons(8976);  // Example remote port number

    inet_pton(AF_INET, "10.62.90.127", &remoteAddress.sin_addr);  // Use  IP address

    int t = connect(socketDescriptor, reinterpret_cast<sockaddr*>(&remoteAddress), sizeof(remoteAddress));
    char buffer[1024];

// Process received data
// ...

    const char* message = "Hello, peer!";
    ALOG("sending message");
    send(socketDescriptor, message, strlen(message), 0);
    close(socketDescriptor);

    return t;
}