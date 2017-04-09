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
    FPSCounter(unsigned int max_samples=DEFAULT_SAMPLE_SIZE);
    /*
    * Setup the counter, call right before the main loop.
    */
    void precalculate();
    /*
    * Collect FPS samples.
    */
    void collectSamples();
    /*
    * Obtain current FPS.
    * integer: Set to true if an integer is desired.
    * returns: Calculated frames per second.
    */
    float getFPS(bool integer=true) const;

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
