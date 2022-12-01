#include "AudioFunctions.h"

Audio Audio::AUDIO_FUNCTIONS;

irrklang::ISound* Audio::play2D(const char* path, bool looped, bool startPaused)
{
	return engine->play2D(path, looped, startPaused, true);
}

irrklang::ISound* Audio::play3D(const char* path, irrklang::vec3df position, bool looped, bool startPaused)
{
	return engine->play3D(path, position, looped, startPaused, true);
}

void Audio::UpdateListenerConfig(vec3 direction)
{
	// position of the listener
	irrklang::ik_f32 x = Camera::MAIN_CAMERA.position.x;
	irrklang::ik_f32 y = Camera::MAIN_CAMERA.position.y;
	irrklang::ik_f32 z = Camera::MAIN_CAMERA.position.z;
	irrklang::vec3df position(x, y, z);

	// the direction the listener looks into. El parametro direction se calcula en el main
	irrklang::vec3df lookDirection(direction.x, direction.y, direction.z);

	// only relevant for doppler effects
	irrklang::vec3df velPerSecond(0, 0, 0);
	
	// where 'up' is in your 3D scene
	irrklang::vec3df upVector(0, 1, 0);

	engine->setListenerPosition(position, lookDirection, velPerSecond, upVector);
}

