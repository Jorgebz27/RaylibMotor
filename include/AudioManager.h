#pragma once
#include "raylib.h"

class AudioManager
{

public:

	static AudioManager* getInstance();
	void init();
	Music bgmusic;
	void LoadbgMusic(const char* filename);
	void PlaybgMusic();
	void Update();

private:

	static AudioManager* instance;
	AudioManager(const AudioManager&) = delete;
	AudioManager& operator=(const AudioManager&) = delete;
	
	AudioManager();
	~AudioManager();
};

