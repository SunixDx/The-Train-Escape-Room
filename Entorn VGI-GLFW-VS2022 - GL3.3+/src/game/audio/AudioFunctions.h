#pragma once
#include <irrKlang/irrKlang.h>
#include <iostream>

#include "../graphics/Camera.h"

class Audio
{
public:
	Audio(): engine(nullptr) {
		engine = irrklang::createIrrKlangDevice();
		if (!engine) {
			std::cout << "ERROR CREATING SOUND ENGINE" << std::endl;
		}
	}
	~Audio() {
		engine->drop();
	}

	irrklang::ISound* play2D(const char* path, bool looped, bool startPaused);
	irrklang::ISound* play3D(const char* path, irrklang::vec3df position, bool looped, bool startPaused);

	void UpdateListenerConfig(vec3 direction);

	static Audio AUDIO_FUNCTIONS;
private:
	irrklang::ISoundEngine* engine;
};


