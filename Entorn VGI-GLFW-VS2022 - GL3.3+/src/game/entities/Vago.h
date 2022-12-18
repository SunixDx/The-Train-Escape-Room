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
		my_porta->my_transform.translate(my_translacio_obrir_porta);
		my_rigid_body_paret3->setCollisionFlags(my_rigid_body_paret3->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
	}

	void afegir_porta(GameEntity* porta, vec3 translacio_obrir)
	{
		addChild(porta);
		my_porta = porta;
		my_translacio_obrir_porta = translacio_obrir;
	}

	static float Z_OFFSET;

	btRigidBody* my_rigid_body_paret1;
	btRigidBody* my_rigid_body_paret2;
	btRigidBody* my_rigid_body_paret3;
	btRigidBody* my_rigid_body_paret4;

	GameEntity* my_porta = nullptr;
	vec3 my_translacio_obrir_porta = {0, 0, 0};
};
