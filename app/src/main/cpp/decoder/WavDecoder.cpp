//
// Created by Homepunk on 17.01.2020.
//

#include <cstdlib>
#include <cstring>
#include <string>
#include "WavDecoder.h"
//#include "../../lib-oboe/apps/OboeTester/app/src/main/cpp/android_debug.h"
#include "../engine/AudioEngine/android_debug.h"

static const long MAX_FILE_SIZE = 30000000;

static float shortToFloat(int16_t i) {
    float f;
    f = ((float) i) / (float) 32768;
    if (f > 1) f = 1;
    if (f < -1) f = -1;
    return f;
};

void WavDecoder::render(float *buffer, int channel, int32_t channelCount, int32_t numFrames) {
    /*  LOGW("render buffer = %f, channel = %1d, channelCount = %2d, numFrames = %3d", buffer, channel,
           channelCount, numFrames);*/

    if (!isLoaded || currentPositionL < 0|| currentPositionR < 0) {
        memset(buffer, 0, sizeof(float) * numFrames);
        return;
    }
//    LOGW("render channel = %1d, numFrames = %2d, currentPositionL = %3d, currentPositionR = %4d, size = %ld", channel, numFrames, currentPositionL, currentPositionR, size);

    if (channel == 0) {
        for (int i = 0, sampleIndex = 0; i < numFrames; i++) {
            buffer[sampleIndex] = shortToFloat(buffers[currentPositionL]);
            sampleIndex += channelCount;
            currentPositionL += channelCount;
        }
        if (currentPositionL >= size) {
            currentPositionL = -1;
        }
    } else {
        for (int i = 0, sampleIndex = 0; i < numFrames; i++) {
            buffer[sampleIndex] = shortToFloat(buffers[currentPositionR]);
            sampleIndex += channelCount;
            currentPositionR += channelCount;
        }
        if (currentPositionR >= size) {
            currentPositionR = -1;
        }
    }
}

void WavDecoder::play() {
    currentPositionL = 0;
    currentPositionR = 1;
}

long WavDecoder::extractWav(const char *filePath) {
    FILE *fp = fopen(filePath, "rb");
    if (fp == nullptr) {
        return -1;
    }
    fseek(fp, 44, 0);
    long size = fread(buffers, sizeof(short), MAX_FILE_SIZE, fp);
    fclose(fp);
    return size;
}

void WavDecoder::load(const char *filePath) {
    buffers = (int16_t *) calloc((size_t) MAX_FILE_SIZE, sizeof(int16_t));
    size = extractWav(filePath);
    currentPositionL = -1;
    currentPositionR = -1;

    isLoaded = true;
}

