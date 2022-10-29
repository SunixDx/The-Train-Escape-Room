#pragma once

#include "entities/Vago.h"

class Level {
public:
	static void buildFirstLevel(GLuint sh_programID);
	Vago* my_vago;
	static Level CURRENT_LEVEL;
};