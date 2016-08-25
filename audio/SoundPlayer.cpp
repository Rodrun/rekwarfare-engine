#include "SoundPlayer.hpp"

#include "SDL_mixer.h"

namespace rekwarfare {

Sound* loadSound(const char* file) {
    Sound* loaded = nullptr;
    loaded = Mix_LoadWAV(file);
    if (!loaded) {
        return nullptr;
    }
    return loaded;
}

void closeSound(Sound* s) {
    Mix_FreeChunk(s);
}

int playSound(int channel, Sound* s, int loops) {
    return Mix_PlayChannel(channel, s, loops);
}

int playSound(int channel, Sound* s, int loops, int ticks) {
    return Mix_PlayChannelTimed(channel, s, loops, ticks);
}

int playSoundFadeIn(int channel, Sound* s, int loops, int ms, int ticks) {
    return Mix_FadeInChannelTimed(channel, s, loops, ms, ticks);
}

void setSoundVolume(Sound* s, unsigned int vol) {
    Mix_VolumeChunk(s, (int) vol);
}

bool beginAudioFormat(int frequency, Uint16 format, ChannelType t,
    int chunksize) {
    return Mix_OpenAudio(frequency, format, t, chunksize) == 0 ? true : false;
}

void endAudioFormat() {
    Mix_CloseAudio();
}

int getCurrentAudioFormat(AudioFormat& af) {
    return Mix_QuerySpec(&af.frequency, &af.format, &af.channels);
}

}
