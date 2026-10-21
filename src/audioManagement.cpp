#include "SDL.h"
#include <iostream>

static constexpr int amplitude {28000};
static constexpr int frequency {440};
static constexpr int samplingRate {44100};
static bool audioPlaying {false};
static constexpr double phaseIncrement {
    2* M_PI * frequency / samplingRate
};

static SDL_AudioDeviceID audioDevice {};

static void audio_callback(void* userdata, Uint8* stream, int bytes) {
    auto* buffer = reinterpret_cast<int16_t *>(stream);
    const auto sampleCount = bytes / sizeof(*buffer);
    static double phase {0.0};

    for (int i {0}; i < sampleCount; ++i) {
        buffer[i] = static_cast<int16_t>(amplitude * std::sin(phase));

        phase += phaseIncrement;

        if (phase >= 2 * M_PI)
            phase -= (2 * M_PI);
        }

}

void initializeAudio() {
    SDL_AudioSpec desiredSpec {};
    SDL_AudioSpec obtainedSpec {};
    SDL_zero(desiredSpec);

    desiredSpec.freq = samplingRate;
    desiredSpec.format = AUDIO_S16SYS;
    desiredSpec.channels = 1;
    desiredSpec.samples = 2048;
    desiredSpec.callback = audio_callback;

    audioDevice = SDL_OpenAudioDevice(nullptr, 0,
                                        &desiredSpec, &obtainedSpec,0 );
    if (audioDevice <= 0)
        std::cerr << "Could not find audio device" << '\n';

}

void playAudio() {
    if (audioDevice != 0 && !audioPlaying) {
        SDL_PauseAudioDevice(audioDevice, 0);
        audioPlaying = true;
    }
}

void pauseAudio() {
    if (audioDevice != 0 && audioPlaying) {
        SDL_PauseAudioDevice(audioDevice, 1);
        audioPlaying = false;
    }
}