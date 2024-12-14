#pragma once
#include "../src/game/graphics/Model.h"
#include "../src/stdafx.h"
#include "../graphics/Transform.h"
#include "../graphics/Mesh.h"
#include  <bullet/btBulletDynamicsCommon.h>
#include "../physics/BulletWorld.h"
#include "InteractableEntity.h"

class Maleta : public InteractableEntity
{
public:
	Maleta(Transform transform, Model* model, GLuint shader_program_id, GameEntity* tapa);

	void interact();

	static float Z_OFFSET;

private:

	btRigidBody* my_rigid_body;
	GameEntity* my_tapa;
	bool my_aixecada;
};

