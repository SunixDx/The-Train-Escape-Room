#pragma once
#include "../src/game/graphics/Model.h"
#include "../src/stdafx.h"
#include "../graphics/Transform.h"
#include "../graphics/Mesh.h"
#include  <bullet/btBulletDynamicsCommon.h>
#include "../physics/BulletWorld.h"
#include "InteractableEntity.h"
#include "GameEntity.h"
#include "../src/game/graphics/Camera.h"

class Lever : public InteractableEntity
{
public:
	Lever(Transform transform, Model* model, GLuint shader_id);

	void interact();

private:
	btRigidBody* my_rigid_body;
	bool pulsada;
};
