//
// Created by haaxm on 5/22/2023.
//

#include "netconfig.h"
#include <jni.h>


extern "C" JNIEXPORT void JNICALL
Java_com_example_myapp_SocketManager_startServer(JNIEnv *env, jobject /* this */) {
int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
if (serverSocket < 0) {
// Handle error
return;
}

struct sockaddr_in serverAddress{};
memset(&serverAddress, 0, sizeof(serverAddress));
serverAddress.sin_family = AF_INET;
serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
serverAddress.sin_port = htons(12345);

if (bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0) {
// Handle error
close(serverSocket);
return;
}

if (listen(serverSocket, 1) < 0) {
// Handle error
close(serverSocket);
return;
}

int clientSocket = accept(serverSocket, nullptr, nullptr);
if (clientSocket < 0) {
// Handle error
close(serverSocket);
return;
}

// Now you can send and receive data on the clientSocket

// Close the sockets when done
close(clientSocket);
close(serverSocket);
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_myapp_SocketManager_connectToServer(JNIEnv *env, jobject /* this */, jstring serverIP) {
const char *ipAddress = env->GetStringUTFChars(serverIP, nullptr);

int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
if (clientSocket < 0) {
// Handle error
return;
}

struct sockaddr_in serverAddress{};
memset(&serverAddress, 0, sizeof(serverAddress));
serverAddress.sin_family = AF_INET;
serverAddress.sin_addr.s_addr = inet_addr(ipAddress);
serverAddress.sin_port = htons(12345);

if (connect(clientSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0) {
// Handle error
close(clientSocket);
return;
}

// Now you can send and receive data on the clientSocket

// Close the socket when done
close(clientSocket);

// Release the allocated string
env->ReleaseStringUTFChars(serverIP, ipAddress);
}