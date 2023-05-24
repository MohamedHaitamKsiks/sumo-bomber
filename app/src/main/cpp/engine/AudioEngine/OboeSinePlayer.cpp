//
// Created by anasm on 5/23/2023.
//
#include "OboeSinePlayer.h"

OboeSinePlayer::OboeSinePlayer() {
    startTime = std::chrono::steady_clock::now();
}

int32_t OboeSinePlayer::startAudio() {
    std::lock_guard<std::mutex> lock(mLock);
    oboe::AudioStreamBuilder builder;
    Result result = builder.setSharingMode(oboe::SharingMode::Exclusive)
            ->setPerformanceMode(oboe::PerformanceMode::LowLatency)
            ->setChannelCount(kChannelCount)
            ->setSampleRate(kSampleRate)
            ->setSampleRateConversionQuality(oboe::SampleRateConversionQuality::Medium)
            ->setFormat(oboe::AudioFormat::Float)
            ->setDataCallback(this)
            ->openStream(mStream);
    if (result != Result::OK) return (int32_t) result;

    result = mStream->requestStart();
    return (int32_t) result;
}

void OboeSinePlayer::stopAudio() {
    std::lock_guard<std::mutex> lock(mLock);
    if (mStream) {
        mStream->stop();
        mStream->close();
        mStream.reset();
    }
}

oboe::DataCallbackResult OboeSinePlayer::onAudioReady(oboe::AudioStream *oboeStream, void *audioData, int32_t numFrames) {
    std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed = now - startTime;
    double elapsedTime = elapsed.count();

    float *floatData = (float *) audioData;
    for (int i = 0; i < numFrames; ++i) {
        float sampleValue = kAmplitude * sinf(mPhase);
        for (int j = 0; j < kChannelCount; j++)
        {
            floatData[i * kChannelCount + j] = sampleValue;
        }
        mPhase += (static_cast<int>(elapsedTime)%5)*mPhaseIncrement;

        if (mPhase >= kTwoPi) mPhase -= kTwoPi;
    }

    return oboe::DataCallbackResult::Continue;
}