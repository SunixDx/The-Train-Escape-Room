#pragma once
#include "../src/game/graphics/Model.h"
#include "../src/stdafx.h"
#include "../graphics/Transform.h"
#include "../graphics/Mesh.h"
#include  <bullet/btBulletDynamicsCommon.h>
#include "../physics/BulletWorld.h"
#include "InteractableEntity.h"

class Libro1: public InteractableEntity
{
public:
	Libro1(Transform transform, Model* model_tancat, Model* model_obert, GLuint shader_id);

	void interact();

private:
	btRigidBody* my_rigid_body;

	Model* my_model_obert;
	Model* my_model_tancat;

	bool abierto  = false;
};

