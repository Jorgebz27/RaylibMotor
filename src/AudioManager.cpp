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
{
	InitAudioDevice();
}

void AudioManager::LoadbgMusic(const char* filename)
{
	bgmusic = LoadMusicStream(filename);
}

void AudioManager::PlaybgMusic()
{
	PlayMusicStream(bgmusic);
}

void AudioManager::Update()
{
	UpdateMusicStream(bgmusic);
}

AudioManager::AudioManager()
{
}

AudioManager::~AudioManager()
{
}
