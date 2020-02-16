#include "SoundFX.h"

SoundFX::SoundFX(const char* filename) {

	loadAudio(filename);

}

SoundFX::~SoundFX() {
	
	Mix_FreeChunk(sfx);

}

void SoundFX::loadAudio(const char* filename) {

	sfx = Mix_LoadWAV(filename);
	Mix_VolumeChunk(sfx, MIX_MAX_VOLUME / 5);

}

void SoundFX::play() {

	Mix_PlayChannel(-1, sfx, 0);

}