
#include "AudioMixer.h"
#include <iostream>

Mix_Music* AudioMixer::menu_music;
Mix_Music* AudioMixer::game_music;

std::vector<SoundFX*> AudioMixer::swordSounds;
SoundFX* AudioMixer::sword01;
SoundFX* AudioMixer::sword02;
SoundFX* AudioMixer::sword03;
SoundFX* AudioMixer::sword04;

std::vector<SoundFX*> AudioMixer::whooshSounds;
SoundFX* AudioMixer::whoosh01;
SoundFX* AudioMixer::whoosh02;

std::vector<SoundFX*> AudioMixer::swordPlayerImpactSounds;
SoundFX* AudioMixer::swordPlayerImpact01;
SoundFX* AudioMixer::swordPlayerImpact02;
SoundFX* AudioMixer::swordPlayerImpact03;
SoundFX* AudioMixer::swordPlayerImpact04;

std::vector<SoundFX*> AudioMixer::fireballPlayerImpactSounds;
SoundFX* AudioMixer::fbPlayerImpact01;
SoundFX* AudioMixer::fbPlayerImpact02;
SoundFX* AudioMixer::fbPlayerImpact03;
SoundFX* AudioMixer::fbPlayerImpact04;

std::vector<SoundFX*> AudioMixer::skeletonHitPlayerSounds;
SoundFX* AudioMixer::skeletonPlayerImpact01;
SoundFX* AudioMixer::skeletonPlayerImpact02;
SoundFX* AudioMixer::skeletonPlayerImpact03;
SoundFX* AudioMixer::skeletonPlayerImpact04;

std::vector<SoundFX*> AudioMixer::skeletonDeathSounds;
SoundFX* AudioMixer::fallingBones01;
SoundFX* AudioMixer::fallingBones02;

std::vector<SoundFX*> AudioMixer::impactBonesSounds;
SoundFX* AudioMixer::impactBones01;
SoundFX* AudioMixer::impactBones02;

std::vector<SoundFX*> AudioMixer::playerDeathSounds;
SoundFX* AudioMixer::playerDeath01;
SoundFX* AudioMixer::playerDeath02;

SoundFX* AudioMixer::fireball;
SoundFX* AudioMixer::fbWallImpact;

std::vector<SoundFX*> AudioMixer::mineSounds;
SoundFX* AudioMixer::mineGems1;


AudioMixer::AudioMixer() {
	init();
}

void AudioMixer::init() {

	if (Mix_OpenAudio(FREQUENCY, MIX_DEFAULT_FORMAT, 2, CHUNK_SIZE) < 0) {
		std::cout << "Error: " << Mix_GetError() << std::endl;
	}

	//Music
	//Must free resources on game exit with Mix_FreeMusic()
	game_music = Mix_LoadMUS("Assets/Sound/game_music.ogg");
	menu_music = loadMusic("Assets/Sound/jata.flac");

	//Sound FX
	//Must free resources on game exit with Mix_FreeChunk()
	sword01 = new SoundFX("Assets/Sound/SFX/Sword/sword-01.wav");
	sword02 = new SoundFX("Assets/Sound/SFX/Sword/sword-02.wav");
	sword03 = new SoundFX("Assets/Sound/SFX/Sword/sword-03.wav");
	sword04 = new SoundFX("Assets/Sound/SFX/Sword/sword-04.wav");
	swordSounds.push_back(sword01);
	swordSounds.push_back(sword02);
	swordSounds.push_back(sword03);
	swordSounds.push_back(sword04);

	whoosh01 = new SoundFX("Assets/Sound/SFX/Sword/whoosh-01.wav");
	Mix_VolumeChunk(whoosh01->sfx, MIX_MAX_VOLUME);
	whoosh02 = new SoundFX("Assets/Sound/SFX/Sword/whoosh-02.wav");
	Mix_VolumeChunk(whoosh02->sfx, MIX_MAX_VOLUME);
	whooshSounds.push_back(whoosh01);
	whooshSounds.push_back(whoosh02);

	swordPlayerImpact01 = new SoundFX("Assets/Sound/SFX/Player_Impact/swordImpactPlayer-01.wav");
	swordPlayerImpact02 = new SoundFX("Assets/Sound/SFX/Player_Impact/swordImpactPlayer-02.wav");
	swordPlayerImpact03 = new SoundFX("Assets/Sound/SFX/Player_Impact/swordImpactPlayer-03.wav");
	swordPlayerImpact04 = new SoundFX("Assets/Sound/SFX/Player_Impact/swordImpactPlayer-04.wav");
	swordPlayerImpactSounds.push_back(swordPlayerImpact01);
	swordPlayerImpactSounds.push_back(swordPlayerImpact02);
	swordPlayerImpactSounds.push_back(swordPlayerImpact03);
	swordPlayerImpactSounds.push_back(swordPlayerImpact04);

	fbPlayerImpact01 = new SoundFX("Assets/Sound/SFX/Player_Impact/fireballImpact-01.wav");
	fbPlayerImpact02 = new SoundFX("Assets/Sound/SFX/Player_Impact/fireballImpact-02.wav");
	fbPlayerImpact03 = new SoundFX("Assets/Sound/SFX/Player_Impact/fireballImpact-03.wav");
	fbPlayerImpact04 = new SoundFX("Assets/Sound/SFX/Player_Impact/fireballImpact-04.wav");
	fireballPlayerImpactSounds.push_back(fbPlayerImpact01);
	fireballPlayerImpactSounds.push_back(fbPlayerImpact02);
	fireballPlayerImpactSounds.push_back(fbPlayerImpact03);
	fireballPlayerImpactSounds.push_back(fbPlayerImpact04);

	skeletonPlayerImpact01 = new SoundFX("Assets/Sound/SFX/Player_Impact/skeletonImpactPlayer-01.wav");
	skeletonPlayerImpact02 = new SoundFX("Assets/Sound/SFX/Player_Impact/skeletonImpactPlayer-02.wav");
	skeletonPlayerImpact03 = new SoundFX("Assets/Sound/SFX/Player_Impact/skeletonImpactPlayer-03.wav");
	skeletonPlayerImpact04 = new SoundFX("Assets/Sound/SFX/Player_Impact/skeletonImpactPlayer-04.wav");
	skeletonHitPlayerSounds.push_back(skeletonPlayerImpact01);
	skeletonHitPlayerSounds.push_back(skeletonPlayerImpact02);
	skeletonHitPlayerSounds.push_back(skeletonPlayerImpact03);
	skeletonHitPlayerSounds.push_back(skeletonPlayerImpact04);

	fireball = new SoundFX("Assets/Sound/SFX/Fireball/fireball-01.wav");
	fbWallImpact = new SoundFX("Assets/Sound/SFX/Fireball/fireballWallImpact.wav");
	Mix_VolumeChunk(fbWallImpact->sfx, MIX_MAX_VOLUME);
	
	fallingBones01 = new SoundFX("Assets/Sound/SFX/Skeleton/FallingBones-01.wav");
	Mix_VolumeChunk(fallingBones01->sfx, MIX_MAX_VOLUME);
	fallingBones02 = new SoundFX("Assets/Sound/SFX/Skeleton/FallingBones-02.wav");
	Mix_VolumeChunk(fallingBones02->sfx, MIX_MAX_VOLUME);
	skeletonDeathSounds.push_back(fallingBones01);
	skeletonDeathSounds.push_back(fallingBones02);

	impactBones01 = new SoundFX("Assets/Sound/SFX/Skeleton/BoneImpact-01.wav");
	impactBones02 = new SoundFX("Assets/Sound/SFX/Skeleton/BoneImpact-02.wav");
	impactBonesSounds.push_back(impactBones01);
	impactBonesSounds.push_back(impactBones02);

	playerDeath01 = new SoundFX("Assets/Sound/SFX/Player_Death/playerDeath-01.wav");
	Mix_VolumeChunk(playerDeath01->sfx, MIX_MAX_VOLUME);
	playerDeath02 = new SoundFX("Assets/Sound/SFX/Player_Death/playerDeath-02.wav");
	Mix_VolumeChunk(playerDeath02->sfx, MIX_MAX_VOLUME);
	playerDeathSounds.push_back(playerDeath01);
	playerDeathSounds.push_back(playerDeath02);

	mineGems1 = new SoundFX("Assets/Sound/SFX/Fountain/SpyroGems.flac");
	Mix_VolumeChunk(mineGems1->sfx, MIX_MAX_VOLUME / 6);
	mineSounds.push_back(mineGems1);
}

void AudioMixer::stopMusic() {

	Mix_HaltMusic();

}

void AudioMixer::playMusic(Mix_Music* music) {

	if (music == NULL) {
		std::cout << "Error: " << Mix_GetError() << std::endl;
	}

	//Play Music
	if (!Mix_PlayingMusic()) {
		std::cout << "Playing Music" << std::endl;
		//if (Mix_PlayMusic(music, -1) < 0) {
		if(!Mix_FadeInMusic(music, -1, 1000)){
			std::cout << "Error: " << Mix_GetError() << std::endl;
		}
	}
	else {
		stopMusic();

		//if (Mix_PlayMusic(music, -1) < 0) {
		if (!Mix_FadeInMusic(music, -1, 1000)) {
			std::cout << "Error: " << Mix_GetError() << std::endl;
		}

	}

}

Mix_Music* AudioMixer::loadMusic(const char* assetFileName) {

	std::cout << "Loading Music: " << assetFileName << std::endl;
	return Mix_LoadMUS(assetFileName);

}

SoundFX* AudioMixer::loadSFX(const char* assetFileName) {

	std::cout << "Loading SFX: " << assetFileName << std::endl;
	return new SoundFX(assetFileName);

}

//Plays a random sound from the list of sounds provided
void AudioMixer::playRandomSound(std::vector<SoundFX*> soundList) {

	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(0, soundList.size()-1);

	soundList.at(dist(rng))->play();

}
