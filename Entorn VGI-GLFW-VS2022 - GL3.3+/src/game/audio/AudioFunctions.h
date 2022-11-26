#include <irrKlang/irrKlang.h>
#include <iostream>

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

private:
	irrklang::ISoundEngine* engine;
};


