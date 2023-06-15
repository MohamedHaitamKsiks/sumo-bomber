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

void SumoR::onInputEvent(InputEvent event) {
    //pointer diff is used to calculate stick position
    vec2 pointerDiff{};

    switch (event.type) {
        //init joystick by clicking on screen randomly (later It should be restricted to the player field)
        case ASEngine::INPUT_EVENT_POINTER_DOWN:
            //pitch
            if (state == SUMO_CATCH && buttonArea.pointInside(event.pointerPosition)) {
                pitch();
                break;
            }
            //dash
            if (pointerDown) {
                if (event.pointerIndex != pointerIndex &&
                    buttonArea.pointInside(event.pointerPosition))
                    dash();
                break;
            }
            //check joystick in arae
            if (!joystickArea.pointInside(event.pointerPosition))
                break;
            //joystick
            pointerDown = true;
            pointerDownPosition = event.pointerPosition;
            pointerIndex = event.pointerIndex;
            break;
            //joysick move
        case ASEngine::INPUT_EVENT_POINTER_MOVE:
            //check pointer index
            if (!pointerDown || event.pointerIndex != pointerIndex)
                break;
            //movement direction
            pointerDiff = event.pointerPosition - pointerDownPosition;
            if (pointerDiff.lengthSquared() < 32.0f * 32.0f)
                direction = pointerDiff / 32.0f;
            else
                direction = pointerDiff.normalized();
            //pointerDownPosition = event.pointerPosition;
            break;
            //release joystick
        case ASEngine::INPUT_EVENT_POINTER_UP:
            //only if pointer index == pointer index
            if (event.pointerIndex != pointerIndex)
                break;
            pointerDown = false;
            direction = vec2::zero();
            int bytesSent = send(Instance::socketDescriptor, direction.toString().c_str(),
                                 direction.toString().length(), 0);

            if (bytesSent == -1) {
                ALOG("Failed to send data to the server.");
            } else {
                ALOG("Sent  bytes to the server.");

                break;

            }
    }}