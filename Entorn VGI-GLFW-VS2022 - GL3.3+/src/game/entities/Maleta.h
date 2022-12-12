#pragma once
#include "../src/game/graphics/Model.h"
#include "../src/stdafx.h"
#include "../graphics/Transform.h"
#include "../graphics/Mesh.h"
#include  <bullet/btBulletDynamicsCommon.h>
#include "../physics/BulletWorld.h"
#include "InteractableEntity.h"
#include "GameEntity.h"
#include "../audio/AudioFunctions.h"


class Maleta : public GameEntity
{
public:
	Maleta(Transform transform, Model* model, GLuint shader_program_id, GameEntity* tapa);

	void interact();

	static float Z_OFFSET;

private:
	bool firstInteraction = true;

	btRigidBody* my_rigid_body;
	GameEntity* my_tapa;
	bool my_aixecada;
};

