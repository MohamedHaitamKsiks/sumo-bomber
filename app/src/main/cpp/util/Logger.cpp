//
// Created by Homepunk on 15.01.2020.
//

#include <android/log.h>
#include "Logger.h"

Logger::Logger() {
    TAG = "JNI_LOGGER";
}

void Logger::v_log(string message) {
    __android_log_write(ANDROID_LOG_DEFAULT, TAG, reinterpret_cast<const char *>(&message));
}

void Logger::d_log(string message) {
    __android_log_write(ANDROID_LOG_DEBUG, TAG, reinterpret_cast<const char *>(&message));
}

void Logger::w_log(string message) {
    __android_log_write(ANDROID_LOG_WARN, TAG, reinterpret_cast<const char *>(&message));
}

void Logger::e_log(string message) {
    __android_log_write(ANDROID_LOG_ERROR, TAG, reinterpret_cast<const char *>(&message));
}

