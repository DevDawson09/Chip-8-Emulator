#ifndef CHIP_8_AUDIOMANAGEMENT_H
#define CHIP_8_AUDIOMANAGEMENT_H

static void audio_callback(void* userdata, Uint8* stream, int bytes);

void initializeAudio();

void playAudio();

void pauseAudio();


#endif //CHIP_8_AUDIOMANAGEMENT_H
