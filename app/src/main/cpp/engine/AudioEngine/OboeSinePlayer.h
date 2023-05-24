//
// Created by anasm on 5/23/2023.
//

#ifndef SUMO_BOMBER_OBOESINEPLAYER_H
#define SUMO_BOMBER_OBOESINEPLAYER_H

//
// Created by anasm on 5/23/2023.
//

#ifndef SUMO_BOMBER_PLAYSOUND_H
#define SUMO_BOMBER_PLAYSOUND_H
#include <oboe/Oboe.h>
#include <math.h>
#include <chrono>
#include <android/log.h>

using namespace oboe;

class OboeSinePlayer: public oboe::AudioStreamDataCallback {
public:
    OboeSinePlayer();
    virtual ~OboeSinePlayer() = default;
    int32_t startAudio();
    void stopAudio();
    oboe::DataCallbackResult onAudioReady(oboe::AudioStream *oboeStream, void *audioData, int32_t numFrames) override;

private:
    std::mutex mLock;
    std::shared_ptr<oboe::AudioStream> mStream;

    static int constexpr kChannelCount = 2;
    static int constexpr kSampleRate = 48000;
    static float constexpr kAmplitude = 0.5f;
    static float constexpr kFrequency = 440;
    static float constexpr kPI = M_PI;
    static float constexpr kTwoPi = kPI * 2;
    float reset=0;
    int sum_numFrames=0;
    std::chrono::steady_clock::time_point startTime;
    static double constexpr mPhaseIncrement = kFrequency * kTwoPi / (double) kSampleRate;
    float mPhase = 0.0;
};

#endif //SUMO_BOMBER_PLAYSOUND_H


#endif //SUMO_BOMBER_OBOESINEPLAYER_H
