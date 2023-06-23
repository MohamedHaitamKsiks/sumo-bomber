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
#include <vector>

using namespace oboe;

class OboeSinePlayer: public oboe::AudioStreamDataCallback {
public:
    OboeSinePlayer();
    virtual ~OboeSinePlayer() = default;
    int32_t startAudio();
    void stopAudio();
    void fillVector(std::vector <float>& vector);
    oboe::DataCallbackResult onAudioReady(oboe::AudioStream *oboeStream, void *audioData, int32_t numFrames) override;

private:
    std::mutex mLock;
    std::shared_ptr<oboe::AudioStream> mStream;

    static int constexpr kChannelCount = 2;
    static int constexpr kSampleRate = 44100;
    static float constexpr kAmplitude = 0.5f;
    static float constexpr kFrequency = 440;
    static float constexpr kPI = M_PI;
    static float constexpr kTwoPi = kPI * 2;
    float reset=0;
    int sum_numFrames=0;
    std::chrono::steady_clock::time_point startTime;
    static double constexpr mPhaseIncrement = kFrequency * kTwoPi / (double) kSampleRate;
    float mPhase = 0.0;
    public: std::vector <float> data;
    int count=0;
};
//extern OboeSinePlayer oboeSinePlayer;
#endif //SUMO_BOMBER_PLAYSOUND_H


#endif //SUMO_BOMBER_OBOESINEPLAYER_H
