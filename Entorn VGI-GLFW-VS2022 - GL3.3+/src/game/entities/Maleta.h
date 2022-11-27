#pragma once
#include "../src/game/graphics/Model.h"
#include "../src/stdafx.h"
#include "../graphics/Transform.h"
#include "../graphics/Mesh.h"
#include  <bullet/btBulletDynamicsCommon.h>
#include "../physics/BulletWorld.h"
#include "InteractableEntity.h"
#include "GameEntity.h"

class Maleta : public GameEntity
{
public:
	Maleta(Transform transform, Model* model, GLuint shader_program_id, GameEntity* tapa);

	void mostrar(glm::mat4 MatriuVista, glm::mat4 MatriuTG) {
		my_model->Draw(MatriuVista, MatriuTG, my_transform, my_shader_program_id);
	}

	void interact();

	static float Z_OFFSET;

private:

	Transform my_transform;
	Model* my_model;
	GLuint my_shader_program_id;
	btRigidBody* my_rigid_body;
	GameEntity* my_tapa;
	bool my_aixecada;
};

