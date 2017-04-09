/*
* Handles audio-related functions.
*/
#pragma once

#include "SDL_mixer.h"

namespace rekwarfare {

enum ChannelType { STEREO=2, MONO=1 };

typedef struct {
    int frequency;
    Uint16 format;
    int channels;
} AudioFormat;

typedef Mix_Chunk Sound;

constexpr int ANY_FREE_CHANNEL = -1;
constexpr int INFINITE_TIMES = -1;
// So SDL_mixer doesn't have to be included explicitly
const auto MAX_VOLUME = MIX_MAX_VOLUME;
const auto DEFAULT_FREQUENCY = MIX_DEFAULT_FREQUENCY;
const auto DEFAULT_FORMAT = MIX_DEFAULT_FORMAT;
/*
* Use with initSDLMixer().
*/
const auto OGG_SUPPORT  = MIX_INIT_OGG;
const auto MOD_SUPPORT  = MIX_INIT_MOD;
const auto MP3_SUPPORT  = MIX_INIT_MP3;
const auto FLAC_SUPPORT = MIX_INIT_FLAC;

/*
* Load a sound from file. Equialent to Mix_LoadWAV(file)
* NOTE: According to mixer's docs: Mix_LoadWAV() can
*  load WAVE, AIFF, RIFF, OGG, and VOC files.
* If nullptr is returned, use Mix_GetError() to get the reason.
*/
Sound* loadSound(const char* file);
void closeSound(Sound*);
/*
* Play a sound for a given amount of time and loop for that
*  amount of time.
* channel: Use -1 or ANY_FREE_CHANNEL to use any open channel.
* loops: Number of times to loop, will play loop + 1 times,
*  use -1 or INFINITE_TIMES to loop infinite times until the
*  amount of ticks pass.
* ticks: Time in milliseconds to play, -1 or PLAY_COMPLETELY to
*  play for the length of the sound.
* returns: -1 on error.
*/
int playSound(int channel, Sound*, int loops, int ticks=-1);
/*
* Play a fading-in sound.
* See playSound()'s documentation for channel, loops, and ticks.
* ms: Milliseconds of time that the fade-in effect should
*  take to go from silence to full volume.
* returns: -1 on error.
*/
int playSoundFadeIn(int channel, Sound*, int loops, int ms, int ticks=-1);
/*
* Set the sound volume, maximum volume is MAX_VOLUME,
*  does nothing if volume is < 0.
* Equivalent of Mix_VolumeChunk(Sound, unsigned int);
*/
void setSoundVolume(Sound*, unsigned int);
/*
* Initialize SDL_Mixer API. Call endAudioFormat() when
*  no more loading/playing functions with the given
*  format are needed (i.e. before termination).
* chunksize: Bytes used per output sample. (recommended not too large or small)
* returns: true on success, false otherwise.
*/
bool beginAudioFormat(int frequency, Uint16 format, ChannelType, int chunksize);
/*
* No loading/playing functions should be played unless
*  beginAudioFormat() is called again.
*/
void endAudioFormat();
/*
* Get audio format of the opened audio device.
* returns: 0 on error.
*/
int getCurrentAudioFormat(AudioFormat&);

}
