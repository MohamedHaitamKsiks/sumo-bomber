#include <oboe/Oboe.h>
#include <math.h>
#include <chrono>
#include <android/log.h>
using namespace oboe;

class OboeSinePlayer: public oboe::AudioStreamDataCallback {
public:
    OboeSinePlayer() {
        startTime = std::chrono::steady_clock::now();
    }
    virtual ~OboeSinePlayer() = default;

    // Call this from Activity onResume()
    int32_t startAudio() {
        std::lock_guard<std::mutex> lock(mLock);
        oboe::AudioStreamBuilder builder;
        // The builder set methods can be chained for convenience.
        Result result = builder.setSharingMode(oboe::SharingMode::Exclusive)
                ->setPerformanceMode(oboe::PerformanceMode::LowLatency)
                ->setChannelCount(kChannelCount)
                ->setSampleRate(kSampleRate)
                ->setSampleRateConversionQuality(oboe::SampleRateConversionQuality::Medium)
                ->setFormat(oboe::AudioFormat::Float)
                ->setDataCallback(this)
                ->openStream(mStream);
        if (result != Result::OK) return (int32_t) result;

        // Typically, start the stream after querying some stream information, as well as some input from the user
        result = mStream->requestStart();
        return (int32_t) result;
    }

    // Call this from Activity onPause()
    void stopAudio() {
        // Stop, close and delete in case not already closed.
        std::lock_guard<std::mutex> lock(mLock);
        if (mStream) {
            mStream->stop();
            mStream->close();
            mStream.reset();
        }
    }

    oboe::DataCallbackResult onAudioReady(oboe::AudioStream *oboeStream, void *audioData, int32_t numFrames) override
    {
        std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed = now - startTime;
        double elapsedTime = elapsed.count();


        // Print elapsed time for debugging
        /*
        __android_log_print(ANDROID_LOG_DEBUG, "MyApp", "Elapsed Time: %f", elapsedTime);
        __android_log_print(ANDROID_LOG_DEBUG, "MyApp", "numFrames: %d", numFrames);
        __android_log_print(ANDROID_LOG_DEBUG, "MyApp", "reset: %f", reset);
        __android_log_print(ANDROID_LOG_DEBUG, "MyApp", "Somme Frames: %d", sum_numFrames);
        */
        sum_numFrames+=numFrames;
        reset+=static_cast<float>(numFrames)/(kSampleRate);

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

private:
    std::mutex         mLock;
    std::shared_ptr<oboe::AudioStream> mStream;

    // Stream params
    static int constexpr kChannelCount = 2;
    static int constexpr kSampleRate = 48000;
    // Wave params, these could be instance variables in order to modify at runtime
    static float constexpr kAmplitude = 0.5f;
    static float constexpr kFrequency = 440;
    static float constexpr kPI = M_PI;
    static float constexpr kTwoPi = kPI * 2;
    float reset=0;
    int sum_numFrames=0;
    std::chrono::steady_clock::time_point startTime;
    static double constexpr mPhaseIncrement = kFrequency * kTwoPi / (double) kSampleRate;
    // Keeps track of where the wave is
    float mPhase = 0.0;


};