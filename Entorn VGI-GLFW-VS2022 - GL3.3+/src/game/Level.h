#pragma once

#include "entities/Vago.h"

class Level {
public:
	static void buildFirstLevel(GLuint sh_programID);
	Vago* my_vago;

	InteractableEntity* my_entity_under_cursor;

	static Level CURRENT_LEVEL;
};