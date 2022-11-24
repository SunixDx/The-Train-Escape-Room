#pragma once
#include "../src/stdafx.h"
#include "../graphics/Transform.h"
#include "../graphics/Mesh.h"
#include "GameEntity.h"
#include <bullet/btBulletDynamicsCommon.h>

class Seient : public GameEntity
{
public:
	Seient(Transform transform, Model* model, GLuint shader_program_id);

	void interact();
	
	btRigidBody* my_rigid_body_banc;
	btRigidBody* my_rigid_body_respatller;
};
