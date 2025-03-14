#include "AudioManager.h"

AudioManager* AudioManager::instance = nullptr;
AudioManager* AudioManager::getInstance()
{
	if (instance == nullptr)
	{
		instance = new AudioManager();
		instance->init();
	}
	return instance;
}

void AudioManager::init()
{	//inicialicar el sistema de audio
	InitAudioDevice();
}

void AudioManager::LoadBackgroundMusic(const char* filename)
{
	backgroundMusic = LoadMusicStream(filename);
}

void AudioManager::PlayBGM()
{
	PlayMusicStream(backgroundMusic);
}

void AudioManager::Update()
{
	UpdateMusicStream(backgroundMusic);
}

AudioManager::~AudioManager()
{
}

AudioManager::AudioManager()
{
}
