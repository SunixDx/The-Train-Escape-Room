#pragma once
#include "../src/stdafx.h"
#include "../graphics/Transform.h"
#include "../graphics/Mesh.h"
#include "Taula.h"
#include "Seient.h"
#include "GameEntity.h"


class Vago : public GameEntity
{
public:
	Vago(Transform transform, Model* model, GLuint shader_id);

	static float Z_OFFSET;
};
