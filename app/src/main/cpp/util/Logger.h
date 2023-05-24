//
// Created by Homepunk on 15.01.2020.
//
/*
#ifndef AUDIO_FREQUENCY_FILTER_TEMP_H
#define AUDIO_FREQUENCY_FILTER_TEMP_H*/

#include <string>
#include <iostream>
#include <sstream>
#include <android/log.h>

using namespace std;

class Logger {
public:
    Logger();

    void v_log(string message);

    void d_log(string message);

    void w_log(string message);

    void e_log(string message);


private:
    const char *TAG;
};
