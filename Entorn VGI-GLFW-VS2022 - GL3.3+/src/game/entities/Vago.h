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

	void obrir_porta()
	{
		BulletWorld::WORLD->my_dynamics_world->removeRigidBody(my_rigid_body_porta);
		auto to_erease = std::find(my_rigidbodies.begin(), my_rigidbodies.end(), my_rigid_body_porta);
		if (to_erease != my_rigidbodies.end())
		{
			delete* to_erease;
			my_rigidbodies.erase(to_erease);
		}
		my_rigid_body_porta = nullptr;
		my_porta->my_transform.translate(my_translacio_obrir_porta);
	}

	void afegir_porta(GameEntity* porta, vec3 translacio_obrir)
	{
		addChild(porta);
		my_porta = porta;
		my_translacio_obrir_porta = translacio_obrir;
	}

	static float Z_OFFSET;

	btRigidBody* my_rigid_body_porta;
	std::vector<btRigidBody*> my_rigidbodies;

	GameEntity* my_porta = nullptr;
	vec3 my_translacio_obrir_porta = {0, 0, 0};
};
