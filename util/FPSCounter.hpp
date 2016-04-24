#pragma once

#include <vector>
#include <cstdint>

#define DEFAULT_SAMPLE_SIZE 10

namespace rekwarfare {

class FPSCounter {
public:
    /*
    * Initialize fps counter with optional maximum samples.
    * max_samples: Maximum amount of FPS samples to collect and average. It
    *  is better to use a smaller number rather than a larger one. Default
    *  is DEFAULT_SAMPLE_SIZE.
    */
    FPSCounter(const unsigned int max_samples=DEFAULT_SAMPLE_SIZE);
    /*
    * Call BEFORE anything else occurs.
    */
    void precalculate();
    /*
    * Collect FPS samples
    */
    void collectSamples();
    /*
    * Obtain current FPS.
    * integer: Set to true if a decimal number is not desired (e.g. 3.14)
    * returns: frames per second
    */
    float getFPS(bool integer) const;

private:
    mutable unsigned int m_maxsamples;
    float m_fps = 0.0f;
    /* The average FPS; The FPS to be returned at getFPS() */
    float m_dispfps = 0.0f;
    float m_deltatime = 0.0f;
    uint32_t m_lasttime;
    uint32_t m_currenttime;
    std::vector<float> m_samples;
    unsigned int m_sample_counter = 0;
};

}
