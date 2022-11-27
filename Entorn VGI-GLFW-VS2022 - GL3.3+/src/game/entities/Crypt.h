#pragma once
#include "../src/game/graphics/Model.h"
#include "../src/stdafx.h"
#include "../graphics/Transform.h"
#include "../graphics/Mesh.h"
#include  <bullet/btBulletDynamicsCommon.h>
#include "../physics/BulletWorld.h"
#include "InteractableEntity.h"
#include "GameEntity.h"

class Crypt: public GameEntity
{
public:
	Crypt(Transform transform, Model* model, GLuint shader_id);

	void interact();

private:
	btRigidBody* my_rigid_body;

	Model* my_model_obert;
	Model* my_model_tancat;
};

