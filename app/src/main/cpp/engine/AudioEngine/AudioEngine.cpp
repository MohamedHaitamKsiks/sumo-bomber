//
// Created by Homepunk on 16.01.2020.
//

#include <string>
#include <oboe/Oboe.h>
#include "AudioEngine.h"
//#include "../../lib-oboe/apps/OboeTester/app/src/main/cpp/android_debug.h"
#include "android_debug.h"


AudioEngine::AudioEngine() {
    wavDecoder = new WavDecoder();
    setUpPlaybackStream();
}

AudioEngine::~AudioEngine() {
    delete wavDecoder;
    closeOutputStream();
}

oboe::DataCallbackResult
AudioEngine::onAudioReady(oboe::AudioStream *audioStream, void *audioData, int32_t numFrames) {
    int32_t channelCount = audioStream->getChannelCount();
    if (audioStream->getFormat() == oboe::AudioFormat::Float) {
        for (int i = 0; i < channelCount; ++i) {
            wavDecoder->render(static_cast<float *>(audioData) + i, i, channelCount, numFrames);
        }
    } else {
/*
        for (int i = 0; i < channelCount; ++i) {
            wavDecoder->render(static_cast<int16_t *>(audioData) + i, i, channelCount, numFrames);
        }
*/
    }
    return oboe::DataCallbackResult::Continue;
}

void AudioEngine::onErrorAfterClose(oboe::AudioStream *oboeStream, oboe::Result error) {
    if (error == oboe::Result::ErrorDisconnected) restartStream();
}

void AudioEngine::restartStream() {
    if (mRestartingLock.try_lock()) {
        closeOutputStream();
        setUpPlaybackStream();
        mRestartingLock.unlock();
    } else {
        LOGW("Restart stream operation already in progress - ignoring this request");
    }
}

void AudioEngine::play() {
    LOGW("play");
    wavDecoder->play();
    oboe::Result result = mPlayStream->requestStart();
    if (result != oboe::Result::OK) {
        LOGE("Error starting stream. %s", oboe::convertToText(result));
    }

    int32_t i = mPlayStream->getSampleRate();
    LOGW("getSampleRate %d", i);
}


void AudioEngine::load(const char *filePath) {
    LOGW("filePath = %s", filePath);
    wavDecoder->load(filePath);
}

void AudioEngine::setUpPlaybackStream() {
    oboe::AudioStreamBuilder builder;
    builder.setAudioApi(mAudioApi);
    builder.setDeviceId(mPlaybackDeviceId);
    //builder.setSharingMode(oboe::SharingMode::Exclusive);
    builder.setSharingMode(oboe::SharingMode::Shared);
    builder.setPerformanceMode(oboe::PerformanceMode::LowLatency);
//  This should match the sample rate of our source files.
    builder.setSampleRate(44100);
//  This should match the channel count of our source files.
    builder.setChannelCount(mChannelCount);
//  If the underlying audio device does not natively support a sample rate of 48000
//  then resample our source audio data using a medium quality resampling algorithm.
    builder.setSampleRateConversionQuality(oboe::SampleRateConversionQuality::Medium);

    builder.setCallback(this);

    oboe::Result result = builder.openStream(&mPlayStream);

    /*
     int32_t bufferSize = mPlayStream->getBufferSizeInFrames();
     if (mBufferSizeSelection == kBufferSizeAutomatic) {
        mLatencyTuner->tune();
    } else {
        int32_t bfr = mBufferSizeSelection * mFramesPerBurst;
        if (bufferSize != bfr) {
            mPlayStream->setBufferSizeInFrames(bfr);
        }
        LOGW("setBufferSizeInFrames %d", mPlayStream->getBufferSizeInFrames());
    }*/

//    mPlayStream->getBuf
    if (result == oboe::Result::OK && mPlayStream != nullptr) {
//        mFramesPerBurst = mPlayStream->getFramesPerBurst();
        LOGW("getFramesPerBurst %d, getBufferSizeInFrames = %2d, getBufferCapacityInFrames = %3d",
             mPlayStream->getBufferSizeInFrames(),
             mPlayStream->getBufferSizeInFrames(),
             mPlayStream->getBufferCapacityInFrames());
        int channelCount = mPlayStream->getChannelCount();

        if (channelCount != mChannelCount) {
            LOGW("Requested %d channels but received %d", mChannelCount, channelCount);
        }
//        mPlayStream->setBufferSizeInFrames(mPlayStream->getBufferSizeInFrames());
//        mLatencyTuner = std::unique_ptr<oboe::LatencyTuner>(new oboe::LatencyTuner(*mPlayStream));
//        mLatencyTuner->tune();
        LOGW("getBufferSizeInFrames after tune %d", mPlayStream->getBufferSizeInFrames());

        //mLatencyTuner->tune()
    } else {
        LOGE("Failed to create stream. Error: %s", oboe::convertToText(result));
    }
}

void AudioEngine::closeOutputStream() {
    if (mPlayStream != nullptr) {
        oboe::Result result = mPlayStream->requestStop();
        if (result != oboe::Result::OK) {
            LOGE("Error stopping output stream. %s", oboe::convertToText(result));
        }

        result = mPlayStream->close();
        if (result != oboe::Result::OK) {
            LOGE("Error closing output stream. %s", oboe::convertToText(result));
        }
    }
}

