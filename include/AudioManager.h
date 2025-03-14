#pragma once
#include"raylib.h"

class AudioManager
{

public: 
	static AudioManager* getInstance();
	void init();

	Music backgroundMusic;
	void LoadBackgroundMusic(const char* filename);
	void PlayBGM();
	void Update();
private:
	AudioManager(const AudioManager&) = delete;
	AudioManager();
	~AudioManager();
	AudioManager& operator=(const AudioManager&) = delete;
	static AudioManager* instance;
};

