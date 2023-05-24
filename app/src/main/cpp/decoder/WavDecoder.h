//
// Created by Homepunk on 17.01.2020.
//

#ifndef AUDIO_FREQUENCY_FILTER_WAVDECODER_H
#define AUDIO_FREQUENCY_FILTER_WAVDECODER_H

#include <cstdint>

class WavDecoder {
public:
    void render(float *buffer, int channel, int32_t channelStride, int32_t numFrames);

    void load(const char *filePath);

    void play();

private:
    int16_t *buffers;
    long size;
    int currentPositionL;
    int currentPositionR;

    bool isLoaded = false;

    long extractWav(const char *filePath);

};


#endif //AUDIO_FREQUENCY_FILTER_WAVDECODER_H
