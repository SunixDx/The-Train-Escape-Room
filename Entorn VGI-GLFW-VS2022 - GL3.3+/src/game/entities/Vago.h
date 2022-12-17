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

	btRigidBody* my_rigid_body_paret1;
	btRigidBody* my_rigid_body_paret2;
	btRigidBody* my_rigid_body_paret3;
	btRigidBody* my_rigid_body_paret4;
};
