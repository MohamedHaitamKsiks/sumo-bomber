//
// Created by Homepunk on 16.01.2020.
//

#ifndef AUDIO_FREQUENCY_FILTER_AUDIOENGINE_H
#define AUDIO_FREQUENCY_FILTER_AUDIOENGINE_H


#include <oboe/AudioStreamCallback.h>
#include <oboe/AudioStreamBuilder.h>
#include <mutex>
#include <oboe/LatencyTuner.h>
#include <string>
#include "AudioFile.h"
#include "../decoder/WavDecoder.h"

constexpr int32_t kBufferSizeAutomatic = 0;

class AudioEngine : oboe::AudioStreamCallback {
public:
    AudioEngine();

    ~AudioEngine();

    void load(const char *filePath);

    void play();

    oboe::DataCallbackResult
    onAudioReady(oboe::AudioStream *audioStream, void *audioData, int32_t numFrames);

    void onErrorAfterClose(oboe::AudioStream *oboeStream, oboe::Result error);

private:
    oboe::AudioStream *mPlayStream;

    oboe::AudioApi mAudioApi = oboe::AudioApi::Unspecified;
    int32_t mPlaybackDeviceId = oboe::kUnspecified;
    int32_t mChannelCount = 2;

//    int32_t mFramesPerBurst;
//    int32_t mBufferSizeSelection = kBufferSizeAutomatic;
//
    std::unique_ptr<oboe::LatencyTuner> mLatencyTuner;
    std::mutex mRestartingLock;

    WavDecoder *wavDecoder;

    void setUpPlaybackStream();

    void restartStream();

    void closeOutputStream();
};


#endif //AUDIO_FREQUENCY_FILTER_AUDIOENGINE_H
