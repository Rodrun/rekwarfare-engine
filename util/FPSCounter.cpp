#include "FPSCounter.hpp"

#include "SDL2/SDL.h"

#include <vector>
#include <cmath>

namespace rekwarfare {

FPSCounter::FPSCounter(const unsigned int max) : m_maxsamples(max) {
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION,
        "Initialized FPS counter with %i max samples", m_maxsamples);
    m_lasttime = SDL_GetTicks();
    m_currenttime = SDL_GetTicks();
    m_samples.reserve(m_maxsamples);
}

void FPSCounter::precalculate() {
    m_lasttime = m_currenttime;
    m_currenttime = SDL_GetTicks();
    m_deltatime = (m_currenttime - m_lasttime) / 1000.0f;
}

float FPSCounter::getFPS(bool integer) const {
    return (integer) ? floor(m_dispfps) : m_dispfps;
}

void FPSCounter::collectSamples() {
    m_fps = 1.0f / m_deltatime;
    if (m_sample_counter < m_maxsamples) {
        m_samples.push_back(m_fps);
        m_sample_counter++;
    } else {
        m_dispfps = 0.0f;
        for (auto sample : m_samples) {
            m_dispfps += sample;
        }
        m_dispfps /= static_cast<float>(m_maxsamples);

        m_samples.clear();
        m_sample_counter = 0;
    }
}

}
