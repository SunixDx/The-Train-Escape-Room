#include "AudioFunctions.h"

irrklang::ISound* Audio::play2D(const char* path, bool looped, bool startPaused)
{
	return engine->play2D(path, looped, startPaused, true);
}

