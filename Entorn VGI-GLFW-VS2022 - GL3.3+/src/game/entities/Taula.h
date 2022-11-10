#pragma once
#include "../src/stdafx.h"
#include "../graphics/Transform.h"
#include "../graphics/Model.h"
#include  <bullet/btBulletDynamicsCommon.h>
#include "../physics/BulletWorld.h"
#include "GameEntity.h"


class Taula : public GameEntity
{
public:
	Taula(Transform transform, Model* model, GLuint shader_program_id);
	~Taula()
	{
		BulletWorld::WORLD->my_dynamics_world->removeRigidBody(my_rigid_body);
		delete my_rigid_body;
	}

	void interact();
private:
	btRigidBody* my_rigid_body;
};
