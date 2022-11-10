#pragma once
#include "../src/stdafx.h"
#include "../graphics/Transform.h"
#include "../graphics/Mesh.h"
#include "InteractableEntity.h"
#include <bullet/btBulletDynamicsCommon.h>

class Seient : public InteractableEntity
{
public:
	Seient(Transform transform, Mesh* mesh, GLuint shader_program_id);

	void mostrar(glm::mat4 MatriuVista, glm::mat4 MatriuTG);

	void interact();


	Transform my_transform;
	Mesh* my_mesh;
	GLuint my_shader_program_id;
	
	btRigidBody* my_rigid_body_banc;
	btRigidBody* my_rigid_body_respatller;

	void mostrarBanc(glm::mat4 MatriuVista, glm::mat4 MatriuTG, GLuint shader_program_id);
	void mostrarRespatller(glm::mat4 MatriuVista, glm::mat4 MatriuTG, GLuint shader_program_id);
};
