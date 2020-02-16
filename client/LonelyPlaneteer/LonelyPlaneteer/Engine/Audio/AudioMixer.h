#pragma once

#include "SDL_mixer.h"
#include "SoundFX.h"
#include <random>
#include <vector>

class AudioMixer
{
public:
	static Mix_Music* game_music;
	static Mix_Music* menu_music;

	static std::vector<SoundFX*> swordSounds;
	static std::vector<SoundFX*> swordPlayerImpactSounds;
	static std::vector<SoundFX*> whooshSounds;
	static std::vector<SoundFX*> fireballPlayerImpactSounds;
	static std::vector<SoundFX*> skeletonDeathSounds;
	static std::vector<SoundFX*> skeletonHitPlayerSounds;
	static std::vector<SoundFX*> impactBonesSounds;
	static std::vector<SoundFX*> playerDeathSounds;
	static std::vector<SoundFX*> mineSounds;

	static SoundFX* fireball;
	static SoundFX* fbWallImpact;
	static SoundFX* mineGems1;

	AudioMixer();
	~AudioMixer() {};

	static void init();

	static void playRandomSound(std::vector<SoundFX*> soundList);

	void stopMusic();
	void playMusic(Mix_Music* music);
	static Mix_Music* loadMusic(const char* assetFilePath);
	static SoundFX* loadSFX(const char* assetFilePath);

private:
	
	static int const FREQUENCY = 44100;
	static int const CHUNK_SIZE = 2048;

	static SoundFX* sword01;
	static SoundFX* sword02;
	static SoundFX* sword03;
	static SoundFX* sword04;

	static SoundFX* swordPlayerImpact01;
	static SoundFX* swordPlayerImpact02;
	static SoundFX* swordPlayerImpact03;
	static SoundFX* swordPlayerImpact04;

	static SoundFX* whoosh01;
	static SoundFX* whoosh02;

	static SoundFX* fbPlayerImpact01;
	static SoundFX* fbPlayerImpact02;
	static SoundFX* fbPlayerImpact03;
	static SoundFX* fbPlayerImpact04;

	static SoundFX* fallingBones01;
	static SoundFX* fallingBones02;

	static SoundFX* impactBones01;
	static SoundFX* impactBones02;

	static SoundFX* skeletonPlayerImpact01;
	static SoundFX* skeletonPlayerImpact02;
	static SoundFX* skeletonPlayerImpact03;
	static SoundFX* skeletonPlayerImpact04;

	static SoundFX* playerDeath01;
	static SoundFX* playerDeath02;

};
