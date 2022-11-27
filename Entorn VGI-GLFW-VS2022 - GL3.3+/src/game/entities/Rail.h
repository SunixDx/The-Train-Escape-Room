#pragma once
#include "GameEntity.h"
#include "../src/game/graphics/Model.h"
#include "../src/game/graphics/Transform.h"

class Rail: public GameEntity
{
public:

	Rail(Transform transform, Model* model, GLuint shader_program_id): GameEntity(transform, model, shader_program_id) {}

	void interact();
};

