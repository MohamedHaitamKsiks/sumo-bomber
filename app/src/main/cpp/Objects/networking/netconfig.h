//
// Created by haaxm on 5/22/2023.
//

#ifndef SUMO_BOMBER_NETCONFIG_H
#define SUMO_BOMBER_NETCONFIG_H

#include "asengine.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <cstring>

#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void JNICALL
Java_com_example_myapp_SocketManager_startServer(JNIEnv *env, jobject /* this */);

JNIEXPORT void JNICALL
Java_com_example_myapp_SocketManager_connectToServer(JNIEnv *env, jobject /* this */, jstring serverIP);

#ifdef __cplusplus
}
#endif


#endif //SUMO_BOMBER_NETCONFIG_H
